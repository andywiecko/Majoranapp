# Developer guide

## Table of contents

- [Developer guide](#developer-guide)
  - [Table of contents](#table-of-contents)
  - [Adding new term](#adding-new-term)
    - [Term implementation](#term-implementation)
    - [Include the header](#include-the-header)
    - [Connection repacking](#connection-repacking)
    - [Term Summary](#term-summary)
  - [Adding new model](#adding-new-model)
    - [Implement the model](#implement-the-model)
    - [Model Summary](#model-summary)

## Adding new term

The program supports Hamiltonian, which can be written in the following form

![hamiltonian](https://latex.codecogs.com/svg.latex?%5Chat%20H%20%3D%20%5Ctext%20i%20%5Csum_%7Bij%7D%20H_%7Bij%7D%20%5Cgamma_i%20%5Cgamma_j)

A detailed explanation of the algorithm can be found in the [paper][pub].

Consider the implementation of `Spinfull::ChemicalTerm`, which describes on-site chemical potential interaction.
Chemical potential term (for spinfull systems) can be written in the following form

![chemical](https://latex.codecogs.com/svg.latex?%5Cmu_i%20%28%5Chat%20n_%7Bi%5Cuparrow%7D&plus;%5Chat%20n_%7Bi%5Cdownarrow%7D%29%20%3D%20-%5Ctfrac%7B%5Ctext%20i%5Cmu_i%7D%7B2%7D%28%20%5Cgamma_%7Bi%5Cuparrow%7D%5E&plus;%5Cgamma_%7Bi%5Cuparrow%7D%5E-&plus;%20%5Cgamma_%7Bi%5Cdownarrow%7D%5E&plus;%5Cgamma_%7Bi%5Cdownarrow%7D%5E-%20%29)

An example of how to implement new terms will be demonstrated below (based on `Spinfull::ChemicalTerm`).

### Term implementation

Implementation of `Spinfull::ChemicalTerm` for spinfull systems is attached below

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

All classes, which represent Hamiltonian's term must have a template member function

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

To implement the term of the Hamiltonian, one needs to use the `Hamiltonian<T>` member function `.InsertBlock`, which has the following syntax

```c++
ham.InsertBlock(gamma1, site1, gamma2, site2, value);
```

where `gamma1` is the first gamma in the term and the `site` is corresponding site number to the `gamma1`.
`gamma2` and `site2` is the second operator defined in the term.
`value` is potential value of the term excluding imaginary unit i (imaginary unit is implied).
`gamma1` and `gamma2` are `enum class` for Majorana operator enumeration

```c++
enum class Gamma
{
    UpPlus = 0,
    UpMinus = 1,
    DownPlus = 2,
    DownMinus = 3
};
```

This enumeration class is used for enumeration of Hamiltonian's matrix rows and columns.

All implemented terms in the program can be found in
`Majoranapp/Majoranapp_bits/SpinfullFiller/.`
and
`Majoranapp/Majoranapp_bits/SpinlessFiller/.`.

### Include the header

New terms must be included in `Majoranapp/Majoranapp_bits/Filler.hpp` file.

```c++
// ...
#include "SpinfullFiller/ChemicalTerm.hpp"
// ...
```

### Connection repacking

To enable user defined connections for new implemented terms to work with JSON script, one have to modify the `Majoranapp/Majoranapp_bits/ConnectionsFiller.hpp`.
Depending on the namespace `Spinfull`, `Spinless` or other, one have to add new term to the corresponding function `static void SpinfullSwitch` or `static void SpinlessSwitch`, by expanding the function with the following code

```c++
template <class T>
static void SpinfullSwitch(
    Hamiltonian<T> &hamiltonian,
    Connections &connections,
    const std::string &name)
{
// ...
    ConnectionsRepacking<T, Spinfull::ChemicalTerm>(hamiltonian, connections, name);
// ...
}
```

### Term Summary

To implement new term:

1. Create header file of the new term in `Majoranapp/Majoranapp_bits/SpinfullFiller/.`,
`Majoranapp/Majoranapp_bits/SpinlessFiller/.` or other namespace than `Spinfull`/`Spinless`;
2. Include header in `Filler`: `Majoranapp/Majoranapp_bits/Filler.hpp`;
3. Update appropriate function in `Majoranapp/Majoranapp_bits/ConnectionsFiller.hpp`;
4. Recompile.

## Adding new model

In this part of the tutorial implementation of the new models will be presented based on the `SpinlessUniformChainModel` implementation.

All implemented models can be found in `Majoranapp/Majoranapp_bits/Factory/.`.

### Implement the model

Consider `SpinlessUniformChainModel` implementation:

```c++
class SpinlessUniformChain : public DefaultViewer
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

        // local
        for (int i = 0; i < L; i++)
        {
            Filler<Spinless::ChemicalTerm>::Fill(ham, parameters, i);
        }

        // non-local
        for (int i = 0; i < L - 1; i++)
        {
            Filler<Spinless::KineticTerm>::Fill(ham, parameters, i, i + 1);
            Filler<Spinless::ProxTerm>::Fill(ham, parameters, i, i + 1, phase);
        }

        return ham;
    }

    static constexpr char name[] = "SpinlessUniformChain";
};
```

Each model implementation requires static member function

```c++
template <class T>
static Hamiltonian<T> Generate(QuantumSystem &quantumSystem)
```

and model name

```c++
static constexpr char  name[]
```

which is used as a model's ID in JSON script.
`Generate(...)` function has argument of a type `QuantumSystem`.
In `QuantumSystem` all information about system is stored (dimensions, parameters, connections etc.).
The model implementation is straightforward.
First, all needed dimensions

```c++
    Dimensions &dimensions = quantumSystem.dimensions;
```

dimensions

```c++
    Parameters &parameters = quantumSystem.parameters;
```

 are caught from `quantumSystem`.
 Then one needs to import dimensions `int L, W, H`, set the degree of the system `deg`

 ```c++
    int deg = 2; // spinless system, spinfull = 4
    double phase = 0.0;
    int L = dimensions.GetLength();

    // check width and height for warning
    int W = dimensions.GetWidth();
    int H = dimensions.GetHeight();
```

In the implementation we used

```c++
    Info::DimensionsWarningOnly1D(L,W,H);
```

such command checks if **only** `L>1`, otherwise an appropriate notification will be display on the screen (note: chain is one dimensional system).

In the next step, user have to specify explicit form of the Hamiltonian, by selecting the terms and connections.
Then, definition of the Hamiltonian object

```c++
    Hamiltonian<T> ham(L, deg);
```

system size (number of sites = `L`) and degree of the system (`deg`) is specified.

`Filler<T>` class is used to fill the Hamiltonian matrix elements, e.g. implementation of the uniform chemical potential interaction(`ChemicalTerm`) can be achieved by the following

```c++
    // `i` enumerates sites
    // `L` total number of sites (one-dimensional system)
    for (int i = 0; i < L; i++)
    {
        // Note: first specify namespace `Spinless`
        //       then the interaction type T
        Filler<Spinless::ChemicalTerm>::Fill(ham, parameters, i);
    }
```

The presented above code snippet corresponds to the following Hamiltonian term

![chemical term](https://latex.codecogs.com/svg.latex?%5Chat%20H_%5Cmu%20%3D%20%5Csum_i%20%5Cmu_i%20%5Chat%20n_i)

In similar way other terms of Hamiltonian, for one-dimensional spinless chain can be adding (particle hopping and proximity effect of the superconductor)

```c++
    for (int i = 0; i < L - 1; i++)
    {
        Filler<Spinless::KineticTerm>::Fill(ham, parameters, i, i + 1);
        Filler<Spinless::ProxTerm>::Fill(ham, parameters, i, i + 1, phase);
    }
```

Finally, one have to include new model class in `Majoranapp/Majoranapp_bits/Factory.hpp` header to make it available in the program.

### Vector Viewers

In the previous example, defined class is derived from `public DefaultViewer`.
By inheritance, author of the model must select `VectorViewer` for the model.
`VectorViewer` specifies how sites should be displayed in the result, e.g. `Grid2DViewer` will map site number *i* in two dimensional grid layout: *i* ->(*x,y*).
`VectorViewers`, which are available, can be found in `Majoranapp/Majoranapp_bits/VectorViewers/.`.
Current version support 3 different `VectorViewers`

- `DefaultViewer`: no mapping, one-dimensional system;
- `Grid2DViewer`: two-dimensional grid mapping: *i* -> (*x,y*);
- `Grid3DViewer`: three-dimensional grid mapping: *i* -> (*x,y,z*);

### Models repacking

To make model name available from JSON input script, one have to modify the `ModelSelector` class.
In `Majoranapp/Majoranapp_bits/Parsers/ModelSelector.hpp`
in function

```c++
template <class T> static auto SelectModel(QuantumSystem &quantumSystem)
```

It can be achieved by adding appropriate `case` with `GetHamiltonian<T1,T2>` function in the `switch` sequence

```c++
// ...
    case str2int(SpinlessUniformChain::name):
        return GetHamiltonian<SpinlessUniformChain,T>(quantumSystem);
// ...
```

### Model Summary

To implement new model

1. Create header file of new model in `Majoranapp/Majoranapp_bits/Factory/.`;
2. Make sure that `VectorViewer` is specified for the model (parent class);
3. Inlude new model in the `Majoranapp/Majoranapp_bits/Factory.hpp`;
4. Update apropriete function in `Majoranapp/Majoranapp_bits/Parser/ModelSelector.hpp`.

[pub]:tutaj_super_link
