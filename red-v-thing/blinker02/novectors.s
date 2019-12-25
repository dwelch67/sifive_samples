
.globl _start
_start:
    lui x2,0x80004
    jal notmain
    j .

.globl dummy
dummy:
    ret

.globl PUT32
PUT32:
    sw x11,(x10)
    ret

.globl GET32
GET32:
    lw x10,(x10)
    ret
