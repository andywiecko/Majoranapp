#ifndef SRC_VECTORVIEWERS_DEFAULTVIEWER_HPP
#define SRC_VECTORVIEWERS_DEFAULTVIEWER_HPP

#include <iostream>
#include <armadillo>

#include "../Info.hpp"

/**
 * @brief  displays vectors unnumbered sites
 */
class DefaultViewer
{
public:
    
    static void View(arma::mat &vectors, int deg)
    {
        int rows = vectors.n_rows;
        int cols = vectors.n_cols;

        std::cout << "# site ";
        for (int col = 0; col < cols; col++)
            for (int _deg = 0; _deg < deg / 2; _deg++)
                std::cout << Info::Gamma(_deg) << "+(" << col << ") "
                          << Info::Gamma(_deg) << "-(" << col << ") ";
        std::cout << std::endl;

        for (int row = 0,site = 0; row < rows; row += deg,site++)
        {
            std::cout << site << " ";
            for (int col = 0; col < cols; col++)
            {
                for (int _deg = 0; _deg < deg; _deg++)
                    std::cout << vectors(row + _deg, col) << " ";
            }
            std::cout << std::endl;
        }
    }

};

#endif