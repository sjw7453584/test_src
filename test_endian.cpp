#include<cstdio>
/* 谈到字节序的问题，必然牵涉到两大CPU派系。那就是Motorola的PowerPC系列CPU和Intel的x86系列CPU。PowerPC系列采用big endian方式存储数据，而x86系列则采用little endian方式存储数据。那么究竟什么是big endian，什么又是little endian呢？

     其实big endian是指低地址存放最高有效字节（MSB），而little endian则是低地址存放最低有效字节（LSB）。

     用文字说明可能比较抽象，下面用图像加以说明。比如数字0x12345678在两种不同字节序CPU中的存储顺序如下所示：

Big Endian

   低地址                                            高地址
   ----------------------------------------->
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     12     |      34    |     56      |     78    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

Little Endian

   低地址                                            高地址
   ----------------------------------------->
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     78     |      56    |     34      |     12    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

union endian{
        int a;
        char b[4];
    };

int main(){

    endian test;
    test.a= 1;
    if ( 0 == test.b[0] )
    {
        printf("this is a bigendian machine\n");
    }
    else
    {
        printf("this is a little-endian machine\n");
    }
}
