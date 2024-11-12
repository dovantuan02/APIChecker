# Download sources Documents > FC24 > Dev > Resource > ByVivotek > 3. Firmware > 240911 > camapp-sdk-000.142

# todo
cd /home/buu/Downloads/camapp-sdk-000.142/camapp-sdk/external/zlib-1.2.11

# config 
CC=/home/buu/Desktop/git_giec/FCA-GIEC/vendor/sdk/build/toolchain/arm-anycloud-linux-uclibcgnueabi.gcc_7.3.0/bin/arm-anycloud-linux-uclibcgnueabi-gcc ./configure --prefix=/home/buu/Desktop/git_giec/FCA-GIEC/fcam/libraries/libz

# build 
make 

# install
make install