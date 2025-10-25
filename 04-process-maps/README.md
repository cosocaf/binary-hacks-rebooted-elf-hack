# プロセスのマップ

`/proc/self/maps`を読むと、現在のプロセスのアドレス空間に何がマップされているかがわかります。

`main.c`に`/proc/self/maps`を読んで出力するだけのプログラムが書かれているので実行してみましょう。

```sh
gcc -std=c23 main.c
./a.out
```

出力例:

```txt
6485addd9000-6485addda000 r--p 00000000 fc:00 24772925                   /home/cosocaf/dev/sfc/binary-hacks-rebooted-elf-hack/04-process-maps/a.out
6485addda000-6485adddb000 r-xp 00001000 fc:00 24772925                   /home/cosocaf/dev/sfc/binary-hacks-rebooted-elf-hack/04-process-maps/a.out
6485adddb000-6485adddc000 r--p 00002000 fc:00 24772925                   /home/cosocaf/dev/sfc/binary-hacks-rebooted-elf-hack/04-process-maps/a.out
6485adddc000-6485adddd000 r--p 00002000 fc:00 24772925                   /home/cosocaf/dev/sfc/binary-hacks-rebooted-elf-hack/04-process-maps/a.out
6485adddd000-6485addde000 rw-p 00003000 fc:00 24772925                   /home/cosocaf/dev/sfc/binary-hacks-rebooted-elf-hack/04-process-maps/a.out
6485c5b50000-6485c5b71000 rw-p 00000000 00:00 0                          [heap]
72711c200000-72711c228000 r--p 00000000 fc:00 3966314                    /usr/lib/x86_64-linux-gnu/libc.so.6
72711c228000-72711c3bd000 r-xp 00028000 fc:00 3966314                    /usr/lib/x86_64-linux-gnu/libc.so.6
72711c3bd000-72711c40c000 r--p 001bd000 fc:00 3966314                    /usr/lib/x86_64-linux-gnu/libc.so.6
72711c40c000-72711c410000 r--p 0020b000 fc:00 3966314                    /usr/lib/x86_64-linux-gnu/libc.so.6
72711c410000-72711c412000 rw-p 0020f000 fc:00 3966314                    /usr/lib/x86_64-linux-gnu/libc.so.6
72711c412000-72711c41f000 rw-p 00000000 00:00 0
72711c456000-72711c459000 rw-p 00000000 00:00 0
72711c472000-72711c474000 rw-p 00000000 00:00 0
72711c474000-72711c476000 r--p 00000000 00:00 0                          [vvar]
72711c476000-72711c478000 r--p 00000000 00:00 0                          [vvar_vclock]
72711c478000-72711c47a000 r-xp 00000000 00:00 0                          [vdso]
72711c47a000-72711c47b000 r--p 00000000 fc:00 3966311                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
72711c47b000-72711c4a9000 r-xp 00001000 fc:00 3966311                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
72711c4a9000-72711c4b4000 r--p 0002f000 fc:00 3966311                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
72711c4b4000-72711c4b6000 r--p 0003a000 fc:00 3966311                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
72711c4b6000-72711c4b7000 rw-p 0003c000 fc:00 3966311                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
72711c4b7000-72711c4b8000 rw-p 00000000 00:00 0
7ffeee0cb000-7ffeee0ec000 rw-p 00000000 00:00 0                          [stack]
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]
```

`[アドレス範囲] [権限] [オフセット] [デバイス] [i-node] [パス名]`という書式になっています。

アドレス範囲は、その領域がプロセスのどの空間にマップされているかを示します。

権限を見ると、それがどのようなセクションだったのかがわかります。
例えば、`r--p`であれば`.rodata`のようなセクション、`rw-p`であれば`.data`のようなセクション、`r-xp`であれば`.text`のようなセクションです。
なお、権限の`p`は`private`を表し、他のプロセスから見えません。`s`なら`shared`であり、共有メモリなどが該当します。

オフセットは、マップした対象のどの領域をマップしているかを示します。

デバイスは、マップした対象がどのデバイスに存在しているかを示します。匿名のマップなら0です。

i-nodeは、マップした対象のi-node番号を示します。匿名のマップなら0です。

パス名は、マップした対象のパスを示します。heapやstackなど、特殊な対象の場合はパスではなく`[heap]`や`[stack]`のように書かれます。

