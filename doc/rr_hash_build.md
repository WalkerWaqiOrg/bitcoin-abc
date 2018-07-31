# RR HASH BUILD

##编译

cd rr_hash

mkdir build

cd build  



Unix*:

cmake ../src -DCMAKE_BUILD_TYPE=Release 



windows msys2:

cmake ../src/ -DCMAKE_BUILD_TYPE=Release -G "MSYS Makefiles" 



make



## 拷贝

拷贝librrhash.so   到  rrcoind 可执行文件 同级目录。



