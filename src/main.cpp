/**
\file
\brief Main file for program execution.
*/

#include "calculate.hpp"

/**
\brief Executes program as many times as user needs.
*/
int main()
{   
    char input;

    calculate();
    
    while (!std::cin.eof()) {
        std::cout << "\nEnter C to continue (E or otherwise to exit): ";
        std::cin >> input;
        
        if (input == 'C' || input == 'c') {
            //Clears stream for proper next usage. 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            calculate();
        } else {
            break;
        } 
    }

    return 0;
}



