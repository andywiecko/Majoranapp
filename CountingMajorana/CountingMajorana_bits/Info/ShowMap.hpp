#ifndef INFO_SHOWMAP_HPP
#define INFO_SHOWMAP_HPP

class ShowMapInfo
{
public:
    template <class T>
    static void ShowMap(T &map)
    {
        for (auto &[key, name] : map)
        {
            std::cout << "# " << key << ": " + name + "\n";
        }
    }

    template <class T1, class T2>
    static void ShowMapCommonValue(T1 &map1, T2 &map2)
    {
        for(const auto &item: map1)
        {
            std::cout << "# "<< item.second << " = " << map2[item.second] << "\n";
        }
    }

};

#endif