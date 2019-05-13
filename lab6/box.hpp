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