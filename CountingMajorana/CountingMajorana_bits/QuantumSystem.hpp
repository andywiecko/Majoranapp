#ifndef QUANTUMSYSTEM_HPP
#define QUANTUMSYSTEM_HPP

#include "QuantumSystem/Parameters.hpp"
#include "QuantumSystem/Dimensions.hpp"
#include "QuantumSystem/Connections.hpp"

class QuantumSystem
{
public:
    Parameters parameters;
    Dimensions dimensions;
    ParametersConnections parametersConnections;
};

#endif