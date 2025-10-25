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

`main.c`の`global_var`は`.data`に、`const_global_var`は`.rodata`に、`thread_local_var`と`const_thread_local_var`は`.tdata`に配置されています。

---

`readelf`の`-d`オプションを使うと、`PT_DYNAMIC`なセグメントの中身を見ることができます。

```sh
readelf -d a.out
```

出力例:

```txt
Dynamic section at offset 0x2dc8 contains 27 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
 0x000000000000000c (INIT)               0x1000
 0x000000000000000d (FINI)               0x1168
 0x0000000000000019 (INIT_ARRAY)         0x3db8
 0x000000000000001b (INIT_ARRAYSZ)       8 (bytes)
 0x000000000000001a (FINI_ARRAY)         0x3dc0
 0x000000000000001c (FINI_ARRAYSZ)       8 (bytes)
 0x000000006ffffef5 (GNU_HASH)           0x3f8
 0x0000000000000005 (STRTAB)             0x4c8
 0x0000000000000006 (SYMTAB)             0x420
 0x000000000000000a (STRSZ)              141 (bytes)
 0x000000000000000b (SYMENT)             24 (bytes)
 0x0000000000000015 (DEBUG)              0x0
 0x0000000000000003 (PLTGOT)             0x3fb8
 0x0000000000000002 (PLTRELSZ)           24 (bytes)
 0x0000000000000014 (PLTREL)             RELA
 0x0000000000000017 (JMPREL)             0x658
 0x0000000000000007 (RELA)               0x598
 0x0000000000000008 (RELASZ)             192 (bytes)
 0x0000000000000009 (RELAENT)            24 (bytes)
 0x000000000000001e (FLAGS)              BIND_NOW
 0x000000006ffffffb (FLAGS_1)            Flags: NOW PIE
 0x000000006ffffffe (VERNEED)            0x568
 0x000000006fffffff (VERNEEDNUM)         1
 0x000000006ffffff0 (VERSYM)             0x556
 0x000000006ffffff9 (RELACOUNT)          3
 0x0000000000000000 (NULL)               0x0
```

| タグ | 意味 | 説明 |
|------|------|------|
| (INIT) | 初期化関数のアドレス | このアドレスにあるコード(通常`.init`セクションの`_init`関数)は動的リンカがプログラムをロードした後、`main`を呼び出す前に呼び出される。 |
| (FINI) | 終了処理関数のアドレス | このアドレスにあるコード(通常`.fini`セクションの`_fini`関数)はmainが終了した後に呼び出される。 |
| (INIT_ARRAY) | 初期化関数ポインタ配列のアドレス | `__attribute__((constructor))`が付与された関数やC++のグローバル変数のコンストラクタなどのポインタが格納されている配列。`(INIT)`の後に呼び出される。 |
| (INIT_ARRAYSZ) | (INIT_ARRAY)の要素数 | |
| (FINI_ARRAY) | 終了処理関数ポインタ配列のアドレス | `__attribute__((destructor))`が付与された関数やC++のグローバル変数のデストラクタなどのポインタが格納されている配列。`(FINI)`の前に呼び出される。 |
| (FINI_ARRAYSZ) | (FINI_ARRAY)の要素数 | |
| (GNU_HASH) | シンボル検索用のハッシュテーブルのアドレス | プログラムが動的リンクライブラリの関数を呼び出す場合、その本体を特定する必要がある。高速なルックアップのためにハッシュテーブルを使用する。 |
| (STRTAB) | 動的文字列テーブル(`.dynstr`セクション)のアドレス | シンボル名や動的リンクライブラリ名などの文字列が格納されている。他のエントリが文字列を使うときはこのテーブルのオフセットで指定する。 |
| (STRSZ) | (STRTAB)の大きさ | |
| (SYMTAB) | 動的シンボルテーブル(`.dynsym`セクション)のアドレス | このプログラムがインポートあるいはエクスポートするシンボルのリスト。 |
| (SYMENT) | (SYMTAB)のエントリあたりのサイズ | 64bit環境では`sizeof(Elf64_Sym)`は24バイト |
| (PLTGOT) | PLTまたはGOTのアドレス | PLT は、外部の関数を呼び出すための間接ジャンプを行うスタブコードの集まり。GOT は、外部のグローバル変数のアドレスを保持するためのテーブル。詳細は後ほど |
| (RELA) | データのリロケーションテーブル(`.rela.dyn`セクション)のアドレス | GOTで扱う。グローバル変数などの再配置情報を含む |
| (JMPREL) | 関数のリロケーションテーブル(`.rela.plt`セクション)のアドレス | PLTで扱う。関数などの再配置情報を含む |
| (RELACOUNT) | (RELA)の内、相対リロケーションの数 | PIEを有効にする場合、実行ファイル(`a.out`)のベースアドレスが変動するので、実行ファイル内部の絶対アドレス参照も再配置が必要。 |
| (VERNEED) | プログラムが依存するライブラリのバージョン情報テーブルのアドレス | 互換性のないライブラリで実行しようとした時にエラーにできるようにする。 |
| (VERNEEDNUM) | (VERNEED)のエントリ数 | |
| (VERSYM) | シンボルバージョン定義テーブルのアドレス | (SYMTAB)の各シンボルがどのバージョンに属するかを示す。(VERNEED)と組み合わせてシンボル単位でバージョンチェックを行う |
| (FLAGS) | リンカの動作を設定するフラグ | `BIND_NOW`はプログラム開始時に全てのリロケーションを行う。 |
| (FLAGS_1) | 追加のフラグ | `NOW`は(FLAGS)の`BIND_NOW`と等価。`PIE`は実行ファイルがPIEであることを示す。 |
| (DEBUG) | デバッグ情報 | 最近はあまり使われないらしい。 |
| (NULL) | `.dynamic`セクションの終端マーカー | |

