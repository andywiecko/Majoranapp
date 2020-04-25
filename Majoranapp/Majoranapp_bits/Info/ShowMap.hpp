#ifndef INFO_SHOWMAP_HPP
#define INFO_SHOWMAP_HPP

#include <map>
#include "Basics.hpp"

#include "../Parsers/SystemOption.hpp"

/**
 * @brief helpers for displaying key bindings maps and others
 */
class ShowMapInfo
{
public:
    /**
     * @brief Displaying map
     * 
     * @tparam T type of map
     * @param map 
     */
    template <class T>
    static void ShowMap(T &map)
    {
        for (auto &[key, name] : map)
        {
            BasicsInfo::Comment(key, name);
        }
    }

    /**
     * @brief displaying common value of two maps
     * 
     * @tparam T1 type of map1
     * @tparam T2 type of map2
     * @param map1 
     * @param map2 
     */
    template <class T1, class T2>
    static void ShowMapCommonValue(T1 &map1, T2 &map2)
    {
        for (const auto &item : map1)
        {
            BasicsInfo::Comment(item.second, map2[item.second]);
        }
    }
};

#endif