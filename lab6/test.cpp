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