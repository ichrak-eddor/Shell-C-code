CC = gcc
# shellcode.c
shell:
	$(CC) shellcode.c -o shellcode 
	./shellcode 	

clear : 
	rm shellcode .codeshell(history)




