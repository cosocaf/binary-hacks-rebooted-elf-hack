# Binary Hacks Rebooted - ELF Hack

Binary Hacks Rebooted 第二章 ELF Hackの輪読用リポジトリ

## 環境構築

`build-essential`が入ったUbuntu環境があるならスキップ

1. Dockerを入れる
2. 下記コマンドを実行

```sh
git clone https://github.com/cosocaf/binary-hacks-rebooted-elf-hack.git
cd binary-hacks-rebooted-elf-hack
docker compose up -d --build
docker compose exec ubuntu-dev bash
```
