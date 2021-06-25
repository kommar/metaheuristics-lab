#pragma once

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

namespace RandomUtils
{
	class CRandomIndex
	{
	public:
		CRandomIndex(int iSize, mt19937 &cRandomEngine);

		size_t iGetNextIndex();

	private:
		void v_shuffle();

		size_t i_size;
		mt19937 &c_random_engine;

		size_t i_next_offset;
		vector<size_t> v_indexes;
	};//class CRandomIndex
}//namespace RandomUtils