curl -O https://musl.libc.org/releases/musl-1.2.5.tar.gz
tar -xzf musl-1.2.5.tar.gz
cd musl-1.2.5
./configure --target=x86_64-linux-musl

giving up on trying musl on macos

