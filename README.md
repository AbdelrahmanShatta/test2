# BigReal Number Implementation

This project implements a BigReal class in C++ for handling arbitrary-precision real numbers. The implementation allows for mathematical operations on real numbers that may be too large or precise for standard floating-point types.

## Files

- [BigReal.h](BigReal.h) - Header file containing the class declaration
- [BigReal.cpp](BigReal.cpp) - Implementation file containing the class methods
- [Main.cpp](Main.cpp) - Example usage and test cases

## Features

- Support for arbitrary-precision real numbers
- Basic arithmetic operations
- String conversion and formatting
- Comparison operations

## Usage

Include the BigReal header in your C++ program:

```cpp
#include "BigReal.h"
```

Create and use BigReal numbers:

```cpp
BigReal num1("123.456");
BigReal num2("789.012");
BigReal result = num1 + num2;
```

## Building

Compile the project using a C++ compiler that supports C++11 or later:

```bash
g++ -std=c++11 Main.cpp BigReal.cpp -o bigreal
```

Run the compiled program:

```bash
./bigreal
```