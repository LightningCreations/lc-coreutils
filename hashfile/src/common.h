//
// Created by chorm on 2020-07-08.
//

#ifndef LCNIX_COMMON_H
#define LCNIX_COMMON_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>


void do_file_hash32(uint32_t h[],size_t out_sz,char out[],size_t block_sz,FILE* f,void(*update)(uint32_t h[],const uint8_t buf[]));
void do_file_hash32_le(uint32_t h[],size_t out_sz,char out[],size_t block_sz,FILE* f,void(*update)(uint32_t h[],const uint8_t buf[]));
void do_file_hash64(uint64_t h[],size_t out_sz,char out[],size_t block_sz, FILE* f,void(*update)(uint64_t h[],const uint8_t buf[]));

void to_le32(const uint8_t* buf,uint32_t* out,size_t outelems);
void to_le64(const uint8_t* buf,uint64_t* out,size_t outelems);
void from_le32(uint8_t* buf,const uint32_t* in,size_t inelems);
void from_le64(uint8_t* buf,const uint64_t* in,size_t inelems);

__attribute__((const)) uint32_t rrotate32(uint32_t val,unsigned by);
__attribute__((const)) uint64_t rrotate64(uint64_t val,unsigned by);
__attribute__((const)) uint32_t lrotate32(uint32_t val,int by);

#endif //LCNIX_COMMON_H
