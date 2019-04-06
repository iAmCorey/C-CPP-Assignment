//
//  def.hpp
//  lab3
//
//  Created by 邱煜 on 2019/3/29.
//  Copyright © 2019 邱煜. All rights reserved.
//

#ifndef def_hpp
#define def_hpp
#include <string>
#define Pi 3.141592654
#define R 6371

const int arraySize = 1000;
const int nameMaxLen = 35;

double calculate(double fLati, double fLong, double sLati, double sLong);
double convert(double angle);
int handleInput(std::string input, int fOrS);
int findIndex(std::string input, int fOrS);
void trim(std::string &str);

struct City{
    std::string cityName;
    std::string countryName;
    double latitude;
    double longtitude;
};

#endif /* stru_h */
