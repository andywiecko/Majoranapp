#include "CountingMajorana/CountingMajorana.hpp"
#include <type_traits>

int main(int argc, char *argv[])
{
	ArgvParser argvParser;
	if (argvParser.Parse(argc, argv))
		return 0;

	Dimensions dimensions = argvParser.dimensions;
	Parameters parameters = argvParser.parameters;

	// TODO hide this in argv
	VectorViewer::length = dimensions.map["Length"];
	VectorViewer::height = dimensions.map["Height"];

	if (ModelSelector::GetSelected() == "@")
	{
		std::cout << "Say whaaaat?"
				  << "\n";
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
	 	* - SpinfullUniform2D    (Length, Height)
	 	*/
		using geometry = SpinfullUniform2D;

		auto ham = Factory<geometry>::Generate<matrixType>(dimensions, parameters);

		Solver::tol = 0.005; // tolerance of convergance
		Solver::noe = 30;	 // number of eigenvalues
		Solver::showEigenvectors = false;
		Solver::Diagonalize(ham);
	}
	else if (ModelSelector::SparseSelected())
	{
		auto ham = ModelSelector::SelectSparse(dimensions, parameters);
		Solver::Diagonalize(ham);
	}
	else if (ModelSelector::DenseSelected())
	{
		auto ham = ModelSelector::SelectDense(dimensions, parameters);
		Solver::Diagonalize(ham);
	}
	else
	{
		// Warning info TODO
		std::cout << "[!] Warning, unrecognized matrix type!\nExiting...\n";
	}
}
