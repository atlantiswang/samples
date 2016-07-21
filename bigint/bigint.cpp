#include "stdafx.h"
#include "bigint.h"
#include <iostream>
using namespace std;

const int BASE = 10;

BigInt::BigInt()
   : mySign(positive),
     myDigits(1,'0'),
     myNumDigits(1)
{
	// all fields initialized in initializer list
#ifdef DEBUG    
        cout << "default constructor called" << endl;
#endif	
}

BigInt::BigInt(const BigInt & rhs)
    : mySign(rhs.mySign),
      myDigits(rhs.myDigits),
      myNumDigits(rhs.myNumDigits)
{
#ifdef DEBUG    
    cout << "copy constructor called with " << rhs << endl;
#endif    
}

BigInt::~BigInt()
{
#ifdef DEBUG
    cout << "destructor called for " << *this << endl;
#endif

}

const BigInt & BigInt::operator = (const BigInt & rhs)
{
#ifdef DEBUG
	cout << "assignment operator called with " << rhs << endl;
#endif

	mySign = rhs.mySign;
	myNumDigits = rhs.myNumDigits;
	myDigits = rhs.myDigits;
	return *this;
}



BigInt::BigInt(int num)
   : mySign(positive),
     myDigits(1,'0'),
     myNumDigits(0)
{
    // check if num is negative, change state and num accordingly

   unsigned int copy;   // use this to avoid problems with INT_MIN != -INT_MAX
 
#ifdef DEBUG    
    cout << "int constructor called  " << num << endl;
#endif   
    if (num < 0)
    {   mySign = negative;
        if (num == INT_MIN)
        {   copy = unsigned(INT_MAX) + 1;
        }
        else
        {   copy = -1 * num;
        }
    }
    else
    {   copy = num;
    }

    // handle least-significant digit of num (handles num == 0)

    AddSigDigit(copy % BASE);
    copy = copy / BASE;

    // handle remaining digits of num

    while (copy != 0)
    {   AddSigDigit(copy % BASE);
        copy = copy / BASE;
    }
}


BigInt::BigInt(const string & s)
  : mySign(positive),
    myDigits(s.length(),'0'),
    myNumDigits(0)
{
    int k;
    int limit = 0;

#ifdef DEBUG    
    cout << "string constructor called s = " << s << endl;
#endif   

    if (s.length() == 0)
    {   myDigits.resize(1);
        AddSigDigit(0);
        return;
    }
    if (s[0] == '-')
    {   mySign = negative;
        limit = 1;
    }
    if (s[0] == '+')
    {   limit = 1;
    }
    // start at least significant digit

    for(k=s.length() - 1; k >= limit; k--)
    {   if (! isdigit(s[k]))
        {   cerr << "badly formed BigInt value = " << s << endl;
            abort();
        }
        AddSigDigit(s[k]-'0');
    }
    Normalize();
}


const BigInt & BigInt::operator -=(const BigInt & rhs)
{
    int diff;
    int borrow = 0;

    int k;
    int len = NumDigits();

    if (this == &rhs)         // subtracting self?
    {
        *this = 0;
        return *this;
    }

    // signs opposite? then lhs - (-rhs) = lhs + rhs

    if (IsNegative() != rhs.IsNegative())
    {
        *this +=(-1 * rhs);
        return *this;
    }
    // signs are the same, check which number is larger
    // and switch to get larger number "on top" if necessary
    // since sign can change when subtracting
    // examples: 7 - 3 no sign change,     3 - 7 sign changes
    //          -7 - (-3) no sign change, -3 -(-7) sign changes
    if ((IsPositive() && (*this) < rhs) ||
        (IsNegative() && (*this) > rhs))
    {
        *this = rhs - *this;
        if (IsPositive()) mySign = negative;
        else              mySign = positive;   // toggle sign
        return *this;
    }
    // same sign and larger number on top

    for(k=0; k < len; k++)
    {
        diff = GetDigit(k) - rhs.GetDigit(k) - borrow;
        borrow = 0;
        if (diff < 0)
        {   diff += BASE;
            borrow = 1;
        }
        ChangeDigit(k,diff);
    }
    Normalize();
    return *this;
}

