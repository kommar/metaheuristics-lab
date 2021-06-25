#pragma once

#include "Mutation.h"
#include "RandomIndex.h"

using namespace RandomUtils;

namespace Mutations
{
	class CRealDifferentialEvolutionMutation : public CDifferentialEvolutionMutation<double>
	{
	public:
		CRealDifferentialEvolutionMutation(IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, bool bIsPopulationRequired);

	protected:
		virtual void v_repair(vector<double> &vSolution);
	};//class CRealDifferentialEvolutionMutation : public CDifferentialEvolutionMutation<double>


	class CRealRand1Mutation : public CRealDifferentialEvolutionMutation
	{
	public:
		CRealRand1Mutation(IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, double dScalingFactor);

	protected:
		virtual void v_mutate(vector<double> &vSolution);

	private:
		double d_scaling_factor;
	};//class CRealRand1Mutation : public CRealDifferentialEvolutionMutation


	class CRealRand2Mutation : public CRealDifferentialEvolutionMutation
	{
	public:
		CRealRand2Mutation(IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, double dScalingFactor0, double dScalingFactor1);

	protected:
		virtual void v_mutate(vector<double> &vSolution);

	private:
		double d_scaling_factor_0;
		double d_scaling_factor_1;
	};//class CRealRand2Mutation : public CRealDifferentialEvolutionMutation


	class CRealCurrentToRandom1Mutation : public CRealDifferentialEvolutionMutation
	{
	public:
		CRealCurrentToRandom1Mutation(IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, double dScalingFactor0, double dScalingFactor1);

	protected:
		virtual void v_mutate(vector<double> &vSolution);

	private:
		double d_scaling_factor_0;
		double d_scaling_factor_1;
	};//class CRealCurrentToRandom1Mutation : public CRealDifferentialEvolutionMutation
}//namespace Mutations