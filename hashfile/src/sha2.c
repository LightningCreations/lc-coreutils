//
// Created by chorm on 2020-07-06.
//

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "select_hash.h"

static void to_le32(const uint8_t* buf,uint32_t* out,size_t outelems){
    for(size_t s = 0;s<outelems;s++)
        out[s] = (buf[4*s])<<24 | (buf[4*s+1])<<16 | (buf[4*s+2])<<8 | (buf[4*s+3]); //NOLINT clang-tidy go home, you're drunk.
}

static void to_le64(const uint8_t* buf,uint64_t* out,size_t outelems){
    for(size_t s = 0;s<outelems;s++)
        out[s] = ((uint64_t)buf[8*s])<<56 | ((uint64_t)buf[8*s+1])<<48 | ((uint64_t)buf[8*s+2])<<40 | ((uint64_t)buf[8*s+3])<<32 //NOLINT clang-tidy go home, you're drunk.
                | ((uint64_t)buf[8*s+4])<<24 | ((uint64_t)buf[8*s+5])<<16 | ((uint64_t)buf[8*s+6])<<8 | ((uint64_t)buf[8*s+7]); //NOLINT clang-tidy go home, you're drunk.
}

static void from_le32(uint8_t* buf,const uint32_t* in,size_t inelems){
    for(size_t s = 0;s<inelems;s++){
        uint32_t b = in[s];
        buf[4*s]   = b>>24;
        buf[4*s+1] = b>>16;
        buf[4*s+2] = b>>8;
        buf[4*s+3] = b;
    }
}

