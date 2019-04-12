# CS205 C/ C++ Programming - Lab Assignment 3

---

**Name**: 邱煜（Qiu Yu）

**SID**: 11611127



## Part1 - Analysis

---

The problem is to calculate the flying distance between two cities. The cities should in the given file `world_cities.csv`. This csv file stores some cities' `city name`, `province or state name(may be absent) `, `country name`, `latitude`, `longtitude`.

The user just need to enter two cities' name only. No need to input their latitudes and longtitudes. This program will search their latitudes and longtitudes from file `world_cities_csv`.

And then the program use the below function to calculate the distance between the two cities and output the result.

>   phi = 90 - latitude 
>
>   theta = longitude 
>
>   c = sin(phi1 * pi / 180 ) * sin(phi2  * pi / 180) * cos((theta1-theta2 )* pi / 180) +cos(phi1  * pi / 180) * cos(phi2  * pi / 180) 
>
>   d = R*arccos(c) 

The program should be in a loop that keeps running until the user input the exit command `bye` (case-insensitive)

And there're some special situation need to handle:

1.  The maximum length for name is 25. (there exists a city whose name is larger than 25)
2.  The size of the array which stores all the cities' information is 800. (The total number is 988 rows.)
3.  The file `world_cities.csv` isn't found.
4.  The input city isn't found or its length < 3.
5.  The input city is some cities' names' substring, such as "New York", "New". The program should display the result and prompt user to choose it when substring matched.



## Part2 - Code

---

```cpp
//
//  main.cpp
//  lab3
//
//  Created by 邱煜 on 2019/3/29.
//  Copyright © 2019 邱煜. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "def.hpp"

using namespace std;

City cities[arraySize];
int citisNum;
string fCity, sCity;

int main() {
    double fLati, fLong, sLati, sLong;
    double result;
    
    ifstream file ("world_cities.csv");
    if(!file.is_open()){
        cout << "Open file failed!" << endl;
        exit(9);
    }
    string value;
    int i = 0;
    while(file.good()){
        // city name
        getline(file, value, ',');
        if(value.length())
        {
            cities[i].cityName = value;
            if(value.length()>nameMaxLen){
                cities[i].cityName = value.substr(0,nameMaxLen);
                cout << value << " is truncated to " << value.substr(0,nameMaxLen) << " because its name is too long." << endl;
                cout << "So please enter the name after truncated if you want to enter this city." << endl;
            }
        }
        // province name(ignored)
        getline(file, value, ',');
        // country name
        getline(file, value, ',');
        if(value.length())
        {
            cities[i].countryName = value;
        }
        // latitude
        getline(file, value, ',');
        if(value.length())
        {
            cities[i].latitude = atof(value.c_str());
        }
        // longtitude
        getline(file, value);
        if(value.length())
        {
            cities[i].longtitude = atof(value.c_str());
        }
        // handle the situation that the number of city > the array size
        if(i>arraySize-2){
            cout << "The cities array has been filled, others data after " << i+1 << " row are not loaded." << endl;
            break;
        }
        i++;
    }
    file.close();
    citisNum = i-1;
    if(i<arraySize-1){
        cout << "Loading successfully!\n" << endl;
    }
    
    while(1){
        cout << "----------------------------------------------------" << endl;
        cout << "Enter the first city's name(Enter \"bye\" to exit): ";
        getline(cin, fCity);
        trim(fCity);
        if(toUpper(fCity) == "BYE"){
            cout << "Bye" << endl;
            exit(0);
        }
        int idx1 = handleInput(fCity, 1);
        while(idx1 == -1){
            cout << "Enter the first city's name(Enter \"bye\" to exit): ";
            getline(cin, fCity);
            trim(fCity);
            if(toUpper(fCity) == "BYE"){
                cout << "Bye" << endl;
                exit(0);
            }
            idx1 = handleInput(fCity, 1);
        }
        cout << "Enter the second city's name(Enter \"bye\" to exit): ";
        getline(cin, sCity);
        trim(sCity);
        if(toUpper(sCity) == "BYE"){
            cout << "Bye" << endl;
            exit(0);
        }
        int idx2 = handleInput(sCity,2);
        while(idx2 == -1){
            cout << "Enter the second city's name(Enter \"bye\" to exit): ";
            getline(cin, sCity);
            trim(sCity);
            if(toUpper(sCity) == "BYE"){
                cout << "Bye" << endl;
                exit(0);
            }
            idx2 = handleInput(sCity,2);
        }
        
        fLati = cities[idx1].latitude;
        fLong = cities[idx1].longtitude;
        sLati = cities[idx2].latitude;
        sLong = cities[idx2].longtitude;
        result = calculate(fLati, fLong, sLati, sLong);
        cout << "The distance between " << fCity <<  " and " << sCity << " is " << result << " km." << endl;
        cout << "----------------------------------------------------\n" << endl;
    }
    return 0;
}

// 0 <= phi <= 180 -180 <= theta <= 180
// -90 <= latitude <= 90 -180 <= longtitude <= 180
double calculate(double fLati, double fLong, double sLati, double sLong){
    double phi1, phi2, theta1, theta2;
    double c;
    double result;
    phi1 = 90 - fLati;
    theta1 = fLong;
    phi2 = 90 - sLati;
    theta2 = sLong;
    c = sin(convert(phi1)) * sin(convert(phi2)) * cos(convert(theta1-theta2)) + cos(convert(phi1)) * cos(convert(phi2)) ;
    result = R * acos(c);
    return result;
}

// conversion from angle to radian
double convert(double angle){
    return angle * Pi / 180;
}

// handle all cases - return the city's index in the cities array
// fOrS - 1 means this is the first city; 2 means second.
int handleInput(string input, int fOrS){
    cout << endl;
    
    // Invalid case - #characters < 3
    if(input.length() < 3){
        cout << "Invalid input - Less than 3 characters." << endl;
        return -1;
    }
    
    // valid cases
    return findIndex(input, fOrS);
}

int findIndex(string cityName, int fOrS){
    int j = 0;
    bool NotFound = true;
    bool alreadyHave = false;
    for (int i = 0; i<citisNum; i++) {
        if (toUpper(cities[i].cityName) == toUpper(cityName)) {
            return i;
        }else if(toUpper(cities[i].cityName).find(toUpper(cityName)) == 0){
            if (!alreadyHave) {
                cout << "The matched cities you want including: " << endl;
                alreadyHave = true;
            }
            NotFound = false;
            cout << j+1 << ": " << cities[i].cityName  << endl;
            j++;
        }
    }
    if (NotFound) {
        cout << "City " << cityName << " not found!" << endl;
    }else{
        cout << "Please input the entire name of the exact city you want.\n" << endl;
    }
    return -1; // not found
}

// clear the whitespaces on both ends of the input string
void trim(string &str){
    if(!str.empty()){
        str.erase(0,str.find_first_not_of(" "));
        str.erase(str.find_last_not_of(" ") + 1);
    }
}

// to upper the input string
string toUpper(string str){
    string new_str = str;
    transform(new_str.begin(), new_str.end(), new_str.begin(), (int (*)(int))toupper);
    return new_str;
}
```



