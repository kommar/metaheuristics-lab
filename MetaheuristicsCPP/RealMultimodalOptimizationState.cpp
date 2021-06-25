#include "RealMultimodalOptimizationState.h"

using namespace Optimizers;


SRealMultimodalSeed::~SRealMultimodalSeed()
{
	delete pvSolution;
}//SRealMultimodalSeed::~SRealMultimodalSeed()


CRealMultimodalOptimizationState::CRealMultimodalOptimizationState(double dMaxValue, int iNumberOfGlobalOptima, double dNicheRadius, double dAccuracy)
	: d_max_value(dMaxValue), i_number_of_global_optima(iNumberOfGlobalOptima), d_niche_radius(dNicheRadius), d_accuracy(dAccuracy)
{
	v_set_new_result();
}//CRealMultimodalOptimizationState::CRealMultimodalOptimizationState(double dMaxValue, int iNumberOfGlobalOptima, double dNicheRadius, double dAccuracy)

CRealMultimodalOptimizationState::~CRealMultimodalOptimizationState()
{
	VectorUtils::vClear(v_seeds);
}//CRealMultimodalOptimizationState::~CRealMultimodalOptimizationState()

bool CRealMultimodalOptimizationState::bUpdate(const vector<double> &vSolution, const double &tValue, long long iIterationNumber, long long iFFE, double dTime, bool bOnlyImprovements)
{
	bool b_updated = false;

	if (abs(tValue - d_max_value) <= d_accuracy)
	{
		vector<size_t> *pv_seed_indexes_within_niche = pv_get_seed_indexes_within_niche(vSolution);

		bool b_at_least_one_equal_or_better = false;

		vector<size_t> v_seed_indexes_to_remove;
		v_seed_indexes_to_remove.reserve(pv_seed_indexes_within_niche->size());

		for (size_t i = 0; i < pv_seed_indexes_within_niche->size(); i++)
		{
			if (tValue > v_seeds[pv_seed_indexes_within_niche->at(i)]->dValue)
			{
				v_seed_indexes_to_remove.push_back(pv_seed_indexes_within_niche->at(i));
			}//if (tValue > v_seeds[pv_seed_indexes_within_niche->at(i)]->dValue)
			else
			{
				b_at_least_one_equal_or_better = true;
			}//else if (tValue > v_seeds[pv_seed_indexes_within_niche->at(i)]->dValue)
		}//for (size_t i = 0; i < pv_seed_indexes_within_niche->size(); i++)

		for (size_t i = v_seed_indexes_to_remove.size(); i > 0; i--)
		{
			s_found_global_optima.erase(v_seeds[v_seed_indexes_to_remove[i - 1]]->pvSolution);

			delete v_seeds[v_seed_indexes_to_remove[i - 1]];
			swap(v_seeds[v_seed_indexes_to_remove[i - 1]], v_seeds[v_seeds.size() + i - v_seed_indexes_to_remove.size() - 1]);
		}//for (size_t i = v_seed_indexes_to_remove.size(); i > 0; i--)

		v_seeds.erase(v_seeds.end() - v_seed_indexes_to_remove.size(), v_seeds.end());

		if (!b_at_least_one_equal_or_better)
		{
			SRealMultimodalSeed *ps_new_seed = new SRealMultimodalSeed{ new vector<double>(vSolution), tValue };
			
			v_seeds.push_back(ps_new_seed);
			s_found_global_optima.insert(ps_new_seed->pvSolution);

			delete pc_result;
			v_set_new_result(iIterationNumber, iFFE, dTime);
			
			b_updated = true;
		}//if (!b_at_least_one_equal_or_better)

		delete pv_seed_indexes_within_niche;
	}//if (abs(tValue - d_max_value) <= d_accuracy)

	return b_updated;
}//bool CRealMultimodalOptimizationState::bUpdate(const vector<double> &vSolution, const double &tValue, long long iIterationNumber, long long iFFE, double dTime, bool bOnlyImprovements)

void CRealMultimodalOptimizationState::vReset()
{
	COptimizationState<double, double, CMultimodalOptimizationResult<double, unordered_set<vector<double>*>::iterator>>::vReset();
	v_set_new_result();
}//void CRealMultimodalOptimizationState::vReset()

vector<size_t> * CRealMultimodalOptimizationState::pv_get_seed_indexes_within_niche(const vector<double> &vSolution)
{
	vector<size_t> *pv_seeds_within_niche = new vector<size_t>();
	pv_seeds_within_niche->reserve(v_seeds.size());

	double d_square_niche_radius = d_niche_radius * d_niche_radius;

	for (size_t i = 0; i < v_seeds.size(); i++)
	{
		if (!b_exceeded_max_square_distance(*v_seeds[i]->pvSolution, vSolution, d_square_niche_radius))
		{
			pv_seeds_within_niche->push_back(i);
		}//if (!b_exceeded_max_square_distance(*v_seeds[i]->pvSolution, vSolution, d_square_niche_radius))
	}//for (size_t i = 0; i < v_seeds.size(); i++)

	return pv_seeds_within_niche;
}//vector<size_t> * CRealMultimodalOptimizationState::pv_get_seed_indexes_within_niche(const vector<double> &vSolution)

void CRealMultimodalOptimizationState::v_set_new_result(long long iIterationNumber, long long iFFE, double dTime)
{
	pc_result = new CMultimodalOptimizationResult<double, unordered_set<vector<double>*>::iterator>(s_found_global_optima.begin(), s_found_global_optima.end(), i_number_of_global_optima, iIterationNumber, iFFE, dTime);
}//void CRealMultimodalOptimizationState::v_set_new_result(long long iIterationNumber, long long iFFE, double dTime)

bool CRealMultimodalOptimizationState::b_exceeded_max_square_distance(const vector<double> &vSolution0, const vector<double> &vSolution1, double dMaxValue)
{
	double d_square_distance = 0;

	for (size_t i = 0; i < vSolution0.size() && d_square_distance <= dMaxValue; i++)
	{
		d_square_distance += (vSolution0[i] - vSolution1[i]) * (vSolution0[i] - vSolution1[i]);
	}//for (size_t i = 0; i < vSolution0.size() && d_square_distance < dMaxValue; i++)

	return d_square_distance > dMaxValue;
}//bool CRealMultimodalOptimizationState::b_exceeded_max_square_distance(const vector<double> &vSolution0, const vector<double> &vSolution1, double dMaxValue)
