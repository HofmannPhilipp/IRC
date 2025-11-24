#include "commandFunctions.hpp"

bool checkNickname(const std::string &nick)
{ 
    //allowed: letters: a-z, A-Z, numbers: 0-9, extras: - [ ] \ ^ { }`
    //firstChar must NOT be extra or number
    //length 1 - 9
    if (nick.empty())
        return false;

    if (!isalpha(nick[0]))
        return false;

    if (nick.length() < 1 || nick.length() > 9)
        return false;
    
    for (size_t i = 0; i < nick.size(); i++)
    {
        char c = nick[i];

        if (isalnum(c)) 
            continue;

        if (c == '-' || c == '[' || c == ']' ||
            c == '\\' || c == '`' || c == '^' ||
            c == '{' || c == '}')
            continue;

        return false;
    }

    return true;
}
