#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strutils.h>
#include <matrixmath.h>
#include "../include/dataset.h"

/**
 * {@inheritdoc}
 */
struct data_entry *data_entry_create(void *value) {
  // Calculate the size of the data_entry structure.
  size_t entry_size = sizeof(struct data_entry);
  // Allocate memory for the data entry.
  struct data_entry *entry = malloc(entry_size);
  if (entry == NULL) {
    // Memory allocation failed.
    return NULL;
  }
  // Initialize the data with the provided value.
  entry->data = value;
  // Return the newly created data entry.
  return entry;
}

/**
 * {@inheritdoc}
 */
struct data_entry *data_entry_create_int(int value) {
  // Allocate memory to store the integer value.
  size_t data_size = sizeof(int);
  // Allocate memory for the integer value.
  int *data = malloc(data_size);
  if (data == NULL) {
    // Memory allocation failed.
    return NULL;
  }
  // Set the integer value.
  *data = value;
  // Create a new data entry with the integer value.
  struct data_entry *entry = data_entry_create(data);
  if (entry == NULL) {
    // Data entry creation failed; free the allocated memory.
    free(data);
    return NULL;
  }
  // Return the newly created data entry.
  return entry;
}

/**
 * {@inheritdoc}
 */
void data_entry_destroy(struct data_entry *entry) {
  if (entry == NULL) {
    // No action needed if entry is NULL.
    return;
  }
  // Free the memory allocated for the data value.
  if (entry->data != NULL) {
    free(entry->data);
  }
  // Free the memory allocated for the data_entry structure itself.
  free(entry);
}

/**
 * {@inheritdoc}
 */
void data_entry_print_int(struct data_entry *entry) {
  if (entry == NULL || entry->data == NULL) {
    // Handle cases where the entry or its value is NULL.
    printf("Invalid data entry.\n");
    return;
  }
  // Dereference the value to print it as an integer.
  int value = *(int *)entry->data;
  // Print the integer value stored in the data_entry.
  printf("%d", value);
}

/**
 * {@inheritdoc}
 */
void data_entry_print_string(struct data_entry *entry) {
  if (entry == NULL || entry->data == NULL) {
    // Handle cases where the entry or its value is NULL.
    printf("Invalid data entry.\n");
    return;
  }
  // Retrieve the value from the entry, assuming it's a string
  char *value = (char *)entry->data;
  // Print the string value stored in the data_entry.
  printf("'%s'", value);
}

/**
 * {@inheritdoc}
 */
void data_entry_print_vector(struct data_entry *entry) {
  if (entry == NULL || entry->data == NULL) {
    printf("Invalid data entry.\n");
    return;
  }
  // Cast the data to a vector
  struct vector *vector_object = (struct vector *)entry->data;
  // Print the vector.
  vector_print(vector_object);
}

/**
 * {@inheritdoc}
 */
struct data_entries *data_entries_create(int size) {
  // Calculate the size of the data_entries structure.
  size_t entries_size = sizeof(struct data_entries);
  // Allocate memory for the data_entries structure.
  struct data_entries *new_entries = malloc(entries_size);
  if (new_entries == NULL) {
    // Memory allocation failed.
    return NULL;
  }
  // Set the size of the collection.
  new_entries->size = size;
  // Allocate memory for the array of pointers to data_entry structures.
  size_t entry_size = sizeof(struct data_entry *);
  new_entries->entries = malloc(size * entry_size);
  if (new_entries->entries == NULL) {
    // Free previously allocated memory if allocation for entries fails.
    free(new_entries);
    return NULL;
  }
  // Initialize all data_entry pointers to NULL.
  for (int i = 0; i < size; i++) {
    new_entries->entries[i] = NULL;
  }
  // Return the newly created data_entries structure.
  return new_entries;
}

/**
 * {@inheritdoc}
 */
void data_entries_destroy(struct data_entries *entries) {
  if (entries == NULL) {
    // No action needed if entries is NULL.
    return;
  }
  // Destroy each data_entry in the array.
  for (int i = 0; i < entries->size; i++) {
    if (entries->entries[i] != NULL) {
      data_entry_destroy(entries->entries[i]);
    }
  }
  // Free the memory allocated for the array of data_entry pointers.
  free(entries->entries);
  // Free the memory allocated for the data_entries structure itself.
  free(entries);
}

/**
 * {@inheritdoc}
 */
