#ifndef VECTORVIEWER_HPP
#define VECTORVIEWER_HPP

#include "Info.hpp"

/**
 * @brief class for viewing eigenvectors
 */
class VectorViewer
{
public:

    //TODO it should be set by argvparser!
    static int height;
    static int length;

    /**
     * @brief displays vectors unnumbered sites
     * 
     * @tparam T 
     * @param vectors 
     * @param deg 
     */
    template <class T>
    static void View(T &vectors, int deg)
    {
        int rows = vectors.n_rows;
        int cols = vectors.n_cols;

        std::cout << "#";
        for (int col = 0; col < cols; col++)
            for (int _deg = 0; _deg < deg / 2; _deg++)
                std::cout << " g+(" << col << ",s=" << _deg << ")"
                          << " g-(" << col << ",s=" << _deg << ")";
        std::cout << std::endl;

        for (int row = 0; row < rows; row += deg)
        {
            for (int col = 0; col < cols; col++)
            {
                for (int _deg = 0; _deg < deg; _deg++)
                    std::cout << vectors(row + _deg, col) << " ";
            }
            std::cout << std::endl;
        }
    }

    /**
     * @brief displays vectors with sites numbered in 2D grid,
     * 
     * e.g. (length=5,height=2)
     * 
     * 0 1 2 3 4
     * 
     * 5 6 7 8 9
     * 
     * @tparam T 
     * @param vectors 
     * @param deg 
     */
    template <class T>
    static void View2DGrid(T &vectors, int deg)
    {
        int rows = vectors.n_rows;
        int cols = vectors.n_cols;

        std::cout << "#";
        for (int col = 0; col < cols; col++)
            for (int _deg = 0; _deg < deg / 2; _deg++)
                std::cout << " g+(" << col << ",s=" << _deg << ")"
                          << " g-(" << col << ",s=" << _deg << ")";
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

            if (x == length - 1)
            {
                x = -1;
                y++;
            }
        }
    }
};

int VectorViewer::height{1};
int VectorViewer::length{10};

#endif