#ifndef MODELSELECTOR_HPP
#define MODELSELECTOR_HPP

#include <string>

#include "Factory.hpp"
#include "Misc.hpp"
#include "Parameters.hpp"
#include "Dimensions.hpp"

class ModelSelector
{
friend class InputScriptParser;

private:
    static std::string selectedModel;
    static std::string selectedMatrixType;

public:
    template <class T>
    static auto SelectModel(Dimensions &dimensions, Parameters &parameters)
    {
        
        switch (str2int(selectedModel.c_str()))
        {
            case str2int("SpinfullUniform2D"):
                return Factory<SpinfullUniform2D>::Generate<T>(dimensions,parameters);
            case str2int("SpinfullUniformChain"):
                return Factory<SpinfullUniformChain>::Generate<T>(dimensions,parameters);

            default:
                return Factory<SpinfullUniformChain>::Generate<T>(dimensions,parameters);
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

    static auto SelectSparse(Dimensions &dimensions, Parameters &parameters)
    {
        return SelectModel<arma::sp_mat>(dimensions,parameters);
    }

    static auto SelectDense(Dimensions &dimensions, Parameters &parameters)
    {
        return SelectModel<arma::mat>(dimensions,parameters);
    }

    static std::string GetSelected()
    {
        return selectedModel+"@"+selectedMatrixType;
    }

};

std::string ModelSelector::selectedModel{""};
std::string ModelSelector::selectedMatrixType{""};

#endif