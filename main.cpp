#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <math.h>
#include <bitset>

using namespace std;

void c()
{
    long long int n;
    cin >> n;
    vector<long long int> odd;
    vector<long long int> even;
    int p = 0;
    for (long long int i = 1; i <= 100000000000; i = i * 2) {
        if(p == 1)
        {
            even.push_back(i);
        }else{
            odd.push_back(i);
        }
        p = (p + 1) % 2;
    }
    ///半分全列挙
    map<long long int, int> oddmap;
    map<long long int, int> evenmap;
    for (unsigned long long int i = 0; i < pow(2, odd.size()); ++i) {
        unsigned long long int check = 1;
        long long int count = 0;
        int index = 0;
        for (;check <= i; check = check << 1) {
            if(i & check)
            {
                ///bitが立っている
                count += odd[index];
            }
            index++;
        }
        if(oddmap.count(count) == 0)
        {
            oddmap[count] = 1;
        }
    }
    for (unsigned long long int i = 0; i < pow(2, even.size()); ++i) {
        unsigned long long int check = 1;
        long long int count = 0;
        int index = 0;
        for (;check <= i; check = check << 1) {
            if(i & check)
            {
                ///bitが立っている
                count += even[index];
            }
            index++;
        }
        if(evenmap.count(count) == 0)
        {
            evenmap[count] = 1;
        }
    }
    long long int plus = 0, minus = 0;
    for (auto o : oddmap) {
        long long int nest = o.first - n;
        if(evenmap.count(nest) > 0)
        {
            plus = o.first;
            minus = nest;
        }
    }
    unsigned long long int result = plus + minus;
    string str = "";
    for (unsigned long long int check = 1; check <= result; check = check << 1) {
        if(check & result)
        {
            str.push_back('1');
        }else{
            str.push_back('0');
        }
    }
    reverse(str.begin(), str.end());
    if(str == "")
    {
        cout << "0" << endl;
    }else{
        cout << str << endl;
    }
}

int main() {
    typedef long long int ll;
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    ///累積和を計算
    vector<ll> asum(n);
    asum[0] = a[0];
    for (int i = 1; i < n; ++i) {
        asum[i] = asum[i - 1] + a[i];
    }
    ///Aj - Ai = cMはAjとAiがmod Mで合同を表す
    ll count = 0;
    map<ll, int> mod;
    for (int i = 0; i < n; ++i) {
        ll temp = asum[i] % m;
        if(mod.count(temp))
        {
            count += mod[temp];
            mod[temp]++;
        }else{
            mod[temp] = 1;
        }
        ///単体でMの倍数の箇所を数える
        if(temp == 0)
        {
            count++;
        }
    }
    cout << count << endl;
    return 0;
}