#pragma once

#include <vector>

using namespace std;

namespace VectorUtils
{
	template <class T>
	void vClear(vector<T*> &vVector)
	{
		for (size_t i = 0; i < vVector.size(); i++)
		{
			delete vVector[i];
		}//for (size_t i = 0; i < vVector.size(); i++)

		vVector.clear();
	}//void vClear(vector<T*> &vVector)
}//namespace VectorUtils
