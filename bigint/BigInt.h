#include <bits/stdc++.h>
using namespace std;
class BigInt
{
private:
    vector<int> a;
    const int base = 10;
    int sign = 1;

    bool isNull() const;
    void clearNulls();
public:
    BigInt(vector<int>);
    BigInt(int, vector<int>);
    BigInt(int);
    BigInt(size_t);
    BigInt();
    BigInt(string);

    int toInt();
    BigInt abs(BigInt);

    BigInt& operator=(BigInt);
    BigInt& operator=(string);
    BigInt operator+();
    BigInt operator-();
    BigInt operator+(int);
    BigInt operator-(int);
    BigInt operator*(int);
    BigInt operator/(int);
    BigInt operator%(int);
    BigInt operator+(BigInt);
    BigInt operator-(BigInt);
    BigInt operator*(BigInt);

    bool operator>(BigInt);
    bool operator<(BigInt);
    bool operator==(BigInt);
    bool operator!=(BigInt);
    bool operator<=(BigInt);
    bool operator>=(BigInt);

    BigInt operator+=(int);
    BigInt operator+=(BigInt);
    BigInt operator-=(int);
    BigInt operator-=(BigInt);
    BigInt operator*=(int);
    BigInt operator*=(BigInt);
    BigInt operator/=(int);
    BigInt operator%=(int);

	friend ostream& operator<<(ostream &, const BigInt&);
	friend istream& operator>>(istream &, BigInt&);
};
