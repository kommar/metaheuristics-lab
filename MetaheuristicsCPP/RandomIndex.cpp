#include "RandomIndex.h"

using namespace RandomUtils;

CRandomIndex::CRandomIndex(int iSize, mt19937 &cRandomEngine)
	: i_size(iSize), c_random_engine(cRandomEngine), i_next_offset(0), v_indexes(iSize)
{
	iota(v_indexes.begin(), v_indexes.end(), 0);
	v_shuffle();
}//CRandomIndex::CRandomIndex(int iSize, mt19937 &cRandomEngine)

size_t CRandomIndex::iGetNextIndex()
{
	if (i_next_offset == i_size)
	{
		v_shuffle();
		i_next_offset = 0;
	}//if (i_next_offset == i_size)

	return v_indexes[i_next_offset++];
}//size_t CRandomIndex::iGetNextIndex()

void CRandomIndex::v_shuffle()
{
	shuffle(v_indexes.begin(), v_indexes.end(), c_random_engine);
}//void CRandomIndex::v_shuffle()