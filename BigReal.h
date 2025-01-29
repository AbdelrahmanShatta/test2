#ifndef BIGREAL_H
#define BIGREAL_H

#include <string>
#include <iostream>

class BigReal {
public:
    class InvalidNumberException : public std::exception {
        std::string msg;
    public:
        InvalidNumberException(const std::string& message) : msg(message) {}
        const char* what() const noexcept override { return msg.c_str(); }
    };

protected:  
    std::string integer;
    std::string decimal;
    int sign;
    void split(const std::string& realNumber);

public:
    bool isValidReal(std::string realNumber);
    BigReal();
    BigReal(std::string realNumber);
    BigReal(const BigReal& other);
    BigReal& operator=(const BigReal& other);
    void setNum(std::string realNumber);
    int size();
    BigReal& add(BigReal& n2);
    BigReal& minus(BigReal& n2);
    BigReal& operator+(BigReal& n2);
    BigReal& operator-(BigReal& n2);
    bool operator>(const BigReal& anotherReal);
    bool operator<(const BigReal& anotherReal);
    bool operator==(const BigReal& anotherReal);
    friend std::ostream& operator<<(std::ostream& os, const BigReal& m);
};

#endif