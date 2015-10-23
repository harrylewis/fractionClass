/*
 * fractionClass.h
 *
 *      Author: Harry Lewis
 *      Definition for a Fraction Class using overloaded operators for CMPE320 assignment 2.
 */

// dependencies
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
// current namespace
using namespace std;

// Fraction Class definition
class Fraction {
    int numer;
    int denom;
public:
    Fraction();
    Fraction(int);
    Fraction(int, int);
    // getters
    int numerator() const { return numer; }
    int denominator() const { return denom; }
    // modifiers
    int greatestCommonFactor(int, int);
    // overloaded binary operators
    Fraction operator - (void) const;
    Fraction operator ++ ();
    Fraction operator ++ (int);
    Fraction operator += (const Fraction&);
    bool operator <= (const Fraction&);
    bool operator == (const Fraction&);
    bool operator >= (const Fraction&);
    
    friend bool operator > (const Fraction&, const Fraction&);
    friend bool operator < (const Fraction&, const Fraction&);
    friend Fraction operator + (const Fraction&, const Fraction&);
    friend Fraction operator - (const Fraction&, const Fraction&);
    friend Fraction operator * (const Fraction&, const Fraction&);
    friend Fraction operator / (const Fraction&, const Fraction&);
    friend bool operator != (const Fraction&, const Fraction&);
    friend istream& operator >> (istream&, Fraction&);
    friend ostream& operator << (ostream&, const Fraction&);
    
};

// Fraction Exception Class definition
class FractionException {
public:
    // init exception with an error message
    FractionException(const string& message);
    // display the error message
    string& what(void);
private:
    // error message stored in 'message'
    string message;
};
