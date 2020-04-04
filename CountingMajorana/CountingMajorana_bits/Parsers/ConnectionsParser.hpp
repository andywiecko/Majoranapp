#ifndef PARSERS_CONNECTIONSPARSER_HPP
#define PARSERS_CONNECTIONSPARSER_HPP

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "../QuantumSystem/Parameters.hpp"
#include "../QuantumSystem/Connections.hpp"

class ConnectionsParser
{
private:
    static bool HasArray(json &connection)
    {
        for (auto element : connection)
        {
            if (element.is_array())
                return true;
        }
        return false;
    }

    static void GetConnection(json &jsonConnection, Connection &connection, double &value)
    {
        if (HasArray(jsonConnection))
            for (auto el : jsonConnection)
            {
                if (el.is_array())
                    connection = el.get<Connection>();

                else if (el.is_number_float())
                    value = el.get<double>();
            }
        else
            connection = jsonConnection.get<Connection>();
    }

    static Connections GetAllConnections(json &parameterConnections,double defaultValue)
    {
        Connections connections;
        for (auto jsonConnection : parameterConnections)
        {
            Connection connection;
            double value{defaultValue};
            GetConnection(jsonConnection, connection, value);
            connections.map[connection] = value;
        }
        return connections;
    }

public:
    template <class T>
    static ParametersConnections Parse(json &jsonConnections, T &parameters)
    {
        ParametersConnections parConn;
        for (auto parameterConnectionsItem : json::iterator_wrapper(jsonConnections))
        {
            json &parameterConnections = parameterConnectionsItem.value();
            const std::string &key = parameterConnectionsItem.key();
            double defaultValue = parameters[key];
            parConn.map[key] = GetAllConnections(parameterConnections, defaultValue);
        }
        
        return parConn;
    }
};

#endif