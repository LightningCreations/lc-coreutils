//
// Created by chorm on 2020-07-06.
//

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "select_hash.h"
#include "common.h"




void sha2_block32(uint32_t h[static 8],const uint8_t buf[64]){
    static const uint32_t k[64] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };
    uint32_t w[64] = {0};
    to_le32(buf,w,16);
    for(size_t n=16;n<64;n++){
        uint32_t s0 = rrotate32(w[n-15],7)^rrotate32(w[n-15],18)^(w[n-15]>>3);
        uint32_t s1 = rrotate32(w[n-2],17)^rrotate32(w[n-2],19)^(w[n-2]>>10);
        w[n] = w[n-16] + s0 + w[n-7] + s1;
    }

    uint32_t a = h[0],b = h[1],c=h[2],d=h[3],e=h[4],f=h[5],g=h[6],i=h[7];

    for(size_t n =0;n<64;n++){
        uint32_t S1 = rrotate32(e,6)^rrotate32(e,11)^rrotate32(e,25);
        uint32_t ch = (e&f)^((~e)&g);
        uint32_t temp1 = i + S1 + ch + k[n] + w[n];
        uint32_t S0 = rrotate32(a,2)^rrotate32(a,13)^rrotate32(a,22);
        uint32_t maj = (a&b)^(a&c)^(b&c);
        uint32_t temp2 = S0 + maj;
        i = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
    h[5] += f;
    h[6] += g;
    h[7] += i;
}
void sha2_block64(uint64_t h[8],const uint8_t buf[128]){
    static const uint64_t k[80] = {
            0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538,
            0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe,
            0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
            0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
            0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab,
            0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
            0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
            0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
            0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
            0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
            0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373,
            0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
            0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c,
            0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6,
            0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
            0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
    };
    uint64_t w[80];
    to_le64(buf,w,16);

    for(size_t n=16;n<80;n++){
        uint64_t s0 = rrotate64(w[n-15],1)^rrotate64(w[n-15],8)^(w[n-15]>>7);
        uint64_t s1 = rrotate64(w[n-2],19)^rrotate64(w[n-2],61)^(w[n-2]>>6);
        w[n] = w[n-16] + s0 + w[n-7] + s1;
    }

    uint64_t a = h[0],b = h[1],c=h[2],d=h[3],e=h[4],f=h[5],g=h[6],i=h[7];

    for(size_t n =0;n<80;n++){
        uint64_t S1 = rrotate64(e,14)^rrotate64(e,18)^rrotate64(e,41);
        uint64_t ch = (e&f)^((~e)&g);
        uint64_t temp1 = i + S1 + ch + k[n] + w[n];
        uint64_t S0 = rrotate64(a,28)^rrotate64(a,34)^rrotate64(a,39);
        uint64_t maj = (a&b)^(a&c)^(b&c);
        uint64_t temp2 = S0 + maj;
        i = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
    h[5] += f;
    h[6] += g;
    h[7] += i;
}


void sha224(char out[56],FILE* file){
    uint32_t h[] = {
            0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
            0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4
    };
    do_file_hash32(h,28,out,64,file,sha2_block32);
}
void sha256(char out[64],FILE* file){
    uint32_t h[] = {
            0x6a09e667UL,0xbb67ae85UL,0x3c6ef372,0xa54ff53aUL,
            0x510e527fUL,0x9b05688cUL,0x1f83d9abUL,0x5be0cd19UL
    };
    do_file_hash32(h,32,out,64,file,sha2_block32);
}
void sha384(char out[96],FILE* file){
    uint64_t h[] = {
            0xcbbb9d5dc1059ed8, 0x629a292a367cd507, 0x9159015a3070dd17, 0x152fecd8f70e5939,
            0x67332667ffc00b31, 0x8eb44a8768581511, 0xdb0c2e0d64f98fa7, 0x47b5481dbefa4fa4
    };
    do_file_hash64(h,48,out,128,file,sha2_block64);
}
void sha512(char out[128],FILE* file){
    uint64_t h[] = {
            0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
            0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
    };
    do_file_hash64(h,64,out,128,file,sha2_block64);
}



void sha1_block(uint32_t h[5],const uint8_t block[64]){
    uint32_t w[80];
    to_le32(block,w,16);
    for(size_t i = 16;i<80;i++)
        w[i] = lrotate32(w[i-3]^w[i-8]^w[i-14]^w[i-16],1);

    uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4];

    for(size_t n = 0; n<80;n++){
        uint32_t f,k;
        if(n<=19){
            f = (b&c)|((~b)&d);
            k = 0x5A827999;
        }else if(n<=39){
            f = b^c^d;
            k = 0x6ED9EBA1;
        }else if(n<=59){
            f = (b&c)|(b&d)|(c&d);
            k = 0x8F1BBCDC;
        }else {
            f = b^c^d;
            k = 0xCA62C1D6;
        }
        uint32_t temp = lrotate32(a,5) + f + e + k + w[n];
        e = d;
        d = c;
        c = lrotate32(b,30);
        b = a;
        a = temp;
    }
    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
}

void sha1(char out[40],FILE* file){
    uint32_t h[5] = {
            0x67452301,
            0xEFCDAB89,
            0x98BADCFE,
            0x10325476,
            0xC3D2E1F0
    };
    do_file_hash32(h,20,out,64,file,sha1_block);
}

__attribute__((constructor)) static void register_sha_hashes(void){
    register_known_hash("sha224",56,sha224);
    register_known_hash("sha256",64,sha256);
    register_known_hash("sha384",96,sha384);
    register_known_hash("sha512",128,sha512);
    register_known_hash("sha1",40,sha1);
}

