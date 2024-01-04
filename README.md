# ccdoc
ccdoc a simple C program that automatically generates markdown documentation for C header files, the program
looks at `.h` files and read comments that are prefixed with `///` (like rust), then it will associate those
comments with the first function found under them, for example 
```c
// myfile.h

/// my simple function
/// that does X, Y and Z
int foo(int. int);
```

markdown output:
```
## int foo(int, int)
my simple function
that does X, Y and Z
```

