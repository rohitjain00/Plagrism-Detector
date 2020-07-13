# Plagrism Detector

This Detector is based on the cpp plagrism detector.

### This works as follows

1. Takes input from two .cpp files
2. Removes all the comments from the code.
3. Removes all the spaces and newlines from the code.
4. The code is converted to tokens.
5. 'F' for function is added to the code.
6. Edit distance is used to compare token's string.

### Token Conversion

Conversion for C code can be found here (https://www.geeksforgeeks.org/c-program-detect-tokens-c-program/)

* We have converted the above code to be used with cpp code.

##### Tokens are classified into following categories
* delimiter
* operator
* Integer/ Real Number
* Keyword
* Identifier
