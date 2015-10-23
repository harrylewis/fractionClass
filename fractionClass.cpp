/*
 * fractionClass.cpp
 *
 *      Author: Harry Lewis
 *      Implementation for a Fraction Class using overloaded operators for CMPE320 assignment 1.
 */

// dependencies
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
// internal dependencies
#include "fractionClass.h"
// current name space
using namespace std;



// Fraction Exception Methods
// --------------------------


// initialize the message to be outputted
FractionException::FractionException(const string& message) : message(message) {}

// display the message
string& FractionException::what() { return message; }


// Fraction Class Methods
// ----------------------


// no-parameter initializer
Fraction::Fraction() : numer(0), denom(1) {}

// 1 parameter initializer
Fraction::Fraction(int numerator) : numer(numerator), denom(1) {}

// 2 parameter intializer
Fraction::Fraction(int numerator, int denominator) : numer(numerator), denom(denominator) {
    if (denominator == 0) {
        throw FractionException("You cannot have a fraction with a denominator of 0");
    } else {
        int gcf = greatestCommonFactor(abs(denominator), abs(numerator));
        numer = numerator / gcf;
        denom = denominator / gcf;
        if (denominator < 0) {
            denom = abs(denominator/gcf);
            numer = -numerator/gcf;
        }
    }
}

// put in lowest terms
int Fraction::greatestCommonFactor(int m, int n) {
    if (m <= n && (n % m == 0)) {
        return m;
    } else if (n < m) {
        return greatestCommonFactor(n, m);
    } else {
        return greatestCommonFactor(m, n % m);
    }
}

// let's negate
Fraction Fraction::operator - (void) const {
    return Fraction(-numer, denom);
}

// let's add
Fraction operator + (const Fraction& addend, const Fraction& addend2) {
    if (addend2.denom == addend.denom) {
        return Fraction(addend2.numer + addend.numer, addend.denom);
    } else {
        return Fraction(addend2.numer * addend.denom + addend2.denom * addend.numer, addend2.denom * addend.denom);
    }
}

// let's subtract
Fraction operator - (const Fraction& subtractor, const Fraction& subtractor2) {
    if (subtractor2.denom == subtractor.denom) {
        return Fraction(subtractor.numer - subtractor2.numer, subtractor2.denom);
    } else {
        return Fraction(subtractor.numer * subtractor2.denom - subtractor2.numer * subtractor.denom, subtractor2.denom * subtractor.denom);
    }
}

// let's multiply
Fraction operator * (const Fraction& multiplicant, const Fraction& multiplicant2) {
    return Fraction(multiplicant.numer * multiplicant2.numer, multiplicant.denom * multiplicant2.denom);
}

// let's divide
Fraction operator / (const Fraction& dividend, const Fraction& dividend2) {
    return Fraction(dividend.numer * dividend2.denom, dividend.denom * dividend2.numer);
}

// post increment
Fraction Fraction::operator ++ (int unused) {
    Fraction clone(numer, denom);
    numer += denom;
    return clone;
}

Fraction Fraction::operator ++ () {
    numer += denom;
    return *this;
}

// increment assignment
Fraction Fraction::operator += (const Fraction& addend) {
    if (denom == addend.denom)
        numer += addend.numer;
    else {
        numer = numer*addend.denom + addend.numer*denom;
        denom = denom*addend.denom;
    }
    
    return *this;
}

// equality operator
bool Fraction::operator == (const Fraction& equalizer) {
    if (numer == equalizer.numer && denom == equalizer.denom) {
        return true;
    }
    return false;
}

// inequality operator
bool operator != (const Fraction& equalizer, const Fraction& negator) {
    if (equalizer.numer != negator.numer || equalizer.denom != negator.denom)
        return true;
    return false;
}

// greater than operator
bool operator > (const Fraction& greater, const Fraction& lesser) {
    if (greater.denom == lesser.denom) {
        if (greater.numer > lesser.numer)
            return false;
        return true;
    } else {
        if (greater.numer*lesser.denom > lesser.numer*greater.denom)
            return true;
        return false;
    }
}

// greater than or equal to operator
bool Fraction::operator >= (const Fraction& lesseror) {
    if (denom == lesseror.denom) {
        if (numer >= lesseror.numer)
            return false;
        return true;
    } else {
        numer = numer*lesseror.denom;
        if (numer >= lesseror.numer*denom)
            return true;
        return false;
    }
}

// less than operator
bool operator < (const Fraction& lesser, const Fraction& greater) {
    if (lesser.denom == greater.denom) {
        if (lesser.numer < greater.numer)
            return false;
        return true;
    } else {
        if (lesser.numer*greater.denom < greater.numer*lesser.denom)
            return true;
        return false;
    }
}

// less than or equal to operator
bool Fraction::operator <= (const Fraction& greateror) {
    if (denom == greateror.denom) {
        if (numer <= greateror.numer)
            return false;
        return true;
    } else {
        numer = numer*greateror.denom;
        if (numer <= greateror.numer*denom)
            return true;
        return false;
    }
}

// let's put into the stream
ostream& operator << (ostream& os, const Fraction& fraction) {
    os << fraction.numerator() << "/" << fraction.denominator();
    return os;
}

// let's take out of the stream
istream& operator >> (istream& is, Fraction& fraction) {
    string input;
    //Fraction frac;
    int n, d;
    getline(is, input);
    string numerString;
    string denomString;
    
    bool slashFlag(false);
    
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '/')
            slashFlag = true;
    }
    
    //in.find
    if (slashFlag) {
        for(int i = 0; i < input.length(); i++){
            if(input[i] == '/'){
                numerString.append(input.substr(0,i));
                denomString.append(input.substr(i+1,input.length() - 1));
                fraction.numer = atoi(numerString.c_str());
                fraction.denom = atoi(denomString.c_str());
            }
        }
    } else {
        fraction.numer = atoi(input.c_str());
        fraction.denom = 1;
    }
    return is;
}