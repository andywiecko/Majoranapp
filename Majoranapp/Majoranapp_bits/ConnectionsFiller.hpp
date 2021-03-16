#ifndef CONNECTIONSFILLER_HPP
#define CONNECTIONSFILLER_HPP

#include "QuantumSystem/Connections.hpp"
#include "Hamiltonian.hpp"
#include "Misc.hpp"
#include "Filler.hpp"

/**
 * @brief class for filling Hamiltonian matrix elements from ParametersConnections
 */
class ConnectionsFiller
{
private:
    /**
     * @brief Repacking local (1-site) term O
     * 
     * @tparam T
     * @tparam O 
     * @param hamiltonian 
     * @param connections 
     */
    template <class T, class O>
    static void LocalConnectionRepacking(Hamiltonian<T> &hamiltonian,
                                         Connections &connections)
    {
        for (auto &connection : connections.map)
        {
            int to = connection.first.at(0);
            double value = connection.second;
            Filler<O>::template Fill<T>(hamiltonian, value, to);
        }
    }

    /**
     * @brief Repacking non-local (2-sites) term O
     * 
     * @tparam T 
     * @tparam O 
     * @param hamiltonian 
     * @param connections 
     */
    template <class T, class O>
    static void NonLocalConnectionRepacking(Hamiltonian<T> &hamiltonian,
                                            Connections &connections)
    {
        for (auto &connection : connections.map)
        {
            int from = connection.first.at(0);
            int to = connection.first.at(1);
            double value = connection.second;
            Filler<O>::template Fill<T>(hamiltonian, value, from, to);
        }
    }

    /**
     * @brief Repacking all terms (local and non-local)
     * 
     * @tparam T 
     * @tparam O 
     * @param hamiltonian 
     * @param connections 
     * @param name 
     */
    template <class T, class O>
    static void ConnectionsRepacking(Hamiltonian<T> &hamiltonian,
                                     Connections &connections,
                                     const std::string &name)
    {
        if (name == O::name)
        {
            if constexpr (O::locality == 1)
            {
                LocalConnectionRepacking<T, O>(hamiltonian, connections);
            }
            else if constexpr (O::locality == 2)
            {
                NonLocalConnectionRepacking<T, O>(hamiltonian, connections);
            }
        }
    }

    /**
     * @brief List of all Spinfull terms which are avaliable from ParametersConnections
     * 
     * @tparam T 
     * @param hamiltonian 
     * @param connections 
     * @param name 
     */
    template <class T>
    static void SpinfullSwitch(Hamiltonian<T> &hamiltonian,
                               Connections &connections,
                               const std::string &name)
    {
        ConnectionsRepacking<T, Spinfull::ChemicalTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::ProxTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::ZeemanXTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::ZeemanYTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::ZeemanZTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::KineticTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::RashbaXTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::RashbaYTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::RashbaZTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::RealKineticTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinfull::ImagKineticTerm>(hamiltonian, connections, name);
    }

    /**
     * @brief List of all Spinless terms which are avaliable from ParametersConnections
     * 
     * @tparam T 
     * @param hamiltonian 
     * @param connections 
     * @param name 
     */
    template <class T>
    static void SpinlessSwitch(Hamiltonian<T> &hamiltonian,
                               Connections &connections,
                               const std::string &name)
    {
        ConnectionsRepacking<T, Spinless::ChemicalTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinless::ProxTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinless::KineticTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinless::RealProxTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinless::ImagProxTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinless::RealKineticTerm>(hamiltonian, connections, name);
        ConnectionsRepacking<T, Spinless::ImagKineticTerm>(hamiltonian, connections, name);
    }

public:
    /**
     * @brief constructing Spinfull terms from ParametersConnections
     * 
     * @tparam T 
     * @param hamiltonian 
     * @param parameterConnections 
     */
    template <class T>
    static void Spinfull(Hamiltonian<T> &hamiltonian,
                         ParametersConnections &parameterConnections)
    {
        for (auto &[name, connections] : parameterConnections.map)
        {
            SpinfullSwitch(hamiltonian, connections, name);
        }
    }

    /**
     * @brief constructing Spinless terms from ParametersConnections
     * 
     * @tparam T 
     * @param hamiltonian 
     * @param parameterConnections 
     */
    template <class T>
    static void Spinless(Hamiltonian<T> &hamiltonian,
                         ParametersConnections &parameterConnections)
    {
        for (auto &[name, connections] : parameterConnections.map)
        {
            SpinlessSwitch(hamiltonian, connections, name);
        }
    }

};

#endif