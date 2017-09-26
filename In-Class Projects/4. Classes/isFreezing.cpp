//
// Created by Connor and Matthew on 4/6/2017.
//

#include "isFreezing.h"

bool isFreezing::isEthylFreezing(){
    if(t<=-173)
        return true;
    else
        return false;
}
bool isFreezing::isEthylBoiling() {
    if (t >= 172)
        return true;
    else
        return false;
}
bool isFreezing::isOxygenFreezing() {
    if (t <= -362)
        return true;
    else
        return false;
}
bool isFreezing::isOxygenBoiling() {
    if (t >= -306)
        return true;
    else
        return false;
}
bool isFreezing::isWaterFreezing() {
    if (t <= 32)
        return true;
    else
        return false;
}
bool isFreezing::isWaterBoiling() {
    if (t >= 212)
        return true;
    else
        return false;
}