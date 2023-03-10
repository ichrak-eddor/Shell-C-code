# Readme

To run this shell you need to download the zip file and extract it using this command 

```bash

unzip  filename.zip

```

Enter the folder codeshell and compile all *.c files using GNU Compiler Collection (GCC) and run under Linux environments like Ubuntu 

**GCC command compiler** 

```bash
gcc -o batchcode batchcode.c
```

```bash
gcc -o shellcode shellcode.c
```

**Run the shell **in interactive mode:**

```bash
./shellcode
```

this is how it looks like

![image](https://user-images.githubusercontent.com/60358423/213917555-da017b46-648d-4c68-b169-38feb6b43336.png)


**to execute on batch mode** 

give access permission 

```bash
chmod u+x filename
```

Or run the shell in batch mode

with bat as a commands file

```bash
./bat
```

### *Makefile:*

You can compile and run the ***shellcode shell*** with the Makefile using the command below.  **This only works for the interactive mode.**

`~/codeshell% make shellcode`

After you finish testing the shellcode shell, you can clean up the unnecessary files in the folder with the following command:

`~/codeshell% make clear `
rm shellcode .codeshell






