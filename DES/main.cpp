#include"func.h"

int main() {
    bool mod;   //mod:1-ecb模式，0-cbc模式
    cout << "请选择模式：\n1----ECB模式\n0----CBC模式\n";
    cin >> mod;
    string str, key;   //初始明文和密钥，密钥初始必须为8个字节（64位）
    TAG:
    cout << "请输入密钥，密钥必须为8个字节：\n";
    if (cin >> key && key.length() != 8) {
        cout << "您输入的密钥不是8位，请重新输入！\n";
        goto TAG;
    }
    cout << "请输入明文：\n";
    //cin >> str;
    getline(cin,str);
    getline(cin,str);
    
    int n = str.length();
    if (n % 8 != 0)n = n + 8 - (n % 8);   //为了使n的长度为8的整数倍
    int **str_bits = new int *[n / 8];         //将明文以二进制存储
    for (int i = 0; i < n / 8; ++i) str_bits[i] = new int[64]();
    int **cip = new int *[n / 8];         //将密文以二进制存储
    for (int i = 0; i < n / 8; ++i) cip[i] = new int[64]();
    int **clear = new int *[n / 8];         //存储由密文转化来的明文
    for (int i = 0; i < n / 8; ++i) clear[i] = new int[64]();
    int *key_bits = new int[64]();            //将密钥以二进制存储，必须为64位
    //将密钥和明文转化为二进制
    CharToBit(str.c_str(), str_bits);
    CharToBit(key.c_str(), key_bits);

    table t;
    int KK[16][48];
    GetK(key_bits, t, KK);//获取k
    if (mod) {
        ofstream out1("../ECB_cipher.txt");    //记录明文和加密结果
        //输出原始明文
        cout << "*****原始明文对应的16进制为：\n";
        for (int i = 0; i < (n / 8); ++i) {
            for (int j = 0; j < 8; ++j) {
                int tmpi = 0, tmpt = 1;
                for (int l = 7; l >= 0; --l) {
                    tmpi += str_bits[i][j * 8 + l] * tmpt;
                    tmpt <<= 1;
                }
                if (tmpi) {
                    cout << hex << tmpi << " ";
                }
            }
        }
        cout << endl;
        //加密
        for (int i = 0; i < (n / 8); ++i) {
            int *strr = Trans(str_bits[i], t.IP, 64);  //记录每次的置换串
            for (int j = 0; j < 16; ++j) {
                NewStr(strr, KK[j], t);                   //结果保存在strr
            }
            //第16次迭代后，把左32位和右32位互换
            int tmpstr[64];
            copy(strr, strr + 64, tmpstr);
            for (int j = 0; j < 32; ++j) {
                strr[j] = tmpstr[j + 32];
                strr[j + 32] = tmpstr[j];
            }
            //IP-1变换
            strr = Trans(strr, t.IP_1, 64);
            //将密文保存到cip
            copy(strr, strr + 64, cip[i]);

            delete[] strr;
        }
        //输出密文
        cout << "*****加密后得到的16进制密文,同时写入ECB_cipher.txt：\n";
        for (int i = 0; i < (n / 8); ++i) {
            for (int j = 0; j < 8; ++j) {
                int tmpi = 0, tmpt = 1;
                for (int l = 7; l >= 0; --l) {
                    tmpi += cip[i][j * 8 + l] * tmpt;
                    tmpt <<= 1;
                }
                if (tmpi) {
                    cout << hex << tmpi << " ";
                    out1 << hex << tmpi << " ";
                }
            }
        }
        cout << "\n";
        //解密
        ofstream out2("../ECB_clear.txt");    //记录明文和加密结果
        for (int i = 0; i < (n / 8); ++i) {
            int *strr = Trans(cip[i], t.IP, 64);  //记录每次的密文
            for (int j = 15; j >= 0; --j)
                NewStr(strr, KK[j], t);//结果保存在strr
            //第16次迭代后，把左32位和右32位互换
            int tmpstr[64];
            copy(strr, strr + 64, tmpstr);
            for (int j = 0; j < 32; ++j) {
                strr[j] = tmpstr[j + 32];
                strr[j + 32] = tmpstr[j];
            }
            //IP-1变换
            strr = Trans(strr, t.IP_1, 64);
            //将明文保存到clear
            copy(strr, strr + 64, clear[i]);
            delete[] strr;
        }
        //输出密文
        cout << "*****解密后得到的明文,同时写入ECB_clear.txt：\n";
        for (int i = 0; i < (n / 8); ++i) {
            for (int j = 0; j < 8; ++j) {
                int tmpi = 0, tmpt = 1;
                for (int l = 7; l >= 0; --l) {
                    tmpi += clear[i][j * 8 + l] * tmpt;
                    tmpt <<= 1;
                }
                if (tmpi) {
                    cout << char(tmpi);
                    out2 << char(tmpi);
                }
            }
        }
        cout << "\n";
    }
        //cbc模式
    else if (!mod) {
        ofstream out1("../CBC_cipher.txt");    //记录明文和加密结果
        //输出原始明文
        cout << "*****原始明文对应的16进制为：\n";
        for (int i = 0; i < (n / 8); ++i) {
            for (int j = 0; j < 8; ++j) {
                int tmpi = 0, tmpt = 1;
                for (int l = 7; l >= 0; --l) {
                    tmpi += str_bits[i][j * 8 + l] * tmpt;
                    tmpt <<= 1;
                }
                if (tmpi) {
                    cout << hex << tmpi << " ";
                }
            }
        }
        cout << endl;
        //加密
        for (int i = 0; i < (n / 8); ++i) {
            int *strr = Trans(str_bits[i], t.IP, 64);  //记录每次的置换串
            for (int j = 0; j < 16; ++j) {
                NewStr(strr, KK[j], t);                   //结果保存在strr
            }
            //第16次迭代后，把左32位和右32位互换
            int tmpstr[64];
            copy(strr, strr + 64, tmpstr);
            for (int j = 0; j < 32; ++j) {
                strr[j] = tmpstr[j + 32];
                strr[j + 32] = tmpstr[j];
            }
            //IP-1变换
            strr = Trans(strr, t.IP_1, 64);
            //将密文保存到cip
            copy(strr, strr + 64, cip[i]);
            //CBC异或
            if (i != n/8-1)
                for (int j = 0; j < 64; ++j)
                    str_bits[i + 1][j] = str_bits[i + 1][j] ^ cip[i][j];
            delete[] strr;
        }
        //输出密文
        cout << "*****加密后得到的16进制密文,同时写入CBC_cipher.txt：\n";
        for (int i = 0; i < (n / 8); ++i) {
            for (int j = 0; j < 8; ++j) {
                int tmpi = 0, tmpt = 1;
                for (int l = 7; l >= 0; --l) {
                    tmpi += cip[i][j * 8 + l] * tmpt;
                    tmpt <<= 1;
                }
                if (tmpi) {
                    cout << hex << tmpi << " ";
                    out1 << hex << tmpi << " ";
                }
            }
        }
        cout << "\n";
        //解密
        ofstream out2("../CBC_clear.txt");    //记录明文和加密结果
        for (int i = 0; i < (n / 8); ++i) {
            int *strr = Trans(cip[i], t.IP, 64);  //记录每次的密文
            for (int j = 15; j >= 0; --j)
                NewStr(strr, KK[j], t);//结果保存在strr
            //第16次迭代后，把左32位和右32位互换
            int tmpstr[64];
            copy(strr, strr + 64, tmpstr);
            for (int j = 0; j < 32; ++j) {
                strr[j] = tmpstr[j + 32];
                strr[j + 32] = tmpstr[j];
            }
            //IP-1变换
            strr = Trans(strr, t.IP_1, 64);
            //将明文保存到clear
            copy(strr, strr + 64, clear[i]);
            //CBC异或
            if (i != 0) {
                for (int j = 0; j < 64; ++j)
                    clear[i][j] = clear[i][j] ^ cip[i - 1][j];
            }
            delete[] strr;
        }
        //输出密文
        cout << "*****解密后得到的明文,同时写入CBC_clear.txt：\n";
        for (int i = 0; i < (n / 8); ++i) {
            for (int j = 0; j < 8; ++j) {
                int tmpi = 0, tmpt = 1;
                for (int l = 7; l >= 0; --l) {
                    tmpi += clear[i][j * 8 + l] * tmpt;
                    tmpt <<= 1;
                }
                if (tmpi) {
                    cout << char(tmpi);
                    out2 << char(tmpi);
                }
            }
        }
        cout << "\n";
    }

    //释放内存
    delete[] str_bits, key_bits;
    return 0;
}