# C/C++ Midterm Review



1.  `const char * p1` == `char const * p2`: point to constant

    `char * const p3`: constant pointer

    

2.  an array: `int a\[3][4]`

    `a\[2][1]` == ` *(a\[2]+1)`

    

3.  `int a = 1, b = 2, c = 3`

    True:` (c < b) < a`

    False: `(c > b) > a`

    >   Explanation:  `c < b` return 0 if false, return 1 if true.



4. A function: 
 ```c++
    #include <iostream>
    int main(){
        int *p = int[5];
        delete p;
        delete p;
        std::cout << "Done" << endl;
        return 0;
    }
 ```


5. `double d = 3/2;` -> `d == 1`;



6.  Use `(*functionName)` to declare a pointer points to a function is the standard approach.



7.  What's 'namespace' feature in C++? 

>   To structure aprogram into logical units