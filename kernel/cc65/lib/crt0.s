; ---------------------------------------------------------------------------
; crt0.s
; ---------------------------------------------------------------------------
;
; Startup code for cc65 (Redpower2 RPC8 version)

.export   _init, _exit
.import   _main

.export   __STARTUP__ : absolute = 1        ; Mark as startup
.import   __RAM_START__, __RAM_SIZE__       ; Linker generated

.import    copydata, zerobss, initlib, donelib

.include  "zeropage.inc"

; ---------------------------------------------------------------------------
; Place the startup code in a special segment

.segment  "STARTUP"

; ---------------------------------------------------------------------------
; magic number

.byte $fe, "RPOS"

; ---------------------------------------------------------------------------
; housekeeping

_init:   
    pha ; work around for the 65EL02 stack pointer bug 
    ldx #$FF ; Initialize stack pointer to $01FF
    txs
    cld ; Clear decimal mode

; ---------------------------------------------------------------------------
; Set cc65 argument stack pointer

    lda #<(__RAM_START__ + __RAM_SIZE__)
    sta sp
    lda #>(__RAM_START__ + __RAM_SIZE__)
    sta sp+1

; ---------------------------------------------------------------------------
; Initialize memory storage

    jsr zerobss              ; Clear BSS segment
    jsr copydata             ; Initialize DATA segment
    jsr initlib              ; Run constructors

; ---------------------------------------------------------------------------
; Call main()
    
    jsr _main

; ---------------------------------------------------------------------------
; Back from main (this is also the _exit entry):

_exit:    
    jsr donelib ; Run destructors
    exitloop:
        wai
        jmp exitloop