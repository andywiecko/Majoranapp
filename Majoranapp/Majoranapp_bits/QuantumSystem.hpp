#ifndef QUANTUMSYSTEM_HPP
#define QUANTUMSYSTEM_HPP

#include "QuantumSystem/Parameters.hpp"
#include "QuantumSystem/Dimensions.hpp"
#include "QuantumSystem/Connections.hpp"

/**
 * @brief class containing all information about quantum system,
 * which is needed for hamiltonian construction 
 */
class QuantumSystem
{
public:
    Parameters parameters;
    Dimensions dimensions;
    ParametersConnections parametersConnections;
};

#endif