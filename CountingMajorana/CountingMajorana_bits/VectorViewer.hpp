#ifndef VECTORVIEWER_HPP
#define VECTORVIEWER_HPP

class VectorViewer
{
public:
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

    template <class T>
    static void View2DGrid(T &vectors, int deg, int length, int height)
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

#endif