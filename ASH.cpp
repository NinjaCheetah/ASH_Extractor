// Original ASH Extractor for ASH0 files is made by `crediar`.
// http://wiibrew.org/wiki/ASH_Extractor
// This is an decompiled version of the program so it can be rebuilt and hopefuly fix the crashing for some .ash files.
// The decompiled code was generated by IDA Pro 7.0 & Hex-Rays decompiler... yep. Just edited to recompile.
// The code should still be considered copyright of `crediar` though. Except for the LOWORD, __ROL__, and __ROL2__ stuff.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
// assume host is little endian
inline uint32_t BIG_TO_HOST(uint32_t x) { return (((x & 0xFF) << 24) | ((x & 0xFF00) << 8) | ((x & 0xFF0000) >> 8) | ((x & 0xFF000000) >> 24)); }
#else
#include <arpa/inet.h>
inline uint32_t BIG_TO_HOST(uint32_t x) { return ntohl(x); }
#endif

// LOWORD, __ROL__, and __ROL2__ are from https://github.com/joxeankoret/tahh/blob/master/comodo/defs.h
// The Copyright is:    Copyright (c) 2007-2015 Hex-Rays
#define LOWORD(x) (*((uint16_t*)&(x)))
template<class T> T __ROL__(T value, int count)
{
    const unsigned int nbits = sizeof(T) * 8;

    if (count > 0)
    {
        count %= nbits;
        T high = value >> (nbits - count);
        if (T(-1) < 0) // signed value
            high &= ~((T(-1) << count));
        value <<= count;
        value |= high;
    }
    else
    {
        count = -count % nbits;
        T low = value << (nbits - count);
        value >>= count;
        value |= low;
    }
    return value;
}
inline uint16_t __ROL2__(uint16_t value, int count) { return __ROL__((uint16_t)value, count); }

