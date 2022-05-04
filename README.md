# Report Style Analyzer Project

- **Programmer:** Xinpeng (David) Liu
- **Date:** 2022-05-02
- **Section:** CSC-331H

The program analyzes any article provided in a text file. It will provide statistical summary about this article and warning on style.

## Contents

The following files should be presented in the same folder:
- `ReportAnalyzer.h` (header file for defining report analyzer class)
- `ReportAnalyzer.cpp` (implementation of report analyzer class)
- `main.cpp` (the driver class)

The following classes should also be included in the folder stated above, because "ReportAnalyzer" class used AVL balanced tree for implementation:
- `AVL.h` (header file of the AVL balanced tree class)
- `AVL.cpp` (Implementation of the AVL balanced tree class)

Lastly, two sample articles are included in this repository. If you wish to analyze these two sample articles please include them in the folder as well:
- `sample1.txt` (sample article one)
- `sample2.txt` (sample article two)

## Menu Driven Program for Testing

The `main.cpp` provides a menu driven program to test the `ReportAnalyzer` class. Please run the `main.cpp` and follow the steps promoted to test. 
If you wish to use your own article, please make sure the article is in `.txt` format and the file is placed in the same folder as `main.cpp`

## To add LargeInt class to your own project
Please copy both `ReportAnalyzer.h`, `ReportAnalyzer.cpp` and its dependency files `AVL.h` and `AVL.cpp` to your project. Then include the header file of ReportAnalyzer class into your program by:
```
#include "ReportAnalyzer.h"
```
