//
// Created by sun on 18-11-28.
//

#ifndef ECC_FUNC_H
#define ECC_FUNC_H

#include <iostream>
#include <random>
#include <string>
#include <algorithm> //to_string
#include <unordered_map>

using namespace std;
typedef long long ll;

struct Node{
    ll x;
    ll y;
};

class ECC{
public:
    ~ECC(){
        delete[] cipher,C1,C2;
    }
    void init();
    void Encryption(string str);//加密并将密文输出到cipher.txt
    void Decryption();//解密并将解密结果出
    void PrintInfo(); //输出a,b,p的值
    void PrintNode();//输出椭圆曲线上的点
    ll r=0;
    Node H,*C1,*C2;  //公钥
    Node ECCadd(Node n1,Node n2);//椭圆曲线上的加
private:
    ll a,b,p=23;  //y^2=x^3+a*x+b
    ll prik=0; //私钥
    Node G;
    ll *cipher,ciplen;
    unordered_multimap<ll,ll> node;  //存放椭圆曲线上的点

    ll GetRand(ll a, ll b);//产生一个a,b区间的随机数
    ll GetRand();//产生一个随机数
    ll QuickAcc(ll a, ll b);//快速积
    ll QuickAcc(ll a, ll b, ll n);//快速积取模
    ll QuickPower(ll v, ll n);//快速幂
    ll QuickPower(ll v, ll n, ll m);//快速幂取模
    bool PrimeNumVal(ll n, ll k);//Miller-Rabin素性检测,k是素性检测的次数,取15次
    ll GetPrimeNum(ll a, ll b);//产生a和b区间的素数,用来产生p
    ll GetYY(ll x);//求Y^2

    void Getabp();//得到a,b,p的值
    void GetNode();//得到椭圆曲线上的点
    void GetKey();//产生公钥和私钥
};

#endif //ECC_FUNC_H
