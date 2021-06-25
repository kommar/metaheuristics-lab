#pragma once

#include "MultimodalOptimizationResult.h"
#include "OptimizationState.h"
#include "VectorUtils.h"

#include <cmath>
#include <unordered_set>
#include <vector>

using namespace std;

namespace Optimizers
{
	struct SRealMultimodalSeed
	{
		~SRealMultimodalSeed();

		vector<double> *pvSolution;
		double dValue;
	};//struct SRealMultimodalSeed

	class CRealMultimodalOptimizationState : public COptimizationState<double, double, CMultimodalOptimizationResult<double, unordered_set<vector<double>*>::iterator>>
	{
	public:
		CRealMultimodalOptimizationState(double dMaxValue, int iNumberOfGlobalOptima, double dNicheRadius, double dAccuracy = 1E-3);

		~CRealMultimodalOptimizationState();

		virtual bool bUpdate(const vector<double> &vSolution, const double &tValue, long long iIterationNumber, long long iFFE, double dTime, bool bOnlyImprovements);

		virtual bool bGlobalOptimumFound() { return (int)s_found_global_optima.size() >= i_number_of_global_optima; }

		virtual void vReset();

	private:
		vector<size_t> *pv_get_seed_indexes_within_niche(const vector<double> &vSolution);

		void v_set_new_result(long long iIterationNumber = 0, long long iFFE = 0, double dTime = 0);

		static bool b_exceeded_max_square_distance(const vector<double> &vSolution0, const vector<double> &vSolution1, double dMaxValue);

		vector<SRealMultimodalSeed*> v_seeds;
		unordered_set<vector<double>*> s_found_global_optima;

		double d_max_value;
		int i_number_of_global_optima;
		double d_niche_radius;
		double d_accuracy;
	};//class CRealMultimodalOptimizationState : public COptimizationState<double, double, CMultimodalOptimizationResult<double>>
}//namespace Optimizers