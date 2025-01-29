#include <algorithm>
#include "BigReal.h"

void BigReal::split(std::string realNumber) {
    if (realNumber.find('.') == std::string::npos) {
        integer = realNumber;
        decimal = "0";
    } else {
        integer = realNumber.substr(0, realNumber.find('.'));
        decimal = realNumber.substr(realNumber.find('.') + 1);
    }
}

bool BigReal::isValidReal(std::string realNumber) {
    auto it = realNumber.begin();
    if (*it == '+' || *it == '-') {
        it++;
    }
    bool dot = false;
    while (it != realNumber.end()) {
        if (std::isdigit(*it) || *it == '.') {
            if (*it == '.') {
                if (dot) {
                    return false;
                }
                dot = true;
            }
            it++;
        } else {
            return false;
        }
    }
    return true;
}

BigReal::BigReal() {
    integer = "0";
    decimal = "0";
    sign = 1;
}

BigReal::BigReal(std::string realNumber) {
    if (isValidReal(realNumber)) {
        if (realNumber[0] == '-') {
            sign = -1;
            realNumber.erase(0, 1);
        } else {
            sign = 1;
            if (realNumber[0] == '+') {
                realNumber.erase(0, 1);
            } else if (realNumber[0] == '.') {
                realNumber = '0' + realNumber;
            }
        }
        split(realNumber);
    } else {
        integer = "0";
        decimal = "0";
        sign = 1;
    }
}

BigReal::BigReal(const BigReal& other) {
    integer = other.integer;
    decimal = other.decimal;
    sign = other.sign;
}

BigReal& BigReal::operator=(const BigReal& other) {
    if (this != &other) {
        integer = other.integer;
        decimal = other.decimal;
        sign = other.sign;
    }
    return *this;
}

void BigReal::setNum(std::string realNumber) {
    if (isValidReal(realNumber)) {
        if (realNumber[0] == '-') {
            sign = -1;
            realNumber.erase(0, 1);
        } else {
            sign = 1;
            if (realNumber[0] == '+') {
                realNumber.erase(0, 1);
            } else if (realNumber[0] == '.') {
                realNumber = '0' + realNumber;
            }
        }
        split(realNumber);
    } else {
        integer = "0";
        decimal = "0";
        sign = 1;
    }
}

int BigReal::size() {
    return integer.size() + decimal.size();
}

BigReal& BigReal::add(BigReal& n2) {
    std::string intresult;
    std::string floatresult;
    std::string int2 = n2.integer;
    std::string dec2 = n2.decimal;
    int difference;
    int sum;
    int carry = 0;
    int y;

    // Handle decimal part
    y = std::max(dec2.size(), decimal.size());
    if (y == dec2.size()) {
        difference = dec2.size() - decimal.size();
        std::string zeros(difference, '0');
        decimal = decimal + zeros;
    }
    if (y == decimal.size()) {
        difference = decimal.size() - dec2.size();
        std::string zeros(difference, '0');
        dec2 = dec2 + zeros;
    }

    for (int i = y - 1; i >= 0; i--) {
        sum = ((dec2[i] - '0') + (decimal[i] - '0') + carry) % 10;
        carry = ((dec2[i] - '0') + (decimal[i] - '0') + carry) / 10;
        floatresult = char(sum + '0') + floatresult;
    }

    // Handle integer part
    y = std::max(int2.size(), integer.size());
    if (y == int2.size()) {
        difference = int2.size() - integer.size();
        std::string zeros(difference, '0');
        integer = zeros + integer;
    }
    if (y == integer.size()) {
        difference = integer.size() - int2.size();
        std::string zeros(difference, '0');
        int2 = zeros + int2;
    }

    for (int i = y - 1; i >= 0; i--) {
        sum = ((int2[i] - '0') + (integer[i] - '0') + carry) % 10;
        carry = ((int2[i] - '0') + (integer[i] - '0') + carry) / 10;
        intresult = char(sum + '0') + intresult;
    }

    if (carry == 1) {
        intresult = '1' + intresult;
    }

    n2.integer = intresult;
    n2.decimal = floatresult;
    return n2;
}