```cpp
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
std::string toUpper(std::string str);

struct City{
    std::string cityName;
    std::string countryName;
    double latitude;
    double longtitude;
};

#endif /* stru_h */
```



## Part 3 - Result & Verification

---

### Requirements part1

#### 1.

![Screen Shot 2019-04-12 at 11.25.48](/Users/Personal/Desktop/Screen Shot 2019-04-12 at 11.25.48.png)

#### 2.

![Screen Shot 2019-04-12 at 11.26.33](/Users/Personal/Desktop/Screen Shot 2019-04-12 at 11.26.33.png)

#### 3.

![Screen Shot 2019-04-12 at 11.27.22](/Users/Personal/Desktop/Screen Shot 2019-04-12 at 11.27.22.png)

#### 4.

![Screen Shot 2019-04-12 at 11.27.36](/Users/Personal/Desktop/Screen Shot 2019-04-12 at 11.27.36.png)



### Part 2

#### 1.

##### Case - bye

![Screen Shot 2019-04-12 at 11.27.36](/Users/Personal/Desktop/Screen Shot 2019-04-12 at 11.27.36.png)

##### Normal case

Test case #1:

```
Input: 
	shenzhen
	beijing
Output: 
	1941.39
Verification:
	1950
```

![Screen Shot 2019-04-12 at 11.31.14](/Users/Personal/Desktop/Screen Shot 2019-04-12 at 11.31.14.png)

![image-20190312151051998](/Users/Personal/Library/Application%20Support/typora-user-images/image-20190312151051998.png)

Test case #2:

```
Input:
	new york city
	rio de janeiro
Output:
	7751.43
Verification:
	7760
```



![image-20190312151334571](/Users/Personal/Library/Application%20Support/typora-user-images/image-20190312151334571.png)

![Screen Shot 2019-04-12 at 11.33.32](/Users/Personal/Desktop/Screen Shot 2019-04-12 at 11.33.32.png)

#### 2.

##### Case - not found & length < 3

![Screen Shot 2019-04-12 at 11.34.20](/Users/Personal/Desktop/Screen Shot 2019-04-12 at 11.34.20.png)

#### 3. 

#####  Case - substring matching - e.g. "New York" and "New"

![Screen Shot 2019-04-12 at 11.30.37](/Users/Personal/Desktop/Screen Shot 2019-04-12 at 11.30.37.png)

#### 4.

##### Case - ignore the whitespaces on both ends.

![Screen Shot 2019-04-12 at 11.31.14](/Users/Personal/Desktop/Screen Shot 2019-04-12 at 11.31.14.png)

## Part 4 - Difficulties & Solutions

---

1.  Some function needs to implements. For example, `ToUpper（）`, `trim（）`. Then I implements them myself.
2.  C++ could detect the overflow of the array. I assign a variable to record how much line it have read. Then once it larger than the pre-setting array size, the program stop reading file and display it.







