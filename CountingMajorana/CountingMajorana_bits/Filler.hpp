#ifndef SPINFULLFILLER_HPP
#define SPINFULLFILLER_HPP

#include "Parameters.hpp"
#include "EnumGamma.hpp"
#include "Hamiltonian.hpp"

// spinfull
#include "SpinfullFiller/ChemicalTerm.hpp"
#include "SpinfullFiller/KineticTerm.hpp"
#include "SpinfullFiller/ProxTerm.hpp"
// - rashba
#include "SpinfullFiller/RashbaXTerm.hpp"
#include "SpinfullFiller/RashbaYTerm.hpp"
#include "SpinfullFiller/RashbaZTerm.hpp"
// - zeeman
#include "SpinfullFiller/ZeemanXTerm.hpp"
#include "SpinfullFiller/ZeemanYTerm.hpp"
#include "SpinfullFiller/ZeemanZTerm.hpp"

// spinless
#include "SpinlessFiller/ChemicalTerm.hpp"
#include "SpinlessFiller/KineticTerm.hpp"
#include "SpinlessFiller/ProxTerm.hpp"

/**
 * @brief static class for spinfull model term filler
 * 
 * Support:
 *  - Spinfull (deg = 4) aka Rashba type model
 *      - Spinfull::KineticTerm \f$t_{ij}\f$
 *      - Spinfull::RashbaXTerm \f$\alpha_{ij}^x\f$
 *      - Spinfull::RashbaYTerm \f$\alpha_{ij}^y\f$
 *      - Spinfull::ProxTerm \f$\Delta_i \f$
 *      - Spinfull::ZeemanXTerm  \f$f_i\f$
 *      - Spinfull::ZeemanZTerm \f$ V_i^Z \f$
 *      - Spinfull::ChemicalTerm \f$ \mu_i \f$
 * 
 *  - Spinless (deg = 2) aka Kitaev type model
 *      - Spinless::KineticTerm \f$t_{ij}\f$
 *      - Spinless::ProxTerm \f$\Delta_{ij}\exp(\phi_{ij}) \f$
 *      - Spinless::ChemicalTerm \f$ \mu_i \f$
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