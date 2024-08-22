#ifndef DATASET_H
#define DATASET_H

/**
 * Represents a single data entry in the dataset.
 *
 * This structure is a generic container that can hold any type of data
 * by storing a pointer to it. The actual data type is determined by the
 * context in which the data entry is used.
 */
struct data_entry {
  /**
   * Pointer to the data stored in the entry. The data can be of any type.
   * It is the responsibility of the user to manage the memory and ensure
   * proper casting when accessing the data.
   *
   * @var void *
   */
  void *data;
};

/**
 * Represents a collection of data entries.
 *
 * This structure is used to manage a list of data entries, which can be
 * input values, output values, or any other collection of data.
 */
struct data_entries {
  /**
   * The number of data entries in the collection.
   *
   * @var int
   */
  int size;

  /**
   * Array of pointers to data entries.
   *
   * @var struct data_entry **
   */
  struct data_entry **entries;
};

/**
 * Represents a row in the dataset, containing collections of input and output data entries.
 *
 * A data_row structure typically holds one or more input data entries and
 * corresponding output data entries, which together represent a single
 * record in the dataset.
 */
struct data_row {
  /**
   * Collection of input data entries for this row.
   *
   * @var struct data_entries *
   */
  struct data_entries *inputs;

  /**
   * Collection of output data entries for this row.
   *
   * @var struct data_entries *
   */
  struct data_entries *outputs;

  /**
   * Pointer to the previous row in the dataset, used to traverse the dataset in reverse order.
   *
   * @var struct data_row *
   */
  struct data_row *previous;

  /**
   * Pointer to the next row in the dataset, used to traverse the dataset in forward order.
   *
   * @var struct data_row *
   */
  struct data_row *next;
};

/**
 * Represents the entire dataset, consisting of multiple rows and metadata.
 *
 * This structure manages a dataset that may contain multiple rows, each with
 * its own input and output data entries. It also includes metadata such as
 * the total number of rows.
 */
struct dataset {
  /**
   * The total number of rows in the dataset.
   *
   * @var int
   */
  int size;

  /**
   * Iterator to traverse through the rows of the dataset.
   *
   * @var struct data_row *
   */
  struct data_row *iterator;

  /**
   * Pointer to the last row in the dataset, used for rapid insertion.
   *
   * This allows new rows to be appended to the dataset efficiently.
   *
   * @var struct data_row *
   */
  struct data_row *last;
};

/**
 * Creates a new data entry instance with the given value.
 *
 * @param void *value
 *   A pointer to the value to store in the data entry
 *
 * @return struct data_entry *
 *   A pointer to the newly created data entry, or NULL on failure.
 */
struct data_entry *data_entry_create(void *value);

/**
 * Creates a data entry with an integer value.
 *
 * @param int value
 *   The integer value to store in the data entry.
 *
 * @return struct data_entry *
 *   A pointer to the newly created data entry, or NULL on failure.
 */
struct data_entry *data_entry_create_int(int value);

/**
 * Destroys a data entry, freeing all allocated memory.
 *
 * @param struct data_entry *entry
 *   The data entry to be destroyed.
 */
void data_entry_destroy(struct data_entry *entry);

/**
 * Creates a collection of data entries with the specified size.
 *
 * @param int size
 *   The number of data entries to create.
 *
 * @return struct data_entries*
 *   A pointer to the newly created data entries collection, or NULL on failure.
 */
struct data_entries *data_entries_create(int size);

/**
 * Destroys a collection of data entries, freeing all allocated memory.
 *
 * This function will iterate over each data entry in the collection,
 * call `data_entry_destroy` to free the individual data entry, and then
 * free the memory allocated for the entries array itself.
 *
 * @param struct data_entries *entries
 *   A pointer to the collection of data entries to be destroyed.
 */
void data_entries_destroy(struct data_entries *entries);

/**
 * Creates a new data row instance.
 *
 * @return struct data_row*
 *   A pointer to the newly created data row, or NULL on failure.
 */
struct data_row *data_row_create();

/**
 * Destroys a data row, freeing all allocated memory.
 *
 * @param struct data_row *row
 *   A pointer to the data row to be destroyed.
 */
void data_row_destroy(struct data_row *row);

/**
 * Creates a new dataset instance.
 *
 * @return struct dataset*
 *   A pointer to the newly created dataset, or NULL on failure.
 */
struct dataset *dataset_create();

/**
 * Destroys a dataset, freeing all allocated memory.
 *
 * @param struct dataset *data
 *   A pointer to the dataset to be destroyed.
 */
void dataset_destroy(struct dataset *data);

/**
 * Appends a new row to the dataset.
 *
 * This function adds a new row to the end of the dataset. It uses the last_row
 * property to quickly find the current last row and attach the new row.
 *
 * @param struct dataset *data
 *   A pointer to the dataset to which the row will be appended.
 * @param struct data_row *row
 *   A pointer to the row to be appended to the dataset.
 *
 * @return int
 *   Returns 0 on success, or -1 if the operation fails (e.g., if data or new_row is NULL).
 */
int dataset_append_row(struct dataset *data, struct data_row *row);

#endif // DATASET_H

#ifndef DATASET_PRINT_H
#define DATASET_PRINT_H

/**
 * Prints the integer value stored in a data entry.
 *
 * This function assumes that the value stored in the data entry is an integer
 * and prints it to the standard output.
 *
 * @param struct data_entry *entry
 *   A pointer to the data entry containing the integer value to print.
 */
