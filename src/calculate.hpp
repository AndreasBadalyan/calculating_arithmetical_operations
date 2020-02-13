/**
\file
\brief Header file that contains include directives and function prototypes.
*/


#ifndef _CALCULATE_
#define _CALCULATE_


#include <iostream>
#include <limits>
#include <cstdlib>
#include <cctype>

typedef void (*operation_func_ptr) (long, long);
void calculate();
bool isnumber(const std::string &);
operation_func_ptr detect_operation(char);
void sum(long, long);
void subtract(long, long);
void multiply(long, long);
void divide(long, long);
void display_error(long, long);
void display_result(long, long, char, long);
void display(const char *);
bool check_mult_bounds(long, long);

#endif
