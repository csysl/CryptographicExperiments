//
// Created by sun on 18-11-28.
//

#include "func.h"

//产生一个a,b区间的随机数
ll ECC::GetRand(ll a, ll b) {
    random_device r;
    default_random_engine e(r());
    uniform_int_distribution<ll> u(a, b);
    ll res = u(e);
    return res;
}

//产生一个随机数
ll ECC::GetRand() {
    random_device r;
    default_random_engine e(r());
    uniform_int_distribution<ll> u;
    ll res = u(e);
    return res;
}

//快速积取模
ll ECC::QuickAcc(ll a, ll b, ll n) {
    ll ans = 0;
    while (b) {
        if (b & 1)
            ans = (ans + a) % n;
        a = (a + a) % n;
        b >>= 1;
    }
    return ans;
}

//快速积
ll ECC::QuickAcc(ll a, ll b) {
    ll ans = 0;
    while (b) {
        if (b & 1)
            ans = ans + a;
        a = a + a;
        b >>= 1;
    }
    return ans;
}

//快速幂
ll ECC::QuickPower(ll v, ll n, ll m) {
    ll ans = 1;
    while (n) {
        if (n & 1)
            ans = QuickAcc(ans, v, m);
        v = QuickAcc(v, v, m);
        n >>= 1;
    }
    return ans;
}

//快速幂
ll ECC::QuickPower(ll v, ll n) {
    ll ans = 1;
    while (n) {
        if (n & 1)
            ans = QuickAcc(ans, v);
        v = QuickAcc(v, v);
        n >>= 1;
    }
    return ans;
}