void data_entries_print(struct data_entries *entries, void (*print_entry)(struct data_entry *)) {
  if (entries == NULL || print_entry == NULL) {
    // No action needed if entries or print_entry is NULL.
    return;
  }
  // Iterate over each data_entry and print it using the provided print function.
  for (int i = 0; i < entries->size; i++) {
    if (entries->entries[i] != NULL) {
      // Print a comma and space to separate input values after the first one.
      if (i != 0) {
        printf(", ");
      }
      // Print the current data_entry.
      print_entry(entries->entries[i]);
    }
  }
}

/**
 * {@inheritdoc}
 */
struct data_row *data_row_create() {
  // Calculate the size of the data row structure.
  size_t size = sizeof(struct data_row);
  // Allocate memory for the data_row structure.
  struct data_row *row = malloc(size);
  if (row == NULL) {
    // Memory allocation failed.
    return NULL;
  }
  // Initialize the input and output data entries to NULL.
  row->inputs = NULL;
  row->outputs = NULL;
  // Initialize the previous and next pointers to NULL.
  row->previous = NULL;
  row->next = NULL;
  // Return the newly created data_row structure.
  return row;
}

/**
 * {@inheritdoc}
 */
void data_row_destroy(struct data_row *row) {
  if (row == NULL) {
    // No action needed if row is NULL.
    return;
  }
  // Destroy the input data entries.
  if (row->inputs != NULL) {
    data_entries_destroy(row->inputs);
    row->inputs = NULL;
  }
  // Destroy the output data entries.
  if (row->outputs != NULL) {
    data_entries_destroy(row->outputs);
    row->outputs = NULL;
  }
  // Free the memory allocated for the data_row structure itself.
  free(row);
}

/**
 * {@inheritdoc}
 */
struct dataset *dataset_create() {
  // Calculate the size of the dataset structure.
  size_t size = sizeof(struct dataset);
  // Allocate memory for the dataset structure.
  struct dataset *object = malloc(size);
  if (object == NULL) {
    // Memory allocation failed.
    return NULL;
  }
  // Initialize the dataset size to 0.
  object->size = 0;
  // Initialize the iterator to NULL.
  object->iterator = NULL;
  // Return the newly created dataset structure.
  return object;
}

/**
 * {@inheritdoc}
 */
void dataset_destroy(struct dataset *data) {
  if (data == NULL) {
    // No action needed if data is NULL.
    return;
  }
  // Iterate through each data_row in the dataset and destroy it.
  struct data_row *current = data->iterator;
  while (current != NULL) {
    struct data_row *next = current->next;
    data_row_destroy(current);
    current = next;
  }
  // Free the memory allocated for the dataset structure itself.
  free(data);
}

/**
 * {@inheritdoc}
 */
void dataset_print(struct dataset *data, void (*print_entry)(struct data_entry *)) {
  // Check if the dataset pointer is NULL.
  if (data == NULL) {
    printf("Dataset is NULL.\n");
    return;
  }
  // Print a header for the dataset.
  printf("-----------------------------------------------\n");
  // Print the number of rows in the dataset.
  printf("Dataset: # rows %d.\n", data->size);
  // Initialize a pointer to iterate over the rows.
  struct data_row *current = data->iterator;
  // Initialize a counter for row numbers.
  int row_number = 1;
  // Iterate over each row in the dataset.
  while (current != NULL) {
    // Print the current row number.
    printf("Row #%d: ", row_number);
    // Print the input values for the current row.
    printf("Input [");
    data_entries_print(current->inputs, print_entry);
    printf("]");
    // Print the output values for the current row.
    printf(" - Output [");
    data_entries_print(current->outputs, print_entry);
    printf("]\n");
    // Move to the next row.
    current = current->next;
    // Increment the row number counter.
    row_number++;
  }
  // Print a footer for the dataset.
  printf("-----------------------------------------------\n");
}

/**
 * {@inheritdoc}
 */
int dataset_append_row(struct dataset *data, struct data_row *row) {
  // Check if the input params are valid.
  if (data == NULL || row == NULL) {
    return -1;
  }
  if (data->last == NULL) {
    // If the dataset is empty, set the new row as the first row.
    data->iterator = row;
  } else {
    // Link the new row to the current last row.
    data->last->next = row;
    row->previous = data->last;
  }
  // Update the last_row to the new row.
  data->last = row;
  // Increment the dataset size.
  data->size++;
  // Return a success response.
  return 0;
}

