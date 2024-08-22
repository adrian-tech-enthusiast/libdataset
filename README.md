## Lib Dataset: A versatile C library for managing and manipulating datasets, perfect for applications involving data processing, machine learning, and data analysis.

Welcome to the C Dataset Library, a powerful and flexible C library designed to manage and manipulate datasets efficiently. Whether you're working on data processing, machine learning, or any form of data analysis, this library provides the tools you need to handle complex data structures with ease.

Equipped with a straightforward API and optimized for performance, it simplifies the process of creating, managing, and processing datasets, making it a valuable asset for both beginners and experienced developers.

### 🎯 Key Features

- **💡 Data Entry Management**: Effortlessly create and manage data entries across various types.
- **⚡ Dataset Operations**: Rapidly insert, delete, and traverse collections of data rows with ease.
- **🔄 Encoding Functions**: Leverage built-in functions for string-to-integer encoding, one-hot encoding, and more.
- **🔍 Printing Capabilities**: Output datasets, data entries, and rows in a readable format—ideal for debugging and analysis.
- **📚 Comprehensive Documentation**: Get up and running quickly with detailed guides and examples.
- **🌍 Open Source & Community-Driven**: Actively maintained with continuous enhancements—your contributions are welcome!

### 🛠 Prerequisites

To use **Lib Dataset**, ensure you have:

- A C compiler (e.g., GCC, Clang)

Additionally, the following libraries should be installed:

1. [**Lib Matrix Math (libmatrixmath)**](https://github.com/adrian-tech-enthusiast/libmatrixmath?tab=readme-ov-file#installation) [v1.1.6](https://github.com/adrian-tech-enthusiast/libmatrixmath/releases/tag/v1.1.6) or later: Powerful tools for vector and matrix manipulation.
2. [**Lib Strutils (libstr)**](https://github.com/adrian-tech-enthusiast/libstr?tab=readme-ov-file#installation) [v1.1.0](https://github.com/adrian-tech-enthusiast/libstr/releases/tag/v1.1.0) or later: Efficient functions for handling character arrays.

### 🚀 Getting Started

Ready to dive in? Clone the **Lib Dataset** repository and follow the installation steps below. Once set up, explore the rich documentation and examples to start integrating this powerful library into your projects.

### ⚙️ Installation

To obtain the most recent stable version of the library, download it from the [official GitHub repository](https://github.com/adrian-tech-enthusiast/libdataset).

First, confirm the latest version available on the [releases page](https://github.com/adrian-tech-enthusiast/libdataset/releases). At the time of writing, the latest stable version is `1.0.0`.

1. Download the `1.0.0` release and save the shared library file at `/usr/local/lib/libdataset.so`:

    ```bash
    sudo curl -L "https://github.com/adrian-tech-enthusiast/libdataset/releases/download/v1.0.0/libdataset.so" -o /usr/local/lib/libdataset.so
    ```

2. Update the system's dynamic loader cache to include the new library:

    ```bash
    sudo ldconfig;
    ```

    Verify the library's availability by running:

    ```bash
    ldconfig -p | grep libdataset
    ```

3. Copy the library header file (`dataset.h`) to a location in your compiler's search path, such as `/usr/include` or `/usr/local/include`:

    ```bash
    sudo curl -L "https://raw.githubusercontent.com/adrian-tech-enthusiast/libdataset/v1.0.0/include/dataset.h" -o /usr/local/include/dataset.h;
    ```

    You can now include the library headers in your C project:

    ```c
    #include <stdio.h>
    #include <dataset.h>
    ```

4. To compile your code with the library, link it during the compilation:

    ```bash
    gcc -o my_program my_program.c -ldataset
    ```

### 📝 Example Usage

Here's a basic example demonstrating how to use Lib Dataset to create and manipulate a dataset:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataset.h"

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
```

### 🤝 Contributions

We'd love for you to contribute to **Lib Dataset**! Whether it's reporting issues, suggesting new features, or submitting pull requests, your input is invaluable.

To contribute:

1. Fork the repository.
2. Create your feature branch (`git checkout -b feature/my-feature`).
3. Commit your changes (`git commit -am 'Add my feature'`).
4. Push to the branch (`git push origin feature/my-feature`).
5. Create a new Pull Request.

### 📄 License

This library is licensed under the `GNU General Public License v3.0`. See the LICENSE file for more details.

### 🙌 Acknowledgments

- Inspired by the need for efficient dataset management in C.
- A big thank you to all contributors and the open-source community for their support and inspiration.
