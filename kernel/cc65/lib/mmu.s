; MMU opcode wrappers for cc65

.export _setMappedRedbusDev, _getMappedRedbusDev, _setRedbusWindowOffset, _getRedbusWindowOffset
.export _enableRedbus, _disableRedbus, _setMemoryMappedWindow, _getMemoryMappedWindow
.export _setBrkAddress, _getBrkAddress, _setPorAddress, _getPorAddress, _logRegisterA

.segment "CODE"

.smart

.proc _setMappedRedbusDev: near
    php
    sep #$30
	.byte $EF
	.byte $00
    plp
	rts
.endproc

.proc _getMappedRedbusDev: near
	.byte $EF
	.byte $80
	rts
.endproc

.proc _setRedbusWindowOffset: near
    php
    sep #$30
    xba
    txa
    xba
	.byte $EF
	.byte $01
    plp
    rts
.endproc

.proc _getRedbusWindowOffset: near
    php
    sep #$30
	.byte $EF
	.byte $81
    xba
    tax
    xba
    plp
    rts
.endproc

.proc _enableRedbus: near
	.byte $EF
	.byte $02
	rts
.endproc

.proc _disableRedbus: near
	.byte $EF
	.byte $82
	rts
.endproc

.proc _setMemoryMappedWindow: near
    php
    sep #$30
    xba
    txa
    xba
	.byte $EF
	.byte $03
    plp
    rts
.endproc

.proc _getMemoryMappedWindow: near
    php
    sep #$30
	.byte $EF
	.byte $83
    xba
    tax
    xba
    plp
    rts
.endproc

.proc _setBrkAddress: near
    php
    sep #$30
    xba
    txa
    xba
	.byte $EF
	.byte $05
    plp
    rts
.endproc

.proc _getBrkAddress: near
    php
    sep #$30
	.byte $EF
	.byte $85
    xba
    tax
    xba
    plp
    rts
.endproc

.proc _setPorAddress: near
	.byte $EF
	.byte $06
    rts
.endproc

.proc _getPorAddress: near
	.byte $EF
	.byte $86
    rts
.endproc

.proc _logRegisterA: near
	.byte $EF
	.byte $FF
    rts
.endproc
