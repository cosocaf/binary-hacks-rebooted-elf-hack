# ELFのセグメント

`main.c`をビルドします。

```sh
gcc -std=c23 main.c
```

プログラムヘッダは`readelf`の`-l`オプションで見ることができます。

```sh
readelf -l a.out
```

出力例:

```txt
Elf file type is DYN (Position-Independent Executable file)
Entry point 0x1060
There are 15 program headers, starting at offset 64

Program Headers:
  Type           Offset             VirtAddr           PhysAddr
                 FileSiz            MemSiz              Flags  Align
  PHDR           0x0000000000000040 0x0000000000000040 0x0000000000000040
                 0x0000000000000348 0x0000000000000348  R      0x8
  INTERP         0x00000000000003dc 0x00000000000003dc 0x00000000000003dc
                 0x000000000000001c 0x000000000000001c  R      0x1
      [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]
  LOAD           0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000670 0x0000000000000670  R      0x1000
  LOAD           0x0000000000001000 0x0000000000001000 0x0000000000001000
                 0x0000000000000175 0x0000000000000175  R E    0x1000
  LOAD           0x0000000000002000 0x0000000000002000 0x0000000000002000
                 0x000000000000018c 0x000000000000018c  R      0x1000
  LOAD           0x0000000000002db0 0x0000000000003db0 0x0000000000003db0
                 0x0000000000000264 0x0000000000000268  RW     0x1000
  DYNAMIC        0x0000000000002dc8 0x0000000000003dc8 0x0000000000003dc8
                 0x00000000000001f0 0x00000000000001f0  RW     0x8
  NOTE           0x0000000000000388 0x0000000000000388 0x0000000000000388
                 0x0000000000000030 0x0000000000000030  R      0x8
  NOTE           0x00000000000003b8 0x00000000000003b8 0x00000000000003b8
                 0x0000000000000024 0x0000000000000024  R      0x4
  NOTE           0x00000000000020fc 0x00000000000020fc 0x00000000000020fc
                 0x0000000000000090 0x0000000000000090  R      0x4
  TLS            0x0000000000002db0 0x0000000000003db0 0x0000000000003db0
                 0x0000000000000008 0x0000000000000008  R      0x4
  GNU_PROPERTY   0x0000000000000388 0x0000000000000388 0x0000000000000388
                 0x0000000000000030 0x0000000000000030  R      0x8
  GNU_EH_FRAME   0x0000000000002018 0x0000000000002018 0x0000000000002018
                 0x0000000000000034 0x0000000000000034  R      0x4
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RW     0x10
  GNU_RELRO      0x0000000000002db0 0x0000000000003db0 0x0000000000003db0
                 0x0000000000000250 0x0000000000000250  R      0x1

 Section to Segment mapping:
  Segment Sections...
   00
   01     .interp
   02     .note.gnu.property .note.gnu.build-id .interp .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt
   03     .init .plt .plt.got .plt.sec .text .fini
   04     .rodata .eh_frame_hdr .eh_frame .note.ABI-tag .note.package
   05     .tdata .init_array .fini_array .dynamic .got .data .bss
   06     .dynamic
   07     .note.gnu.property
   08     .note.gnu.build-id
   09     .note.ABI-tag .note.package
   10     .tdata
   11     .note.gnu.property
   12     .eh_frame_hdr
   13
   14     .tdata .init_array .fini_array .dynamic .got
```

---

`readelf`の`-j`オプションを使うと、セグメントの中身を見ることができます。

```sh
readelf -j .rodata a.out
```

出力例:

```txt
Hex dump of section '.rodata':
  0x00002000 01000200 bbbb0000 68656c6c 6f2c2077 ........hello, w
  0x00002010 6f726c64 210a00                     orld!..
```

---

`main.c`の`global_var`は`.data`に、`const_global_var`は`.rodata`に、`thread_local_var`と`const_thread_local_var`は`.tdata`に配置されています。

