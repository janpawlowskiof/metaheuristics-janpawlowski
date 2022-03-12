#pragma once

#include "RealMutations.h"
#include "RealMutationES11Adaptation.h"

#include <list>

using namespace std;

namespace Mutations
{
	class CRealNullRealMutationES11Adaptation : public IRealMutationES11Adaptation
	{
	public:
		CRealNullRealMutationES11Adaptation(CRealGaussianMutation &cMutation);

		virtual void vAdapt(double dBeforeMutationValue, vector<double> &vBeforeMutationSolution, double dAfterMutationValue, vector<double> &vAfterMutationSolution) { }

		virtual CRealGaussianMutation &cGetMutation() { return c_mutation; };

	private:
		CRealGaussianMutation &c_mutation;
	};//class CRealNullRealMutationES11Adaptation : public IRealMutationES11Adaptation


	class CRealOneFifthRuleMutationES11Adaptation : public CRealNullRealMutationES11Adaptation
	{
	public:
		CRealOneFifthRuleMutationES11Adaptation(int iArchiveSize, double dModifier, CRealGaussianMutation &cMutation);

		virtual void vAdapt(double dBeforeMutationValue, vector<double> &vBeforeMutationSolution, double dAfterMutationValue, vector<double> &vAfterMutationSolution);

	private:
		static const double d_ONE_FIFTH;

		int i_archive_size;
		double d_modifier;

		int i_successes_counter;

		list<bool> l_successes;
	};//class CRealOneFifthRuleMutationES11Adaptation : public CRealNullRealMutationES11Adaptation
}//namespace Mutations