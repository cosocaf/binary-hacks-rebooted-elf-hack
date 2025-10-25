# 1. レジスタ

gdbを起動して実行中のプロセスのレジスタを見てみます。

```sh
# ビルド
gcc -std=c23 main.c
# プロセスをgdbで起動
gdb -q ./a.out

# 以下gdb内

# main関数に入った時点でプログラムを一時停止
break main
# プログラムを実行
run
# レジスタの中身を確認
info registers
``````

<details>
<summary>出力例:</summary>

```txt
rax            0x555555555129      93824992235817
rbx            0x7fffffffe718      140737488348952
rcx            0x555555557df8      93824992247288
rdx            0x7fffffffe728      140737488348968
rsi            0x7fffffffe718      140737488348952
rdi            0x1                 1
rbp            0x7fffffffe5f0      0x7fffffffe5f0
rsp            0x7fffffffe5f0      0x7fffffffe5f0
r8             0x0                 0
r9             0x7ffff7fc6160      140737353900384
r10            0x0                 0
r11            0x203               515
r12            0x1                 1
r13            0x0                 0
r14            0x555555557df8      93824992247288
r15            0x7ffff7ffd000      140737354125312
rip            0x555555555131      0x555555555131 <main+8>
eflags         0x246               [ PF ZF IF ]
cs             0x33                51
ss             0x2b                43
ds             0x0                 0
es             0x0                 0
fs             0x0                 0
gs             0x0                 0
k0             0x4000000           67108864
k1             0x140000            1310720
k2             0x0                 0
k3             0x0                 0
k4             0x0                 0
k5             0x0                 0
k6             0x0                 0
k7             0x0                 0
fs_base        0x7ffff7f9d740      140737353733952
gs_base        0x0                 0
```
</details>

各レジスタについて:

## 汎用レジスタ (スタックポインタを含む)

| レジスタ | 説明 |
|----------|------|
| **rax** | 算術演算用, AccumulatorのA |
| **rbx** | メモリアドレッシングのベースアドレス, BaseのB |
| **rcx** | ループ命令(`loop`)や文字列操作系(`rep`)の繰り返し回数, CounterのC |
| **rdx** | Aレジスタでは足りない場合(e.g., `mul`)で補助的に使用, DataのD |
| **rsi** | 文字列操作用, Source IndexでSI |
| **rdi** | 文字列操作用, Destination IndexでDI |
| **rbp** | 現在の関数のスタックのベースアドレス, Base PointerでBP |
| **rsp** | 現在のスタックの先端を指すアドレス, Stack PointerでSP |
| **r8~r15** | x64で追加, 最初から汎用レジスタとして作られたので単純に連番 |

## 制御系のレジスタ

| レジスタ | 説明 |
|----------|------|
| **rip** | プログラムカウンタ, Instruction PointerでIP |
| **eflags** | フラグレジスタ, CPU状態を持つ, 上位32bitは使われてないのでrflagsとして使うことはほぼない |

## セグメント系のレジスタ

64bit(long mode)ではcs, ss, ds, esはベースアドレスが0として扱われる。fsとgsは0以外に設定できる。

| レジスタ | 説明 |
|----------|------|
| **cs** | コードセグメント, 特権レベルなど |
| **ss** | スタックセグメント, rspやrbpの基準点 |
| **ds** | データセグメント, rbxの基準点 |
| **es** | エクストラセグメント, rdiの基準点 |
| **fs** | エクストラセグメント, esの次だからfs, thread local storageなどに使う (OSやABIによる) |
| **gs** | エクストラセグメント, fsの次だからgs, linuxではカーネルが使う |
| **fs_base** | fsが指すアドレス |
| **gs_base** | gsが指すアドレス |

## オペマスクレジスタ

`k0`~`k7`のこと。AVX-512で使う。今回の話では特に出てこない。

