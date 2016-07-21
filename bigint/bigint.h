#ifndef _BIGINT_H
#define _BIGINT_H

#include <string>
#include "tvector.h"
using namespace std;

class BigInt
{
  public:
    
    BigInt();                    // default constructor, value = 0
    BigInt(int);                 // assign an integer value
    BigInt(const string &);    // assign a string
    
    BigInt(const BigInt & rhs);
    ~BigInt();
    
    // operators: arithmetic, relational
	const BigInt & BigInt::operator = (const BigInt & rhs);

    const BigInt & operator += (const BigInt &);
    const BigInt & operator -= (const BigInt &);
    const BigInt & operator *= (const BigInt &);
    const BigInt & operator *= (int num);
   
    string   ToString() const;   // convert to string
    int      ToInt()    const;   // convert to int
    double   ToDouble() const;   // convert to double 

    // facilitate operators ==, <, << without friends

    bool Equal(const BigInt & rhs)        const;
    bool LessThan(const BigInt & rhs)     const;

  private:
    
    // other helper functions

    bool IsNegative()  const;    // return true iff number is negative
    bool IsPositive()  const;    // return true iff number is positive
    int  NumDigits()   const;    // return # digits in number
    
    int  GetDigit(int k) const;
    void AddSigDigit(int value);
    void ChangeDigit(int k, int value);
    void Normalize();
    // private state/instance variables

    enum Sign{positive,negative};
    Sign mySign;                // is number positive or negative
    tvector<char> myDigits;     // stores all digits of number
    int myNumDigits;		// stores # of digits of number 
};

// free functions
ostream & operator <<(ostream &, const BigInt &);
istream & operator >>(istream &, BigInt &);

BigInt operator +(const BigInt & lhs, const BigInt & rhs);
BigInt operator -(const BigInt & lhs, const BigInt & rhs);
BigInt operator *(const BigInt & lhs, const BigInt & rhs);
BigInt operator *(const BigInt & lhs, int num);
BigInt operator *(int num, const BigInt & rhs);

bool operator == (const BigInt & lhs, const BigInt & rhs);
bool operator <  (const BigInt & lhs, const BigInt & rhs);
bool operator != (const BigInt & lhs, const BigInt & rhs);
bool operator >  (const BigInt & lhs, const BigInt & rhs);
bool operator >= (const BigInt & lhs, const BigInt & rhs);
bool operator <= (const BigInt & lhs, const BigInt & rhs);

#endif   // _BIGINT_H not defined

