#pragma once

#include <vector>

using namespace std;

namespace Optimizers
{
	template <typename TElement, typename TIterator>
	class CMultimodalOptimizationResult
	{
	public:
		CMultimodalOptimizationResult(const TIterator &itFoundGlobalOptimaBegin, const TIterator &itFoundGlobalOptimaEnd, int iNumberOfGlobalOptima, long long iLastUpdateIteration, long long iLastUpdateFFE, double dLastUpdateTime)
			: i_number_of_global_optima(iNumberOfGlobalOptima), i_last_update_iteration(iLastUpdateIteration), i_last_update_ffe(iLastUpdateFFE), d_last_update_time(dLastUpdateTime)
		{
			double d_best_value = -DBL_MAX;

			for (TIterator it = itFoundGlobalOptimaBegin; it != itFoundGlobalOptimaEnd; it++)
			{
				v_found_global_optima.push_back(*it);
			}//for (TIterator it = itFoundGlobalOptimaBegin; it != itFoundGlobalOptimaEnd; it++)
		}//CMultimodalOptimizationResult(const TIterator &itFoundGlobalOptimaBegin, const TIterator &itFoundGlobalOptimaEnd, long long iLastUpdateIteration, long long iLastUpdateFFE, double dLastUpdateTime)

		vector<vector<TElement>*>  &vGetFoundGlobalOptima() { return v_found_global_optima; }
		int iGetNumberOfGlobalOptima() { return i_number_of_global_optima; }

		long long iGetLastUpdateIteration() { return i_last_update_iteration; }
		long long iGetLastUpdateFFE() { return i_last_update_ffe; }
		double dGetLastUpdateTime() { return d_last_update_time; }

	private:
		vector<vector<TElement>*> v_found_global_optima;
		int i_number_of_global_optima;

		long long i_last_update_iteration;
		long long i_last_update_ffe;
		double d_last_update_time;
	};//class CMultimodalOptimizationResult
}//namespace Optimizers