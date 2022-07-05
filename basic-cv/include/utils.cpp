#include "utils.h"

std::string getSeparator(int length) {
    std::string sep = "";
    for (int i = 0; i < length; i++) 
        sep += '-';
    sep += '\n';
    return sep;
}