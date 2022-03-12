#include "RealEvolutionStrategy11.h"

using namespace Optimizers;

CRealEvolutionStrategy11::CRealEvolutionStrategy11(IEvaluation<double> &cEvaluation, IStopCondition &cStopCondition, IRealMutationES11Adaptation &cMutationAdaptation, mt19937 &cRandomEngine)
	: COptimizer<double>(cEvaluation, cStopCondition), c_mutation_adaptation(cMutationAdaptation), c_random_engine(cRandomEngine)
{

}//CRealEvolutionStrategy11::CRealEvolutionStrategy11(IEvaluation<double> &cEvaluation, IStopCondition &cStopCondition, IRealMutationES11Adaptation &cMutationAdaptation, mt19937 &cRandomEngine)

void CRealEvolutionStrategy11::v_initialize(clock_t tStartTime)
{
	CRealRandomGenerator c_random_generation(c_evaluation.cGetConstraint(), c_random_engine);
	
	vector<double> v_initial_solution((size_t)c_evaluation.iGetSize());
	c_random_generation.vFill(v_initial_solution);

	b_check_new_best(v_initial_solution, c_evaluation.dEvaluate(v_initial_solution));
}//void CRealEvolutionStrategy11::v_initialize(clock_t tStartTime)

bool CRealEvolutionStrategy11::b_run_iteration(long long iIterationNumber, clock_t tStartTime)
{
	CRealGaussianMutation &c_mutation = c_mutation_adaptation.cGetMutation();

	vector<double> v_candidate_solution(pcGetResult()->vGetBestSolution());

	c_mutation.bMutate(v_candidate_solution);
	double d_candidate_value = c_evaluation.dEvaluate(v_candidate_solution);

	c_mutation_adaptation.vAdapt(pcGetResult()->dGetBestValue(), pcGetResult()->vGetBestSolution(), d_candidate_value, v_candidate_solution);

	return b_check_new_best(v_candidate_solution, d_candidate_value);
}//bool CRealEvolutionStrategy11::b_run_iteration(long long iIterationNumber, clock_t tStartTime)