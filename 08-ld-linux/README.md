# ld-linux

説明は本の#5と同じなので省略します。

以下コピペ用

`LD_PRELOAD`:

```sh
gcc -std=c23 -o libhoge.so -shared -fPIC hoge.c
gcc -std=c23 -o libfuga.so -shared -fPIC fuga.c
gcc -std=c23 -o main main.c libhoge.so

# hoge
LD_LIBRARY_PATH=. ./main

# fuga
LD_PRELOAD=./libfuga.so LD_LIBRARY_PATH=. ./main
```

`LD_DEBUG`:

```sh
# libhoge.so
LD_DEBUG=symbols LD_LIBRARY_PATH=. ./main

# libfuga.so
LD_PRELOAD=./libfuga.so LD_DEBUG=symbols LD_LIBRARY_PATH=. ./main
```

`LD_AUDIT`:

```sh
gcc -o libaudit.so -shared -fPIC audit.c
LD_AUDIT=libaudit.so LD_LIBRARY_PATH=. ./main
```

