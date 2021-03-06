# Majoranapp

## Table of contents

- [Majoranapp](#majoranapp)
  - [Table of contents](#table-of-contents)
  - [About](#about)
  - [Quick tutorial](#quick-tutorial)
    - [Install](#install)
      - [Installing `Armadillo`](#installing-armadillo)
      - [Installing `nlohmann-json`](#installing-nlohmann-json)
    - [Compiling `Majoranapp`](#compiling-majoranapp)
    - [Prepare input script](#prepare-input-script)
    - [Run](#run)
  - [Models](#models)
  - [Cite](#cite)
  - [Contributors](#contributors)

## About

Codes for Majorana zero modes identification in non-interacting systems.
The program supports the input script in JSON format, see an example below.
The current version of the program is header-only.
The program supports Hamiltonian, which can be written in the following form

![hamiltonian](https://latex.codecogs.com/svg.latex?%5Chat%20H%20%3D%20%5Ctext%20i%20%5Csum_%7Bij%7D%20H_%7Bij%7D%20%5Cgamma_i%20%5Cgamma_j)

where gammas are general Majorana operators.
The detailed description of the algorithm, which is used for identification of the Majorana zero modes can be found in the [paper][pub].

## Quick tutorial

### Install

#### Installing `Armadillo`

`Majoranapp` depends on the [`Armadillo`][arma] library.
Before compiling `Majoranapp` please follow the instructions for `Armadillo` installation.
Before installing Armadillo, it is recommended to install (at least) the following libraries: 
[LAPACK](http://www.netlib.org/lapack/),
[ARPACK](https://www.caam.rice.edu/software/ARPACK/),
[BLAS](http://www.netlib.org/blas/),
[OPENBLAS](https://www.openblas.net/) (**highly recommended!**). When the installation of the selected libraries is completed, please install Armadillo.

#### Installing `nlohmann-json`

`Majoranapp` supports input scripts for setting system parameters.
One have to install [nlohmann-json](https://github.com/nlohmann/json).
It can be install from `Github`
or package manager

```bash
sudo apt install nlohmann-json-dev
```

Make sure that you have installed at least `version 3.7.3`.

### Compiling `Majoranapp`

`Majoranapp` requires `C++17` and it is tested with `g++-7.5`,
to complie run `make`

```bash
make
```

One can generate documentation locally by

```bash
make doxy
```

which requires `doxygen`.

### Prepare input script

`Majoranapp` handles custom user input scripts, which are stored in JSON format.
Input scripts have 5 parts (2 of them are necessary)

- `model name` (mandatory) select model (see [Docs][docs] for details);
- `matrix type` (mandatory) select matrix data storage type, current two options are available:
  - `dense` (exact diagonalization);
  - `sparse` (Krylov space based methods);
- `dimensions` set dimensions of the system:
  - `length`;
  - `width`;
  - `height`;
- `parameters` set system parameters (see [Docs][docs]);
- `connections` set user defined geometries (available for the selected models);
- `solver options` set eigendecomposition options:
  - `tol` convergence tolerance (lower the better, see [Armadillo][arma] docs);
  - `noe` number of eigenvalues (sparse);
  - `nov` number of eigenvectors;
  - `target` eigenvalues (see [Armadillo][arma] docs);
  - `showEigenvalues` (bool, default `true`) display the lambdas, see the [publication][pub] for the details;
  - `showEigenvectors` (bool, default `false`) display eigenvectors for the corresponding lambdas.

```json
{
  "model name": "SpinlessUniformChain",
  "matrix type": "sparse",
  "dimensions": {
    "Length": 1000
  },
  "parameters": {
    "t_integral": 10.0,
    "delta": -1.0,
    "mu_potential": 0.0
  },
  "solver options": {
    "tol": 0.0,
    "noe": 50,
    "nov": 2,
    "target": "sa",
    "showEigenvalues": true,
    "showEigenvectors": true
  }
}
```

To see example scripts go into the `InputScripts` directory.

### Run

What is the next step after the prepared input script?
To run the simulation for the selected `input_script.json`, type

```bash
./majoranapp.exe -f input_script.json
```

One does not have to prepare separate input scripts for slightly different cases.
 The parameters can be specified after input script flag, example

```bash
./majoranapp.exe -f input_script.json -L 10
```

This will run the simulation for the system with parameters set in the input script but the length will be set to 10.

Use `-h` flag to see the current key bindings for the system parameters and program options:

```bash
$ ./majoranapp.exe -h
# ========================================
# Majoranapp       @ 0.200.0 (alpha)
# armadillo        @ 9.850.1 (Pyrocumulus Wrath)
# nlohmann JSON    @ 3.7.3
# ========================================
# Program options
# opt ARG description
# ========================================
# -f [ARG] filename: select inputscript filename
# -h       help: show help page
# -q       quiet: decrease output verbosity
# -v       verbose: increase output verbosity
# ========================================
# Parameters settings
# key   name
# ========================================
# -H Height
# -L Length
# -W Width
# -X rashbaX
# -Y rashbaY
# -Z rashbaZ
# -d delta
# -m mu_potential
# -t t_integral
# -x zeemanX
# -y zeemanY
# -z zeemanZ
# ========================================
# Example
# ========================================
# The following command will run program with
# settings and parameters loaded from JSON
# and the Length will be replaced by 100:
#
# ./majoranapp.exe -f inputscript.json -L 100
```

The verbose flag (`-v`) can be useful for debugging and for measuring the program execution time.

## Models

To see the full model description please visit the [Docs][docs] page.
Current version support the following models:

- Spinless models (aka Kitaev models)
  - chain
  - 2D system
  - user geometry defined
- Spinfull models (aka Rashba models)
  - chain
  - 2D system
  - 3D system
  - user geometry defined

## Cite

Please cite the following papers if you use the program in your research and/or software.

- [arxiv][pub]

## Contributors

- [Andrzej Więckowski](https://andywiecko.github.io) @ Wrocław University of Science and Technology
- [Michał Kupczyński](https://scholar.google.com/citations?user=0aTIsJMAAAAJ&hl=en) @ Wrocław University of Science and Technology

[pub]:https://arxiv.org/abs/2006.10153
[arma]:http://arma.sourceforge.net/
[docs]:https://andywiecko.github.io/Majoranapp/index.html
