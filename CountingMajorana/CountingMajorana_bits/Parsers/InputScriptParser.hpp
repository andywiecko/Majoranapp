#ifndef PARSERS_INPUTSCRIPTPARSER_HPP
#define PARSERS_INPUTSCRIPTPARSER_HPP

#include <map>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

#include "../Misc.hpp"
#include "../QuantumSystem/Parameters.hpp"
#include "../QuantumSystem/Dimensions.hpp"
#include "../Solver.hpp"
#include "ModelSelector.hpp"

#include "ConnectionsParser.hpp"

// for convenience
using json = nlohmann::json;

class InputScriptParser
{

private:
    template <class T>
    static void ParseMap(json &jsonMap, T &map)
    {
        for (auto it : json::iterator_wrapper(jsonMap))
        {
            json &val = it.value();
            const std::string &key = it.key();
            //std::cout << key << " " << val << "\n";
            map[key] = val;
        }
    }

    static void ParseSolverOptions(json &solverOptions)
    {
        for (auto it : json::iterator_wrapper(solverOptions))
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
    typedef int type;
    static void Parse(std::string filename,
                      Parameters &parameters,
                      Dimensions &dimensions)
    {

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
        ParametersConnections parConn;
        parConn = ConnectionsParser::Parse(inputScript["connections"],parameters.map);

    }
};

#endif