# 10-dlfcn

説明は本の#7と同じなので省略します。

以下コピペ用

```sh
gcc -fPIC libhello.c -o libhello.so -shared
gcc dlopen-sample.c -o dlopen-sample.out

# Hello from libhello
./dlopen-sample.out
```

実行ファイルは再コンパイルせずに、共有ライブラリの方を書き換えるだけで挙動が変わることが確認できます。

```sh
sed -i "s/from libhello/Binary Hacks!/" ./libhello.c
gcc -fPIC libhello.c -o libhello.so -shared

# Hello Binary Hacks!
./dlopen-sample.out
```

---

```sh
gcc malloc-hook.c -shared -fPIC -o malloc-hook.so
LD_PRELOAD=./malloc-hook.so uname
```

malloc が呼ばれるたびに、確保されるメモリのサイズが標準エラー出力に出力されることが確認できます。

