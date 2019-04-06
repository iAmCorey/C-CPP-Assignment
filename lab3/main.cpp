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
#include "def.hpp"

using namespace std;

City cities[arraySize];
string citiesStr[1000];
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
        i++;
    }
    file.close();
    citisNum = i-1;
    cout << "Loading successfully!" << endl;
    //verification
    // cout << cities[598].latitude << ", "<< cities[598].longtitude << endl;
//    for (int j = 0; j<i-1; j++) {
//        cout << j << cities[j].cityName << ", "<< cities[j].countryName;
//        cout << cities[j].latitude << cities[j].longtitude << endl;
//    }
    
    while(1){
        cout << "Enter the first city's name(Enter \"bye\" to exit): ";
        getline(cin, fCity);
        trim(fCity);
        if(fCity == "bye"){
            cout << "Bye" << endl;
            exit(0);
        }
        int idx1 = handleInput(fCity, 1);
        while(idx1 == -1){
            cout << "Enter the first city's name(Enter \"bye\" to exit): ";
            getline(cin, fCity);
            trim(fCity);
            idx1 = handleInput(fCity, 1);
        }
        
        cout << "Enter the second city's name(Enter \"bye\" to exit): ";
        getline(cin, sCity);
        trim(sCity);
        if(sCity == "bye"){
            cout << "Bye" << endl;
            exit(0);
        }
        int idx2 = handleInput(sCity,2);
        while(idx2 == -1){
            cout << "Enter the second city's name(Enter \"bye\" to exit): ";
            getline(cin, sCity);
            trim(sCity);
            idx2 = handleInput(sCity,2);
        }
        
        fLati = cities[idx1].latitude;
        fLong = cities[idx1].longtitude;
        sLati = cities[idx2].latitude;
        sLong = cities[idx2].longtitude;
        result = calculate(fLati, fLong, sLati, sLong);
        cout << "The distance between " << fCity <<  " and " << sCity << " is " << result << " km." << endl;
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
    // Invalid case - #characters < 3
    if(input.length() < 3){
        cout << "Invalid input - Less than 3 characters." << endl;
        return -1;
    }
    
    // "New" case
    if(input == "New"){
        string choice = "0";
        cout << "There're several cities whose name starts with \"New\", please select the correct one by the index." << endl;
        cout << "1: New Delhi\n2: New Orleans\n3: New York City\n4: Newcastle upon Tyne\n5: Newcastle" << endl;
        getline(cin, choice);
        trim(choice);
        char *end;
        while(choice!="1" && choice!="2" && choice!="3" && choice!="4" && choice!="5") {
            cout << "Invalid choice" << endl;
            cout << "1: New Delhi\n2: New Orleans\n3: New York City\n4: Newcastle upon Tyne\n5: Newcastle" << endl;
            getline(cin, choice);
            trim(choice);
        }
        if(choice=="1"){
            if(fOrS == 1)fCity = "New Delhi";
            else if(fOrS == 2)sCity = "New Delhi";
        }else if(choice=="2"){
            if(fOrS == 1)fCity = "New Orleans";
            else if(fOrS == 2)sCity = "New Orleans";
        }else if(choice=="3"){
            if(fOrS == 1)fCity = "New York City";
            else if(fOrS == 2)sCity = "New York City";
        }else if(choice=="4"){
            if(fOrS == 1)fCity = "Newcastle upon Tyne";
            else if(fOrS == 2)sCity = "Newcastle upon Tyne";
        }else if(choice=="5"){
            if(fOrS == 1)fCity = "Newcastle";
            else if(fOrS == 2)sCity = "Newcastle";
        }
        return (int)strtol(choice.c_str(), &end, 10) + 595;
    }
    
    // "New York" case
    if (input == "New York") {
        if(fOrS == 1)fCity = "New York City";
        else if(fOrS == 2)sCity = "New York City";
        return 598;
    }
    
    // other valid cases
    return findIndex(input, fOrS);
    
}

// handle valid cases - return the index of the city in the cities array
int findIndex(string cityName, int fOrS){
    for (int i = 0; i<citisNum; i++) {
        if (cities[i].cityName == cityName) {
            return i;
        }
    }
    cout << "City " << cityName << " not found!" << endl;
    return -1; // not found
}

// clear the whitespaces on both ends of the input string
void trim(string &str){
    if(!str.empty()){
        str.erase(0,str.find_first_not_of(" "));
        str.erase(str.find_last_not_of(" ") + 1);
    }
}
