#ifndef SRC_VECTORVIEWERS_GRID2D_HPP
#define SRC_VECTORVIEWERS_GRID2D_HPP

#include "../VectorViewer.hpp"

/**
 * @brief displays vectors with sites numbered in 2D grid,
 * 
 * e.g. (length=5,height=2)
 * 
 * 0 1 2 3 4
 * 
 * 5 6 7 8 9
 * 
 */
class Grid2DViewer
{
public:
static void View(arma::mat &vectors, int deg)
    {
        int rows = vectors.n_rows;
        int cols = vectors.n_cols;

        std::cout << "# (site)x y ";
        for (int col = 0; col < cols; col++)
            for (int _deg = 0; _deg < deg / 2; _deg++)
                std::cout << Info::Gamma(_deg) << "+(" << col << ") "
                          << Info::Gamma(_deg) << "-(" << col << ") ";
        std::cout << std::endl;

        for (int row = 0, x = 0, y = 0; row < rows; row += deg, x++)
        {
            std::cout << x << " " << y << " ";
            for (int col = 0; col < cols; col++)
            {
                for (int _deg = 0; _deg < deg; _deg++)
                    std::cout << vectors(row + _deg, col) << " ";
            }
            std::cout << std::endl;

            if (x == VectorViewer::length - 1)
            {
                x = -1;
                y++;
            }
        }
    }
    
};

#endif