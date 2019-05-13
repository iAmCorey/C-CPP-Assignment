# CS205 C/ C++ Programming - Lab Assignment 6

---

**Name**: 邱煜（Qiu Yu）

**SID**: 11611127



## Part1 - Analysis

---

This assignment is to design a class called `Box` whose dimensions are integers and private to the class.  The dimensions are labelled: length, breadth, height.

And this class should has 3 constructors: default constructor`Box()`, parameterized constructor`Box(int, int, int)`, parameterized constructor, and copy constructor`Box(const Box &)`.

And this class should has 4 member functions - `int getLength()`, `int getBreadth()`, `int getHeight()`, `long long CalculateVolume()`.

Besides, I need to overload 2 operators. `bool operator<(Box &, Box &)` and `std::ostream &operator<<(std::ostream &, Box &)`.

Finally, I need to write some test cases to check if my codes are right.



## Part2 - Code

---

### box.cpp

```cpp
#include "box.hpp"
#include <cstdlib>
#include <iosfwd>
#include <iostream>

using namespace std;

Box::Box() : length(0), breadth(0), height(0) {}
Box::Box(int l, int b, int h) : length(l), breadth(b), height(h) {}
Box::Box(const Box &box)
    : length(box.length), breadth(box.breadth), height(box.height) {}

int Box::getLength() { return length; }
int Box::getBreadth() { return breadth; }
int Box::getHeight() { return height; }
long long Box::CalculateVolume() { return length * breadth * height; }

ostream &operator<<(ostream &os, Box &box) {
    os << box.getLength() << " " << box.getBreadth() << " " << box.getHeight();
    return os;
}
bool operator<(Box &b1, Box &b2) {
    return (b1.getLength() < b2.getLength()) ||
           (b1.getBreadth() < b2.getBreadth() &&
            b1.getLength() == b2.getLength()) ||
           (b1.getHeight() < b2.getHeight() &&
            b1.getBreadth() == b2.getBreadth() &&
            b1.getLength() == b2.getLength());
}
bool operator>(Box &b1, Box &b2) {
    return !(b1 < b2);
}
```



### box.hpp

```cpp
#ifndef box_hpp
#define box_hpp

#include <iosfwd>

class Box {
   private:
    // members - in range [0, 100000]
    int length;
    int breadth;
    int height;

   public:
    // constructor and destructor
    Box();
    Box(int, int, int);
    Box(const Box &);
    ~Box(){};

    // member functions
    int getLength();
    int getBreadth();
    int getHeight();
    long long CalculateVolume();
    
};

// overload operator
std::ostream &operator<<(std::ostream &, Box &);
bool operator<(Box &, Box &);
bool operator>(Box &, Box &);

#endif
```



## Part 3 - Result & Verification

------



### Test.cpp

```cpp
#include <iostream>
#include "box.hpp"

using namespace std;

int main(){
    Box b1;
    Box b2(1,2,3);
    Box b3 = Box(0,2,3);
    Box b4(1,1,3);
    Box b5(1,2,2);

    cout << b1 << endl;
    cout << b2 << endl;
    cout << b3 << endl;
    
    if(b3 < b2){
        cout << "b3 < b2" << endl;
    }
    if(b4 < b2){
        cout << "b4" << endl;
    }
    if(b5 < b2){
        cout << "b5" << endl;
    }
    return 0;
}
```



#### Expected Output

```
0 0 0
1 2 3
0 2 3
b3 < b2
b4
b5
```



#### Real Output

```
0 0 0
1 2 3
0 2 3
b3 < b2
b4
b5
```



![Screen Shot 2019-05-13 at 21.57.51](/Users/Personal/Desktop/Screen Shot 2019-05-13 at 21.57.51.png)



## Part 4 - Difficulties & Solutions

---

1.  I met difficulties when implementing copy constructor. We need to use `const` variable as the parameter.







