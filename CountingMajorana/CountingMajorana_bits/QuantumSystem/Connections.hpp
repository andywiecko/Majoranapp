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
    std::map<std::string,Connections> map;
};

#endif