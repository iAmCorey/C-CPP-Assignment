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
