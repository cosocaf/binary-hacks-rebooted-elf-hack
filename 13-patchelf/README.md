# patchelfでELFバイナリのフィールドを書き換える

説明は本の#16と同じなので省略します。

以下コピペ用

```sh
gcc -nostdlib -static hello.s -o hello
./hello
```

---

`ls`の`PT_INTERP`を書き換える:

```sh
cp $(which ls) .
./ls

patchelf --set-interpreter ./hello ./ls
./ls
```

