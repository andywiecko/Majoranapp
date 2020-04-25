# Developer guide

## Adding term

Method described in the [paper][pub] supports all Hamiltonians,
which can be written in the following form

![hamiltonian](https://latex.codecogs.com/svg.latex?%5Chat%20H%20%3D%20%5Ctext%20i%20%5Csum_%7Bij%7D%20H_%7Bij%7D%20%5Cgamma_i%20%5Cgamma_j)

Let's analyse the `ChemicalTerm`.
Such term should be responsible for the following matrix elements

![mu](https://latex.codecogs.com/svg.latex?%5Cmu_i%28%5Chat%20n_%7Bi%5Cuparrow%7D%20&plus;%20%5Chat%20n_%7Bi%5Cdownarrow%7D%29%20%3D%20-%5Ctfrac%7B%5Ctext%20i%20%5Cmu_i%7D2%20%28%5Cgamma_%7Bi%5Cuparrow%7D%5E&plus;%5Cgamma_%7Bi%5Cuparrow%7D%5E-&plus;%5Cgamma_%7Bi%5Cdownarrow%7D%5E&plus;%5Cgamma_%7Bi%5Cdownarrow%7D%5E-%29)

```c++
class ChemicalTerm
{
public:

    template <class T>
    static void Fill(Hamiltonian<T> &ham, double mu, int i)
    {
        ham.InsertBlock(Gamma::UpPlus, i, Gamma::UpMinus, i, -0.5 * mu);
        ham.InsertBlock(Gamma::DownPlus, i, Gamma::DownMinus, i, -0.5 * mu);
    }

    static const std::string name;
    static constexpr size_t locality{1};
};

const std::string ChemicalTerm::name{"mu_potential"};
```

## Adding model

TODO


[pub]:tuta_super_link