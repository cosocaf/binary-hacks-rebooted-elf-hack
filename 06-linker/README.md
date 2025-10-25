# 静的リンクと動的リンク

`gcc`は既定で動的リンクを行います。

```sh
gcc -std=c23 -g main.c
```

`ldd`コマンドで動的リンクされているライブラリを見ることができます。

```sh
ldd a.out
```

出力例:

```txt
        linux-vdso.so.1 (0x0000726a7cb45000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x0000726a7c800000)
        /lib64/ld-linux-x86-64.so.2 (0x0000726a7cb47000)
```

---

`-static`オプションをつけると静的リンクになります。

```sh
gcc -std=c23 -static -g main.c
ldd a.out
# "not a dynamic executable"と出力されるはず
```

---

生成ファイルの大きさを比べてみます。

```sh
gcc -std=c23 -o dynamic.out main.c
gcc -std=c23 -static -o static.out main.c
ls -la .
```

ファイルサイズにかなり差が出るはずです。

---

`gdb`でスタートアップの流れを観察してみます。

```sh
gcc -std=c23 -g main.c
gdb -q ./a.out

set breakpoint pending on
break main # a.outの関数
break __libc_start_main # libcの関数
break _dl_start # ld-linuxの関数
run

bt
```

出力例:

```txt
#0  _dl_start (arg=0x7fffffffe700) at ./elf/rtld.c:519
#1  0x00007ffff7fe2708 in _start () from /lib64/ld-linux-x86-64.so.2
#2  0x0000000000000001 in ?? ()
#3  0x00007fffffffe9c6 in ?? ()
#4  0x0000000000000000 in ?? ()
```

`main.c`ではなく`ld-linux`の`rtld.c`で停止し、`ld-linux`としてのトレースが見えているはずです。

```sh
c
bt
```

出力例:

```txt
#0  __libc_start_main_impl (main=0x555555555149 <main>, argc=1, argv=0x7fffffffe708, init=0x0, fini=0x0,
    rtld_fini=0x7ffff7fc6160 <_dl_fini>, stack_end=0x7fffffffe6f8) at ../csu/libc-start.c:242
#1  0x0000555555555085 in _start ()
```

`main`の前に`libc`の`csu(C Start Up)`で停止し、`_start`のシンボルの位置が先ほどとは異なっているはずです。

```sh
c
bt
```

出力例:

```txt
#0  main () at main.c:4
```

ようやく`main()`に辿り着きました。

---

`gdb`で静的リンクの場合のスタートアップの流れを追います。

```sh
gcc -std=c23 -static -g main.c
gdb -q ./a.out

set breakpoint pending on
break main
break __libc_start_main
break _dl_start
run

bt
```

出力例:

```txt
#0  0x0000000000404200 in __libc_start_main_impl ()
#1  0x0000000000401765 in _start ()
```

動的リンクの場合とは異なり`_dl_start`は存在しないため、`__libc_start_main`で停止します。

```sh
c
bt
```

出力例:

```txt
#0  main () at main.c:4
```

`ld-linux`が呼ばれることなく`main()`に辿り着きました。

