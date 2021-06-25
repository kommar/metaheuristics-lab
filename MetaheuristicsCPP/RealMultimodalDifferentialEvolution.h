#pragma once

#include "Generator.h"
#include "MultimodalOptimizationResult.h"
#include "Mutation.h"
#include "PopulationOptimizer.h"
#include "RealMultimodalOptimizationState.h"
#include "Selection.h"

#include <ctime>
#include <unordered_set>
#include <vector>

using namespace Generators;
using namespace Mutations;
using namespace Selections;

using namespace std;

namespace Optimizers
{
	class CRealMultimodalDifferentialEvolution : public CPopulationOptimizer<double, double, CMultimodalOptimizationResult<double, unordered_set<vector<double>*>::iterator>>
	{
	public:
		CRealMultimodalDifferentialEvolution(IMultimodalEvaluation<double> &cMultimodalEvaluation,
			IStopCondition &cStopCondition,
			IGenerator<double> &cGeneration,
			IDifferentialEvolutionMutation<double> &cMutation,
			mt19937 &cRandomEngine,
			int iPopulationSize,
			double dCrossoverProbability);

	protected:
		virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime);

		virtual void v_mutation();
		virtual void v_selection();

	private:
		void v_update_mutation_data();

		void v_crossover();

		vector<CIndividual<double, double>*> v_mutants_trials;

		CNullSelection<double, double> c_null_selection;
		IDifferentialEvolutionMutation<double> &c_de_mutation;

		mt19937 &c_random_engine;

		double d_crossover_probability;
	};//class CRealMultimodalDifferentialEvolution : public CPopulationOptimizer<double, double, CMultimodalOptimizationResult<double, unordered_set<vector<double>*>::iterator>>
}//namespace Optimizers