//
//  main.cpp
//  lab7
//
//  Created by 邱煜 on 2019/5/26.
//  Copyright © 2019 邱煜. All rights reserved.
//

#include <iostream>
#include <vector>
#include <type_traits>
#include "template.hpp"

using namespace std;

int main(){
    cout << boolalpha << is_incrementable<int>() << endl;
    cout << boolalpha << is_incrementable<double>() << endl;
    cout << boolalpha << is_incrementable<float>() << endl;
    cout << boolalpha << is_incrementable<char>() << endl;
    cout << is_incrementable<std::string>() << endl;
    cout << is_incrementable<std::vector<int> >() << endl;

    return 0;
}


