cd /home/buu/Downloads/camapp-sdk-000.142/camapp-sdk/external/curl-7.61.1

export CROSS_COMPILE="/home/buu/Desktop/git_giec/FCA-GIEC/vendor/sdk/build/toolchain/arm-anycloud-linux-uclibcgnueabi.gcc_7.3.0/bin/arm-anycloud-linux-uclibcgnueabi"
export CPPFLAGS="-I/home/buu/Desktop/git_giec/FCA-GIEC/fcam/libraries/libopenssl/include"
export LDFLAGS="-L/home/buu/Desktop/git_giec/FCA-GIEC/fcam/libraries/libopenssl/lib"
export AR=${CROSS_COMPILE}-ar
export AS=${CROSS_COMPILE}-as
export LD=${CROSS_COMPILE}-ld
export RANLIB=${CROSS_COMPILE}-ranlib
export CC=${CROSS_COMPILE}-gcc
export NM=${CROSS_COMPILE}-nm
export LIBS="-lssl -lcrypto"
./configure --prefix=/home/buu/Desktop/git_giec/giec_libcurl/FCA-GIEC/fcam/libraries/libcurl --target=arm-anycloud-linux-uclibcgnueabi --host=arm-anycloud-linux-uclibcgnueabi --with-ssl=/home/buu/Desktop/git_giec/FCA-GIEC/fcam/libraries/libopenssl

make 
make install