# Binary Hacks Rebooted - ELF Hack

Binary Hacks Rebooted 第二章 ELF Hackの輪読用リポジトリ

## 環境構築

次のパッケージが入っているx86_64のlinux環境があればokです。

- gcc 14
- gdb
- patchelf

```sh
apt update

apt install -y --no-install-recommends \
  software-properties-common \
  build-essential \
  gcc-14 g++-14 \
  gdb \
  patchelf \
  ca-certificates \
  curl \
  git \
  vim

update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 100
update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-14 100
```

そうでない環境なら仮想環境などを用いてください。

### Mac (Apple silicon)

#### Docker

gdbでレジスタが見えません。see: <https://github.com/docker/for-mac/issues/6921>

```
git clone https://github.com/cosocaf/binary-hacks-rebooted-elf-hack.git
cd binary-hacks-rebooted-elf-hack
docker compose up -d --build
docker compose exec ubuntu-dev bash
```

#### QEMU

Dockerのplatform指定だとgdbでレジスタが見えなかったりするので、それが嫌であればqemu上にubuntuのcloud imageを立てます。(時間かかります)

依存パッケージをインストールする:

```sh
brew install qemu cdrtools
```

ubuntu cloud imageのisoをダウンロードする:

```sh
curl -L -o ubuntu-noble-amd64.img https://cloud-images.ubuntu.com/noble/current/noble-server-cloudimg-amd64.img
```

書き込み用のディスクを用意:

```sh
qemu-img create -f qcow2 -F qcow2 -b ubuntu-noble-amd64.img ubuntu.qcow2 20G
```

user-dataを作成する:

下記内容のファイルを`user-data`という名前で保存
(`<username>`, `<github_username>`, `<public_key>`は適宜置き換える。`github_username`と`public_key`はどちらか片方でok)

```yaml
#cloud-config
users:
  - name: <username>
    uid: 1000
    ssh_import_id:
      - gh:<github_username>
    groups: [sudo, adm]
    sudo: ALL=(ALL) NOPASSWD:ALL
    shell: /bin/bash
    ssh_authorized_keys:
      - <public_key>

ssh_pwauth: false
disable_root: true

package_update: true
package_upgrade: true
packages:
  - build-essential
  - gdb
  - gcc-14
  - g++-14
  - patchelf
  - curl
  - git
  - vim

timezone: Asia/Tokyo
locale: ja_JP.UTF-8

runcmd:
  - update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 100
  - update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-14 100
```

meta-dataを作成する:

下記内容のファイルを`meta-data`という名前で保存

```yaml
instance-id: iid-noble-001
local-hostname: noble-qemu
```

cloud-initのseedを作る:

```sh
mkisofs -output seed.img -volid cidata -joliet -rock user-data meta-data
```

qemuを立ち上げる:

```sh
qemu-system-x86_64 \
  -accel tcg \
  -cpu qemu64 \
  -smp 4 -m 8G \
  -machine q35 \
  -drive if=virtio,file=ubuntu.qcow2,format=qcow2 \
  -drive if=virtio,file=seed.img,format=raw \
  -nic user,model=virtio-net-pci,hostfwd=tcp::2222-:22 \
  -display none \
  -serial mon:stdio
```

初回セットアップに十数分かかると思います。

立ち上げたqemuにsshで接続する:

```sh
ssh -p 2222 <username>@127.0.0.1
```

リポジトリをクローンする:

```
git clone https://github.com/cosocaf/binary-hacks-rebooted-elf-hack.git
cd binary-hacks-rebooted-elf-hack
```

