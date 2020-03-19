#ifndef SPINFULLFILLER_HPP
#define SPINFULLFILLER_HPP

#include "Parameters.hpp"
#include "EnumGamma.hpp"
#include "Hamiltonian.hpp"

// spinfull
#include "SpinfullFiller/ChemicalTerm.hpp"
#include "SpinfullFiller/KineticTerm.hpp"
#include "SpinfullFiller/ProxTerm.hpp"
#include "SpinfullFiller/RashbaXTerm.hpp"
#include "SpinfullFiller/RashbaYTerm.hpp"
#include "SpinfullFiller/ZeemanTerm.hpp"
#include "SpinfullFiller/SpinFlipTerm.hpp"
// spinless
#include "SpinlessFiller/ChemicalTerm.hpp"
#include "SpinlessFiller/KineticTerm.hpp"
#include "SpinlessFiller/ProxTerm.hpp"

/**
 * @brief static class for spinfull model term filler
 * 
 * Support:
 *  - Spinfull (deg = 4) aka Rashba type model
 *      - kinetic term \f$t_{ij}\f$
 *      - Rashba term \f$\alpha_{ij}\f$
 *      - proximity (superconducting) term \f$\Delta_i \f$
 *      - Zeeman term \f$ V_i^Z \f$
 *      - chemical potential term \f$ \mu_i \f$
 * 
 *  - Spinless (deg = 2) aka Kitaev type model
 *      - kinetic term \f$t_{ij}\f$
 *      - proximity (superconducting) term \f$\Delta_{ij}\exp(\phi_{ij}) \f$
 *      - chemical potential term \f$ \mu_i \f$
 */
template <class O>
class Filler
{
public:
    template <class T, typename... Targs>
    static void Fill(Hamiltonian<T> &ham, Targs... Fargs)
    {
        O::template Fill<T>(ham, Fargs...);
    }

    template <class T, typename... Targs>
    static void Fill(Hamiltonian<T> &ham, Parameters &parameters, Targs... Fargs)
    {
        O::template Fill<T>(ham, parameters.map[O::name], Fargs...);
    }

private:
    static void DegreeWarning()
    {
        // TODO
    }
};

#endif