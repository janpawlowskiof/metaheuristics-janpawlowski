#include "RealMutations.h"

using namespace Mutations;


CRealGaussianMutation::CRealGaussianMutation(double dSigma, IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, double dProbability)
	: CMutation<double>(dProbability, cEvaluationProfile, cRandomEngine), v_sigmas((size_t)cEvaluationProfile.iGetSize())
{
	vSetSigmas(dSigma);
}//CRealGaussianMutation::CRealGaussianMutation(double dSigma, IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, double dProbability)

CRealGaussianMutation::CRealGaussianMutation(vector<double> &vSigmas, IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, double dProbability)
	: CMutation<double>(dProbability, cEvaluationProfile, cRandomEngine), v_sigmas(vSigmas)
{

}//CRealGaussianMutation::CRealGaussianMutation(vector<double> &vVariances, IEvaluationProfile<double> &cEvaluationProfile, mt19937 &cRandomEngine, double dProbability)

bool CRealGaussianMutation::bMutate(vector<double> &vSolution)
{
	bool b_successful_mutation = false;

	uniform_real_distribution<double> c_uniform_ditr;
	normal_distribution<double> c_gaussian_distr;

	for (size_t i = 0; i < vSolution.size(); i++)
	{
		if (c_uniform_ditr(c_random_engine) <= dGetProbability())
		{
			do
			{
				vSolution[i] += v_sigmas[i] * c_gaussian_distr(c_random_engine);
			} while (!c_evaluation_profile.cGetConstraint().bIsFeasible((int)i, vSolution[i]));

			b_successful_mutation = true;
		}//if (c_uniform_ditr(c_random_engine) <= dGetProbability())
	}//for (size_t i = 0; i < vSolution.size(); i++)

	return b_successful_mutation;
}//bool CRealGaussianMutation::bMutate(vector<double> &vSolution)

void CRealGaussianMutation::vMultiplySigmas(double dMultiplier)
{
	for (size_t i = 0; i < v_sigmas.size(); i++)
	{
		v_sigmas[i] *= dMultiplier;
	}//for (size_t i = 0; i < v_sigmas.size(); i++)
}//void CRealGaussianMutation::vMultiplySigmas(double dMultiplier)

void CRealGaussianMutation::vSetSigmas(double dSigma)
{
	fill(v_sigmas.begin(), v_sigmas.end(), dSigma);
}//void CRealGaussianMutation::vSetSigmas(double dSigma)