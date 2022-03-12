#pragma once

#include "Mutation.h"

namespace Mutations
{
	class CBinaryBitFlipMutation : public CMutation<bool>
	{
	public:
		CBinaryBitFlipMutation(double dProbability, IEvaluationProfile<bool> &cEvaluationProfile, mt19937 &cRandomEngine);

		virtual bool bMutate(vector<bool> &vSolution);
	};//class CBinaryBitFlipMutation : public CMutation<bool>
}//namespace Mutations