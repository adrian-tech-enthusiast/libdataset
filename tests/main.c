#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arithmetic_operations.h"

/**
 * Main function to control the flow of the program.
 *
 * @param int argc
 *   The number of command-line arguments.
 * @param char const *argv[]
 *   Array of command-line argument strings.
 *
 * @return int
 *   Returns 0 on successful execution, or a non-zero value if an error occurs.
 */
int main(int argc, char const *argv[]) {
  // Generate a dataset with random additions.
  int count = 10;
  int min = 10;
  int max = 40;
  struct dataset *int_dataset = random_generate_additions(count, min, max);
  // Print the integer dataset.
  dataset_print(int_dataset, &data_entry_print_int);
  // Convert the integer dataset to a string dataset.
  struct dataset *string_dataset = dataset_string_encode(int_dataset);
  // Print the string dataset.
  dataset_print(string_dataset, &data_entry_print_string);
  // Define the list of supported tokens to prepare the array for one hot encoding..
  char tokens[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', ' ', '\0'};
  int tokens_size = strlen(tokens);
  struct dataset *int_encoded_dataset = dataset_int_encode(string_dataset, tokens, tokens_size);
  // Print the integer encoded dataset.
  dataset_print(int_encoded_dataset, &data_entry_print_int);
  // One hot encode
  struct dataset *one_hot_encoded_dataset = dataset_one_hot_encode(int_encoded_dataset, tokens_size);
  // Print the One hot encoded dataset.
  dataset_print(one_hot_encoded_dataset, &data_entry_print_vector);
  // Clean up memory.
  dataset_destroy(int_dataset);
  dataset_destroy(string_dataset);
  dataset_destroy(int_encoded_dataset);
  dataset_destroy(one_hot_encoded_dataset);
  int_dataset = NULL;
  string_dataset = NULL;
  int_encoded_dataset = NULL;
  one_hot_encoded_dataset = NULL;
  // Return success status.
  return EXIT_SUCCESS;
}
