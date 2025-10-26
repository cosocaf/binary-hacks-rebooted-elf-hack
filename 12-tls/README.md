# Thread Local Storage

説明は本の#10と同じなので省略します。

以下コピペ用

```sh
gcc -std=c23 -o libhoge.so -shared -fPIC hoge.c
gcc -std=c23 -o main main.c ./libhoge.so
```

Local Executable:

```sh
objdump -d main --disassemble=local_executable_access -M intel --no-show-raw-insn
readelf -r main
```

Initial Executable:

```sh
objdump -d main --disassemble=initial_executable_access -M intel --no-show-raw-insn
readelf -r main
```

General Dynamic:

```sh
objdump -d libhoge.so --disassemble=general_dynamic_access -M intel --no-show-raw-insn
readelf -r libhoge.so
```

Local Dynamic:

```sh
objdump -d libhoge.so --disassemble=local_dynamic_access -M intel --no-show-raw-insn
readelf -r libhoge.so
```

