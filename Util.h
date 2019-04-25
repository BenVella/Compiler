//
// Created by bennet.vella on 26/03/2019.
//

#ifndef COMPILER_UTIL_H
#define COMPILER_UTIL_H


#include <set>
#include <iostream>

class Util {
public:
    static bool setContains(std::set<int> p_set, int p_val);
    static bool setContains(std::set<std::string> p_set, std::string p_val);
};


#endif //COMPILER_UTIL_H
