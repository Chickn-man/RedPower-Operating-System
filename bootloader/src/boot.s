!cpu 65EL02

windowaddr=$FF00
screenrow=windowaddr
cursorx=windowaddr+$1
cursory=windowaddr+$2
cursor=windowaddr+$3
keybuff=windowaddr+$4
keypos=windowaddr+$5
keylast=windowaddr+$6
screenline=windowaddr+$10

diskbuff=windowaddr
disksector=windowaddr+$80
diskcommand=windowaddr+$82


*= $0 ; zero page
ver: !word $0 ; 16 bit kernel version id
arg0: !word $0 ; argument 0 for passing to functions
loadaddr: !word $0
sector: !word $0

*= $500 ; bootloader 
clc
xce
rep #$30 ; 16 bit registers

!al
lda #$1 ; screen id
mmu #0
lda #windowaddr
mmu #1 ; map window to windowaddr
mmu #2 ; enable redbus

sep #$30 ; 8 bit registers
!as

stz cursorx ; cursor x
stz cursory ; cursor y
stz cursor ; reset cursor
jsr clearscreen

rep #$30
!al
lda #1
sta sector
lda #$700
sta sector_store_addr
jsr readsector
sep #$30
!as

jsr hellorld

init:
    lda mbr_type_1
    cmp #$0e
    beq hasfs
    jmp nofs
hasfs:
    rep #$30
    !al
    lda mbr_lbas_1
    sta sector
    jsr readsector

    
hlt:
    jmp hlt

jmp $400

hellot: !text "Hellorld!", 0
errort: !text "error", 0
nofst: !text "no fat16 filesystem detected on disk, maybe wrong type in mbr (should be 0x0e)", 0
nokernelt: !text "/boot/kernel is missing or corrupt", 0

error:
    rep #$30 ; 16 bit mode
    !al
    lda #errort
    sta arg0
    !as
    sep #$30 ; 8 bit mode
    jsr print
    jmp hlt

nofs:
    rep #$30 ; 16 bit mode
    !al
    lda #nofst
    sta arg0
    !as
    sep #$30 ; 8 bit mode
    jsr print
    jmp hlt

nokernel:
    rep #$30 ; 16 bit mode
    !al
    lda #nokernelt
    sta arg0
    !as
    sep #$30 ; 8 bit mode
    jsr print
    jmp hlt

clearscreen:
    lda #1
    mmu #$00

    lda #' '
    LDX #49
clsss
    stx screenrow
    ldy #79
clsnl:
    sta screenline, Y
    dey
    bpl clsnl
    dex
    bpl clsss
clsret:
    rts

print:
    lda #1
    mmu #$00

    ldx cursorx
    ldy #0
printloop:
    lda (arg0), Y
    cmp #0
    beq printret
    sta screenline, X
    iny
    inx
    jmp printloop
printret:
    rts

readphysector:
    php
    sep #30
    !as
    !rs
    ldx #3
retry_read:
    cpx #0
    bne nodiskerr
    jmp error
nodiskerr:
    dex
    rep #$30
    !al
    lda #2
    mmu #0
    sep #$30
    !as
    lda #4
    sta diskcommand
    wai
    lda diskcommand
    cmp #$FF
    beq retry_read
    plp
    rts

readsector:
    php
    rep #$30
    !al
    !rl
    lda #2
    mmu #0
    ldx #0
    ldy #4
    lda #4
    sta 254
    lda sector
    mul 254
    sta disksector
rsloop:
    dey
    phx
    jsr readphysector
    rep #$30
    plx
    rhy
    ldy #0
    bra rscp
rscpr:
    rly
    cpy #0
    beq rsret
    inc disksector
    bra rsloop
rscp:
    lda diskbuff, y
    !byte $9d
sector_store_addr: !word sector_buffer
    inx
    inx
    iny
    iny
    cpy #128
    beq rscpr
    bra rscp
rsret:
    plp
    rts

*= $6be ; mbr entry 1
bootable_1: !byte $80 ; bootable
!byte $1 ; head
;     Sector| Cylinder
!word %0000100000000000
mbr_type_1: !byte $0e ; fat16 lba mapped
!byte $d ; head
;     Sector| Cylinder
!word %0011010000110000
mbr_lbas_1: !byte $40, $00, $00, $00 ; starts at $40
mbr_lbae_1: !byte $c0, $3f, $00, $00 ; size of $3fc0

*= $6fe
!word $aa55

*= $700 ; extended boot code
hellorld:
    rep #$30 ; 16 bit mode
    !al
    lda #hellot
    sta arg0
    !as
    sep #$30 ; 8 bit mode
    jsr print
    rts

*= $900 ; boot services memory

*= $1000 ; kernel

*= $2000 ; ram

*= $fd00 ; sector buffer
sector_buffer:

*= $ff00 ; redbus window