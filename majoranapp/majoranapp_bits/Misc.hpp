#ifndef MISC_HPP
#define MISC_HPP

/**
 * @brief converting c_str() into constexpr int, which can be used in switch statement
 * 
 * @code
 * switch (value)
 * {
 *      case str2int("model 1"):
 *      ...
 * }
 * @endcode
 * 
 * @param str 
 * @param h 
 * @return constexpr unsigned int 
 */
constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

#endif