/**
 * Finds the index of a token in the tokens array.
 *
 * @param char token
 *   The token to find.
 * @param char *tokens
 *   The array of tokens.
 * @param int tokens_size
 *   The size of the tokens array.
 *
 * @return int
 *   The index of the token in the tokens array, or -1 if not found.
 */
static int find_token_index(char token, char *tokens, int tokens_size) {
  // Check for null pointers and invalid size.
  if (tokens == NULL || tokens_size <= 0) {
    // Invalid input.
    return -1;
  }
  // Iterate through the tokens array.
  for (int i = 0; i < tokens_size; i++) {
    if (tokens[i] == token) {
      // Token found at index i.
      return i;
    }
  }
  // Token not found in the array.
  return -1;
}

/**
 * Encodes a string data entry into a collection of integer data entries based on a set of tokens.
 *
 * This function converts each character in the string data entry to its corresponding index
 * in the provided tokens array, creating a new `data_entries` structure that holds the
 * encoded integer values.
 *
 * @param struct data_entry *entry
 *   The data entry containing the string to be encoded.
 * @param char *tokens
 *   The array of tokens used for encoding, where each character in the string is mapped to an index.
 * @param int tokens_size
 *   The number of tokens in the tokens array.
 *
 * @return struct data_entries*
 *   A pointer to the newly created `data_entries` structure containing the integer representations
 *   of the string, or NULL if encoding fails.
 */
static struct data_entries *data_entry_int_encode(struct data_entry *entry, char *tokens, int tokens_size) {
  // Check if the input data entry is NULL or does not contain a value.
  if (entry == NULL || entry->data == NULL) {
    return NULL;
  }
  // Cast the data entry value to a string and get its length.
  char *string_value = (char *)entry->data;
  int length = strlen(string_value);
  // Create a new data_entries structure to hold the encoded integer values.
  struct data_entries *encoded_entries = data_entries_create(length);
  if (encoded_entries == NULL) {
    // Data entries creation failed.
    return NULL;
  }
  // Encode each character in the string.
  for (int j = 0; j < length; j++) {
    int index = find_token_index(string_value[j], tokens, tokens_size);
    encoded_entries->entries[j] = data_entry_create_int(index);
  }
  // Return the populated data_entries structure.
  return encoded_entries;
}

/**
 * Converts an integer data entries to a string data entries.
 *
 * This function assumes that the data entry contains an integer value. It converts this integer
 * to a string representation and returns a new data entry containing the string.
 *
 * @param struct data_entry *entry
 *   The integer data entry to be converted.
 * @param char *tokens
 *   The array of tokens used for encoding, where each character in the string is mapped to an index.
 * @param int tokens_size
 *   The number of tokens in the tokens array.
 *
 * @return struct data_entry*
 *   A new data entry containing the string representation of the integer, or NULL on failure.
 */
static struct data_entries *data_entry_string_encode(struct data_entry *entry, char *tokens, int tokens_size) {
  // Check if the input data entry is NULL or if it does not contain a value.
  if (entry == NULL || entry->data == NULL) {
    return NULL;
  }
  // Retrieve the integer value from the data entry.
  int int_value = *((int *)entry->data);
  // Convert the integer value to a string representation.
  char *string_value = itos(int_value);
  // Check if the conversion was successful.
  if (string_value == NULL) {
    // Return NULL to indicate failure in conversion.
    return NULL;
  }
  // Create a new data_entries structure to hold the encoded string values.
  struct data_entries *encoded_entries = data_entries_create(1);
  if (encoded_entries == NULL) {
    // Data entries creation failed.
    free(string_value);
    return NULL;
  }
  // Add the string value to the encoded entries.
  encoded_entries->entries[0] = data_entry_create(string_value);
  // Return the populated data_entries structure.
  return encoded_entries;
}

/**
 * Encodes an integer data entry into a one-hot encoded representation.
 *
 * This function creates a new `data_entries` structure where each integer value
 * is transformed into a one-hot encoded vector based on the size of the tokens array.
 *
 * @param struct data_entry *entry
 *   The data entry containing the integer value to be one-hot encoded.
 * @param char *tokens
 *   The array of tokens used for encoding (not used in one-hot encoding).
 * @param int tokens_size
 *   The number of tokens in the tokens array, which determines the size of the one-hot vector.
 *
 * @return struct data_entries*
 *   A pointer to the newly created `data_entries` structure containing the one-hot encoded values,
 *   or NULL if encoding fails.
 */
