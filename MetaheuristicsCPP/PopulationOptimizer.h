#pragma once

#include "Generator.h"
#include "Individual.h"
#include "Mutation.h"
#include "Optimizer.h"
#include "VectorUtils.h"

#include <vector>

using namespace Generators;
using namespace Mutations;

using namespace std;

namespace Optimizers
{
	template <typename TElement>
	class CPopulationOptimizer : public COptimizer<TElement>
	{
	public:
		CPopulationOptimizer(IEvaluation<TElement> &cEvaluation, IStopCondition &cStopCondition, IGenerator<TElement> &cGeneration, IMutation<TElement> &cMutation)
			: COptimizer<TElement>(cEvaluation, cStopCondition), c_generation(cGeneration), c_mutation(cMutation)
		{

		}//CPopulationOptimizer(IEvaluation<TElement> &cEvaluation, IStopCondition &cStopCondition, IGeneration<TElement> &cGeneration, IMutation<TElement> &cMutation)

		virtual ~CPopulationOptimizer()
		{
			VectorUtils::vClear(v_population);
		}//virtual ~CPopulationOptimizer()

		int iGetLambda() { return i_lambda; }

	protected:
		virtual void v_initialize(clock_t tStartTime)
		{
			VectorUtils::vClear(v_population);
			v_population.reserve((size_t)i_lambda);

			for (int i = 0; i < i_lambda; i++)
			{
				v_population.push_back(pc_create_individual());
			}//for (int i = 0; i < i_lambda; i++)

			v_evaluate();
			b_check_new_best();
		}//virtual void v_initialize(clock_t tStartTime)

		void v_evaluate()
		{
			for (size_t i = 0; i < v_population.size(); i++)
			{
				v_population[i]->dEvaluate();
			}//for (size_t i = 0; i < v_population.size(); i++)
		}//void v_evaluate()

		bool b_check_new_best(bool bOnlyImprovements = true)
		{
			CIndividual<TElement> *pc_current_best_individual = v_population.front();

			for (size_t i = 1; i < v_population.size(); i++)
			{
				if (v_population[i]->dGetFitness() > pc_current_best_individual->dGetFitness())
				{
					pc_current_best_individual = v_population[i];
				}//if (v_population[i]->dGetFitness() > pc_current_best_individual->dGetFitness())
			}//for (size_t i = 1; i < v_population.size(); i++)

			return COptimizer<TElement>::b_check_new_best(pc_current_best_individual->vGetGenotype(), pc_current_best_individual->dGetFitness(), bOnlyImprovements);
		}//void v_check_new_best()

		virtual CIndividual<TElement> *pc_create_individual()
		{
			return new CIndividual<TElement>(c_generation.pvCreate(this->c_evaluation.iGetSize()), this->c_evaluation, c_mutation);
		}//virtual CIndividual<TElement> *pc_create_individual()

		vector<CIndividual<TElement>*> v_population;

		IGenerator<TElement> &c_generation;

	private:
		int i_lambda;

		IMutation<TElement> &c_mutation;
	};//class CPopulationOptimizer : public COptimizer<TElement>
}//namespace Optimizers