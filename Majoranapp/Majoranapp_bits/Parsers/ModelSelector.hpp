#ifndef PARSERS_MODELSELECTOR_HPP
#define PARSERS_MODELSELECTOR_HPP

#include <string>
#include <vector>

#include "../Factory.hpp"
#include "../Misc.hpp"
#include "../QuantumSystem.hpp"
#include "../QuantumSystem/Parameters.hpp"
#include "../QuantumSystem/Dimensions.hpp"
#include "../VectorViewer.hpp"

/**
 * @brief selecting model through name
 */
class ModelSelector
{
    friend class InputScriptParser;

private:
    static std::string selectedModel;
    static std::string selectedMatrixType;
    static std::vector<std::string> supportedModels;

    template<class T1, class T2>
    static auto GetHamiltonian(QuantumSystem &quantumSystem)
    {
        VectorViewer::View = &T1::View;
        return Factory<T1>::template Generate<T2>(quantumSystem);
    }

public:
    template <class T>
    static auto SelectModel(QuantumSystem &quantumSystem)
    {
        // TODO:
        // - add ::name to models,
        // - automate te viewer selector -> templetize the switch
        switch (str2int(selectedModel.c_str()))
        {
        // Spinfull cases
        case str2int(SpinfullUniform3D::name):
            return GetHamiltonian<SpinfullUniform3D,T>(quantumSystem);
        case str2int(SpinfullUniform2D::name):
            return GetHamiltonian<SpinfullUniform2D,T>(quantumSystem);
        case str2int(SpinfullUniformChain::name):
            return GetHamiltonian<SpinfullUniformChain,T>(quantumSystem);
        case str2int(SpinfullUserDefined::name):
            return GetHamiltonian<SpinfullUserDefined,T>(quantumSystem);
        case str2int(SpinfullUniformMagnetic2D::name):
            return GetHamiltonian<SpinfullUniformMagnetic2D,T>(quantumSystem);

        // Spinless cases
        case str2int(SpinlessUniform2D::name):
            return GetHamiltonian<SpinlessUniform2D,T>(quantumSystem);
        case str2int(SpinlessUniformChain::name):
            return GetHamiltonian<SpinlessUniformChain,T>(quantumSystem);
        case str2int(SpinlessUserDefined::name):
            return GetHamiltonian<SpinlessUserDefined,T>(quantumSystem);

        default:
            Info::Warning("Warning, unrecognized model and/or matrix type: ", ModelSelector::GetSelected());
            Info::Warning("Running with default: ", "SpinfullUniformChain @ " + selectedMatrixType);
            return GetHamiltonian<SpinfullUniformChain,T>(quantumSystem);
        }
    }

    static bool SparseSelected()
    {
        return selectedMatrixType == "sparse";
    }

    static bool DenseSelected()
    {
        return selectedMatrixType == "dense";
    }

    /**
     * @brief arma::sp_mat template specialization
     * 
     * @param quantumSystem 
     * @return auto 
     */
    static auto SelectSparse(QuantumSystem &quantumSystem)
    {
        return SelectModel<arma::sp_mat>(quantumSystem);
    }

    /**
     * @brief arma::mat template specialization
     * 
     * @param quantumSystem 
     * @return auto 
     */
    static auto SelectDense(QuantumSystem &quantumSystem)
    {
        return SelectModel<arma::mat>(quantumSystem);
    }

    /**
     * @brief Get the Selected object 
     * 
     * @return std::string containing selected model name and data type (sparse/dense)
     */
    static std::string GetSelected()
    {
        return selectedModel + " @ " + selectedMatrixType;
    }
};

std::string ModelSelector::selectedModel{""};
std::string ModelSelector::selectedMatrixType{""};

#endif