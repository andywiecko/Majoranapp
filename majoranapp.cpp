#include "Majoranapp/Majoranapp.hpp"

int main(int argc, char *argv[])
{
	Info::StartClock();
	ArgvParser argvParser;
	if (argvParser.Parse(argc, argv))
		return 0;

	QuantumSystem &quantumSystem = argvParser.quantumSystem;

	if (ModelSelector::GetSelected() == " @ ")
	{

		using matrixType = arma::sp_mat;
		using geometry = SpinfullUniform2D;

		// [!] TODO hide logging in the Factory
		Info::LogBegining("Producing Hamiltonian...");
		auto ham = Factory<geometry>::Generate<matrixType>(quantumSystem);
		Info::LogAccomplished();

		Solver::tol = 0.005; // tolerance of convergence
		Solver::noe = 30;	 // number of eigenvalues
		Solver::showEigenvectors = false;
		Solver::Diagonalize(ham);
	}
	// parsed from JSON
	else if (ModelSelector::SparseSelected())
	{
		Info::LogBegining("Producing Hamiltonian...");
		auto ham = ModelSelector::SelectSparse(quantumSystem);
		Info::LogAccomplished();

		Solver::Diagonalize(ham);
		//ham.Print();
	}
	else if (ModelSelector::DenseSelected())
	{
		Info::LogBegining("Producing Hamiltonian...");
		auto ham = ModelSelector::SelectDense(quantumSystem);
		Info::LogAccomplished();

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