static struct data_entries *data_entry_one_hot_encode(struct data_entry *entry, char *tokens, int tokens_size) {
  // Validate input parameters.
  if (entry == NULL || entry->data == NULL || tokens_size <= 0) {
    return NULL;
  }
  // Cast the data entry value to an integer.
  int value = *(int *)entry->data;
  // Ensure the integer value is within the valid range for one-hot encoding.
  if (value < 0 || value >= tokens_size) {
    return NULL;
  }
  // Create a vector to hold the one-hot encoded values.
  struct vector *one_hot_vector = vector_create(tokens_size);
  if (one_hot_vector == NULL) {
    return NULL;
  }
  // Initialize the vector with the one-hot encoded representation.
  for (int index = 0; index < tokens_size; index++) {
    int encoded_value = (index == value) ? 1 : 0;
    if (vector_setl(one_hot_vector, index, encoded_value) == NULL) {
      // Clean up if setting the vector value fails.
      vector_destroy(one_hot_vector);
      return NULL;
    }
  }
  // Create a new `data_entries` structure to hold the one-hot encoded vector.
  struct data_entries *encoded_entries = data_entries_create(1);
  if (encoded_entries == NULL) {
    vector_destroy(one_hot_vector);
    return NULL;
  }
  // Create a new `data_entry` for the vector and add it to the `data_entries` structure.
  encoded_entries->entries[0] = data_entry_create(one_hot_vector);
  if (encoded_entries->entries[0] == NULL) {
    // Clean up and return NULL if memory allocation fails.
    data_entries_destroy(encoded_entries);
    vector_destroy(one_hot_vector);
    return NULL;
  }
  // Return the populated one-hot encoded `data_entries` structure.
  return encoded_entries;
}

/**
 * Allocates memory for an array of data_entries pointers and initializes it.
 *
 * @param int size
 *   The number of entries in the collection.
 *
 * @return struct data_entries**
 *   A pointer to the allocated and initialized entries_collection array, or NULL if allocation fails.
 */
static struct data_entries **data_entries_collection_create(int size) {
  // Calculate the total size of the array.
  size_t collection_size = size * sizeof(struct data_entries);
  struct data_entries **entries_collection = malloc(collection_size);
  if (entries_collection == NULL) {
    // Memory allocation failed.
    return NULL;
  }
  // Initialize all pointers in the array to NULL.
  for (int i = 0; i < size; i++) {
    entries_collection[i] = NULL;
  }
  return entries_collection;
}

/**
 * Frees the memory allocated for the entries_collection array and its contents.
 *
 * @param struct data_entries **entries_collection
 *   The array of data_entries to be destroyed.
 * @param int size
 *   The number of entries in the collection.
 */
static void data_entries_collection_destroy(struct data_entries **entries_collection, int size) {
  if (entries_collection == NULL) {
    // No action needed if the collection is NULL.
    return;
  }
  // Free each data_entries in the array.
  for (int i = 0; i < size; i++) {
    if (entries_collection[i] != NULL) {
      data_entries_destroy(entries_collection[i]);
    }
  }
  // Free the array of pointers itself.
  free(entries_collection);
}

/**
 * Encodes a data entries by transforming its entries using a provided encoding function.
 *
 * @param struct data_entries *raw_entries
 *   The raw data entries to be encoded.
 * @param char *tokens
 *   The array of tokens used for encoding.
 * @param int tokens_size
 *   The size of the tokens array.
 * @param encode_entry
 *   The function used to encode individual data entries.
 *
 * @return struct data_entries*
 *   A new data entries containing the encoded values, or NULL on failure.
 */
