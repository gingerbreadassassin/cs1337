//
// Created by CNESS on 4/4/2017.
//

#ifndef INC_6_CLASSES_FARRAY_H
#define INC_6_CLASSES_FARRAY_H


class farray {
private:
    float* array;
    int farraysize;

public:
    // constructors
    farray();
    farray(int);

    // destructor
    ~farray(){delete [] array;}

    // accessors
    float farget(int index) const {return array[index];}
    float farmax() const;
    float farmin() const;
    float faravg() const;

    // mutators
    void farput(int index, float num){array[index] = num;}
};


#endif //INC_6_CLASSES_FARRAY_H