int main(int argc, char **argv)
{
    int result; // eax
    FILE *input_file0; // eax
    FILE *input_file1; // esi
    int input_size; // edi
    uint32_t *input_content; // eax
    uint32_t *input_content1; // ebp
    int v9; // ecx
    int v10; // eax
    unsigned int decompressed_size; // edi
    uint8_t *outbuf; // eax
    uint8_t *outbuf1; // esi
    unsigned int v14; // eax
    unsigned int v15; // ebx
    unsigned int v16; // edi
    signed int v17; // edx
    uint16_t *v18; // eax
    int v19; // ecx
    unsigned int v20; // edx
    unsigned int v21; // ebp
    int16_t v22; // cx
    int v23; // ebp
    unsigned int v24; // ecx
    int16_t v25; // cx
    int v26; // ebp
    signed int v27; // ebp
    int v28; // edx
    int v29; // ecx
    unsigned int v30; // ST70_4
    unsigned int v31; // edi
    unsigned int v32; // ebp
    int16_t v33; // cx
    int v34; // edx
    unsigned int v35; // ecx
    int16_t v36; // cx
    int v37; // edx
    signed int v38; // edx
    int v39; // ebp
    unsigned int v40; // ecx
    unsigned int v41; // ecx
    int v42; // eax
    int16_t v43; // ax
    uint16_t v44; // ax
    unsigned int v45; // edx
    unsigned int v46; // ecx
    int v47; // edx
    unsigned int v48; // ecx
    uint8_t *v49; // eax
    int v50; // ebp
    unsigned int v51; // edx
    FILE *v52; // eax
    FILE *v53; // esi
    size_t v54; // eax
    size_t Count; // [esp+8h] [ebp-1088h]
    size_t Counta; // [esp+8h] [ebp-1088h]
    size_t Countb; // [esp+8h] [ebp-1088h]
    uint32_t *input_content2; // [esp+18h] [ebp-1078h]
    unsigned int decompressed_size1; // [esp+1Ch] [ebp-1074h]
    unsigned int v60; // [esp+20h] [ebp-1070h]
    unsigned int v61; // [esp+24h] [ebp-106Ch]
    unsigned int v62; // [esp+24h] [ebp-106Ch]
    uint16_t *v63; // [esp+28h] [ebp-1068h]
    unsigned int v64; // [esp+38h] [ebp-1058h]
    signed int v65; // [esp+60h] [ebp-1030h]
    signed int v66; // [esp+60h] [ebp-1030h]
    signed int v67; // [esp+68h] [ebp-1028h]
    int v68; // [esp+6Ch] [ebp-1024h]
    int v69; // [esp+74h] [ebp-101Ch]
    int v70; // [esp+78h] [ebp-1018h]
    int v71; // [esp+7Ch] [ebp-1014h]
    void *outbuf2; // [esp+88h] [ebp-1008h]
    int DstBuf; // [esp+8Ch] [ebp-1004h]
    char Dest; // [esp+90h] [ebp-1000h]

    printf(" ASH v0.1\n by crediar\n");
    printf(" built %s\n", "Aug 20 2008");
    printf(" #wiidev efnet\n\n");
#if _DEBUG
    input_file0 = fopen("D:/code2/ASH_2/Debug/mii.arc.ash", "rb");
#else
    if (argc != 2)
        return 0;
    input_file0 = fopen(argv[1], "rb");
#endif
    input_file1 = input_file0;
    if (!input_file0)
    {
        printf("Could not open file\n");
        return 0;
    }
    fread(&DstBuf, 4u, 1u, input_file0);
    if (DstBuf & 0x1000000)
    {
        printf("This is not a valid ASH file\n");
        return 0;
    }
    fseek(input_file1, 0, 2);
    input_size = ftell(input_file1);
    fseek(input_file1, 0, 0);
    input_content = (uint32_t *)malloc(input_size);
    input_content1 = input_content;
    input_content2 = input_content;
    fread(input_content, 1u, input_size, input_file1);
    fclose(input_file1);
    v9 = input_content1[1] >> 24;
    v10 = (input_content1[1] >> 8) & 0xFF00;
    decompressed_size = v10 | (v9 | ((input_content1[1] & 0xFFFFFF00) << 8)) & 0xFFFFFF;
    decompressed_size1 = v10 | (v9 | ((input_content1[1] & 0xFFFFFF00) << 8)) & 0xFFFFFF;
    printf("Decompressed size: %d\n", v10 | (v9 | ((input_content1[1] & 0xFFFFFF00) << 8)) & 0xFFFFFF);
    outbuf = (uint8_t *)malloc(decompressed_size);
    outbuf1 = outbuf;
    outbuf2 = outbuf;
    memset(outbuf, 0, decompressed_size);
    v14 = BIG_TO_HOST(input_content1[2]);
    v68 = 0;
    v71 = 0;
    v67 = 16;
    v15 = BIG_TO_HOST(input_content1[2]);
    v16 = BIG_TO_HOST(*(uint32_t *)((char *)input_content + v14));
    v70 = v14 + 4;
    v63 = (uint16_t *)malloc(0x100000u);
    memset(v63, 0, 0x100000u);
    v17 = 512;
    v18 = v63 + 10236;
    v65 = 512;
    v69 = 0;
    while (1)
    {
        while (1)
        {
            if (v68 == 31)
            {
                Count = v15 >> 31;
                v15 = BIG_TO_HOST(*(uint32_t *)((char *)input_content1 + v67));
                v67 += 4;
                v68 = 0;
            }
            else
            {
                ++v68;
                Count = (uint64_t)v15 >> 31;
                v15 *= 2;
            }
            if (!Count)
                break;
            v69 += 2;
            *v18 = __ROL2__(v17 | 0x8000, 8);
            v18[1] = __ROL2__(v17 | 0x4000, 8);
            v18 += 2;
            ++v17;
            ++v65;
        }
        v19 = v68 + 9;
        v20 = v15 >> 23;
        if ((unsigned int)(v68 + 9) <= 0x20)
        {
            if (v68 == 23)
            {
                v15 = BIG_TO_HOST(*(uint32_t *)((char *)input_content1 + v67));
                v67 += 4;
                v68 = 0;
                goto LABEL_18;
            }
            v15 <<= 9;
        }
        else
        {
            v21 = *(uint32_t *)((char *)input_content1 + v67);
            v67 += 4;
            v19 = v68 - 23;
            v20 |= BIG_TO_HOST(v21) >> (64 - (v68 + 9));
            v15 = BIG_TO_HOST(v21) << (v68 - 23);
        }
        v68 = v19;
    LABEL_18:
        --v69;
        v22 = __ROL2__(*(v18 - 1), 8);
        v23 = v22 & 0x8000;
        --v18;
        v24 = v22 & 0x1FFF;
        if (v23)
            break;
    LABEL_21:
        v63[v24] = __ROL2__(v20, 8);
        v17 = v65;
        input_content1 = input_content2;
    }
    while (1)
    {
        v63[v24 + 1023] = __ROL2__(v20, 8);
        v20 = (v24 * 2 >> 1) & 0x1FFF;
        v60 = (v24 * 2 >> 1) & 0x1FFF;
        if (!v69)
            break;
        --v69;
        v25 = __ROL2__(*(v18 - 1), 8);
        v26 = v25 & 0x8000;
        --v18;
        v24 = v25 & 0x1FFF;
        if (!v26)
            goto LABEL_21;
    }
    v27 = 2048;
    v66 = 2048;
    while (2)
    {
        v28 = v70;
        while (1)
        {
            if (v71 == 31)
            {
                Counta = v16 >> 31;
                v16 = BIG_TO_HOST(*(uint32_t *)((char *)input_content2 + v28));
                v28 += 4;
                v71 = 0;
                v70 = v28;
            }
            else
            {
                ++v71;
                Counta = (uint64_t)v16 >> 31;
                v16 *= 2;
            }
            if (!Counta)
                break;
            v69 += 2;
            *v18 = __ROL2__(v27 | 0x8000, 8);
            v18[1] = __ROL2__(v27 | 0x4000, 8);
            v18 += 2;
            ++v27;
            ++v66;
        }
        v29 = v71 + 11;
        if ((unsigned int)(v71 + 11) > 0x20)
        {
            v30 = v16 >> 21;
            v31 = BIG_TO_HOST(*(uint32_t *)((char *)input_content2 + v28));
            v70 = v28 + 4;
            v29 = v71 - 21;
            LOWORD(v32) = (v31 >> (64 - (v71 + 11))) | v30;
            v16 = v31 << (v71 - 21);
            goto LABEL_34;
        }
        v32 = v16 >> 21;
        v61 = v16 >> 21;
        if (v29 == 32)
        {
            v16 = BIG_TO_HOST(*(uint32_t *)((char *)input_content2 + v28));
            LOWORD(v32) = v61;
            v71 = 0;
            v70 = v28 + 4;
        }
        else
        {
            v16 <<= 11;
        LABEL_34:
            v71 = v29;
        }
        --v69;
        v33 = __ROL2__(*(v18 - 1), 8);
        v34 = v33 & 0x8000;
        --v18;
        v35 = v33 & 0x1FFF;
        if (!v34)
        {
        LABEL_38:
            v63[v35 + 2046] = __ROL2__(v32, 8);
            v27 = v66;
            continue;
        }
        break;
    }
    while (1)
    {
        v63[v35 + 6141] = __ROL2__(v32, 8);
        v62 = (v35 * 2 >> 1) & 0x1FFF;
        if (!v69)
            break;
        --v69;
        LOWORD(v32) = (v35 * 2 >> 1) & 0x1FFF;
        v36 = __ROL2__(*(v18 - 1), 8);
        v37 = v36 & 0x8000;
        --v18;
        v35 = v36 & 0x1FFF;
        if (!v37)
            goto LABEL_38;
    }
    Countb = decompressed_size1;
    while (2)
    {
        v38 = v67;
        v39 = v68;
        while (1)
        {
            v40 = v60;
            v64 = v60;
            if (v60 >= 0x200)
            {
                do
                {
                    v41 = v15 >> 31;
                    if (v39 == 31)
                    {
                        v15 = BIG_TO_HOST(*(uint32_t *)((char *)input_content2 + v38));
                        v38 += 4;
                        v39 = 0;
                    }
                    else
                    {
                        ++v39;
                        v15 *= 2;
                    }
                    v42 = v64;
                    if (v41)
                        v43 = v63[v42 + 1023];
                    else
                        v43 = v63[v42];
                    v44 = __ROL2__(v43, 8);
                    v40 = v44;
                    v64 = v44;
                } while (v44 >= 0x200u);
                v67 = v38;
                v68 = v39;
            }
            if (v40 >= 0x100)
                break;
            *outbuf1++ = v40;
            if (!--decompressed_size1)
                goto LABEL_69;
        }
        v45 = v62;
        if (v62 >= 0x800)
        {
            do
            {
                v46 = v16 >> 31;
                if (v71 == 31)
                {
                    v16 = BIG_TO_HOST(*(uint32_t *)((char *)input_content2 + v70));
                    v70 += 4;
                    v71 = 0;
                }
                else
                {
                    ++v71;
                    v16 *= 2;
                }
                v47 = v45;
                if (v46)
                    v45 = (uint16_t)__ROL2__(v63[v47 + 6141], 8);
                else
                    v45 = (uint16_t)__ROL2__(v63[v47 + 2046], 8);
            } while (v45 >= 0x800);
            v40 = v64;
        }
        v48 = v40 - 253;
        v49 = &outbuf1[~v45 + 1];
        v50 = ~v48 + decompressed_size1 + 1;
        v51 = v48 >> 3;
        decompressed_size1 += ~v48 + 1;
        if (v48 >> 3)
        {
            do
            {
                *outbuf1 = *(v49 - 1);
                outbuf1[1] = *v49;
                outbuf1[2] = v49[1];
                outbuf1[3] = v49[2];
                outbuf1[4] = v49[3];
                outbuf1[5] = v49[4];
                outbuf1[6] = v49[5];
                outbuf1[7] = v49[6];
                v49 += 8;
                outbuf1 += 8;
                --v51;
            } while (v51);
            if (v48 & 7)
            {
                v48 &= 7u;
                goto LABEL_65;
            }
        }
        else
        {
            do
            {
            LABEL_65:
                // CRASHES here due to out-of-bound buffer access (v49) with mii.arc.ash
                *outbuf1++ = *(v49++ - 1);
                --v48;
            } while (v48);
        }
        if (v50)
            continue;
        break;
    }
LABEL_69:
    printf("Decompressed %d bytes\n", Countb);
    sprintf(&Dest, "%s.arc", argv[1]);
    v52 = fopen(&Dest, "wb");
    v53 = v52;
    if (v52)
    {
        v54 = fwrite(outbuf2, 1u, Countb, v52);
        printf("Wrote:%d\n", v54);
        fclose(v53);
        result = 1;
    }
    else
    {
        printf("Could not create/write file\n");
        result = 0;
    }
    return result;
}
