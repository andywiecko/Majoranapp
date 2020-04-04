#include "CountingMajorana/CountingMajorana.hpp"

int main(int argc, char *argv[])
{
	ArgvParser argvParser;
	if (argvParser.Parse(argc, argv))
		return 0;

	QuantumSystem &quantumSystem = argvParser.quantumSystem;

	if (ModelSelector::GetSelected() == " @ ")
	{
		/**
		 * @brief matrix typedef:
		 * support for: arma::mat, arma::sp_mat
		 */
		using matrixType = arma::sp_mat;

		/**
		 * @brief geometry and model type
		 * support for:
		 * - SpinfullUniformChain (Length)
		 * - SpinlessUniformChain (Length)
	 	 * - SpinfullUniform2D    (Length, Width)
	 	 */
		using geometry = SpinfullUniform2D;

		auto ham = Factory<geometry>::Generate<matrixType>(quantumSystem);

		Solver::tol = 0.005; // tolerance of convergance
		Solver::noe = 30;	 // number of eigenvalues
		Solver::showEigenvectors = false;
		Solver::Diagonalize(ham);
	}
	// parsed from JSON
	else if (ModelSelector::SparseSelected())
	{
		auto ham = ModelSelector::SelectSparse(quantumSystem);
		Solver::Diagonalize(ham);
		//ham.Print()
	}
	else if (ModelSelector::DenseSelected())
	{
		auto ham = ModelSelector::SelectDense(quantumSystem);
		Solver::Diagonalize(ham);
		//ham.Print();
	}
	else
	{
		Info::Warning("Warning, unrecognized model and/or matrix type: ",
					  ModelSelector::GetSelected());
		Info::Warning("Exiting...");
	}
}
