#ifndef PARSERS_CONNECTIONSPARSER_HPP
#define PARSERS_CONNECTIONSPARSER_HPP

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "../QuantumSystem/Parameters.hpp"
#include "../QuantumSystem/Connections.hpp"

/**
 * @brief parsing connections from JSON file
 * 
 */
class ConnectionsParser
{
private:
    /**
     * @brief checks if one of the item in json is an array
     * 
     * @param connection json object
     * @return true array item exists
     * @return false array item does not exist
     */
    static bool HasArray(json &connection)
    {
        for (auto element : connection)
        {
            if (element.is_array())
                return true;
        }
        return false;
    }

    /**
     * @brief Get the Connection object
     * 
     * @param jsonConnection json object to unpack
     * @param connection parsed Connection
     * @param value parsed value
     */
    static void GetConnection(json &jsonConnection, Connection &connection, double &value)
    {
        // value and array has been provided
        if (HasArray(jsonConnection))
            for (auto el : jsonConnection)
            {
                if (el.is_array())
                    connection = el.get<Connection>();

                else if (el.is_number_float())
                    value = el.get<double>();
            }
        // no value has been provided, provided numbers are sites coordinates
        else
            connection = jsonConnection.get<Connection>();
    }

    /**
     * @brief Get the all Connections objects from json object
     * 
     * @param parameterConnections json object to parse
     * @param defaultValue default value of the connection
     * @return Connections 
     */
    static Connections GetAllConnections(json &parameterConnections, double defaultValue)
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
    /**
     * @brief Parsing json object to ParametersConnetions
     * 
     * @tparam T 
     * @param jsonConnections 
     * @param parameters 
     * @return ParametersConnections 
     */
    template <class T>
    static ParametersConnections Parse(json &jsonConnections, T &parameters)
    {
        ParametersConnections parConn;
        for (auto parameterConnectionsItem : jsonConnections.items())
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