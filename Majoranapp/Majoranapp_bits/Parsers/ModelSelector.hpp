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

public:
    template <class T>
    static auto SelectModel(QuantumSystem &quantumSystem)
    {
        // TODO:
        // - add ::name to models,
        // - automate te viewer selector -> templetize the switch
        switch (str2int(selectedModel.c_str()))
        {
        case str2int("SpinfullUniform3D"):
            VectorViewer::View = &SpinfullUniform3D::View;
            return Factory<SpinfullUniform3D>::Generate<T>(quantumSystem);

        case str2int("SpinfullUniform2D"):
            VectorViewer::View = &SpinfullUniform2D::View;
            return Factory<SpinfullUniform2D>::Generate<T>(quantumSystem);

        case str2int("SpinfullUniformChain"):
            return Factory<SpinfullUniformChain>::Generate<T>(quantumSystem);

        case str2int("SpinfullUserDefined"):
            return Factory<SpinfullUserDefined>::Generate<T>(quantumSystem);

        case str2int("SpinlessUniform2D"):
            VectorViewer::View = &SpinlessUniform2D::View;
            return Factory<SpinlessUniform2D>::Generate<T>(quantumSystem);

        case str2int("SpinlessUniformChain"):
            return Factory<SpinlessUniformChain>::Generate<T>(quantumSystem);

        case str2int("SpinlessUserDefined"):
            return Factory<SpinlessUserDefined>::Generate<T>(quantumSystem);

        default:
            Info::Warning("Warning, unrecognized model and/or matrix type: ", ModelSelector::GetSelected());
            Info::Warning("Running with default: ", "SpinfullUniformChain @ " + selectedMatrixType);
            return Factory<SpinfullUniformChain>::Generate<T>(quantumSystem);
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