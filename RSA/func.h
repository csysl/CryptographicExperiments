//
// Created by sun on 18-11-13.
//

#ifndef RSA_FUNC_H
#define RSA_FUNC_H

#include <iostream>
#include <random>   //random_device;default_random_engine;uniform_int_distribution;
#include <fstream>  //ofstream;
#include <string>
//#include <climits>
//#include <iomanip>

typedef unsigned long long ll;
using namespace std;

class RSA {
public:
    ll e, n, PubKey[2],*cipher,ciplen;

    RSA() {};
    ~RSA(){
        delete[] this->cipher;
    }

    void init(); //初始化
    void SaveKey();//把秘钥保存到key.txt
    void Encryption(string str);//加密并将密文输出到cipher.txt
    void Decryption(ll *cip,ll clen);//输入密文，并将解密结果输出
    void Decryption();//解密并将解密结果出
    bool CheckD(); //检测d的正确性
    void out() ;//把参数输出
private:
    ll p, q, f, d, kk, PriKey[2];//kk是(ed-1)/f的值
    ll GetRand(ll a, ll b);//产生一个a,b区间的随机数
    ll GetRand();//产生一个随机数
    ll QuickAcc(ll a, ll b);//快速积
    ll QuickAcc(ll a, ll b, ll n);//快速积取模
    ll QuickPower(ll v, ll n, ll m);//快速幂取模
    bool PrimeNumVal(ll n, ll k);//Miller-Rabin素性检测,k是素性检测的次数,取15次
    ll GetPrimeNum(ll a, ll b);//产生a和b区间的素数,用来产生p,q,e
    void GetD();//获取d,k用来取模,值是(ed-1)/m的值
};

#endif //RSA_FUNC_H
