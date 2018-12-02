//
// Created by sun on 18-11-13.
//
#include "func.h"

int main() {
    string str;
    RSA rsa;
    rsa.init();//初始化
    rsa.SaveKey();//把秘钥保存到txt
    cout<<"密钥已保存！\n";
    if(rsa.CheckD()){
        cout<<"请输入要加密的明文，可以是任意长度！\n";
        getline(cin,str);
        cout<<"加密结果，同时结果保存在cipher.txt中:\n";
        rsa.Encryption(str);//加密并写入txt
        cout<<"解密结果:\n";
        rsa.Decryption();//解密
    }
    return 0;
}