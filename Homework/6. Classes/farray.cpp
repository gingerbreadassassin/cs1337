//
// Created by CNESS on 4/4/2017.
//

#include "farray.h"

// default constructor
/*void*/ farray::farray() {
    array = new float[10];
    *array = {0};
    farraysize = 10;
}

// constructor
/*void*/ farray::farray(int n) {
    array = new float[n];
    *array = {0};
    farraysize = n;
}

// returns the biggest element of the array
float farray::farmax() const{
    float max = array[0];
    for(int i = 1; i < farraysize; i++){
        if(max < array[i]) {
            max = array[i];
        }
    }
    return max;
}

// returns the smallest element of the array
float farray::farmin() const{
    float min = array[0];
    for(int i = 1; i < farraysize; i++){
        if(min > array[i]){
            min = array[i];
        }
    }
    return min;
}

// returns the average of all elements in array
float farray::faravg() const{
    float tot = 0;
    for(int i = 0; i < farraysize; i++)
        tot += array[i];
    return tot/farraysize;
}