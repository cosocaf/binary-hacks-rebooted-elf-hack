.intel_syntax noprefix

.section .data
msg:
  .ascii "Hello, World!\n"
len = . - msg

.section .text
.globl _start
_start:
  lea rsi, msg[rip]
  mov rdx, len
  mov rdi, 1  # 1: stdout
  mov rax, 1  # 1: sys_write
  syscall
  mov rdi, 0  # 0: exit code 0
  mov rax, 60 # 60: sys_exit
  syscall

