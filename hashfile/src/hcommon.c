//
// Created by chorm on 2020-07-08.
//

#include "common.h"
#include <string.h>

void to_le32(const uint8_t* buf,uint32_t* out,size_t outelems){
    for(size_t s = 0;s<outelems;s++)
        out[s] = (buf[4*s])<<24 | (buf[4*s+1])<<16 | (buf[4*s+2])<<8 | (buf[4*s+3]); //NOLINT clang-tidy go home, you're drunk.
}

void to_le64(const uint8_t* buf,uint64_t* out,size_t outelems){
    for(size_t s = 0;s<outelems;s++)
        out[s] = ((uint64_t)buf[8*s])<<56 | ((uint64_t)buf[8*s+1])<<48 | ((uint64_t)buf[8*s+2])<<40 | ((uint64_t)buf[8*s+3])<<32 //NOLINT clang-tidy go home, you're drunk.
                 | ((uint64_t)buf[8*s+4])<<24 | ((uint64_t)buf[8*s+5])<<16 | ((uint64_t)buf[8*s+6])<<8 | ((uint64_t)buf[8*s+7]); //NOLINT clang-tidy go home, you're drunk.
}

void from_le32(uint8_t* buf,const uint32_t* in,size_t inelems){
    for(size_t s = 0;s<inelems;s++){
        uint32_t b = in[s];
        buf[4*s]   = b>>24;
        buf[4*s+1] = b>>16;
        buf[4*s+2] = b>>8;
        buf[4*s+3] = b;
    }
}

void from_le64(uint8_t* buf,const uint64_t* in,size_t inelems){
    for(size_t s = 0;s<inelems;s++){
        uint64_t b = in[s];
        buf[8*s]   = b>>56;
        buf[8*s+1] = b>>48;
        buf[8*s+2] = b>>40;
        buf[8*s+3] = b>>32;
        buf[8*s+4] = b>>24;
        buf[8*s+5] = b>>16;
        buf[8*s+6] = b>>8;
        buf[8*s+7] = b;
    }
}

__attribute__((const)) uint32_t rrotate32(uint32_t val,unsigned by) {
    return (val>>by) | (val<<(32-by));
}

__attribute__((const)) uint64_t rrotate64(uint64_t val,unsigned by) {
    return (val>>by) | (val<<(64-by));
}

__attribute__((const)) uint32_t lrotate32(uint32_t val,int by){
    return (val<<by)|(val>>(32-by));
}

static const char hex[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

void do_file_hash64(uint64_t h[],size_t out_sz,char out[],size_t block_sz, FILE* file,void(*update)(uint64_t h[],const uint8_t buf[])){
    uint8_t buf[block_sz];
    size_t totalSz=0;
    uint64_t readSz;
    while((readSz=fread(buf,1,block_sz,file))==block_sz) {
        update(h, buf);
        totalSz +=readSz;
    }
    totalSz += readSz;
    buf[readSz++] =0x80;
    if(block_sz-readSz<8){
        memset(buf+readSz,0,block_sz-readSz);
        update(h,buf);
        readSz = 0;
    }
    memset(buf+readSz,0,128-readSz);
    totalSz *=8;
    from_le64(buf+(block_sz-8),&totalSz,1);
    update(h,buf);
    uint8_t buf1[out_sz];
    from_le64(buf1,h,out_sz/8);
    for(size_t s = 0;s<out_sz;s++){
        out[2*s] = hex[buf1[s]>>4];
        out[2*s+1] = hex[buf1[s]&0xf];
    }
}

#include <stdlib.h>

void do_file_hash32(uint32_t h[],size_t out_sz,char out[],size_t block_sz,FILE* file,void(*update)(uint32_t h[],const uint8_t buf[])){
    uint8_t buf [block_sz];
    size_t totalSz=0;
    uint64_t readSz;
    while((readSz=fread(buf,1,block_sz,file))==block_sz) {
        update(h, buf);
        totalSz +=readSz;
    }
    totalSz += readSz;
    buf[readSz++] =0x80;
    if(block_sz-readSz<8){
        memset(buf+readSz,0,block_sz-readSz);
        update(h,buf);
        readSz = 0;
    }
    memset(buf+readSz,0,block_sz-readSz);
    totalSz *=8;
    from_le64(buf+(block_sz-8),&totalSz,1);
    update(h,buf);
    uint8_t buf1[out_sz];
    from_le32(buf1,h,out_sz/4);
    for(size_t s = 0;s<out_sz;s++){
        out[2*s] = hex[buf1[s]>>4];
        out[2*s+1] = hex[buf1[s]&0xf];
    }
}