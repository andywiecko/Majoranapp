#ifndef SRC_VECTORVIEWERS_GRID3D_HPP
#define SRC_VECTORVIEWERS_GRID3D_HPP

#include "../VectorViewer.hpp"

/**
 * @brief displays vectors with sites numbered in 3D grid,
 * 
 * e.g. (length=5,width=2,height=2)
 * 
 * slice(0)
 * 0 1 2 3 4
 * 
 * 5 6 7 8 9
 * 
 * slice(1)
 * 10 11 12 13 14
 * 
 * 15 16 17 18 19
 */
class Grid3DViewer
{

private:
    static void ToCoord(int i, int &x, int &y, int &z, int L, int W)
    {
        x = i % L;
        y = (i / L) % W;
        z = i / (L * W);
    }

public:
    static void View(arma::mat &vectors, int deg)
    {
        int rows = vectors.n_rows;
        int cols = vectors.n_cols;

        std::cout << "# x y z ";
        for (int col = 0; col < cols; col++)
            for (int _deg = 0; _deg < deg / 2; _deg++)
                std::cout << Info::Gamma(_deg) << "+(" << col << ") "
                          << Info::Gamma(_deg) << "-(" << col << ") ";
        std::cout << std::endl;

        
        for (int row = 0, site = 0,x,y,z; row < rows; row += deg, site++)
        {
            ToCoord(site, x, y, z, VectorViewer::length, VectorViewer::width);

            std::cout << x << " " << y << " " << z << " ";
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