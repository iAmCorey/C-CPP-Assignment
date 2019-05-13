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
