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
arg1: !word $0 ; argument 1 for passing to functions
arg2: !word $0 ; argument 2 for passing to functions      
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

lda mbr_type_1
cmp #$01
beq hasfs
jmp nofs

hasfs:
rep #$30
!al
lda mbr_lbas_1
sta sector
lda #sector_buffer
sta sector_store_addr
jsr readsector

jsr load_kernel
jmp error

hlt:
    jmp hlt

jmp $400

hellot: !text "Hellorld!", 0
errort: !text "error", 0
nofst: !text "no fat12 filesystem detected on disk, maybe wrong type in mbr (should be 0x01)", 0

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
    ldx #49
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
!byte $0 ; head
;     Sector| Cylinder
!word %0000100000000000
mbr_type_1: !byte $01 ; fat12
!byte $8 ; head
;     Sector| Cylinder
!word %0001110000000000
mbr_lbas_1: !32 $00000002 ; starts at $2
mbr_lbae_1: !32 $000001fe ; size of 510

*= $6fe
!word $aa55

*= $700 ; extended boot code
load_kernel:
    rep #$30
    !al
    lda #hellot
    sta arg0
    sep #$30
    !as 
    jsr print

    ; compare fs type
    rep #$30
    !al
    lda #FS_TYPE
    sta arg0
    lda #fatt
    sta arg1
    lda #8
    sta arg2
    sep #$30
    !as
    !rs
    jsr memcmp
    cpx #0
    beq fat12

    rep #$30
    !al
    lda #notf12t
    sta arg0
    sep #$30
    !as 
    jsr print

    jmp hlt

fat12:
    ; copy serial number
    rep #$30
    !al
    lda #FS_SERIAL
    sta arg0
    lda #fat_serial
    sta arg1
    lda #4
    sta arg2
    sep #$30
    !as
    jsr memcopy

    ; copy fs lable
    rep #$30
    !al
    lda #FS_LABLE
    sta arg0
    lda #fat_lable
    sta arg1
    lda #11
    sta arg2
    sep #$30
    !as
    jsr memcopy

    lda FS_SPC
    sta fat_spc
    lda FS_COPIES
    sta fat_copies
    rep #$30
    !al
    lda FS_RSRVD
    sta fat_rsrvd
    lda FS_ROOT
    sta fat_root
    lda FS_SPF
    sta fat_spf

    jmp hlt

memcopy:
    php 
    sep #$30
    !as
    !rs
    ldy #0
mcploop:
    lda (arg0), Y
    sta (arg1), Y
    iny 
    cpy arg2
    bne mcploop
    plp 
    rts

memcmp:
    php 
    sep #$30
    !as
    !rs
    ldy #0
mcmploop:
    lda (arg0), Y
    cmp (arg1), Y
    bne mcmpne
    iny 
    cpy arg2
    bne mcmploop
    ldx #0
    plp 
    rts  
mcmpne:
    ldx #1
    plp 
    rts 

fatt: !text "FAT12   "
notf12t: !text "File system is not fat12", 0
notrposfst: !text "File system is not RPOS boot partition (wrong lable)", 0
nobootfldrt: !text "/boot/ not found", 0
nokernelt: !text "/boot/kernel is missing or corrupt", 0

*= $900 ; boot services memory
fat_serial:!32 $00000000
fat_lable: !text "           "
fat_spc:   !byte $00
fat_rsrvd: !word $0000
fat_copies:!byte $00
fat_root:  !word $0000
fat_spf:   !word $0000

*= $1000 ; kernel

*= $2000 ; ram

*= $f900
file_allocation_table:

*= $fd00 ; sector buffer
sector_buffer:
FS_SPC=sector_buffer+$d
FS_RSRVD=sector_buffer+$e
FS_COPIES=sector_buffer+$10
FS_ROOT=sector_buffer+$11
FS_SPF=sector_buffer+$16
FS_SERIAL=sector_buffer+$27 
FS_LABLE=sector_buffer+$2b
FS_TYPE=sector_buffer+$36

*= $ff00 ; redbus window