static struct data_entries *data_entries_encode(struct data_entries *raw_entries, char *tokens, int tokens_size, struct data_entries *(*encode_entry)(struct data_entry *, char *, int)) {
  // Allocate memory for an array of encoded entries.
  struct data_entries **entries_collection = data_entries_collection_create(raw_entries->size);
  if (entries_collection == NULL) {
    // Memory allocation failed.
    return NULL;
  }
  // Track the size of encoded entries and encoding success.
  int encoded_entries_size = 0;
  int failed = 0;
  // Encode each entry in the raw_entries.
  for (int i = 0; i < raw_entries->size; i++) {
    entries_collection[i] = encode_entry(raw_entries->entries[i], tokens, tokens_size);
    if (entries_collection[i] == NULL) {
      failed = 1;
    } else {
      encoded_entries_size += entries_collection[i]->size;
    }
  }
  // Clean up if encoding failed.
  if (failed == 1) {
    data_entries_collection_destroy(entries_collection, raw_entries->size);
    return NULL;
  }
  // Create a new data_entries structure for the encoded values.
  struct data_entries *encoded_entries = data_entries_create(encoded_entries_size);
  if (encoded_entries == NULL) {
    data_entries_collection_destroy(entries_collection, raw_entries->size);
    return NULL;
  }
  // Populate the encoded_entries structure with encoded values.
  int index = 0;
  for (int j = 0; j < raw_entries->size; j++) {
    for (int k = 0; k < entries_collection[j]->size; k++) {
      encoded_entries->entries[index] = entries_collection[j]->entries[k];
      index++;
    }
  }
  // Free the temporary collection of entries.
  for (int j = 0; j < raw_entries->size; j++) {
    free(entries_collection[j]);
  }
  free(entries_collection);
  // Return the encoded data_entries structure.
  return encoded_entries;
}

/**
 * Encodes a data row by transforming its data entries using a provided encoding function.
 *
 * @param struct data_row *raw_row
 *   The raw data row to be encoded.
 * @param char *tokens
 *   The array of tokens used for encoding.
 * @param int tokens_size
 *   The size of the tokens array.
 * @param encode_entry
 *   The function used to encode individual data entries.
 *
 * @return struct data_row*
 *   A new data row containing the encoded values, or NULL on failure.
 */
static struct data_row *data_row_encode(struct data_row *raw_row, char *tokens, int tokens_size, struct data_entries *(*encode_entry)(struct data_entry *, char *, int)) {
  // Create a new data_row for the encoded entries.
  struct data_row *encoded_row = data_row_create();
  if (encoded_row == NULL) {
    return NULL;
  }
  // Encode the input data entries.
  encoded_row->inputs = data_entries_encode(raw_row->inputs, tokens, tokens_size, encode_entry);
  if (encoded_row->inputs == NULL) {
    data_row_destroy(encoded_row);
    return NULL;
  }
  // Encode the output data entries.
  encoded_row->outputs = data_entries_encode(raw_row->outputs, tokens, tokens_size, encode_entry);
  if (encoded_row->outputs == NULL) {
    data_row_destroy(encoded_row);
    return NULL;
  }
  // Return the encoded data_row.
  return encoded_row;
}

/**
 * {@inheritdoc}
 */
struct dataset *dataset_encode(struct dataset *raw_dataset, char *tokens, int tokens_size, struct data_entries *(*encode_entry)(struct data_entry *, char *, int)) {
  // Check if the input parameters are NULL or invalid.
  if (raw_dataset == NULL) {
    return NULL;
  }
  // Create a new dataset to hold the encoded rows.
  struct dataset *encoded_dataset = dataset_create();
  if (encoded_dataset == NULL) {
    return NULL;
  }
  // Pointers for traversing the raw and encoded rows.
  struct data_row *current = raw_dataset->iterator;
  // Process each row in the raw dataset.
  while (current != NULL) {
    // Encode the current row and append the row to the encoded dataset.
    struct data_row *encoded_row = data_row_encode(current, tokens, tokens_size, encode_entry);
    if (encoded_row == NULL || dataset_append_row(encoded_dataset, encoded_row) != 0) {
      dataset_destroy(encoded_dataset);
      return NULL;
    }
    // Move cursor to the next row in the dataset.
    current = current->next;
  }
  // Return the new dataset containing the encoded rows.
  return encoded_dataset;
}

/**
 * {@inheritdoc}
 */
struct dataset *dataset_int_encode(struct dataset *string_dataset, char *tokens, int tokens_size) {
  // Encode the dataset using the integer encoding function.
  return dataset_encode(string_dataset, tokens, tokens_size, data_entry_int_encode);
}

/**
 * {@inheritdoc}
 */
struct dataset *dataset_string_encode(struct dataset *int_dataset) {
  // Return the new dataset containing the encoded string representations.
  return dataset_encode(int_dataset, NULL, 0, data_entry_string_encode);
}

/**
 * {@inheritdoc}
 */
struct dataset *dataset_one_hot_encode(struct dataset *int_encoded_dataset, int tokens_size) {
  // Encode the dataset using the one-hot encoding function.
  return dataset_encode(int_encoded_dataset, NULL, tokens_size, data_entry_one_hot_encode);
}
