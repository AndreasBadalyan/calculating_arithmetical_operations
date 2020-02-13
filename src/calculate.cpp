/**
\file 
\brief Source file that contains program functions.
*/

#include "calculate.hpp"

/**
Displays given message to the screen.
\param message Text to be displayed.
*/
void display(const char * message)
{
   std::cout << message << std::endl;
}

/**
Contains main logic of the program. 
Accepts user input statement and displays calculated result. 
*/
void calculate()
{
    std::string component;
    long operand1 = 0;
    long operand2 = 0;
    operation_func_ptr operation;

    while (!std::cin.eof()) {      
        display("Enter one arithmetical expression in this format:\n"
                "integer1 operation integer2\nwhere operation is one of +, -, /, *");
        std::cin >> component;

        if (!isnumber(component)) {
            continue;
        }
        operand1 = std::atol(component.c_str());
        std::cin >> component;
        
        if (component.length() != 1) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        operation = detect_operation(component[0]);
        std::cin >> component;

        if (!isnumber(component)) {
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        operand2 = std::atol(component.c_str());
        (*operation)(operand1, operand2);
        break;
    }
}

/**
Checks if given argument is a string representation of a number.
\param str_number String to be validated.
\return Either given argument is a number.
*/
bool isnumber(const std::string &str_number)
{
    int length = str_number.length();

    if (!(std::isdigit(str_number[0]) || str_number[0] == '-' && length != 1)) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    for (int i = 1; i < length; ++i) {
        
        if (!std::isdigit(str_number[i])) {   
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
    }
    return true;
}

/**
Detects and validates given operation symbol.
\param operation Operation symbol to be validated.
\return Pointer to the operation function or error function.
*/
operation_func_ptr detect_operation(char operation)
{
    long value = operation;

    switch (value) {

        case '+':
            return sum;

        case '-':
            return subtract;
        
        case '*': 
            return multiply;

        case '/':
            return divide;
    
        default:
            return display_error;
    }
}

/**
Calculates and displays the sum of two numbers.
\param op1, op2 Numbers to sum.
*/
void sum(long op1, long op2)
{
    long limit_max = std::numeric_limits<long>::max(); 
    long limit_min = std::numeric_limits<long>::min();

    if (op1 > 0 && op2 > 0 && limit_max - op1 < op2 || op1 < 0 && op2 < 0 && limit_min + op1 > op2) {
        display("The sum of operands is out of range.");
    } else {
        display_result(op1, op2, '+', op1 + op2);
    }
}

/**
Subtracts second number from the first one and displays the result.
\param op1, op2 Numbers to be subtracted from each other.
*/
void subtract(long op1, long op2)
{
    long limit_max = std::numeric_limits<long>::max(); 
    long limit_min = std::numeric_limits<long>::min();

    if (op1 > 0 && op2 < 0 && limit_max + op2 < op1 || op1 < 0 && op2 > 0 && limit_min + op1 < op2) {
        display("The subtraction result is out of range.");
    } else {
        display_result(op1, op2, '-', op1 - op2);
    }
}

/**
Multiplies two numbers and displays the result.
\param op1, op2 Numbers to multiply.
*/
void multiply(long op1, long op2)
{
    if (check_mult_bounds(op1, op2)) {
        display("The multiplication result is out of range.");
    } else {
        display_result(op1, op2, '*', op1 * op2);
    }
}

/**
Divides first number by the second one and displays the result.
\param op1, op2 Numbers to be divided.
*/
void divide(long op1, long op2)
{
    if (op2) {
        double value = static_cast<double>(op1);
        std::cout << op1 << " / " << op2 << " = " << value / op2 << std::endl;
    } else {
        std::cout << "Zero division error!" << std::endl;
    }
}

/**
Displays result of arithmetic operation on the screen.
\param op1, op2 Arithmetic operation operands.
\param operation Arithmetic operation.
\param result Result of arithmetic operation.
*/
void display_result(long op1, long op2, char operation, long result)
{
    std::cout << op1 << ' ' << operation << ' ' << op2 
              << " = " << result << std::endl;
}

/**
Displays an error on the screen.
*/
void display_error(long op1, long op2)
{
    std::cout << "Invalid operator!" << std::endl;
}

/**
Checks if multiplication result will be in accepted limits.
\param op1, op2 Numbers to be multiplied.
\return Either result is inside the limits or not.
*/
bool check_mult_bounds(long op1, long op2)
{
    long limit_max = std::numeric_limits<long>::max(); 
    long limit_min = std::numeric_limits<long>::min();

    if (op1 > 0 && op2 > 0 && limit_max / op1 < op2 || op1 < 0 && op2 < 0 && limit_max / op1 > op2) {
        return true;
    } else if (op1 > 0 && op2 < 0 && limit_min / op1 > op2 || op1 < 0 && op2 > 0 && limit_min / op1 < op2) {
        return true;
    }
    return false;
}

