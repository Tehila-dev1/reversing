
include 'win32a.inc'

format PE console
entry start

section '.data' data readable writeable
     filename  db  "input.txt",0
	 byteaRead dd  ?
	 file_buffer db 11 dup(0)
	 fileNumber dd ?
	 int_format db "%d",0
	 
	 newline  db 13, 10 ,0
	 
	 datasize dd 4
	 regnum   dd ?
	 regkey   db  "input",0
	 regdir   db "Software\\assembly",0
	 
	 
section '.text' code readable executable
start:
	 
	 ;file
	 push   0
	 push   0x80
	 push   3
	 push   0
	 push   0
	 push   0x80000000
	 push   filename
	 call   [CreateFileA]
	 
	 push   0
	 push   byteaRead
	 push   10
	 push   file_buffer
	 push   eax
	 call   [ReadFile]
	 
	 push   fileNumber
	 push   int_format
	 push   file_buffer
	 call   [sscanf_s]
	 add    esp,12
	 
	 mov    eax, [fileNumber]
	 call   print_eax
	 
	 
	 mov    esi,newline
	 call   print_str
	 mov    eax, [fileNumber]
	 call   convert
     call   print_eax
	 
	 mov    esi,newline
	 call   print_str
	 ;registry
	 
	 push  datasize 
	 push  regnum
	 push  0
	 push  0x18
	 push  regkey
	 push  regdir
	 push  0x80000001	 
	 call  [RegGetValueA]
	 
	 mov    eax, [regnum]
	 call   print_eax
	 mov    esi,newline
	 call   print_str
	 mov    eax, [regnum]
	 call   convert
     call   print_eax
	 
	 push	0 
	 call	[ExitProcess]

convert:
    xor  ebx,ebx 
	mov  bx,ax
	shr  eax ,16 ;ah-1 ,al-2, bh-3, bl-4
	xor ah, bl
	xor bl,ah
	xor ah,bl
	xor al,bh
	xor bh,al
	xor al,bh
	shl eax,16
	mov ax,bx
	; b^a
    ret

include 'training.inc'

