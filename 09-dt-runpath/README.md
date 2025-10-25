# 共有ライブラリを検索するディレクトリ

説明は本の#6と同じなので省略します。

以下コピペ用

```sh
gcc -o libfoo.so -shared -fPIC foo.c
gcc -o main main.c libfoo.so

# foofoo
LD_LIBRARY_PATH=. ./main
```

```sh
readelf --dynamic main | grep NEEDED
# 0x0000000000000001 (NEEDED) Shared library: [libfoo.so]
# 0x0000000000000001 (NEEDED) Shared library: [libc.so.6]
```

セキュリティ実行モード:

```sh
cp ./main ./main_suid
sudo chown root:root ./main_suid
sudo chmod u+s ./main_suid
LD_LIBRARY_PATH=. ./main_suid
# ./main_suid: error while loading shared libraries: libfoo.so: cannot open shared object file: No such file or directory
```

`DT_RUNPATH`:

```sh
gcc -o main_runpath_app/lib/libfoo.so -shared -fPIC foo.c
gcc -o main_runpath_app/bin/main_runpath main.c main_runpath_app/lib/libfoo.so -Wl,-rpath='$ORIGIN/../lib'
```

`readelf -d`で`DT_RUNPATH`が指定されていることがわかります。

```sh
readelf -d ./main_runpath_app/bin/main_runpath | grep RUNPATH
```

