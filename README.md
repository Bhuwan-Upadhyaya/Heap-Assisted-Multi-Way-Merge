# Lab Assignment 2: Heap-Assisted Multi-Way Merge

## Overview
This project implements a **heap-assisted multi-way merge** to process multiple sorted input files containing strings. The program outputs unique strings in ascending order, along with the count of files each string appears in.

## Goals
- Understand the structure and behavior of **heaps**.
- Apply heap-based merging to efficiently combine sorted data from multiple sources.

## Requirements
- Input consists of `n` sorted files with unique strings in each file.
- Output is a file named `out.dat` containing each unique string and the number of files it appears in.
- The merging process uses a **single heap-assisted merge**, avoiding multiple binary merges or heapsort.

## Features
- Efficient multi-way merge using a **min-heap**.
- Handles duplicate strings across files.
- Outputs results in the format: `<string> <count>`.

## Input Format
- **in.dat** specifies the list of input files:
  ```
  4
  in0.dat
  in1.dat
  in2.dat
  in3.dat
  ```
- Each input file contains sorted strings.

## Output Format
- The output file (`out.dat`) will contain lines like:
  ```
  abc 2
  def 1
  efg 2
  ghi 4
  ```

## Compilation
Compile the program using GCC:
```
$ gcc -o lab2 lab2.c
```

## Execution
Run the program using standard input redirection:
```
$ ./lab2 < in.dat
```

## Example Input and Output
**Input Files:**
- `in0.dat`: abc, ghi, mno
- `in1.dat`: abc, efg, ghi

**Output File (`out.dat`):**
```
abc 2
efg 1
ghi 2
mno 1
```

## Files Included
- `lab2.c`: Main source code.
- `Makefile`: Compilation instructions.
- `README.md`: Documentation.

## Author
- **Bhuwan Bhuwan
- **ID:** 1002079187

## License
This project is for educational purposes only.

## References
- Course notes and resources provided by Prof. Weems.
- Heap implementation from class resources.

---
**Submission Deadline:** October 3, 5:00 PM on Canvas.

Ensure your code is well-commented and follows the provided guidelines.