//Miller-Rabin素性检测
bool ECC::PrimeNumVal(ll n, ll k) {
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
ll ECC::GetPrimeNum(ll a, ll b) {
    TAG:
    ll tmp = GetRand(a, b);
    if (!(tmp & 1))
        goto TAG;
    if (!PrimeNumVal(tmp, 15))
        goto TAG;
    return tmp;
}

//获得a,b,p的值
void ECC::Getabp() {
    a = GetRand(1, 1000);
    p = GetPrimeNum(1e3, 1e4);
    while (1) {
        b = GetRand(1, 1000);
        //4*a^3+27*b^2 (mod p)!=0
        ll tmp = QuickAcc(4, QuickPower(a, 3, p), p) + QuickAcc(27, QuickPower(b, 2, p), p);
        tmp %= p;
        if (tmp != 0)
            break;
    }
}

//求Y^2
ll ECC::GetYY(ll x) {
    ll tmp1 = QuickPower(x, 3, p);
    ll tmp2 = QuickAcc(a, x, p);
    ll tmp = (tmp1 + tmp2) % p;
    ll res = (tmp + b) % p;
    return res;
}

//得到椭圆曲线上的点
void ECC::GetNode() {
    for (ll x = 1; x < p; ++x) {
        ll yy = GetYY(x);
        long double tmp = yy;
        auto y = sqrt(tmp);
        if (y - ll(y) > 1e-8)
            continue;
        node.insert(pair(x, y));
    }
}

//初始化
void ECC::init() {
    Getabp();
    GetNode();
    GetKey();
}

//打印信息
void ECC::PrintInfo() {
    string str = "椭圆曲线为:y^2=x^3+" + to_string(a) + "*x+" + to_string(b) + " mod " + to_string(p);
    cout << str << endl;
    cout << "node_num: " << node.size() << endl;
//    cout<<"prik: "<<prik<<endl;
//    cout<<"pubk: "<<pubk<<endl;
    cout << "公钥: " << G.x << " " << G.y << endl;
    cout << "私钥: " << H.x << " " << H.y << endl;
}

//打印椭圆曲线上的点
void ECC::PrintNode() {
    for (auto &iter:node) {
        cout << iter.first << " " << iter.second << endl;
    }
}

Node ECC::ECCadd(Node n1, Node n2) {
    ll tmpx, tmpy;
    ll k;
    tmpx = n2.x - n1.x;
    tmpy = n2.y - n1.y;
    if (tmpx == 0 && tmpy == 0) {
        ll tmp1 = QuickAcc(2, n1.x, p);
        ll tmp2 = 0;
        for (ll i = 1; i < p; ++i) {
            if (QuickAcc(tmp1, i, p) == 1) {
                tmp2 = i;
                break;
            }
        }
        ll tmp3 = (QuickAcc(QuickPower(n1.y, 2, p), 3, p) + a) % p;
        k = QuickAcc(tmp2, tmp3, p);
    } else {
        if (tmpx > 0 && tmpy > 0) {
            ll tmp2 = 0;
            for (ll i = 1; i < p; ++i) {
                if (QuickAcc(tmpx, i, p) == 1) {
                    tmp2 = i;
                    break;
                }
            }
            k = QuickAcc(tmpy, tmp2, p);
        } else if (tmpx < 0 && tmpy < 0) {
            ll tmp2 = 0;
            for (ll i = 1; i < p; ++i) {
                if (QuickAcc(-tmpx, i, p) == 1) {
                    tmp2 = i;
                    break;
                }
            }
            k = QuickAcc(-tmpy, tmp2, p);
        } else if (tmpx > 0 && tmpy < 0) {
            ll tmp2 = 0;
            for (ll i = 1; i < p; ++i) {
                if (QuickAcc(tmpx, i, p) == 1) {
                    tmp2 = i;
                    break;
                }
            }
            ll tmp3 = p - (-tmpy) % p;
            k = QuickAcc(tmp3, tmp2, p);
        } else if (tmpx < 0 && tmpy > 0) {
            ll tmp2 = 0;
            for (ll i = 1; i < p; ++i) {
                if (QuickAcc(-tmpx, i, p) == 1) {
                    tmp2 = i;
                    break;
                }
            }
            ll tmp3 = p + (-tmpy) % p;
            k = QuickAcc(tmp3, tmp2, p);
        }
    }

    ll kk = k;
    if (k < 0)
        kk = -k;
    Node nn;
    nn.x = (QuickPower(kk, 2) - n1.x - n2.x) % p;
    nn.y = k * (n1.x - nn.x) - n1.y;
    if (nn.y < 0)
        nn.y = p - (-nn.y) % p;
    else
        nn.y = nn.y % p;

    return nn;
}

//产生公钥和私钥
void ECC::GetKey() {
    ll ran = GetRand(0, node.size());
    auto iter = node.begin();
    for (int i = 1; i < ran; ++i)
        ++iter;
    G.x = (*iter).first;
    G.y = (*iter).second;
    prik = GetRand(1e3, 1e4);
    Node tmp = G;
    for (ll i = 0; i < prik; ++i)
        tmp = ECCadd(tmp, G);
    H.x = tmp.x;
    H.y = tmp.y;
}

//加密
void ECC::Encryption(string str) {
    auto len = str.length();
    cipher = new ll[len]();
    C1 = new Node[len]();
    C2 = new Node[len]();
    ciplen = len;
    r = GetRand(1, len);
    for (int i = 0; i < len; ++i) {
        ll tmp = ll(str[i]); //对应tmp点
        cipher[i]=tmp;
        auto iter = node.begin();
        Node tm;
        for (int j = 1; j < tmp; ++j)
            ++iter;
        tm.x = (*iter).first;
        tm.y = (*iter).second;
        //cout<<tm.x<<" "<<tm.y<<endl;
        C1[i] = H;
        for (int j = 0; j < r; ++j)
            C1[i] = ECCadd(C1[i], H);
        C1[i] = ECCadd(C1[i], tm);
        C2[i] = G;
        for (int j = 0; j < r; ++j)
            C2[i] = ECCadd(C2[i], G);
    }
    cout << endl << "**加密成功!" << endl;
}

//解密
void ECC::Decryption() {
    //C1-kC2=M+rK-k(rG)=M+rK-r(kG)=M
    Node tmp;
    tmp = C2[0];

    for (ll j = 0; j < r; ++j) {
        tmp = ECCadd(tmp, C2[0]);
    }
    //cout<<tmp.x<<" "<<tmp.y<<endl;
    tmp.x=p-(-tmp.x)%p;
    tmp.y=p-(-tmp.y)%p;
    ll tag;
    for (ll i = 0; i < ciplen; ++i) {
        Node tmp2;
        tmp2=ECCadd(C1[i],tmp);
        //cout<<tmp2.x<<" "<<tmp2.y<<endl;
        tag=0;
        for(auto iter:node){
            ++tag;
            if(iter.first==tmp2.x&&iter.second==tmp2.y)
                break;
        }
        cout<<char(cipher[i])<<" ";
    }
    cout<<"\n**解密成功！\n";
}