BigReal& BigReal::minus(BigReal& n2) {
    std::string intresult;
    std::string floatresult;
    std::string int2 = n2.integer;
    std::string dec2 = n2.decimal;
    int difference;
    int diff;
    int borrow = 0;
    int y;

    // Handle decimal part
    y = std::max(dec2.size(), decimal.size());
    if (y == dec2.size()) {
        difference = dec2.size() - decimal.size();
        std::string zeros(difference, '0');
        decimal = decimal + zeros;
    }
    if (y == decimal.size()) {
        difference = decimal.size() - dec2.size();
        std::string zeros(difference, '0');
        dec2 = dec2 + zeros;
    }

    if (*this > n2) {
        for (int i = y - 1; i >= 0; i--) {
            diff = (decimal[i] - '0') - (dec2[i] - '0') + borrow;
            if (diff < 0) {
                diff += 10;
                borrow = -1;
            } else {
                borrow = 0;
            }
            floatresult = char(diff + '0') + floatresult;
        }
        n2.decimal = floatresult;
    } else {
        for (int i = y - 1; i >= 0; i--) {
            diff = (dec2[i] - '0') - (decimal[i] - '0') + borrow;
            if (diff < 0) {
                diff += 10;
                borrow = -1;
            } else {
                borrow = 0;
            }
            floatresult = char(diff + '0') + floatresult;
        }
        n2.decimal = floatresult;
    }

    // Handle integer part
    y = std::max(int2.size(), integer.size());
    if (y == int2.size()) {
        difference = int2.size() - integer.size();
        std::string zeros(difference, '0');
        integer = zeros + integer;
    }
    if (y == integer.size()) {
        difference = integer.size() - int2.size();
        std::string zeros(difference, '0');
        int2 = zeros + int2;
    }

    if (*this > n2) {
        for (int i = y - 1; i >= 0; i--) {
            diff = (integer[i] - '0') - (int2[i] - '0') + borrow;
            if (diff < 0) {
                diff += 10;
                borrow = -1;
            } else {
                borrow = 0;
            }
            intresult = char(diff + '0') + intresult;
        }
        n2.integer = intresult;
    } else {
        for (int i = y - 1; i >= 0; i--) {
            diff = (int2[i] - '0') - (integer[i] - '0') + borrow;
            if (diff < 0) {
                diff += 10;
                borrow = -1;
            } else {
                borrow = 0;
            }
            intresult = char(diff + '0') + intresult;
        }
        n2.sign = -1;
        n2.integer = intresult;
    }
    return n2;
}

BigReal& BigReal::operator+(BigReal& n2) {
    if (sign == -1 && n2.sign == 1) {
        sign *= -1;
        return n2.minus(*this);
    } else if (sign == 1 && n2.sign == -1) {
        n2.sign *= -1;
        return this->minus(n2);
    } else if (sign == -1 && n2.sign == -1) {
        return this->add(n2);
    } else {
        return this->add(n2);
    }
}

BigReal& BigReal::operator-(BigReal& n2) {
    if (sign == -1 && n2.sign == 1) {
        n2.sign *= -1;
        return this->add(n2);
    } else if (sign == 1 && n2.sign == -1) {
        n2.sign *= -1;
        return this->add(n2);
    } else if (sign == -1 && n2.sign == -1) {
        bool allZeros = true;
        for (char c : integer) {
            if (c != '0') {
                allZeros = false;
                break;
            }
        }
        if (allZeros) {
            for (char c : n2.integer) {
                if (c != '0') {
                    allZeros = false;
                    break;
                }
            }
        }
        if (allZeros) {
            sign = 1;
        }
        return n2.minus(*this);
    } else {
        return this->minus(n2);
    }
}

bool BigReal::operator>(const BigReal& anotherReal) {
    if (sign == 1 && anotherReal.sign == -1) {
        return true;
    }
    if (sign == -1 && anotherReal.sign == 1) {
        return false;
    }
    if (sign == -1 && anotherReal.sign == -1) {
        BigReal a(*this);
        a.sign = 1;
        BigReal b(anotherReal);
        b.sign = 1;
        return (a < b);
    }

    std::string n1 = integer;
    std::string d1 = decimal;
    std::string n2 = anotherReal.integer;
    std::string d2 = anotherReal.decimal;

    // Pad integers with leading zeros
    int maxIntLen = std::max(n1.size(), n2.size());
    n1 = std::string(maxIntLen - n1.size(), '0') + n1;
    n2 = std::string(maxIntLen - n2.size(), '0') + n2;

    // Pad decimals with trailing zeros
    int maxDecLen = std::max(d1.size(), d2.size());
    d1 = d1 + std::string(maxDecLen - d1.size(), '0');
    d2 = d2 + std::string(maxDecLen - d2.size(), '0');

    std::string num1 = n1 + d1;
    std::string num2 = n2 + d2;

    return num1 > num2;
}

bool BigReal::operator<(const BigReal& anotherReal) {
    if (sign == 1 && anotherReal.sign == -1) {
        return false;
    }
    if (sign == -1 && anotherReal.sign == 1) {
        return true;
    }
    if (sign == -1 && anotherReal.sign == -1) {
        BigReal a(*this);
        a.sign = 1;
        BigReal b(anotherReal);
        b.sign = 1;
        return (a > b);
    }

    std::string n1 = integer;
    std::string d1 = decimal;
    std::string n2 = anotherReal.integer;
    std::string d2 = anotherReal.decimal;

    // Pad integers with leading zeros
    int maxIntLen = std::max(n1.size(), n2.size());
    n1 = std::string(maxIntLen - n1.size(), '0') + n1;
    n2 = std::string(maxIntLen - n2.size(), '0') + n2;

    // Pad decimals with trailing zeros
    int maxDecLen = std::max(d1.size(), d2.size());
    d1 = d1 + std::string(maxDecLen - d1.size(), '0');
    d2 = d2 + std::string(maxDecLen - d2.size(), '0');

    std::string num1 = n1 + d1;
    std::string num2 = n2 + d2;

    return num1 < num2;
}

bool BigReal::operator==(const BigReal& anotherReal) {
    return integer == anotherReal.integer && 
           decimal == anotherReal.decimal && 
           sign == anotherReal.sign;
}

std::ostream& operator<<(std::ostream& os, const BigReal& m) {
    if (m.sign == -1) {
        os << "-";
    }
    os << m.integer;
    if (m.decimal != "0") {
        os << "." << m.decimal;
    }
    return os;
}