#pragma once

#include "Mutation.h"

#include <Evaluation.h>
#include <vector>

using namespace Mutations;

using namespace Evaluations;
using namespace std;

namespace Optimizers
{
	template <typename TElement>
	class CIndividual
	{
	public:
		CIndividual(vector<TElement> *pvGenotype, IEvaluation<TElement> &cEvaluation, IMutation<TElement> &cMutation)
			: c_evaluation(cEvaluation), c_mutation(cMutation)
		{

		}//CIndividual(vector<TElement> *pvGenotype, IEvaluation<TElement> &cEvaluation, IMutation<TElement> &cMutation)

		CIndividual(const CIndividual<TElement> &cOther)
			: c_evaluation(cOther.c_evaluation), c_mutation(cOther.c_mutation)
		{
			pv_genotype = new vector<double>(*cOther.pv_genotype);
		}//CIndividual(const CIndividual<TElement> &cOther)

		~CIndividual()
		{
			delete pv_genotype;
		}//~CIndividual()

		double dEvaluate()
		{
			if (!b_is_evaluated)
			{
				d_fitness = c_evaluation.dEvaluate(*pv_genotype);
				b_is_evaluated = true;
			}//if (!b_is_evaluated)

			return dGetFitness();
		}//double dEvaluate()

		bool bMutate()
		{
			bool b_successful_mutation = c_mutation.bMutate(*pv_genotype);

			if (b_successful_mutation)
			{
				b_is_evaluated = false;
			}//if (b_successful_mutation)

			return b_successful_mutation;
		}//bool bMutate()

		vector<TElement> &vGetGenotype() { return *pv_genotype; }
		double dGetFitness() { return d_fitness; }

	private:
		vector<TElement> *pv_genotype;

		IEvaluation<TElement> &c_evaluation;
		IMutation<TElement> &c_mutation;

		bool b_is_evaluated;
		double d_fitness;
	};//class CIndividual
}//namespace Optimizers
