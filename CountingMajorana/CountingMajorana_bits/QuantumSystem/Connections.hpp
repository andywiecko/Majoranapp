#ifndef QUANTUMSYSTEM_CONNECTIONS_HPP
#define QUANTUMSYSTEM_CONNECTIONS_HPP

#include <map>
#include <vector>
#include <string>

using Connection = std::vector<int>;

class Connections
{
public:
    std::map<Connection, double> map;
};

class ParametersConnections
{
public:
    std::map<std::string, Connections> map;

    void Print()
    {
        // display parsed values
        for (auto item : this->map)
        {
            std::cout << "# " << item.first << ": ";
            for (auto conn : item.second.map)
            {
                std::cout << "[ ";
                for (auto el : conn.first)
                    std::cout << el << " ";
                std::cout << "] : ";
                std::cout << conn.second << ", ";
            }
            std::cout << std::endl;
        }
    }
};

#endif