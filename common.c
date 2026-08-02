#include"common.h"
int get_size(unsigned char size[])
{
    return ((size[0]<<24)|(size[1]<<16)|(size[2]<<8)|size[3]);
}
void convert_size(int size,unsigned char bytes[])
{
    bytes[0]=(size>>24)&0xFF;
    bytes[1]=(size>>16)&0xFF;
    bytes[2]=(size>>8)&0xFF;
    bytes[3]=size & 0xFF;
}   