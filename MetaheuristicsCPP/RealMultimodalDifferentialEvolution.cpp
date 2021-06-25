#include "RealMultimodalDifferentialEvolution.h"

using namespace Optimizers;

CRealMultimodalDifferentialEvolution::CRealMultimodalDifferentialEvolution(IMultimodalEvaluation<double> &cMultimodalEvaluation, IStopCondition &cStopCondition, IGenerator<double> &cGeneration, IDifferentialEvolutionMutation<double> &cMutation, mt19937 &cRandomEngine, int iPopulationSize, double dCrossoverProbability)
	: CPopulationOptimizer<double, double, CMultimodalOptimizationResult<double, unordered_set<vector<double>*>::iterator>>(cMultimodalEvaluation, cStopCondition, new CRealMultimodalOptimizationState(cMultimodalEvaluation.tGetMaxValue(), cMultimodalEvaluation.iGetNumberOfGlobalOptima(), cMultimodalEvaluation.dGetNicheRadius()), cGeneration, c_null_selection, cMutation, iPopulationSize), c_de_mutation(cMutation), c_random_engine(cRandomEngine), d_crossover_probability(dCrossoverProbability)
{

}//CRealMultimodalDifferentialEvolution::CRealMultimodalDifferentialEvolution(IMultimodalEvaluation<double> &cMultimodalEvaluation, IStopCondition &cStopCondition, IGenerator<double> &cGeneration, IDifferentialEvolutionMutation<double> &cMutation, mt19937 &cRandomEngine, int iPopulationSize, double dCrossoverProbability)

bool CRealMultimodalDifferentialEvolution::b_run_iteration(long long iIterationNumber, clock_t tStartTime)
{
	v_update_mutation_data();

	for (size_t i = 0; i < pv_population->size(); i++)
	{
		v_mutants_trials.push_back(new CIndividual<double, double>(*pv_population->at(i)));
	}//for (size_t i = 0; i < pv_population->size(); i++)

	v_mutation();
	v_crossover();
	v_selection();

	return b_update_state();
}//bool CRealMultimodalDifferentialEvolution::b_run_iteration(long long iIterationNumber, clock_t tStartTime)

void CRealMultimodalDifferentialEvolution::v_mutation()
{
	for (size_t i = 0; i < v_mutants_trials.size(); i++)
	{
		v_mutants_trials[i]->bMutate();
	}//for (size_t i = 0; i < v_mutants_trials.size(); i++)
}//void CRealMultimodalDifferentialEvolution::v_mutation()

void CRealMultimodalDifferentialEvolution::v_selection()
{
	for (size_t i = 0; i < pv_population->size(); i++)
	{
		v_mutants_trials[i]->vEvaluate();

		if (v_mutants_trials[i]->tGetFitness() > pv_population->at(i)->tGetFitness())
		{
			delete pv_population->at(i);
			pv_population->at(i) = v_mutants_trials[i];
		}//if (v_mutants_trials[i]->tGetFitness() > pv_population->at(i)->tGetFitness())
		else
		{
			delete v_mutants_trials[i];
		}//else if (v_mutants_trials[i]->tGetFitness() > pv_population->at(i)->tGetFitness())
	}//for (size_t i = 0; i < pv_population->size(); i++)

	v_mutants_trials.clear();
}//void CRealMultimodalDifferentialEvolution::v_selection()

void CRealMultimodalDifferentialEvolution::v_crossover()
{
	uniform_real_distribution<double> c_uniform_distr;
	uniform_int_distribution<size_t> c_first_index_distr(0, (size_t)c_evaluation.iGetSize());

	size_t i_first_index, i_index;

	for (size_t i = 0; i < pv_population->size(); i++)
	{
		i_first_index = c_first_index_distr(c_random_engine);

		for (size_t j = 1; j < pv_population->at(i)->vGetGenotype().size(); j++)
		{
			if (c_uniform_distr(c_random_engine) > d_crossover_probability)
			{
				i_index = (i_first_index + j) % pv_population->at(i)->vGetGenotype().size();
				v_mutants_trials[i]->vGetGenotype()[i_index] = pv_population->at(i)->vGetGenotype()[i_index];
			}//if (c_uniform_distr(c_random_engine) > d_crossover_probability)
		}//for (size_t j = 1; j < pv_population->at(i)->vGetGenotype().size(); j++)
	}//for (size_t i = 0; i < pv_population->size(); i++)
}//void CRealMultimodalDifferentialEvolution::v_crossover()

void CRealMultimodalDifferentialEvolution::v_update_mutation_data()
{
	if (c_de_mutation.bIsPopulationRequired())
	{
		vector<vector<double>*> v_genotypes;
		v_genotypes.reserve(pv_population->size());

		for (size_t i = 0; i < pv_population->size(); i++)
		{
			v_genotypes.push_back(&pv_population->at(i)->vGetGenotype());
		}//for (size_t i = 0; i < pv_population->size(); i++)

		c_de_mutation.vSetPopulation(v_genotypes);
	}//if (c_de_mutation.bIsPopulationRequired())
}//void CRealMultimodalDifferentialEvolution::v_update_mutation_data()