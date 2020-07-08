//
// Created by chorm on 2020-07-08.
//

#include "common.h"
#include "select_hash.h"

#include <string.h>

static void md5_block(uint32_t h[4],const uint8_t block[64]){
    const static uint8_t S[] ={
            7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
            5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
            4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
            6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
    };
    const static uint32_t K[] = {
            0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
            0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
            0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
            0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
            0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
            0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
            0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
            0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
            0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
            0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
            0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
            0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
            0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
            0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
            0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
            0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };

    uint32_t w[16];
    memcpy(w,block,64);
    uint32_t A = h[0], B = h[1], C = h[2], D = h[3];
    for(size_t n = 0;n<64;n++) { // Don't fall for off-by-one errors again
        uint32_t F,g;
        if(n<16){
            F = (B&C)^((~B)&D);
            g = n;
        }else if(n<32){
            F = (D&B)|((~D)&C);
            g = (5*n+1)%16;
        }else if(n<48){
            F = B^C^D;
            g = (3*n+5)%16;
        }else{
            F = C^(B|(~D));
            g = (7*n)%16;
        }
        F += A + K[n] + w[g];
        A = D;
        D = C;
        C = B;
        B += lrotate32(F,S[n]);
    }
    h[0] += A;
    h[1] += B;
    h[2] += C;
    h[3] += D;
}

static void md5(char out[],FILE* f){
    uint32_t h[] ={0x67452301,0xefcdab89,0x98badcfe,0x10325476};
    do_file_hash32_le(h,16,out,64,f,md5_block);
}

__attribute__((constructor)) static void register_md5sum(void){
    register_known_hash("md5",32,md5);
}