const BigInt & BigInt::operator +=(const BigInt & rhs)
{

    int sum;
    int carry = 0;

    int k;
    int len = NumDigits();         // length of larger addend

    if (this == &rhs)              // to add self, multiply by 2
    {
      *this *= 2;
      return *this;
    }

    if (rhs == 0)                   // zero is special case
    {
   return *this;
    }

    if (IsPositive() != rhs.IsPositive())    // signs not the same, subtract
    {
        *this -= (-1 * rhs);
        return *this;
    }

    // process both numbers until one is exhausted

    if (len < rhs.NumDigits())
    {
        len = rhs.NumDigits();
    }
    for(k=0; k < len; k++)
    {
        sum = GetDigit(k) + rhs.GetDigit(k) + carry;
        carry = sum / BASE;
        sum = sum % BASE;

        if (k < myNumDigits)
        {
            ChangeDigit(k,sum);
        }
        else
        {
            AddSigDigit(sum);
        }
    }
    if (carry != 0)
    {
        AddSigDigit(carry);
    }
    return *this;
}

BigInt operator +(const BigInt & lhs, const BigInt & rhs)
{
    BigInt result(lhs);
    result += rhs;
    return result;
}

BigInt operator -(const BigInt & lhs, const BigInt & rhs)
{
    BigInt result(lhs);
    result -= rhs;
    return result;
}

string BigInt::ToString() const
{
    int k;
    int len = NumDigits();
    string s = "";

    if (IsNegative())
    {
        s = '-';
    }
    for(k=len-1; k >= 0; k--)
    {
        s += char('0'+GetDigit(k));
    }
    return s;
}

int BigInt::ToInt() const
{
    int result = 0;
    int k;
    if (INT_MAX < *this) return INT_MAX;
    if (*this < INT_MIN) return INT_MIN;

    for(k=NumDigits()-1; k >= 0; k--)
    {
        result = result * BASE + GetDigit(k);
    }
    if (IsNegative())
    {
        result *= -1;
    }
    return result;
}

double BigInt::ToDouble() const
{
    double result = 0.0;
    int k;
    for(k=NumDigits()-1; k >= 0; k--)
    {
        result = result * BASE + GetDigit(k);
    }
    if (IsNegative())
    {
        result *= -1;
    }
    return result;
}

ostream & operator <<(ostream & out, const BigInt & big)
{
    out << big.ToString();
    return out;
}

istream & operator >> (istream & in, BigInt & big)
{
    string s;
    in >> s;
    big = BigInt(s);
    return in;
}

bool operator == (const BigInt & lhs, const BigInt & rhs)
{
    return lhs.Equal(rhs);
}

bool BigInt::Equal(const BigInt & rhs) const
{

    if (NumDigits() != rhs.NumDigits() || IsNegative() != rhs.IsNegative())
    {
        return false;
    }
    // assert: same sign, same number of digits;

    int k;
    int len = NumDigits();
    for(k=0; k < len; k++)
    {
        if (GetDigit(k) != rhs.GetDigit(k)) return false;
    }

    return true;
}

bool operator != (const BigInt & lhs, const BigInt & rhs)
{
    return ! (lhs == rhs);
}

bool operator < (const BigInt & lhs, const BigInt & rhs)
{
    return lhs.LessThan(rhs);
}

