//
// Created by Connor and Matthew on 4/6/2017.
//

#ifndef INC_4_CLASSES_ISFREEZING_H
#define INC_4_CLASSES_ISFREEZING_H


class isFreezing {
private:
    int t;
public:
    // constructor
    /*void*/ isFreezing(){t = 0;}
    // accessors
    bool isEthylFreezing();
    bool isEthylBoiling();
    bool isOxygenFreezing();
    bool isOxygenBoiling();
    bool isWaterFreezing();
    bool isWaterBoiling();
    // mutators
    void setTemp(int temperature){t = temperature;}
};


#endif //INC_4_CLASSES_ISFREEZING_H
