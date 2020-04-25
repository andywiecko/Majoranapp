# Developer guide

## Adding term

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