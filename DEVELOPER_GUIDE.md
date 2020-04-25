# Developer guide

## Table of contents

- [Developer guide](#developer-guide)
  - [Table of contents](#table-of-contents)
  - [Adding term](#adding-term)
  - [Connection repacking](#connection-repacking)
  - [Adding model](#adding-model)
  - [Models repacking](#models-repacking)
  - [Vector Viewers](#vector-viewers)

## Adding term

The program supports Hamiltonian, which can be written in the following form

![hamiltonian](https://latex.codecogs.com/svg.latex?%5Chat%20H%20%3D%20%5Ctext%20i%20%5Csum_%7Bij%7D%20H_%7Bij%7D%20%5Cgamma_i%20%5Cgamma_j)

One can read more details about algorithm in the [paper][pub].

Consider the implementation of `ChemicalTerm`, which describes on-site chemical potential interaction.
Chemical potential term (for spinfull systems) can be written in the following form

![chemical](https://latex.codecogs.com/svg.latex?%5Cmu_i%20%28%5Chat%20n_%7Bi%5Cuparrow%7D&plus;%5Chat%20n_%7Bi%5Cdownarrow%7D%29%20%3D%20-%5Ctfrac%7B%5Ctext%20i%5Cmu_i%7D%7B2%7D%28%20%5Cgamma_%7Bi%5Cuparrow%7D%5E&plus;%5Cgamma_%7Bi%5Cuparrow%7D%5E-&plus;%20%5Cgamma_%7Bi%5Cdownarrow%7D%5E&plus;%5Cgamma_%7Bi%5Cdownarrow%7D%5E-%20%29)

Implementation of `ChemicalTerm` for spinfull systems is attached below

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

All classes, which represent Hamiltonian's term must have template member function

```c++
template <class T>
static void Fill(Hamiltonian<T> &ham, args...)
{
    //...
}
```

and two `const(expr)` variables:

- `static const std::string name` term ID used e.g. for input scripts;
- `static constexpr size_t locality` number of sites related to the term.

To implement term of the Hamiltonian, one needs to use `Hamiltonian<T>` member function `.InsertBlock`, which has the following syntax

```c++
ham.InsertBlock(gamma1, site1, gamma2, site2, value);
```

where `gamma1` is the first gamma in the term and `site` is corresponding site number to the `gamma1`.
`gamma2` and `site2` is the second operator defined in term.
`value` is potential value of the term excluding imaginary unit i (imaginary unit is implied).
`gamma1` and `gamma2` are `enum class` for Majorana opreator enumeration

```c++
enum class Gamma
{
    UpPlus = 0,
    UpMinus = 1,
    DownPlus = 2,
    DownMinus = 3
};
```

This enumeration class is used for enumeration of Hamiltonian's matrix rows and columns numbers.

All implemented terms in the program can be found in
`Majoranapp/Majoranapp_bits/SpinfullFiller/.`
and
`Majoranapp/Majoranapp_bits/SpinlessFiller/.`.

## Connection repacking

TODO

## Adding model

Consider `SpinlessUniformChainModel`

```c++
class SpinlessUniformChain
{
public:
    template <class T>
    static Hamiltonian<T> Generate(QuantumSystem &quantumSystem)
    {
        Dimensions &dimensions = quantumSystem.dimensions;
        Parameters &parameters = quantumSystem.parameters;

        int deg = 2;
        double phase = 0.0;
        int L = dimensions.GetLength();

        // check width and height for warning
        int W = dimensions.GetWidth();
        int H = dimensions.GetHeight();
        Info::DimensionsWarningOnly1D(L,W,H);

        Hamiltonian<T> ham(L, deg);
        for (int i = 0; i < L - 1; i++)
        {
            Filler<Spinless::KineticTerm>::Fill(ham, parameters, i, i + 1);
            Filler<Spinless::ProxTerm>::Fill(ham, parameters, i, i + 1, phase);
        }
        for (int i = 0; i < L; i++)
        {
            Filler<Spinless::ChemicalTerm>::Fill(ham, parameters, i);
        }

        return ham;
    }
};
```

All implemented models can be found in ``Majoranapp/Majoranapp_bits/Factory/.`

## Models repacking

TODO

## Vector Viewers

TODO

[pub]:tutaj_super_link