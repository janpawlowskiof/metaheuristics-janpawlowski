#include "BinaryRandomSearch.h"
#include "OptimizationResult.h"
#include "RealCMAES.h"
#include "RealEvolutionStrategy11.h"
#include "RealMutations.h"
#include "RealMutationES11Adaptations.h"
#include "StopConditions.h"

#include <BinaryEvaluations.h>
#include <iostream>
#include <random>
#include <RealEvaluations.h>

using namespace Optimizers;
using namespace StopConditions;

using namespace Evaluations;
using namespace std;


template <typename TElement>
void v_report_optimization_result(COptimizationResult<TElement> &cOptimizationResult)
{
	cout << "value: " << cOptimizationResult.dGetBestValue() << endl;
	cout << "\twhen (time): " << cOptimizationResult.dGetBestTime() << " s" << endl;
	cout << "\twhen (iteration): " << cOptimizationResult.iGetBestIteration() << endl;
	cout << "\twhen (FFE): " << cOptimizationResult.iGetBestFFE() << endl;
}//void v_report_optimization_result(COptimizationResult<TElement> &cOptimizationResult)

void v_lab_3_sphere_cmaes(mt19937 &cRandomEngine)
{
	CRealSphereEvaluation c_sphere_evaluation(10);

	CIterationsStopCondition c_stop_condition(c_sphere_evaluation.dGetMaxValue(), 1000);

	CRealCMAES c_cmaes(c_sphere_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_sphere_cmaes(mt19937 &cRandomEngine)

void v_lab_3_sphere_10_cmaes(mt19937 &cRandomEngine)
{
	CRealSphere10Evaluation c_sphere_10_evaluation(10);

	CIterationsStopCondition c_stop_condition(c_sphere_10_evaluation.dGetMaxValue(), 1000);

	CRealCMAES c_cmaes(c_sphere_10_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_sphere_cmaes(mt19937 &cRandomEngine)

void v_lab_3_ellipsoid_cmaes(mt19937 &cRandomEngine)
{
	CRealEllipsoidEvaluation c_ellipsoid_evaluation(10);

	CIterationsStopCondition c_stop_condition(c_ellipsoid_evaluation.dGetMaxValue(), 1000);

	CRealCMAES c_cmaes(c_ellipsoid_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_ellipsoid_cmaes(mt19937 &cRandomEngine)

void v_lab_3_step_2_sphere_cmaes(mt19937 &cRandomEngine)
{
	CRealStep2SphereEvaluation c_step_2_sphere_evaluation(10);

	CIterationsStopCondition c_stop_condition(c_step_2_sphere_evaluation.dGetMaxValue(), 1000);

	CRealCMAES c_cmaes(c_step_2_sphere_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_step_2_sphere_cmaes(mt19937 &cRandomEngine)

void v_lab_3_rastrigin_cmaes(mt19937 &cRandomEngine)
{
	CRealRastriginEvaluation c_rastrigin_evaluation(10);

	CIterationsStopCondition c_stop_condition(c_rastrigin_evaluation.dGetMaxValue(), 1000);

	CRealCMAES c_cmaes(c_rastrigin_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_rastrigin_cmaes(mt19937 &cRandomEngine)

void v_lab_3_ackley_cmaes(mt19937 &cRandomEngine)
{
	CRealAckleyEvaluation c_ackley_evaluation(10);

	CIterationsStopCondition c_stop_condition(c_ackley_evaluation.dGetMaxValue(), 1000);

	CRealCMAES c_cmaes(c_ackley_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_ackley_cmaes(mt19937 &cRandomEngine)

void v_lab_2_sphere(mt19937 &cRandomEngine)
{
	CRealSphereEvaluation c_sphere_evaluation(2);

	vector<double> v_sigmas((size_t)c_sphere_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(c_sphere_evaluation.dGetMaxValue(), 1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_sphere_evaluation, cRandomEngine);
	CRealNullRealMutationES11Adaptation c_mutation_adaptation(c_mutation);

	CRealEvolutionStrategy11 c_es11(c_sphere_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	v_report_optimization_result(*c_es11.pcGetResult());
}//void v_lab_2_sphere(mt19937 &cRandomEngine)

void v_lab_2_sphere_10(mt19937 &cRandomEngine)
{
	CRealSphere10Evaluation c_sphere_10_evaluation(2);

	vector<double> v_sigmas((size_t)c_sphere_10_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(c_sphere_10_evaluation.dGetMaxValue(), 1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_sphere_10_evaluation, cRandomEngine);
	CRealNullRealMutationES11Adaptation c_mutation_adaptation(c_mutation);

	CRealEvolutionStrategy11 c_es11(c_sphere_10_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	v_report_optimization_result(*c_es11.pcGetResult());
}//void v_lab_2_sphere_10(mt19937 &cRandomEngine)

void v_lab_2_ellipsoid(mt19937 &cRandomEngine)
{
	CRealEllipsoidEvaluation c_ellipsoid_evaluation(2);

	vector<double> v_sigmas((size_t)c_ellipsoid_evaluation.iGetSize(), 1);

	CIterationsStopCondition c_stop_condition(c_ellipsoid_evaluation.dGetMaxValue(), 1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_ellipsoid_evaluation, cRandomEngine);
	CRealNullRealMutationES11Adaptation c_mutation_adaptation(c_mutation);

	CRealEvolutionStrategy11 c_es11(c_ellipsoid_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	v_report_optimization_result(*c_es11.pcGetResult());
}//void v_lab_2_ellipsoid(mt19937 &cRandomEngine)

void v_lab_2_step_2_sphere(mt19937 &cRandomEngine)
{
	CRealStep2SphereEvaluation c_step_2_sphere_evaluation(2);

	vector<double> v_sigmas((size_t)c_step_2_sphere_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(c_step_2_sphere_evaluation.dGetMaxValue(), 1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_step_2_sphere_evaluation, cRandomEngine);
	CRealNullRealMutationES11Adaptation c_mutation_adaptation(c_mutation);

	CRealEvolutionStrategy11 c_es11(c_step_2_sphere_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	v_report_optimization_result(*c_es11.pcGetResult());
}//void v_lab_2_step_2_sphere(mt19937 &cRandomEngine)

void v_lab_1_one_max(mt19937 &cRandomEngine)
{
	CBinaryOneMaxEvaluation c_evaluation(5);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	v_report_optimization_result(*c_random_search.pcGetResult());
}//void v_lab_1_one_max(mt19937 &cRandomEngine)

void v_lab_1_standard_deceptive_concatenation(mt19937 &cRandomEngine)
{
	CBinaryStandardDeceptiveConcatenationEvaluation c_evaluation(5, 1);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	v_report_optimization_result(*c_random_search.pcGetResult());
}//void v_lab_1_standard_deceptive_concatenation(mt19937 &cRandomEngine)

void v_lab_1_bimodal_deceptive_concatenation(mt19937 &cRandomEngine)
{
	CBinaryBimodalDeceptiveConcatenationEvaluation c_evaluation(10, 1);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	v_report_optimization_result(*c_random_search.pcGetResult());
}//void v_lab_1_bimodal_deceptive_concatenation(mt19937 &cRandomEngine)

void v_lab_1_ising_spin_glass(mt19937 &cRandomEngine)
{
	CBinaryIsingSpinGlassEvaluation c_evaluation(25);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	v_report_optimization_result(*c_random_search.pcGetResult());
}//void v_lab_1_ising_spin_glass(mt19937 &cRandomEngine)

void v_lab_1_nk_landscapes(mt19937 &cRandomEngine)
{
	CBinaryNKLandscapesEvaluation c_evaluation(10);
	CIterationsStopCondition c_stop_condition(c_evaluation.dGetMaxValue(), 500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	v_report_optimization_result(*c_random_search.pcGetResult());
}//void v_lab_1_nk_landscapes(mt19937 &cRandomEngine)

int main()
{
	random_device c_seed_generator;
	mt19937 c_random_engine(c_seed_generator());

	v_lab_3_sphere_cmaes(c_random_engine);
	v_lab_3_sphere_10_cmaes(c_random_engine);
	v_lab_3_ellipsoid_cmaes(c_random_engine);
	v_lab_3_step_2_sphere_cmaes(c_random_engine);
	v_lab_3_rastrigin_cmaes(c_random_engine);
	v_lab_3_ackley_cmaes(c_random_engine);

	v_lab_2_sphere(c_random_engine);
	v_lab_2_sphere_10(c_random_engine);
	v_lab_2_ellipsoid(c_random_engine);
	v_lab_2_step_2_sphere(c_random_engine);

	v_lab_1_one_max(c_random_engine);
	v_lab_1_standard_deceptive_concatenation(c_random_engine);
	v_lab_1_bimodal_deceptive_concatenation(c_random_engine);
	v_lab_1_ising_spin_glass(c_random_engine);
	v_lab_1_nk_landscapes(c_random_engine);

	return 0;
}//int main()