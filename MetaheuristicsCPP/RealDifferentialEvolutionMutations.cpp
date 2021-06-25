#include "RealDifferentialEvolutionMutations.h"

using namespace Mutations;


CRealDifferentialEvolutionMutation::CRealDifferentialEvolutionMutation(IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, bool bIsPopulationRequired)
	: CDifferentialEvolutionMutation<double>(cEvaluationProfile, cRandomEngine, bIsPopulationRequired)
{

}//CRealDifferentialEvolutionMutation::CRealDifferentialEvolutionMutation(IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, bool bIsPopulationRequired)

void CRealDifferentialEvolutionMutation::v_repair(vector<double> &vSolution)
{
	IConstraint<double> &c_contraint = c_evaluation_profile.cGetConstraint();

	for (size_t i = 0; i < vSolution.size(); i++)
	{
		if (vSolution[i] < c_contraint.tGetLowerBound(i))
		{
			vSolution[i] = c_contraint.tGetLowerBound(i);
		}//if (vSolution[i] < c_contraint.tGetLowerBound(i))
		else if (vSolution[i] > c_contraint.tGetUpperBound(i))
		{
			vSolution[i] = c_contraint.tGetUpperBound(i);
		}//else if (vSolution[i] > c_contraint.tGetUpperBound(i))
	}//for (size_t i = 0; i < vSolution.size(); i++)
}//void CRealDifferentialEvolutionMutation::v_repair(vector<double> &vSolution)


CRealRand1Mutation::CRealRand1Mutation(IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, double dScalingFactor)
	: CRealDifferentialEvolutionMutation(cEvaluationProfile, cRandomEngine, true), d_scaling_factor(dScalingFactor)
{

}//CRealRand1Mutation::CRealRand1Mutation(IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, double dScalingFactor)

void CRealRand1Mutation::v_mutate(vector<double> &vSolution)
{
	CRandomIndex c_random_index(v_population.size(), c_random_engine);

	size_t i_index_0 = c_random_index.iGetNextIndex();
	size_t i_index_1 = c_random_index.iGetNextIndex();
	size_t i_index_2 = c_random_index.iGetNextIndex();

	for (size_t i = 0; i < vSolution.size(); i++)
	{
		vSolution[i] = v_population[i_index_0]->at(i) + d_scaling_factor * (v_population[i_index_1]->at(i) - v_population[i_index_2]->at(i));
	}//for (size_t i = 0; i < vSolution.size(); i++)
}//void CRealRand1Mutation::v_mutate(vector<double> &vSolution)


CRealRand2Mutation::CRealRand2Mutation(IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, double dScalingFactor0, double dScalingFactor1)
	: CRealDifferentialEvolutionMutation(cEvaluationProfile, cRandomEngine, true), d_scaling_factor_0(dScalingFactor0), d_scaling_factor_1(dScalingFactor1)
{

}//CRealRand2Mutation::CRealRand2Mutation(IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, double dScalingFactor0, double dScalingFactor1)

void CRealRand2Mutation::v_mutate(vector<double> &vSolution)
{
	CRandomIndex c_random_index(v_population.size(), c_random_engine);

	size_t i_index_0 = c_random_index.iGetNextIndex();
	size_t i_index_1 = c_random_index.iGetNextIndex();
	size_t i_index_2 = c_random_index.iGetNextIndex();
	size_t i_index_3 = c_random_index.iGetNextIndex();
	size_t i_index_4 = c_random_index.iGetNextIndex();

	for (size_t i = 0; i < vSolution.size(); i++)
	{
		vSolution[i] = v_population[i_index_0]->at(i) 
			+ d_scaling_factor_0 * (v_population[i_index_1]->at(i) - v_population[i_index_2]->at(i))
			+ d_scaling_factor_1 * (v_population[i_index_3]->at(i) - v_population[i_index_4]->at(i));
	}//for (size_t i = 0; i < vSolution.size(); i++)
}//void CRealRand2Mutation::v_mutate(vector<double> &vSolution)


CRealCurrentToRandom1Mutation::CRealCurrentToRandom1Mutation(IEvaluationProfile<double>& cEvaluationProfile, mt19937 & cRandomEngine, double dScalingFactor0, double dScalingFactor1)
	: CRealDifferentialEvolutionMutation(cEvaluationProfile, cRandomEngine, true), d_scaling_factor_0(dScalingFactor0), d_scaling_factor_1(dScalingFactor1)
{

}//CRealCurrentToRandom1Mutation::CRealCurrentToRandom1Mutation(IEvaluationProfile<double>& cEvaluationProfile, mt19937 & cRandomEngine, double dScalingFactor0, double dScalingFactor1)

void CRealCurrentToRandom1Mutation::v_mutate(vector<double> &vSolution)
{
	CRandomIndex c_random_index(v_population.size(), c_random_engine);

	size_t i_index_0 = c_random_index.iGetNextIndex();
	size_t i_index_1 = c_random_index.iGetNextIndex();
	size_t i_index_2 = c_random_index.iGetNextIndex();

	for (size_t i = 0; i < vSolution.size(); i++)
	{
		vSolution[i] += d_scaling_factor_0 * (v_population[i_index_0]->at(i) - vSolution[i]) + d_scaling_factor_1 * (v_population[i_index_1]->at(i) - v_population[i_index_2]->at(i));
	}//for (size_t i = 0; i < vSolution.size(); i++)
}//void CRealCurrentToRandom1Mutation::v_mutate(vector<double> &vSolution)