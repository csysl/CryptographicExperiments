#include "func.h"

int main() {
    ECC ecc;
    ecc.init();
    ecc.PrintInfo();
    //ecc.PrintNode();

    string str;
    cout<<"请输入要加密的明文，可以是任意长度！\n";
    getline(cin,str);
    ecc.Encryption(str);//加密并写入txt
    cout<<"解密结果:\n";
    ecc.Decryption();//解密

    return 0;
}