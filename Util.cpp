//
// Created by bennet.vella on 26/03/2019.
//

#include "Util.h"
#include <iostream>

bool Util::setContains(std::set<int> p_set, int p_val) {
    return p_set.find(p_val) != p_set.end();
}

bool Util::setContains(std::set<std::string> p_set, std::string p_val) {
    return p_set.find(p_val) != p_set.end();
}
