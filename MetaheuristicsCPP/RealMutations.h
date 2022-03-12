#pragma once

#include <algorithm>
#include <vector>

#include "Mutation.h"

using namespace std;

namespace Mutations
{
	class CRealGaussianMutation : public CMutation<double>
	{
	public:
		CRealGaussianMutation(double dSigma, IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, double dProbability = 1.0);
		CRealGaussianMutation(vector<double> &vSigmas, IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, double dProbability = 1.0);

		virtual bool bMutate(vector<double> &vSolution);

		void vMultiplySigmas(double dMultiplier);

		double dGetSigma(int iDimension) { return v_sigmas[(size_t)iDimension]; }

		void vSetSigmas(double dSigma);
		void vSetSigma(int iDimension, double dSigma) { v_sigmas[(size_t)iDimension] = dSigma; }

	private:
		vector<double> v_sigmas;
	};//class CRealGaussianMutation : public CMutation<double>
}//namespace Mutations