static void from_le64(uint8_t* buf,const uint64_t* in,size_t inelems){
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

__attribute__((const)) static uint32_t rrotate32(uint32_t val,unsigned by) {
    return (val>>by) | (val<<(32-by));
}

__attribute__((const)) static uint64_t rrotate64(uint64_t val,unsigned by) {
    return (val>>by) | (val<<(64-by));
}

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
            0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL, 0x3956c25bf348b538ULL,
            0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL, 0xd807aa98a3030242ULL, 0x12835b0145706fbeULL,
            0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL, 0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL,
            0xc19bf174cf692694ULL, 0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
            0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL, 0x983e5152ee66dfabULL,
            0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL, 0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL,
            0x06ca6351e003826fULL, 0x142929670a0e6e70ULL, 0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL,
            0x53380d139d95b3dfULL, 0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
            0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL, 0xd192e819d6ef5218ULL,
            0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL, 0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL,
            0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL, 0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL,
            0x682e6ff3d6b2b8a3ULL, 0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
            0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL, 0xca273eceea26619cULL,
            0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL, 0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL,
            0x113f9804bef90daeULL, 0x1b710b35131c471bULL, 0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL,
            0x431d67c49c100d4cULL, 0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
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
        uint64_t temp1 = S1 + ch + k[n] + w[n];
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

static void sha2_32(uint32_t h[static 8],FILE* file){
    uint8_t buf[64];
    size_t totalSz=0;
    uint64_t readSz;
    while((readSz=fread(buf,1,64,file))==64) {
        sha2_block32(h, buf);
        totalSz +=readSz;
    }
    totalSz += readSz;
    buf[readSz++] =0x80;
    if(64-readSz<8){
        memset(buf+readSz,0,64-readSz);
        sha2_block32(h,buf);
        readSz = 0;
    }
    memset(buf+readSz,0,64-readSz);
    totalSz *=8;
    from_le64(buf+56,&totalSz,1);
    sha2_block32(h,buf);
}

static void sha2_64(uint64_t h[static 8],FILE* file){
    uint8_t buf[128];
    size_t totalSz=0;
    uint64_t readSz;
    while((readSz=fread(buf,1,128,file))==128) {
        sha2_block64(h, buf);
        totalSz +=readSz;
    }
    totalSz += readSz;
    buf[readSz++] =0x80;
    if(128-readSz<8){
        memset(buf+readSz,0,128-readSz);
        sha2_block64(h,buf);
        readSz = 0;
    }
    memset(buf+readSz,0,128-readSz);
    totalSz *=8;
    from_le64(buf+120,&totalSz,1);
    sha2_block64(h,buf);
}

static const char hex[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

void sha224(char out[56],FILE* file){
    uint32_t h[] = {
            0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
            0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4
    };
    sha2_32(h,file);
    uint8_t buf[28];
    from_le32(buf,h,8);

    for(size_t s = 0;s<sizeof(buf);s++){
        out[2*s] = hex[buf[s]>>4];
        out[2*s+1] = hex[buf[s]&0xf];
    }
}
void sha256(char out[64],FILE* file){
    uint32_t h[] = {
            0x6a09e667UL,0xbb67ae85UL,0x3c6ef372,0xa54ff53aUL,
            0x510e527fUL,0x9b05688cUL,0x1f83d9abUL,0x5be0cd19UL
    };
    sha2_32(h,file);
    uint8_t buf[32];
    from_le32(buf,h,8);

    for(size_t s = 0;s<sizeof(buf);s++){
        out[2*s] = hex[buf[s]>>4];
        out[2*s+1] = hex[buf[s]&0xf];
    }
}
void sha384(char out[96],FILE* file){
    uint64_t h[] = {
            0xcbbb9d5dc1059ed8ULL, 0x629a292a367cd507ULL, 0x9159015a3070dd17ULL, 0x152fecd8f70e5939ULL,
            0x67332667ffc00b31ULL, 0x8eb44a8768581511ULL, 0xdb0c2e0d64f98fa7ULL, 0x47b5481dbefa4fa4ULL
    };
    sha2_64(h,file);
    uint8_t buf[48];
    from_le64(buf,h,6);

    for(size_t s = 0;s<sizeof(buf);s++){
        out[2*s] = hex[buf[s]>>4];
        out[2*s+1] = hex[buf[s]&0xf];
    }
}
void sha512(char out[128],FILE* file){
    uint64_t h[] = {
            0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL, 0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
            0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL, 0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL
    };
    sha2_64(h,file);
    uint8_t buf[64];
    from_le64(buf,h,8);

    for(size_t s = 0;s<sizeof(buf);s++){
        out[2*s] = hex[buf[s]>>4];
        out[2*s+1] = hex[buf[s]&0xf];
    }
}

uint32_t lrotate(uint32_t val,int by){
    return (val<<by)|(val>>(32-by));
}

void sha1_block(uint32_t h[5],uint8_t block[64]){
    uint32_t w[80];
    to_le32(block,w,16);
    for(size_t i = 16;i<79;i++)
        w[i] = lrotate(w[i-3]^w[i-8]^w[i-14]^w[i-16],1);

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
        uint32_t temp = lrotate(a,5) + f + e + k + w[n];
        e = d;
        d = c;
        c = lrotate(b,30);
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
    uint8_t buf[64];
    size_t totalSz=0;
    uint64_t readSz;
    while((readSz=fread(buf,1,64,file))==64) {
        sha1_block(h, buf);
        totalSz +=readSz;
    }
    totalSz += readSz;
    buf[readSz++] =0x80;
    if(64-readSz<8){
        memset(buf+readSz,0,64-readSz);
        sha1_block(h,buf);
        readSz = 0;
    }
    memset(buf+readSz,0,64-readSz);
    totalSz *=8;
    from_le64(buf+56,&totalSz,1);

    sha1_block(h,buf);
    uint8_t buf1[20];
    from_le32(buf1,h,5);
    for(size_t s = 0;s<sizeof(buf1);s++){
        out[2*s] = hex[buf1[s]>>4];
        out[2*s+1] = hex[buf1[s]&0xf];
    }
}

void register_sha_hashes(void){
    register_known_hash("sha224",56,sha224);
    register_known_hash("sha256",64,sha256);
    register_known_hash("sha384",96,sha384);
    register_known_hash("sha512",128,sha512);
    register_known_hash("sha1",40,sha1);
}

