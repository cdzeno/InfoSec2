# Write an assembly program which reads as input two positive integer numbers and  
# print the difference between the first and the second one                        
# (you can assume that the difference will never be negative)                      
                                                                                   
.text                                                                              
.global _start                                                                     
                                                                                   
                                                                                   
_start:                                                                            
        movl $0x4,  %eax                                                           
        movl $0x1,  %ebx                                                           
        movl $msg1, %ecx                                                           
        movl $len1, %edx                                                           
        int  $0x80                                                                 
        # sys_write                                                                
                                                                                   
        movl $0x3,  %eax
        movl $0x0,  %ebx
        movl $var1, %ecx
        movl $0x3,  %edx
        int $0x80
        # sys_read

        movl var1, %eax
        andl $0x00909, %eax
        shrl $0x10, %eax

        movl $0x0, %ebx
        movl $0x0, %edx
        
        movl $10, %ecx
        movb $al, $dl
        imul %ecx, %edx, %ebx

        mov %ah, %dl
        add %edx, $ebx

        movl $0x1, %eax
        int $0x80
        # sys_exit
                                                                                   
.data                                                                              
                                                                                   
msg1: .ascii "Inserisci il primo numero: "                                         
len1 = .-msg1                                                                      
msg2: .ascii "Inserisci il secondo numero: "                                       
len2 = .-msg2                                                                      
                                                                                   
var1: .long 0                                                                      
var2: .long 0