bool BigInt::LessThan(const BigInt & rhs) const
{
    // if signs aren't equal, self < rhs only if self is negative

    if (IsNegative() != rhs.IsNegative())
    {
        return IsNegative();
    }

    // if # digits aren't the same must check # digits and sign

    if (NumDigits() != rhs.NumDigits())
    {
        return (NumDigits() < rhs.NumDigits() && IsPositive()) ||
               (NumDigits() > rhs.NumDigits() && IsNegative());
    }

    // assert: # digits same, signs the same

    int k;
    int len = NumDigits();

    for(k=len-1; k >= 0; k--)
    {
        if (GetDigit(k) < rhs.GetDigit(k)) return IsPositive();
        if (GetDigit(k) > rhs.GetDigit(k)) return IsNegative();
    }
    return false;      // self == rhs
}

bool operator > (const BigInt & lhs, const BigInt & rhs)
{
    return rhs < lhs;
}

bool operator <= (const BigInt & lhs, const BigInt & rhs)
{
    return lhs == rhs || lhs < rhs;
}
bool operator >= (const BigInt & lhs, const BigInt & rhs)
{
    return lhs == rhs || lhs > rhs;
}

void BigInt::Normalize()
{
    int k;
    int len = NumDigits();
    for(k=len-1; k >= 0; k--)        // find a non-zero digit
    {
        if (GetDigit(k) != 0) break;
        myNumDigits--;               // "chop" off zeros
    }
    if (k < 0)    // all zeros
    {
        myNumDigits = 1;
        mySign = positive;
    }
}

const BigInt & BigInt::operator *=(int num)
{
    int carry = 0;
    int product;               // product of num and one digit + carry
    int k;
    int len = NumDigits();

    if (0 == num)              // treat zero as special case and stop
    {
        *this = 0;
        return *this;
    }

    if (BASE < num|| num < 0)        // handle pre-condition failure
    {
        *this *= BigInt(num);
        return *this;
    }

    if (1 == num)              // treat one as special case, no work
    {
        return *this;
    }

    for(k=0; k < len; k++)     // once for each digit
    {
        product = num * GetDigit(k) + carry;
        carry = product/BASE;
        ChangeDigit(k,product % BASE);
    }

    while (carry != 0)         // carry all digits
    {
        AddSigDigit(carry % BASE);
        carry /= BASE;
    }
    return *this;
}


BigInt operator *(const BigInt & a, int num)
{
    BigInt result(a);
    result *= num;
    return result;
}

BigInt operator *(int num, const BigInt & a)
{
    BigInt result(a);
    result *= num;
    return result;
}


const BigInt & BigInt::operator *=(const BigInt & rhs)
{
    // uses standard "grade school method" for multiplying

   if (IsNegative() != rhs.IsNegative())
   {
      mySign = negative;
   }
   else
   {
      mySign = positive;
   }

    BigInt self(*this);                        // copy of self
    BigInt sum(0);                             // to accumulate sum
    int k;
    int len = rhs.NumDigits();                 // # digits in multiplier

    for(k=0; k < len; k++)
    {
       sum += self * rhs.GetDigit(k);          // k-th digit * self
       self *= BASE;                           // add a zero
    }
    *this = sum;
    return *this;
}

BigInt operator *(const BigInt & lhs, const BigInt & rhs)
{
    BigInt result(lhs);
    result *= rhs;
    return result;
}



int BigInt::NumDigits() const
{
    return myNumDigits;
}

int BigInt::GetDigit(int k) const
{
    if (0 <= k && k < NumDigits())
    {
        return myDigits[k] - '0';
    }
    return 0;
}

void BigInt::ChangeDigit(int k, int value)
{
    if (0 <= k && k < NumDigits())
    {
        myDigits[k] = char('0' + value);
    }
    else
    {
        cerr << "error changeDigit " << k << " " << myNumDigits << endl;
    }
}

void BigInt::AddSigDigit(int value)
{
    if (myNumDigits >= myDigits.length())
    {
        myDigits.resize(myDigits.length() * 2);
    }
    myDigits[myNumDigits] = char('0' + value);
    myNumDigits++;
}

bool BigInt::IsNegative() const
{
   return mySign == negative;
}

bool BigInt::IsPositive() const
{
   return mySign == positive;
}
