.intel_syntax noprefix
.text
.globl main

main:
  push rbp
  mov rbp, rsp

  mov dword ptr [rbp-4], 10
  mov dword ptr [rbp-8], 20
  mov eax, dword ptr [rbp-4]
  add eax, dword ptr [rbp-8]

  pop rbp
  ret

