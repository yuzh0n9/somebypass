#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;



// 魔改：主要魔改表，比如 a 对应的char是97，2对应的char是50，在encode表中将a和2互换，那么在decode表中将下标为97和50的两个值互换即可
// 每次使用表前，随机打乱encode表，然后生成一个对应的decode表的数组
// 解码时使用
static const unsigned char base64_suffix_map[256] = {
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 253, 255,
    255, 253, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 253, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255,  62, 255, 255, 255,  63,
    52,  53,  54,  55,  56,  57,  58,  59,  60,  61, 255, 255,
    255, 254, 255, 255, 255,   0,   1,   2,   3,   4,   5,   6,
    7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,
    19,  20,  21,  22,  23,  24,  25, 255, 255, 255, 255, 255,
    255,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,
    37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
    49,  50,  51, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255 };


// 编码表
static char base64en[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',  'I', 'J', 'K',
        'L', 'M', 'N', 'O', 'P',  'Q', 'R', 'S', 'T', 'U', 'V',
        'W', 'X',   'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f','g',
        'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
        's', 't', 'u', 'v',  'w', 'x', 'y', 'z', '0', '1', '2',
        '3', '4', '5', '6', '7', '8', '9', '+', '/', '\0'};



void base64_encode(const char* data,char* out){
    // 长度计算
    int data_len = strlen(data);
    // data_len = 20;
    if(data_len == 0){
        out[0] = '\0';
        return;
    }

    int index = 0;
    char c = '\0';
    char last_c = '\0';

    for(int i=0;i<data_len;i++){
        c = data[i];
        switch (i%3) {
            case 0:
                out[index++] = base64en[(c>>2) & 0x3f];
                break;
            case 1:
                out[index++] = base64en[(last_c & 0x3) << 4 | ((c >> 4) & 0xf)];
                break;
            case 2:
                out[index++] = base64en[((last_c & 0xf)) << 2 | ((c >> 6) & 0x3)];
                out[index++] = base64en[c & 0x3f];
                break;
        }
        last_c = c;
    }

    if(data_len % 3 == 1){
        out[index++] = base64en[(c & 0x3) << 4];
        out[index++] = '=';
        out[index++] = '=';
    }

    if(data_len % 3 == 2){
        out[index++] = base64en[(c & 0xf) << 2];
        out[index++] = '=';
    }

}

void base64_encode1(const char* data,char* out,  char* base64_en1){
    // 长度计算
    int data_len = strlen(data);
    // data_len = 20;
    if(data_len == 0){
        out[0] = '\0';
        return;
    }

    int index = 0;
    char c = '\0';
    char last_c = '\0';

    for(int i=0;i<data_len;i++){
        c = data[i];
        switch (i%3) {
            case 0:
                out[index++] = base64_en1[(c>>2) & 0x3f];
                break;
            case 1:
                out[index++] = base64_en1[(last_c & 0x3) << 4 | ((c >> 4) & 0xf)];
                break;
            case 2:
                out[index++] = base64_en1[((last_c & 0xf)) << 2 | ((c >> 6) & 0x3)];
                out[index++] = base64_en1[c & 0x3f];
                break;
        }
        last_c = c;
    }

    if(data_len % 3 == 1){
        out[index++] = base64_en1[(c & 0x3) << 4];
        out[index++] = '=';
        out[index++] = '=';
    }

    if(data_len % 3 == 2){
        out[index++] = base64_en1[(c & 0xf) << 2];
        out[index++] = '=';
    }

}

int base64_decode(char* data,char* output) {
    int data_len = strlen(data);

    int t = 0, x = 0, y = 0;
    unsigned char c = '0';
    int g = 3;
    for (int i = 0; i < data_len; i++)
    {
        // 需要解码的数据对应的ASCII值对应base64_suffix_map的值
        c = base64_suffix_map[data[i]];
        if (c == 255) return -1;// 对应的值不在转码表中
        if (c == 253) continue;// 对应的值是换行或者回车
        if (c == 254) { c = 0; g--; }// 对应的值是'='
        t = (t<<6) | c; // 将其依次放入一个int型中占3字节
        
        if (++y == 4) {
            output[x++] = (unsigned char)((t>>16)&0xff);
            if (g > 1) output[x++] = (unsigned char)((t>>8)&0xff);
            if (g > 2) output[x++] = (unsigned char)(t&0xff);
            y = t = 0;
        }
    }
    
    return 0;
}

int base64_decode2(char* data,char* output, unsigned char* base64_decode1) {
    int data_len = strlen(data);

    int t = 0, x = 0, y = 0;
    unsigned char c = '0';
    int g = 3;
    for (int i = 0; i < data_len; i++)
    {
        // 需要解码的数据对应的ASCII值对应base64_suffix_map的值
        c = base64_decode1[data[i]];
        if (c == 255) return -1;// 对应的值不在转码表中
        if (c == 253) continue;// 对应的值是换行或者回车
        if (c == 254) { c = 0; g--; }// 对应的值是'='
        t = (t<<6) | c; // 将其依次放入一个int型中占3字节
        
        if (++y == 4) {
            output[x++] = (unsigned char)((t>>16)&0xff);
            if (g > 1) output[x++] = (unsigned char)((t>>8)&0xff);
            if (g > 2) output[x++] = (unsigned char)(t&0xff);
            y = t = 0;
        }
    }
    
    return 0;
}



// 随机打乱一个数组


void  random(  char  a[],  int  n)
{

    srand((unsigned int)time(NULL)); //随机数种子;

    char temp = '\0';
    int num = 0;
	for (int i = 0; i<n - 1; i++)
	{
		num = i + rand() % (n - 1 - i); // 取随机数
		temp = a[i];
		a[i] = a[num];
		a[num] = temp; //交换
	}

  }



int main() {



    // 打乱encode表
    char base64en1[sizeof(base64en)];
    memset(base64en1, '\0', sizeof(base64en));
    strcpy(base64en1, base64en);
    random(base64en1, 60);
    


    unsigned char base64_decode1[256];
    memset(base64_decode1, '\0', sizeof(base64_suffix_map));
    strcpy((char*)base64_decode1, (char*)base64_suffix_map);

    int a = 0;
    for (int i = 0; i < sizeof(base64en); i++)
    {
        char* q = find(base64en1, base64en1+64, base64en[i]);
        a = q - base64en1;
        // printf("%c", base64_suffix_map[base64en[i]]); 
        base64_decode1[base64en[i]] = base64_suffix_map[base64en[a]];
    }
    
    
    // printf("%s\n", base64en1);

    const char* text = "输入点";
    char out[100] = {0};
    // base64_encode(text, out);
    base64_encode1(text, out, base64en1);
    printf("%s\n", out);

    char output[100] = {0};
    base64_decode2(out, output, base64_decode1);
    printf("%s\n", output);

    return 0;
}
