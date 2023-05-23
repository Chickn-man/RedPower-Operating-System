[org 0x7d80]
mov ah, 0x0e
mov bh, 0
mov al, 'n'
int 0x10
mov al, 'o'
int 0x10
mov al, 't'
int 0x10
mov al, ' '
int 0x10
mov al, 'b'
int 0x10
mov al, 'o'
int 0x10
mov al, 'o'
int 0x10
mov al, 't'
int 0x10
mov al, 'a'
int 0x10
mov al, 'b'
int 0x10
mov al, 'l'
int 0x10
mov al, 'e'
int 0x10
hlt:
    hlt
    jmp hlt