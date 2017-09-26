/*
 * Connor Ness - cdn073000
 * Mario Bolivar - mjb160330
 */

#include <iostream>
#include <fstream>
#include "Encryption.h"
#include "Copy.h"
#include "Uppercase.h"

using namespace std;

int main() {
    ifstream inFile;
    ofstream outFile;

    Encryption obj1(15);
    obj1.doFilter(inFile, outFile);

    Uppercase obj2;
    obj2.doFilter(inFile, outFile);

    Copy obj3;
    obj3.doFilter(inFile, outFile);

    return 0;
}