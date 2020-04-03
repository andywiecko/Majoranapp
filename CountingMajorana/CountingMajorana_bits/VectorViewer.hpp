#ifndef VECTORVIEWER_HPP
#define VECTORVIEWER_HPP

#include <functional>

#include "Info.hpp"
#include "QuantumSystem/Dimensions.hpp"
#include "VectorViewers/DefaultViewer.hpp"


using ViewerFunction = std::function<void(arma::mat &vectors, int deg)>;

/**
 * @brief class for viewing eigenvectors
 */
class VectorViewer
{
public:

    static int height;
    static int length;
    static int width;

    static ViewerFunction View;

    static void SetDimensions(Dimensions dimensions)
    {
        height = dimensions.GetHeight();
        length = dimensions.GetLength();
        width = dimensions.GetWidth();
    }

};

int VectorViewer::height{1};
int VectorViewer::length{10};
int VectorViewer::width{1};


ViewerFunction VectorViewer::View = &DefaultViewer::View;

#endif