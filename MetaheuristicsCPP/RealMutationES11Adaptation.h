#pragma once

#include "RealMutations.h"

#include <vector>

using namespace std;

namespace Mutations
{
	class IRealMutationES11Adaptation
	{
	public:
		virtual ~IRealMutationES11Adaptation() = default;

		virtual void vAdapt(double dBeforeMutationValue, vector<double> &vBeforeMutationSolution, double dAfterMutationValue, vector<double> &vAfterMutationSolution) = 0;

		virtual CRealGaussianMutation &cGetMutation() = 0;
	};//class IMutationES11Adaptation
}//namespace Mutations