#ifndef PLATFORMER_HELPER_H
#define PLATFORMER_HELPER_H
#include <string>
#include <cctype>

std::string strip(const std::string &inpt)
{
    auto start_it = inpt.begin();
    auto end_it = inpt.rbegin();
    while (std::isspace(*start_it))
        ++start_it;
    while (std::isspace(*end_it))
        ++end_it;
    return std::string(start_it, end_it.base());
}

#endif //PLATFORMER_HELPER_H
