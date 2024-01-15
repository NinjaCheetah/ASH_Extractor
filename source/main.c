// Original ASH Extractor for ASH0 files made by `crediar`.
// http://wiibrew.org/wiki/ASH_Extractor
// This is an decompiled version of the program so it can be rebuilt and hopefully fixed, now maintained by NinjaCheetah.
// All copyright for this code still belongs to crediar.

#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Assume host is little endian
static uint32_t BIG_TO_HOST(uint32_t x) {
    return (x & 0xFF) << 24 | (x & 0xFF00) << 8 | (x & 0xFF0000) >> 8 | (x & 0xFF000000) >> 24;
}

#define LOWORD(x) (*((uint16_t*)&(x)))

// Byteswap 16
static uint16_t bswap16(uint16_t value) {
    return value << 8 | value >> 8;
}

int main(int argc, char **argv)
{
    int result; // eax
    FILE *input_file; // esi
    int input_size; // edi
    uint32_t *input_content; // eax
    int v9; // ecx
    int v10; // eax
    unsigned int decompressed_size;
    uint8_t *outbuf; // eax
    unsigned int input_content_big;
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
    int check_file_done;
    FILE *output_file;
    size_t Count; // [esp+8h] [ebp-1088h]
    size_t Counta; // [esp+8h] [ebp-1088h]
    size_t Countb; // [esp+8h] [ebp-1088h]
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
    int DstBuf; // [esp+8Ch] [ebp-1004h]
    char destination;

    printf(" ASH v0.2\n by crediar\n updated by NinjaCheetah\n");
    printf(" built %s\n", __DATE__);
    // Check if arguments are passed and if file exists
    if (argc != 2) {
        return 0;
    }
    input_file = fopen(argv[1], "rb");
    if (!input_file)
    {
        printf("Could not open file\n");
        return 0;
    }
    fread(&DstBuf, 4u, 1u, input_file);
    if (DstBuf & 0x1000000)
    {
        printf("This is not a valid ASH file\n");
        return 0;
    }
    fseek(input_file, 0, 2);
    input_size = ftell(input_file);
    fseek(input_file, 0, 0);
    input_content = (uint32_t *)malloc(input_size);
    //input_content = input_content;
    //input_content = input_content;
    fread(input_content, 1u, input_size, input_file);
    fclose(input_file);
    v9 = input_content[1] >> 24;
    v10 = (input_content[1] >> 8) & 0xFF00;
    decompressed_size = v10 | (v9 | ((input_content[1] & 0xFFFFFF00) << 8)) & 0xFFFFFF;
    printf("Decompressed size: %d\n", v10 | (v9 | ((input_content[1] & 0xFFFFFF00) << 8)) & 0xFFFFFF);
    outbuf = (uint8_t *)malloc(decompressed_size);
    memset(outbuf, 0, decompressed_size);
    input_content_big = BIG_TO_HOST(input_content[2]);
    v68 = 0;
    v71 = 0;
    v67 = 16;
    v15 = BIG_TO_HOST(input_content[2]);
    v16 = BIG_TO_HOST(*(uint32_t *)((char *)input_content + input_content_big));
    v70 = input_content_big + 4;
    v63 = (uint16_t *)malloc(0x100000u);
    memset(v63, 0, 0x100000u);
    v17 = 512;
    v18 = v63 + 10236;
    v65 = 512;
    v69 = 0;
    while (true)
    {
        while (true)
        {
            if (v68 == 31)
            {
                Count = v15 >> 31;
                v15 = BIG_TO_HOST(*(uint32_t *)((char *)input_content + v67));
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
            *v18 = bswap16(v17 | 0x8000);
            v18[1] = bswap16(v17 | 0x4000);
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
                v15 = BIG_TO_HOST(*(uint32_t *)((char *)input_content + v67));
                v67 += 4;
                v68 = 0;
                goto LABEL_18;
            }
            v15 <<= 9;
        }
        else
        {
            v21 = *(uint32_t *)((char *)input_content + v67);
            v67 += 4;
            v19 = v68 - 23;
            v20 |= BIG_TO_HOST(v21) >> (64 - (v68 + 9));
            v15 = BIG_TO_HOST(v21) << (v68 - 23);
        }
        v68 = v19;
    LABEL_18:
        --v69;
        v22 = bswap16(*(v18 - 1));
        v23 = v22 & 0x8000;
        --v18;
        v24 = v22 & 0x1FFF;
        if (v23)
            break;
    LABEL_21:
        v63[v24] = bswap16(v20);
        v17 = v65;
        //input_content = input_content;
    }
    while (true)
    {
        v63[v24 + 1023] = bswap16(v20);
        v20 = (v24 * 2 >> 1) & 0x1FFF;
        v60 = (v24 * 2 >> 1) & 0x1FFF;
        if (!v69)
            break;
        --v69;
        v25 = bswap16(*(v18 - 1));
        v26 = v25 & 0x8000;
        --v18;
        v24 = v25 & 0x1FFF;
        if (!v26)
            goto LABEL_21;
    }
    v27 = 2048;
    v66 = 2048;
    while (true)
    {
        v28 = v70;
        while (true)
        {
            if (v71 == 31)
            {
                Counta = v16 >> 31;
                v16 = BIG_TO_HOST(*(uint32_t *)((char *)input_content + v28));
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
            *v18 = bswap16(v27 | 0x8000);
            v18[1] = bswap16(v27 | 0x4000);
            v18 += 2;
            ++v27;
            ++v66;
        }
        v29 = v71 + 11;
        if ((unsigned int)(v71 + 11) > 0x20)
        {
            v30 = v16 >> 21;
            v31 = BIG_TO_HOST(*(uint32_t *)((char *)input_content + v28));
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
            v16 = BIG_TO_HOST(*(uint32_t *)((char *)input_content + v28));
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
        v33 = bswap16(*(v18 - 1));
        v34 = v33 & 0x8000;
        --v18;
        v35 = v33 & 0x1FFF;
        if (!v34)
        {
        LABEL_38:
            v63[v35 + 2046] = bswap16(v32);
            v27 = v66;
            continue;
        }
        break;
    }
    while (true)
    {
        v63[v35 + 6141] = bswap16(v32);
        v62 = (v35 * 2 >> 1) & 0x1FFF;
        if (!v69)
            break;
        --v69;
        LOWORD(v32) = (v35 * 2 >> 1) & 0x1FFF;
        v36 = bswap16(*(v18 - 1));
        v37 = v36 & 0x8000;
        --v18;
        v35 = v36 & 0x1FFF;
        if (!v37)
            goto LABEL_38;
    }
    Countb = decompressed_size;
    while (true)
    {
        v38 = v67;
        v39 = v68;
        while (true)
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
                        v15 = BIG_TO_HOST(*(uint32_t *)((char *)input_content + v38));
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
                    v44 = bswap16(v43);
                    v40 = v44;
                    v64 = v44;
                } while (v44 >= 0x200u);
                v67 = v38;
                v68 = v39;
            }
            if (v40 >= 0x100)
                break;
            *outbuf++ = v40;
            if (!--decompressed_size)
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
                    v16 = BIG_TO_HOST(*(uint32_t *)((char *)input_content + v70));
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
                    v45 = bswap16(v63[v47 + 6141]);
                else
                    v45 = bswap16(v63[v47 + 2046]);
            } while (v45 >= 0x800);
            v40 = v64;
        }
        v48 = v40 - 253;
        v49 = &outbuf[-v45];
        check_file_done = -v48 + decompressed_size;
        decompressed_size += -v48;
        while (v48) {
            *outbuf++ = *(v49++ - 1);
            v48--;
        }
        // If this value isn't zero, there's more to read
        if (check_file_done)
            continue;
        break;
    }
    // Decompressed!
LABEL_69:
    printf("Decompressed %d bytes\n", Countb);
    sprintf(&destination, "%s.arc", argv[1]);
    output_file = fopen(&destination, "wb");
    if (output_file)
    {
        size_t bytes_written = fwrite(outbuf, 1u, Countb, output_file);
        printf("Wrote:%d\n", bytes_written);
        fclose(output_file);
        result = 1;
    }
    else
    {
        printf("Could not create/write file\n");
        result = 0;
    }
    return result;
}
