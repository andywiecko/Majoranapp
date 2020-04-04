#ifndef CONNECTIONSFILLER_HPP
#define CONNECTIONSFILLER_HPP

#include "QuantumSystem/Connections.hpp"
#include "Hamiltonian.hpp"
#include "Misc.hpp"
#include "Filler.hpp"

class ConnectionsFiller
{
private:
    // untempletize size_t sites -> move it to terms definition
    template <class T, class O, size_t sites = 2>
    static void ConnectionsRepacking(Hamiltonian<T> &hamiltonian,
                                          Connections &connections,
                                          const std::string &name)
    {
        if constexpr (sites == 1)
        {
            if (name == O::name)
            {
                for (auto &connection : connections.map)
                {
                    int to = connection.first.at(0);
                    double value = connection.second;
                    Filler<O>::template Fill<T>(hamiltonian, value, to);
                }
            }
        }
        else if constexpr (sites == 2)
        {
            if (name == O::name)
            {
                for (auto &connection : connections.map)
                {
                    int from = connection.first.at(0);
                    int to = connection.first.at(1);
                    double value = connection.second;
                    Filler<O>::template Fill<T>(hamiltonian, value, from, to);
                }
            }
        }
    }

    template <class T>
    static void SpinfullSwitch(Hamiltonian<T> &hamiltonian,
                               Connections &connections,
                               const std::string &name)
    {
        ConnectionsRepacking<T, Spinfull::ChemicalTerm,1>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::ProxTerm,1>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::ZeemanXTerm,1>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::ZeemanYTerm,1>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::ZeemanZTerm,1>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::KineticTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::RashbaXTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::RashbaYTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::RashbaZTerm>(hamiltonian, connections, name);
    }

public:
    template <class T>
    static void Spinfull(Hamiltonian<T> &hamiltonian,
                         ParametersConnections &parameterConnections)
    {
        for (auto &[name, connections] : parameterConnections.map)
        {
            SpinfullSwitch(hamiltonian, connections, name);
        }
    }
};

#endif