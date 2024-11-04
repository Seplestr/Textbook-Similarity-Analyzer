# Textbook Similarity Analyzer

## Overview

The **Textbook Similarity Analyzer** is a C++ application designed to identify and rank the most similar pairs of textbooks from a collection of `.txt` files. By analyzing word frequencies and implementing text normalization techniques, the program provides insightful comparisons between different educational materials.

## Features

- **Automated Text Processing**: Reads and analyzes multiple textbook files from a specified directory.
- **Text Normalization**:
  - Converts all text to uppercase for consistent comparison.
  - Removes non-alphanumeric characters to focus solely on meaningful words.
  - Excludes common stop words (`"A"`, `"AND"`, `"AN"`, `"OF"`, `"IN"`, `"THE"`) to enhance analysis accuracy.
- **Word Frequency Analysis**:
  - Counts the frequency of each word in a textbook.
  - Identifies the top 100 most frequent words in each file.
  - Normalizes word counts to account for varying textbook lengths.
- **Similarity Calculation**: Computes a similarity index for each pair of textbooks by summing the normalized frequencies of common top words.
- **Comprehensive Reporting**: Generates a sorted list of the top 10 most similar textbook pairs based on the computed similarity indices.

## How It Works

1. **Reading Text Files**: The program scans a specified directory and reads all `.txt` files representing different textbooks.

2. **Preprocessing**:
   - Converts text to uppercase and removes non-alphanumeric characters.
   - Filters out common stop words.

3. **Word Frequency Analysis**:
   - Counts word frequencies and identifies the top 100 words.
   - Normalizes these frequencies for fair comparison.

4. **Similarity Calculation**:
   - Constructs a similarity matrix and computes similarity indices.

5. **Reporting**:
   - Outputs the top 10 most similar textbook pairs.

## Installation

### Prerequisites

- **C++17 Compiler**: Ensure you have a C++17 compatible compiler installed (e.g., `g++` version 7 or higher).
- **Filesystem Library Support**: The program utilizes the `<filesystem>` library, which is standard in C++17 and later.

### Steps

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/textbook-similarity-analyzer.git
