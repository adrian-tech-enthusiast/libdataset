#!/bin/bash

# @file debug.sh
# @brief Script for debugging the project executable using GNU Debugger (gdb).
#
# This script automates the process of debugging the project executable. It relies on the
# `debug_project` function from the `helper.sh` script to run the executable through `gdb`,
# providing a stack trace to assist with debugging. The script assumes that the executable 
# has been built and is located in the specified binary path.


# Determine the directory of the script.
SCRIPT_DIR=$(dirname "$(readlink -f "$0")");
# Load helper functions.
source "$SCRIPT_DIR/helper.sh";

# Global Settings.
BASE_NAME='libdataset'   # Base name for the project (used to construct the executable name).
PROJECT_PATH=$(pwd)      # Root path of the project (where the executable is located).

# Debug the project executable.
debug_project "$BASE_NAME" "$PROJECT_PATH";
