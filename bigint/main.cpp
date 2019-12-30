#include <bits/stdc++.h>
#include "BigInt.h"
using namespace std;

BigInt::BigInt()
{
    return;
}
BigInt::BigInt(vector<int> _a)
{
    sign = 1;
    a.resize(_a.size());
    for(size_t i = 0; i < a.size(); i++)
        a[i] = _a[i];
}
BigInt::BigInt(int _sign, vector<int> _a)
{
    sign = _sign;
    a.resize(_a.size());
    for(size_t i = 0; i < a.size(); i++)
        a[i] = _a[i];
}
BigInt::BigInt(size_t x)
{
    a.resize(x, 0);
}
BigInt::BigInt(int x)
{
    sign = (x >= 0 ? 1 : -1);
    while(x)
    {
        a.push_back(x % base);
        x /= base;
    }
}
BigInt::BigInt(string x)
{
    sign = (x[0] == '-' ? -1 : 1);
    while(x.size() && x.back() != '-')
    {
        a.push_back(x.back() - '0');
        x.pop_back();
    }
}

int BigInt::toInt()
{
    if(isNull()) return 0;
    int res = 0;
    for(size_t i = a.size() - 1; i >= 0; i--)
    {
        res = res * 10 + a[i];
    }
    res *= sign;
    return res;
}
bool BigInt::isNull() const
{
    return a.size() == 1 && a[0] == 0;
}
void BigInt::clearNulls()
{
    while(a.size() > 1 && a.back() == 0)
        a.pop_back();
}
istream& operator>>(istream &input, BigInt &_a)
{
    _a.a.clear();
    char x;
    input.get(x);
    if(x == '-')
        _a.sign = -1;
    else
    {
        _a.sign = 1;
        _a.a.push_back(x - '0');
    }
    while(input.get(x))
    {
        if(x < '0' || x > '9')
        {
            reverse(_a.a.begin(), _a.a.end());
            return input;
        }
        _a.a.push_back(x - '0');
    }
    return input;
}
ostream& operator<<(ostream &output, const BigInt &_a)
{
    if(_a.sign == -1 && !_a.isNull())
        output << '-';
    for(int i = (int) _a.a.size() - 1; i >= 0; i--)
        output << _a.a[i];
    return output;
}
bool BigInt::operator==(BigInt _a)
{
    if(isNull() && _a.isNull())
        return 1;
    if(sign * _a.sign == -1)
        return 0;
    if(a.size() != _a.a.size())
        return 0;
    for(int i = (int)a.size() - 1; i >= 0; i--)
        if(a[i] != _a.a[i]) return 0;
    return 1;
}
BigInt BigInt::abs(BigInt _a)
{
    return BigInt(1, _a.a);
}
bool BigInt::operator!=(BigInt _a)
{
    return 1 ^ (*this == _a);
}
bool BigInt::operator<(BigInt _a)
{
    int x = 0;
    if(a.size() == 0 && _a.a.size() == 0)
        return 0;
    if(sign == -1 && _a.sign == 1)
        return 1;
    if(sign == 1 && _a.sign == -1)
        return 0;
    if(sign == -1 && _a.sign == -1)
        x = 1;
    if(a.size() != _a.a.size())
        return a.size() < _a.a.size();
    for(int i = (int)a.size() - 1; i >= 0; i--)
        if(a[i] < _a.a[i]) return x ^ 1;
        else if(a[i] > _a.a[i]) return x ^ 0;
    return 0;
}
bool BigInt::operator>=(BigInt _a)
{
    return 1 ^ (*this < _a);
}
bool BigInt::operator>(BigInt _a)
{
    return (*this >= _a) && (*this != _a);
}
bool BigInt::operator<=(BigInt _a)
{
    return 1 ^ (*this > _a);
}
BigInt& BigInt::operator=(BigInt _a)
{
    a.clear();
    a.resize(_a.a.size());
    sign = _a.sign;
    for(size_t i = 0; i < _a.a.size(); i++)
        a[i] = _a.a[i];
    return *this;
}
BigInt& BigInt::operator=(string x)
{
    sign = (x[0] == '-' ? -1 : 1);
    while(x.size() && x.back() != '-')
    {
        a.push_back(x.back() - '0');
        x.pop_back();
    }
    return *this;
}
BigInt BigInt::operator+()
{
    return BigInt(*this);
}
BigInt BigInt::operator-()
{
    return BigInt(-sign, a);
}
BigInt BigInt::operator+(BigInt x)
{
    BigInt res;
    bool carry = 0;
    if(sign == 1 && x.sign == 1)
    {
        res.sign = 1;
        for(size_t i = 0; i < max(a.size(), x.a.size()) || carry; i++)
        {
            res.a.push_back((i < a.size() ? a[i] : 0) + (i < x.a.size() ? x.a[i] : 0) + carry);
            carry = res.a.back() >= base;
            res.a.back() %= base;
        }
    }
    else if(sign == 1 && x.sign == -1)
    {
        if(abs(*this) >= abs(x))
        {
            res.sign = 1;
            for(size_t i = 0; i < a.size() || carry; i++)
            {
                res.a.push_back(a[i] - (i < x.a.size() ? x.a[i] : 0) - carry);
                carry = res.a.back() < 0;
                if(carry)
                    res.a.back() += base;
            }
            res.clearNulls();
        }
        else
            return -(BigInt(1, x.a) - BigInt(1, a));
    }
    else if(sign == -1 && x.sign == 1)
    {
        if(abs(*this) >= abs(x))
            return -(BigInt(1, a) - BigInt(1, x.a));
        else
            return (BigInt(1, x.a) - BigInt(1, a));
    }
    else if(sign == -1 && x.sign == -1)
    {
        return -(BigInt(1, a) + BigInt(1, x.a));
    }
    return res;
}
BigInt BigInt::operator-(BigInt x)
{
    return *this + BigInt(-x.sign, x.a);
}
BigInt BigInt::operator+(int x)
{
    return *this + BigInt(x);
}
BigInt BigInt::operator-(int x)
{
    return *this - BigInt(x);
}
BigInt BigInt::operator+=(int x)
{
    *this = *this + BigInt(x);
    return *this;
}
BigInt BigInt::operator+=(BigInt _a)
{
    *this = *this + _a;
    return *this;
}
BigInt BigInt::operator-=(int x)
{
    *this = *this - BigInt(x);
    return *this;
}
BigInt BigInt::operator-=(BigInt _a)
{
    *this = *this - _a;
    return *this;
}
BigInt BigInt::operator*(BigInt _a)
{
    BigInt res((size_t)(a.size() + _a.a.size() + 1));
    res.sign = sign * _a.sign;
    for(size_t i = 0; i < res.a.size(); i++)
        res.a[i] = 0;
    for(size_t i = 0; i < a.size(); i++)
    {
        for(size_t j = 0; j < _a.a.size(); j++)
        {
            res.a[i + j] = res.a[i + j] + a[i] * 1ll * _a.a[j];
        }
    }
    for(size_t i = 0; i < res.a.size(); i++)
    {
        if(res.a[i] > base)
        {
            res.a[i + 1] += res.a[i] / base;
            res.a[i] %= base;
        }
    }
    res.clearNulls();
    return res;
}
BigInt BigInt::operator*(int x)
{
    return *this * BigInt(x);
}
BigInt BigInt::operator*=(BigInt x)
{
    *this = *this * x;
    return *this;
}
BigInt BigInt::operator*=(int x)
{
    *this *= BigInt(x);
    return *this;
}
BigInt BigInt::operator/(int x)
{
    if(x == 0)
        throw "Division by zero";
    BigInt res(a.size());
    int carry = 0;
    for(int i = (int)a.size() - 1; i >= 0; i--)
    {
        long long cur = a[i] + carry * 1ll * base;
        res.a[i] = int(cur / x);
        carry = int(cur % x);
    }
    res.clearNulls();
    return res;
}
BigInt BigInt::operator/=(int x)
{
    *this = *this / x;
    return *this;
}
BigInt BigInt::operator%(int x)
{
    if(x == 0)
        throw "Division by zero";
    BigInt res(a.size());
    int carry = 0;
    for(int i = (int)a.size() - 1; i >= 0; i--)
    {
        long long cur = a[i] + carry * 1ll * base;
        res.a[i] = int(cur / x);
        carry = int(cur % x);
    }
    res.clearNulls();
    return BigInt(carry);
}
BigInt BigInt::operator%=(int x)
{
    *this = *this % x;
    return *this;
}
int main()
{
    BitInt a, b;
    cin >> a >> b;
    return 0;
}
