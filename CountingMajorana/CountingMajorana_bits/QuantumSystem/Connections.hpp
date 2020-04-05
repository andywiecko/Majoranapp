#ifndef QUANTUMSYSTEM_CONNECTIONS_HPP
#define QUANTUMSYSTEM_CONNECTIONS_HPP

#include <map>
#include <vector>
#include <string>

/**
 * @brief container for sites numbers
 */
using Connection = std::vector<int>;

/**
 * @brief map of Connection and values (double)
 */
class Connections
{
public:
    std::map<Connection, double> map;
};

/**
 * @brief map of Parameter name and Connections
 * 
 */
class ParametersConnections
{
public:
    std::map<std::string, Connections> map;

    //TODO move to Info
    void Print()
    {
        // display parsed values
        for (auto item : this->map)
        {
            std::cout << "# " << item.first << ":\n";
            for (auto conn : item.second.map)
            {
                std::cout << "#   ( ";
                for (auto el : conn.first)
                    std::cout << el << " ";
                std::cout << ") : ";
                std::cout << conn.second << "\n";
            }
            
        }
    }
};

#endif