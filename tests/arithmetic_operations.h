#ifndef ARITHMETIC_OPERATIONS_H
#define ARITHMETIC_OPERATIONS_H

#include "../include/dataset.h"

// Define constants for the number of inputs and outputs for each data row.
#define NUM_INPUTS 2
#define NUM_OUTPUTS 1

/**
 * Generates a random integer within a specified range.
 *
 * @param int min
 *   The minimum value of the generated integer.
 *
 * @param int max
 *   The maximum value of the generated integer.
 *
 * @return int
 *   A randomly generated integer within the specified range [min, max].
 */
int random_generate_integer(int min, int max);

/**
 * Function to create a data row with random integer values and their sum.
 *
 * @param int min
 *   The minimum integer value for the random numbers.
 *
 * @param int max
 *   The maximum integer value for the random numbers.
 *
 * @return struct data_row*
 *   A pointer to the newly created data row, otherwise NULL.
 */
struct data_row *random_generate_addition_row(int min, int max);

/**
 * Function to generate a dataset with random data.
 *
 * This function creates a dataset with rows containing random integer values
 * and their sums. Each row's input consists of random integers, and the output
 * is the sum of these integers.
 *
 * @param int count
 *   The number of additions (rows) to generate.
 *
 * @param int min
 *   The minimum value for the random integers.
 *
 * @param int max
 *   The maximum value for the random integers.
 *
 * @return struct dataset*
 *   A pointer to the generated `dataset` structure, otherwise NULL.
 */
struct dataset *random_generate_additions(int count, int min, int max);

#endif // ARITHMETIC_OPERATIONS_H