void data_entry_print_int(struct data_entry *entry);

/**
 * Prints the string value stored in a data entry.
 *
 * This function assumes that the value stored in the data entry is a null-terminated
 * string and prints it to the standard output.
 *
 * @param struct data_entry *entry
 *   A pointer to the data entry containing the string value to print.
 */
void data_entry_print_string(struct data_entry *entry);

/**
 * Prints the contents of a vector stored in a data entry.
 *
 * This function assumes that the value stored in the data entry is a `struct vector`
 * and prints the contents of the vector to the standard output.
 *
 * @param struct data_entry *entry
 *   A pointer to the data entry containing the vector to print.
 */
void data_entry_print_vector(struct data_entry *entry);

/**
 * Prints the contents of a collection of data entries.
 *
 * This function will iterate over each data entry in the collection and
 * call the provided print function to display the content of each entry.
 *
 * @param struct data_entries *entries
 *   A pointer to the collection of data entries to be printed.
 * @param void (*print_entry)(struct data_entry *)
 *   Function pointer to a function that prints a single data entry.
 */
void data_entries_print(struct data_entries *entries, void (*print_entry)(struct data_entry *));

/**
 * Prints the contents of the dataset in a formatted manner.
 *
 * This function iterates through the dataset and prints each row in the format:
 *
 * Dataset: # rows <size>.
 * Row #<row_index>: Input [<input_1>, <input_2>] - Output [<output>]
 *
 * @param struct dataset *data
 *   A pointer to the dataset to be printed.
 * @param void (*print_entry)(struct data_entry*)
 *   Function pointer to a function that prints a data entry.
 */
void dataset_print(struct dataset *data, void (*print_entry)(struct data_entry *));

#endif // DATASET_PRINT_H

#ifndef DATASET_ENCODE_H
#define DATASET_ENCODE_H

/**
 * Encodes each data entry in the given dataset using a specified encoding function,
 * and returns a new dataset with the encoded data.
 *
 * This function creates a new dataset where each row is transformed using the provided
 * `encode_entry` function. The function iterates through each row of the raw dataset,
 * encodes the data entries, and constructs the new encoded dataset.
 *
 * @param struct dataset *raw_dataset
 *   A pointer to the raw dataset to be encoded. The dataset should not be NULL.
 * @param char *tokens
 *   A pointer to the array of tokens used for encoding. This may be NULL if the encoding
 *   function does not require tokens.
 * @param int tokens_size
 *   The size of the tokens array. It should be greater than 0. If tokens is NULL, this parameter
 *   can be set to 0.
 * @param struct data_entries *(*encode_entry)(struct data_entry *, char *, int)
 *   A function pointer to the encoding function that transforms individual data entries. This function
 *   should take a data entry, an array of tokens, and the size of the tokens array as input and return
 *   a pointer to the encoded data entries.
 *
 * @return struct dataset*
 *   A pointer to the newly created dataset containing the encoded data. Returns NULL if
 *   any errors occur during encoding or memory allocation failures.
 */
struct dataset *dataset_encode(struct dataset *raw_dataset, char *tokens, int tokens_size, struct data_entries *(*encode_entry)(struct data_entry *, char *, int));

/**
 * Encodes a string dataset into an integer dataset based on a set of tokens
 *
 * This function converts each character in the dataset to its corresponding index
 * in the tokens array. The resulting dataset contains integer representations of
 * the original strings.
 *
 * @param struct dataset *string_dataset
 *   A pointer to the dataset containing string values to be encoded.
 * @param char *tokens
 *   A string containing the supported tokens for encoding.
 * @param int tokens_size
 *   The size of the tokens string.
 *
 * @return struct dataset*
 *   A new dataset containing integer representations of the strings, or NULL if encoding fails.
 */
struct dataset *dataset_int_encode(struct dataset *string_dataset, char *tokens, int tokens_size);

/**
 * Converts an integer dataset to a string dataset using predefined tokens.
 *
 * This function processes each data entry in the provided integer dataset,
 * converting the integer values to their corresponding string representations.
 * The conversion is performed by the `data_entry_string_encode` function, which
 * translates an integer data entry into a string data entry. The resulting dataset
 * will contain string representations of the original integers.
 *
 * This function is useful when you need to transform datasets that contain integer
 * values into a more human-readable string format, typically for serialization,
 * display, or logging purposes.
 *
 * @param struct dataset *int_dataset
 *   A pointer to the dataset containing integer values to be converted to strings.
 *
 * @return struct dataset*
 *   A new dataset containing string representations of the integer values, or NULL
 *   if the conversion fails or the input dataset is invalid.
 */
struct dataset *dataset_string_encode(struct dataset *int_dataset);

/**
 * One-hot encodes an integer dataset based on a set of tokens.
 *
 * This function converts each integer in the dataset to a one-hot encoded vector based
 * on the provided tokens. The resulting dataset contains one-hot encoded representations
 * of the original integers.
 *
 * @param struct dataset *int_encoded_dataset
 *   A pointer to the dataset containing integer encoded values to be one-hot encoded.
 * @param int tokens_size
 *   The size of the tokens string.
 *
 * @return struct dataset*
 *   A new dataset containing one-hot encoded representations of the integers, or NULL if encoding fails.
 */
struct dataset *dataset_one_hot_encode(struct dataset *int_encoded_dataset, int tokens_size);

#endif // DATASET_ENCODE_H
