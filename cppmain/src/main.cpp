#include <eval-params.h>
#include <ImpreciseValue.h>
#include <Model.h>
#include <MonteCarloSimulator.h>
#include <system-constants.h>
#include <SimulationResult.h>
#include <iostream>

#include "Timer.h"

using namespace std;

int main(int argc, char **argv) {
	Timer timer;

	cout.precision(10);
	try {
		timer.startCount("Model");

		Model model(ATOM_1_LEVELS_NUMBER, ATOM_2_LEVELS_NUMBER,
				ATOM_3_LEVELS_NUMBER, FIELD_1_FOCK_STATES_NUMBER,
				FIELD_2_FOCK_STATES_NUMBER, FIELD_3_FOCK_STATES_NUMBER, KAPPA,
				DELTA_OMEGA, G, scE, J);

		timer.printElapsedTime("Model");

		MonteCarloSimulator monteCarloSimulator(MONTE_CARLO_SAMPLES_NUMBER,
				model);

		SimulationResult *result = monteCarloSimulator.simulate(TIME_STEP_SIZE,
				TIME_STEPS_NUMBER, CUDA_THREADS_PER_BLOCK, CUDA_N_BLOCKS);

		ImpreciseValue *firstCavityPhotons = result->getFirstCavityPhotons();
		cout << "Avg field photons in the first cavity: "
				<< firstCavityPhotons->mean << "; standard deviation: "
				<< firstCavityPhotons->standardDeviation << endl;

		ImpreciseValue *secondCavityPhotons = result->getSecondCavityPhotons();
		cout << "Avg field photons in the second cavity: "
				<< secondCavityPhotons->mean << "; standard deviation: "
				<< secondCavityPhotons->standardDeviation << endl;

		ImpreciseValue *thirdCavityPhotons = result->getThirdCavityPhotons();
		cout << "Avg field photons in the third cavity: "
				<< thirdCavityPhotons->mean << "; standard deviation: "
				<< thirdCavityPhotons->standardDeviation << endl;

		timer.printElapsedTime("Total time");

		//freeing up resources
		delete result;
	} catch (const std::string &message) {
		cerr << message << endl;
	} catch (char *message) {
		cerr << message << endl;
	} catch (...) {
		cout << "Exception has been thrown - terminating" << endl;
	}

	return 0;
}
