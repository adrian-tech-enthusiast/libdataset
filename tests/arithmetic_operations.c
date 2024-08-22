#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arithmetic_operations.h"

/**
 * {@inheritdoc}
 */
int random_generate_integer(int min, int max) {
  // Generate number in range [min, max].
  return min + rand() % (max - min + 1);
}

/**
 * {@inheritdoc}
 */
struct data_row *random_generate_addition_row(int min, int max) {
  // Generate random integer values for the inputs.
  int a = random_generate_integer(min, max);
  int b = random_generate_integer(min, max);
  // Compute the sum of the two inputs.
  int c = a + b;
  // Create data entries for the inputs and output.
  struct data_entry *entry_a = data_entry_create_int(a);
  if (entry_a == NULL) {
    return NULL;
  }
  struct data_entry *entry_b = data_entry_create_int(b);
  if (entry_b == NULL) {
    data_entry_destroy(entry_a);
    return NULL;
  }
  struct data_entry *entry_c = data_entry_create_int(c);
  if (entry_c == NULL) {
    data_entry_destroy(entry_a);
    data_entry_destroy(entry_b);
    return NULL;
  }
  // Create a new data row.
  struct data_row *row = data_row_create();
  if (row == NULL) {
    // Failed to create data row, clean up and return NULL.
    data_entry_destroy(entry_a);
    data_entry_destroy(entry_b);
    data_entry_destroy(entry_c);
    return NULL;
  }
  // Allocate space for the input entries.
  row->inputs = data_entries_create(NUM_INPUTS);
  if (row->inputs == NULL) {
    data_row_destroy(row);
    data_entry_destroy(entry_a);
    data_entry_destroy(entry_b);
    data_entry_destroy(entry_c);
    return NULL;
  }
  // Set the input entries.
  row->inputs->entries[0] = entry_a;
  row->inputs->entries[1] = entry_b;
  // Allocate space for the output entries.
  row->outputs = data_entries_create(NUM_OUTPUTS);
  if (row->outputs == NULL) {
    data_row_destroy(row);
    data_entry_destroy(entry_a);
    data_entry_destroy(entry_b);
    data_entry_destroy(entry_c);
    return NULL;
  }
  // Set the outputs entries.
  row->outputs->entries[0] = entry_c;
  // Return the newly created data row.
  return row;
}

/**
 * {@inheritdoc}
 */
struct dataset *random_generate_additions(int count, int min, int max) {
  // Allocate memory for a new dataset structure.
  struct dataset *data = dataset_create();
  if (data == NULL) {
    // Return NULL if dataset creation fails.
    return NULL;
  }
  // Seed the random number generator using the current time for randomness.
  srand(time(NULL));
  // Create rows with random integer values and their sums.
  for (int i = 0; i < count; i++) {
    // Generate a new data row with two random input integers and their sum as output.
    struct data_row *row = random_generate_addition_row(min, max);
    // Append the generated row to the dataset.
    if (row == NULL || dataset_append_row(data, row) != 0) {
      // If row creation fails, clean up by destroying the dataset and return NULL.
      dataset_destroy(data);
      return NULL;
    }
  }
  // Return the populated dataset containing the generated rows.
  return data;
}
