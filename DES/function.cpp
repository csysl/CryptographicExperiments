#include"func.h"

//将密码转换为二进制
void CharToBit(const char *str, int *bits) {
    int m = strlen(str);
    for (int i = 0; i < m; ++i) {
        for (int j = 8 - 1, k = 0; j >= 0; --j, ++k) {
            bits[i * 8 + k] = ((str[i] >> j) & 1);
        }
    }
}

//将明文转换为二进制
void CharToBit(const char *str, int **bits) {
    int m = strlen(str);
    for (int i = 0; i < m; ++i) {
        for (int j = 8 - 1, k = 0; j >= 0; --j, ++k) {
            bits[i / 8][(i % 8) * 8 + k] = ((str[i] >> j) & 1);
        }
    }
}

//置换IP和IP-1
int *Trans(const int *bits, const int *IP, int length) {
    int *res = new int[length];
    for (int i = 0; i < length; ++i) {
        res[i] = bits[IP[i] - 1];
    }
    return res;
}


//置换IP和IP-1
int *Trans2(const int *bits, const int *IP, int length) {
    int *res = new int[length];
    for (int i = 0; i < length; ++i) {
        res[IP[i] - 1] = bits[i];
    }
    return res;
}

//用来做测试的
int *Trans(const int *bits, int length) {
    int *res = new int[length];
    for (int i = 0; i < length; ++i) {
        res[i] = bits[i];
    }
    return res;
}
//左移操作
/*
 * bits:
 * bit_n:
 * length:
 */
void ShiftL(int *bits, int bit_n, int length) {
    int *tmp = new int[bit_n]();
    int tmpl = length / 2;
    for (int k = 1; k <= 2; ++k) {
        int tag = (k - 1) * tmpl;
        for (int i = tag; i < tag + bit_n; ++i)
            tmp[i] = bits[i];
        for (int i = tag; i < tag + tmpl - bit_n; ++i)
            bits[i] = bits[i + bit_n];
        for (int i = tag + tmpl - bit_n; i < tag + tmpl; ++i)
            bits[i] = tmp[i - (tmpl - bit_n)];
    }

    delete[] tmp;
}

//得到16次迭代的k
void GetK(int *key, table &t, int KK[16][48]) {
    int *keyy = Trans(key, t.PC_1, 56);   //记录
    for (int j = 0; j < 15; ++j) {
        ShiftL(keyy, t.shiftBits[j], 56);        //左移操作
        int *k = Trans(keyy, t.PC_2, 48);            //每次的k，48位
        copy(k, k + 48, KK[j]);   //保存k
        delete[]k;
    }
    delete[] keyy;
}

//得到每次迭代后的整串
void NewStr(int *bits, const int *kk, const table &t) {
    int bitts[64];
    copy(bits, bits + 64, bitts);
    //得到左边32位，Li=Ri-1
    //copy(bitts,bitts+32,bits);
    for (int i = 0; i < 32; ++i)
        bits[i] = bitts[i + 32];
    //得到右边32位，Ri=Li-1^F(Ri-1,Ki)
    int tmpR[32];   //
    copy(bits + 32, bits + 64, tmpR);

    int *tmpr = Trans(tmpR, t.E, 48);  //右边扩展到48位
    for (int i = 0; i < 48; ++i) //k和右边异或
        tmpr[i] = tmpr[i] ^ kk[i];
    int *res = new int[32];
    for (int i = 0; i < 8; ++i) {
        int row = 2 * tmpr[i * 6] + tmpr[i * 6 + 5];
        int col = 8 * tmpr[i * 6 + 1] + 4 * tmpr[i * 6 + 2] + 2 * tmpr[i * 6 + 3] + tmpr[i * 6 + 4];
        int tmp = t.S_BOX[i][row][col];
        for (int j = 3; j >= 0; --j) {    //S盒变换
            res[i * 4 + j] = (tmp & 1);
            tmp >>= 1;
        }
    }
    res = Trans(res, t.P, 32);    //P变换,得到F的结果
    for (int i = 0; i < 32; ++i)  //Ri=Li-1^F(Ri-1,Ki)
        bits[i + 32] = res[i] ^ bitts[i];
    delete[] tmpr, res;
}

//异或函数
void OX(int *f, int *tmp) {
    for (int i = 0; i < 64; ++i)
        f[i] = f[i] ^ tmp[i];
}
