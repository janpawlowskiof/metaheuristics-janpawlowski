#include "BinaryMutations.h"

using namespace Mutations;


CBinaryBitFlipMutation::CBinaryBitFlipMutation(double dProbability, IEvaluationProfile<bool> &cEvaluationProfile, mt19937 &cRandomEngine)
	: CMutation<bool>(dProbability, cEvaluationProfile, cRandomEngine)
{

}//CBinaryBitFlipMutation::CBinaryBitFlipMutation(double dProbability, IEvaluationProfile<bool> &cEvaluationProfile, mt19937 &cRandomEngine)

bool CBinaryBitFlipMutation::bMutate(vector<bool> &vSolution)
{
	bool b_successful_mutation = false;

	uniform_real_distribution<double> c_uniform_ditr;

	for (size_t i = 0; i < vSolution.size(); i++)
	{
		if (c_uniform_ditr(c_random_engine) <= dGetProbability())
		{
			if (c_evaluation_profile.cGetConstraint().bIsFeasible((int)i, !vSolution[i]))
			{
				vSolution[i] = !vSolution[i];
				b_successful_mutation = true;
			}//if (c_evaluation_profile.cGetConstraint().bIsFeasible((int)i, !vSolution[i]))
		}//if (c_uniform_ditr(c_random_engine) <= dGetProbability())
	}//for (size_t i = 0; i < vSolution.size(); i++)

	return b_successful_mutation;
}//bool CBinaryBitFlipMutation::bMutate(vector<bool> &vSolution)