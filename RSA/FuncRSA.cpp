//
// Created by sun on 18-11-13.
//
#include "func.h"

//产生一个a,b区间的随机数
ll RSA::GetRand(ll a, ll b) {
    random_device r;
    default_random_engine e(r());
    uniform_int_distribution<ll> u(a, b);
    ll res = u(e);
    return res;
}

//产生一个随机数
ll RSA::GetRand() {
    random_device r;
    default_random_engine e(r());
    uniform_int_distribution<ll> u;
    ll res = u(e);
    return res;
}

//快速积
ll RSA::QuickAcc(ll a, ll b) {
    ll ans = 0;
    while (b) {
        if (b & 1)
            ans = ans + a;
        a = a + a;
        b >>= 1;
    }
    return ans;
}

//快速积取模
ll RSA::QuickAcc(ll a, ll b, ll n) {
    ll ans = 0;
    while (b) {
        if (b & 1)
            ans = (ans + a) % n;
        a = (a + a) % n;
        b >>= 1;
    }
    return ans;
}

//快速幂
ll RSA::QuickPower(ll v, ll n, ll m) {
    ll ans = 1;
    while (n) {
        if (n & 1)
            ans = QuickAcc(ans, v, m);
        v = QuickAcc(v, v, m);
        n >>= 1;
    }
    return ans;
}

//Miller-Rabin素性检测
bool RSA::PrimeNumVal(ll n, ll k) {
    ll i, j, a, x, y, t, u;
    if (n == 2)
        return true;
    if (n < 2 || !(n & 1))
        return false;
    for (t = 0, u = n - 1; !(u & 1); t++, u >>= 1);//n-1=u*2^t
    for (i = 0; i < k; i++) {
        a = GetRand() % (n - 1) + 1;
        x = QuickPower(a, u, n);
        for (j = 0; j < t; j++) {
            y = QuickAcc(x, x, n);
            if (y == 1 && x != 1 && x != n - 1)
                return false;
            x = y;
        }
        if (x != 1)
            return false;
    }
    return true;
}

//产生素数
ll RSA::GetPrimeNum(ll a, ll b) {
    TAG:
    ll tmp = GetRand(a, b);
    if (!(tmp & 1))
        goto TAG;
    if (!PrimeNumVal(tmp, 15))
        goto TAG;
    return tmp;
}

//获取d,kk是求模对象，kk是(ed-1)/f的值
void RSA::GetD() {
    kk = 0;
    while (1) {
        ++kk;
        ll tmp = QuickAcc(f, kk) + 1;
        d = tmp / e;
        if (QuickAcc(e, d) == tmp)
            break;
    }
}
//初始化
void RSA::init() {
    p = GetPrimeNum(1e4, 1e5);
    q = GetPrimeNum(1e4, 1e5);
    n = QuickAcc(p, q);
    f = QuickAcc(p - 1, q - 1);
    e = GetPrimeNum(2, 10000);
    GetD();
    PubKey[0]=e;PubKey[1]=n;
    PriKey[0]=d;PriKey[1]=n;
};
//把秘钥保存到key.txt
void RSA::SaveKey(){
    ofstream outkey("../key.txt");
    outkey<<PubKey[0]<<" "<<PubKey[1]<<endl;
    outkey<<PriKey[0]<<" "<<PriKey[1];
    outkey.close();
}
//加密并将密文输出到cipher.txt
void RSA::Encryption(string str){
    ofstream outcipher("../cipher.txt");
    auto len=str.length();
    cipher=new ll[len]();
    ciplen=len;
    for(int i=0;i<len;++i){
        ll tmp=ll(str[i]);
        cipher[i]=QuickPower(tmp,PubKey[0],PubKey[1]);
        cout<<cipher[i]<<" ";
        outcipher<<cipher[i]<<" ";
    }
    cout<<endl<<"**加密成功!"<<endl;
}
//输入密文，并将解密结果输出
void RSA::Decryption(ll *cip,ll clen){
    for(int i=0;i<clen;++i){
        ll tmp=QuickPower(cip[i],PriKey[0],PriKey[1]);
        //cout<<tmp<<" ";
        cout<<char(tmp);
    }
    cout<<endl<<"**解密成功!"<<endl;
}
//解密并将解密结果出
void RSA::Decryption(){
    for(int i=0;i<ciplen;++i){
        ll tmp=QuickPower(cipher[i],PriKey[0],PriKey[1]);
        //cout<<tmp<<" ";
        cout<<char(tmp);
    }
    cout<<endl<<"**解密成功!"<<endl;
}
//检测d的正确性
bool RSA::CheckD() {
    ll tmp1 = QuickAcc(d, e);
    ll tmp2 = QuickAcc(kk, f) + 1;
    if (tmp1 == tmp2)
        return true;
    return false;
}
//把参数输出
void RSA::out() {
    cout << "p:" << p << "\n";
    cout << "q:" << q << "\n";
    cout << "n:" << n << "\n";
    cout << "f:" << f << "\n";
    cout << "e:" << e << "\n";
    cout << "d:" << d << "\n";
};
