# アドレス空間

`main.c`をビルドします。

```sh
gcc -std=c23 main.c
```

---

`.data`セクションの中身を見てみます。

```sh
objdump -s -j .data a.out
```

```txt
a.out:     file format elf64-x86-64

Contents of section .data:
 4000 00000000 00000000 08400000 00000000  .........@......
 4010 55550000                             UU..
```

`main.c`の`int data_section = 0x5555;`で作成されたデータが入っていることがわかります。

---

`.bss`セクションの中身を見てみます。

```sh
objdump -s -j .bss a.out
```

```txt
a.out:     file format elf64-x86-64

Contents of section .bss:
 4014 00000000 00000000 00000000           ............
```

データは0埋めされています。

---

`.rodata`セクションの中身を見てみます。

```sh
objdump -s -j .rodata a.out
```

```txt
a.out:     file format elf64-x86-64

Contents of section .rodata:
 2000 01000200 aaaa0000 68656c6c 6f2c2077  ........hello, w
 2010 6f726c64 2100                        orld!.
```

`main.c`の`const int rodata_section = 0xaaaa;`で作成されたデータと、
main関数の中の文字列リテラル`"hello, world!"`が入っていることがわかります。

---

`a.out`をディスアセンブルしてみます。

```sh
objdump -M intel -d a.out
```

```txt
0000000000001149 <main>:
    1149:       f3 0f 1e fa             endbr64
    114d:       55                      push   rbp
    114e:       48 89 e5                mov    rbp,rsp
    1151:       48 83 ec 20             sub    rsp,0x20
    1155:       64 48 8b 04 25 28 00    mov    rax,QWORD PTR fs:0x28
    115c:       00 00
    115e:       48 89 45 f8             mov    QWORD PTR [rbp-0x8],rax
    1162:       31 c0                   xor    eax,eax
    1164:       48 8d 05 9d 0e 00 00    lea    rax,[rip+0xe9d]        # 2008 <rodata_section+0x4>
    116b:       48 89 45 e8             mov    QWORD PTR [rbp-0x18],rax
    116f:       c7 45 f3 61 62 63 64    mov    DWORD PTR [rbp-0xd],0x64636261
    1176:       c6 45 f7 65             mov    BYTE PTR [rbp-0x9],0x65
    117a:       b8 00 00 00 00          mov    eax,0x0
    117f:       48 8b 55 f8             mov    rdx,QWORD PTR [rbp-0x8]
    1183:       64 48 2b 14 25 28 00    sub    rdx,QWORD PTR fs:0x28
    118a:       00 00
    118c:       74 05                   je     1193 <main+0x4a>
    118e:       e8 bd fe ff ff          call   1050 <__stack_chk_fail@plt>
    1193:       c9                      leave
    1194:       c3                      ret
```

わかりにくいですが、`mov dword ptr [rbp-0xd], 0x64636261`は`"abcd"`を、`mov byte ptr [rbp-0x9], 0x65`は`"e"`を代入しています。
(ASCIIコードにおいて`a`は`0x61`です。)

同じ`const char[]`でも、文字列リテラルは`.rodata`セクションに作成され、文字配列はスタックに直接構築されます。

