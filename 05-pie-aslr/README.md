# PIEとASLR

まずは普通にgccでビルドしましょう。

```sh
gcc -std=c23 main.c
```

`readelf`でa.outをみてみます。

```sh
readelf -l a.out
```

出力例:

```txt
Elf file type is DYN (Position-Independent Executable file)
Entry point 0x1160
There are 14 program headers, starting at offset 64

...
```

`DYN (Position-Independent Executable file)`と出力されている通り、何もしなければ勝手にPIEとしてコンパイル・リンクされます。

`a.out`を実行するたびに`a.out`がマップされるアドレスが変わっているはずです。

```sh
./a.out
./a.out
./a.out
```

---

次に、`-no-pie`オプションをつけてビルドします。

```sh
gcc -std=c23 -no-pie main.c
```

`readelf`で`a.out`をみてみます。

出力例:

```txt
Elf file type is EXEC (Executable file)
Entry point 0x401150
There are 14 program headers, starting at offset 64

...
```

`DYN`から`EXEC (Executable file)`に変わりました。この状態で`a.out`を実行すると、マップされるアドレスが固定されます。

```sh
./a.out
./a.out
./a.out
```

ただし、`[heap]`以降は`ASLR`が担う部分であり、実行するたびに変わっているはずです。

---

`setarch`コマンドを使用すると`ASLR`を無効化した状態でプログラムを実行できます。

```sh
setarch -R ./a.out
```

何度実行しても`[heap]`以降のアドレスも固定化されていることがわかります。

