#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "infi.h"

/**  A variable that marks a valid value     */
const int VALID = 0;
/**  A variable that marks an invalid value     */
const int INVALID = -1;

/**  The locations of the various parameters in the input set    */
const int LOC_OF_FUNC = 1;
const int LOC_OF_A = 2;
const int LOC_OF_B = 3;
const int LOC_OF_N = 4;
const int LOC_OF_X0 = 5;
const int LOC_OF_H = 6;

/**    The number of functions given   */
const int NUM_OF_FUNC = 6;
/**    The number of parameters received as input   */
const int NUM_OF_PARM = 7;

/** Message - Invalid inputt   */
const char *INVALID_INPUT_MSG = "Invalid input\n";

/** Message - The number of parameters is incorrect   */
const char *NUM_OF_PARM_MSG = "Usage: NumericalAnalyzer <function number> <a> <b> <N> <x0> <h>\n";

/**   A character that indicates the end of a string    */
const char END_STR = '\0';

/**
 * @brief Given function number 1
 * @param x Variable to calculate the function
 * @return The result of the function
 */
double func1(double x)
{
    return ((pow(x, 2)) / 4);
}

/**
 * @brief Given function number 2
 * @param x Variable to calculate the function
 * @return The result of the function
 */
double func2(double x)
{
    return ((-pow(x, 3) + 3 * pow(x, 2) + x - 4 * sqrt(x)) / (2 * x * sqrt(x)));
}

/**
 * @brief Given function number 3
 * @param x Variable to calculate the function
 * @return The result of the function
 */
double func3(double x)
{
    return (pow(sin(x), 2) - pow(cos(x), 2));
}

/**
 * @brief Given function number 4
 * @param x Variable to calculate the function
 * @return The result of the function
 */
double func4(double x)
{
    return sin(x) / (1 + cos(2 * x));
}

/**
 * @brief Given function number 5
 * @param x Variable to calculate the function
 * @return The result of the function
 */
double func5(double x)
{
    return exp(x);
}

/**
 * @brief Given function number 6
 * @param x Variable to calculate the function
 * @return The result of the function
 */
double func6(double x)
{
    return sinh(2 * x) / (M_E * pow(x, 2));
}

/**
 * @brief const array of all given functions
 */
const RealFunction allFunc[] = {func1, func2, func3, func4, func5, func6};

/**
 * @brief A function that reads and checks the legality of a Double number
 * @param string A string containing a number
 * @param num Variable to get the number
 * @return 0 with the number valid, -1 otherwise
 */
int readDoubleNum(const char *string, double *num)
{
    char *end = NULL;
    *num = strtod(string, &end); // get number
    /*  Check that the number is valid  */
    if (*end != END_STR)
    {
        return INVALID;
    }
    return VALID;
}

/**
 * @brief A function that reads and checks a positive integer from a string
 * @param string A string containing a number
 * @return A number with everything is valid, -1 otherwise
 */
int readInt(const char *string)
{
    char *end = NULL;
    double number;
    number = strtod(string, &end); // get number
    /*  Check that the number is valid  */
    if ((*end != END_STR) || ((double) (int) number != number) || (number <= VALID))
    {
        return INVALID;
    }
    return (int) number;
}

/**
 * @brief Main function
 * @param Number of parameters
 * @param argv An array of parameters
 * @return 0 With everything passed legally, 1 otherwise
 */
int main(int argc, char *argv[])
{

    if (argc != NUM_OF_PARM) // Checking the number of arguments
    {
        fprintf(stderr, "%s", NUM_OF_PARM_MSG);
        return EXIT_FAILURE;
    }

    int frucNum1, n4;
    double a2, b3, x_05, h6;

    // Accept and check all  parameters
    if (((frucNum1 = readInt(argv[LOC_OF_FUNC])) <= VALID) ||
        (frucNum1 > NUM_OF_FUNC) ||
        ((n4 = readInt(argv[LOC_OF_N])) < VALID) ||
        (readDoubleNum(argv[LOC_OF_A], &a2) < VALID) ||
        (readDoubleNum(argv[LOC_OF_B], &b3) < VALID) ||
        (readDoubleNum(argv[LOC_OF_X0], &x_05) < VALID) ||
        (readDoubleNum(argv[LOC_OF_H], &h6) < VALID) ||
        (a2 >= b3))
    {
        fprintf(stderr, "%s", INVALID_INPUT_MSG);
        return EXIT_FAILURE;
    }

    //Testing the values in the definition field
    if (isnan(allFunc[frucNum1 - 1](x_05 + h6)) ||
        isnan(allFunc[frucNum1 - 1](x_05 - h6)))
    {
        fprintf(stderr, "%s", INVALID_INPUT_MSG);
        return EXIT_FAILURE;
    }
    double interRes = integration(allFunc[frucNum1 - 1], a2, b3, n4);
    double derRes = derivative(allFunc[frucNum1 - 1], x_05, h6);

    // Check that the results are valid
    if (isnan(interRes) || isnan(derRes))
    {
        fprintf(stderr, "%s", INVALID_INPUT_MSG);
        return EXIT_FAILURE;
    }

    // Print results
    printf("Integral: %0.5f\n", interRes);
    printf("Derivative: %0.5f\n", derRes);

    return EXIT_SUCCESS;
}
