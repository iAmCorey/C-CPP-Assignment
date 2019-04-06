//
//  main.c
//  lab1
//
//  Created by 邱煜 on 2019/2/22.
//  Copyright © 2019 邱煜. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define Pi 3.141592654
#define R 6371

double calculate(double fLati, double fLong, double sLati, double sLong);
double convert(double angle);

int main() {
    char fCity[100], sCity[100];
    double fLati, fLong, sLati, sLong;
    int response;
    double result;
    
    printf("Please input the first city's name: ");
    scanf("%[^\n]", fCity);
    getchar();
    while (strlen(fCity)>30) {
        printf("Input is too long, please do not exceed 30 characters: ");
        scanf("%[^\n]", fCity);
        getchar();
    }
    
    printf("Please input the first city's latitude: ");
    response = scanf("%lf", &fLati);
    getchar();
    while (!(fLati >= -90 && fLati <= 90 && response == 1)) {
        printf("The latitude should be in range [-90, 90]: ");
        scanf("%lf", &fLati);
        getchar();
    }
    
    printf("Please input the first city's longitude: ");
    response = scanf("%lf", &fLong);
    getchar();
    while (!(fLong >= -180 && fLong <= 180 && response == 1)) {
        printf("The longtitude should be in range [-180, 180]: ");
        scanf("%lf", &fLong);
        getchar();
        
    }
    
    printf("Please input the second city's name: ");
    scanf("%[^\n]", sCity);
    getchar();
    while (strlen(sCity)>30) {
        printf("Input is too long, please do not exceed 30 characters: ");
        scanf("%[^\n]", sCity);
        getchar();
    }
    
    printf("Please input the second city's latitude: ");
    response = scanf("%lf", &sLati);
    getchar();
    while (!(sLati >= -90 && sLati <= 90 && response == 1)) {
        printf("The latitude should be in range [-90, 90]: ");
        scanf("%lf", &sLati);
        getchar();
    }
    
    printf("Please input the second city's longitude: ");
    response = scanf("%lf", &sLong);
    getchar();
    while (!(sLong >= -180 && sLong <= 180 && response == 1)) {
        printf("The longitude should be in range [-180, 180]: ");
        scanf("%lf", &sLong);
        getchar();
    }
    
    result = calculate(fLati, fLong, sLati, sLong);
    printf("The distance between %s and %s is %f km.\n", fCity, sCity, result);
    return 0;
}


double calculate(double fLati, double fLong, double sLati, double sLong){
    // 0 <= phi <= 180 -180 <= theta <= 180
    // -90 <= latitude <= 90 -180 <= longtitude <= 180
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

double convert(double angle){
    // conversion from angle to radian
    return angle * Pi / 180;
}
