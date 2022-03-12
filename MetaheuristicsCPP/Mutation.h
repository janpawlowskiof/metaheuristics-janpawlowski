#pragma once

#include <Evaluation.h>
#include <random>
#include <vector>

using namespace Evaluations;
using namespace std;

namespace Mutations
{
	template <typename TElement>
	class IMutation
	{
	public:
		virtual ~IMutation() = default;

		virtual bool bMutate(vector<TElement> &vSolution) = 0;

		virtual double dGetProbability() = 0;

		virtual void vSetProbability(double dProbability) = 0;
	};//class IMutation


	template <typename TElement>
	class CMutation
	{
	public:
		CMutation(double dProbability, IEvaluationProfile<TElement> &cEvaluationProfile, mt19937 &cRandomEngine)
			: d_probability(dProbability), c_evaluation_profile(cEvaluationProfile), c_random_engine(cRandomEngine)
		{

		}//CMutation(double dProbability, IEvaluationProfile<TElement> &cConstraint, mt19937 &cRandomEngine)

		virtual double dGetProbability() { return d_probability; }

		virtual void vSetProbability(double dProbability) { d_probability = dProbability; }

	protected:
		IEvaluationProfile<TElement> &c_evaluation_profile;
		mt19937 &c_random_engine;

	private:
		double d_probability;
	};//class CMutation


	template <typename TElement>
	class CNullMutation : CMutation<TElement>
	{
	public:
		CNullMutation(double dProbability, IEvaluationProfile<TElement> &cEvaluationProfile, mt19937 &cRandomEngine)
			: CMutation<TElement>(dProbability, cEvaluationProfile, cRandomEngine)
		{

		}//CNullMutation(double dProbability, IEvaluationProfile<TElement> &cEvaluationProfile, mt19937 &cRandomEngine)

		virtual bool bMutate(vector<TElement> &vSolution) { return false; }
	};//class CNullMutation : CMutation<TElement>
}//namespace Mutations