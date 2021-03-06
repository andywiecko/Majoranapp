#ifndef PARSERS_INPUTSCRIPTPARSER_HPP
#define PARSERS_INPUTSCRIPTPARSER_HPP

#include <map>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

#include "../Misc.hpp"
#include "../QuantumSystem.hpp"
#include "../QuantumSystem/Parameters.hpp"
#include "../QuantumSystem/Dimensions.hpp"
#include "../Solver.hpp"
#include "ModelSelector.hpp"

#include "ConnectionsParser.hpp"

// for convenience
using json = nlohmann::json;

/**
 * @brief Parsing JSON input script
 */
class InputScriptParser
{

private:
    /**
     * @brief unpacking json into map
     * 
     * @tparam T type map
     * @param jsonMap 
     * @param map 
     */
    template <class T>
    static void ParseMap(json &jsonMap, T &map)
    {
        for (auto it : jsonMap.items())
        {
            json &val = it.value();
            const std::string &key = it.key();
            //std::cout << key << " " << val << "\n";
            map[key] = val;
        }
    }

    /**
     * @brief Parsing Solver options (TODO move to separate class)
     * 
     * @param solverOptions 
     */
    static void ParseSolverOptions(json &solverOptions)
    {
        for (auto it : solverOptions.items())
        {
            json &val = it.value();
            const std::string &key = it.key();
            //std::cout << key << " " << val << "\n";

            switch (str2int(key.c_str()))
            {
            case str2int("tol"):
                Solver::tol = val;
                break;
            case str2int("noe"):
                Solver::noe = val;
                break;
            case str2int("nov"):
                Solver::nov = val;
                break;
            case str2int("target"):
                Solver::target = val.get<std::string>();
                break;
            case str2int("showEigenvalues"):
                Solver::showEigenvalues = val;
                break;
            case str2int("showEigenvectors"):
                Solver::showEigenvectors = val;
                break;
            default:
                Info::Warning("Warning! Unrecognized option: ", key);
            }
        }
    }

public:
    //typedef int type;
    /**
     * @brief parse JSON file into QuantumSystem object
     * 
     * @param filename JSON file filename
     * @param quantumSystem 
     */
    static void Parse(std::string filename,
                      QuantumSystem &quantumSystem)
    {
        Info::LogBegining("Parsing JSON input script...");
        Parameters &parameters = quantumSystem.parameters;
        Dimensions &dimensions = quantumSystem.dimensions;
        ParametersConnections &parametersConnections = quantumSystem.parametersConnections;

        std::ifstream inputScriptFile{filename};
        json inputScript;
        inputScriptFile >> inputScript;

        // selecting the model
        auto &modelName = inputScript["model name"];
        ModelSelector::selectedModel = modelName.get<std::string>();
        auto &matrixType = inputScript["matrix type"];
        ModelSelector::selectedMatrixType = matrixType.get<std::string>();

        // TODO add warning when parameter name is invalid!
        ParseMap(inputScript["parameters"], parameters.map);
        ParseMap(inputScript["dimensions"], dimensions.map);
        ParseSolverOptions(inputScript["solver options"]);

        //parsing connections
        parametersConnections = ConnectionsParser::Parse(inputScript["connections"], parameters.map);
        Info::LogAccomplished();
    }
};

#endif