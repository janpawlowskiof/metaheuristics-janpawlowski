#include "RealEvaluations.h"

using namespace Evaluations;


CRealEvaluation::CRealEvaluation(int iSize, double dMaxValue, double dLowerBound, double dUpperBound)
	: CEvaluation(iSize, dMaxValue), c_constraint(dLowerBound, dUpperBound, iSize)
{

}//CRealEvaluation::CRealEvaluation(int iSize, double dMaxValue, double dLowerBound, double dUpperBound)


CRealHorizontalScalingEvaluation::CRealHorizontalScalingEvaluation(IEvaluation<double> &cRealEvaluation, vector<double> &vFactors)
	: CEvaluation<double>(cRealEvaluation.iGetSize(), cRealEvaluation.dGetMaxValue()), c_real_evaluation(cRealEvaluation), v_factors(vFactors)
{
	vector<double> v_lower_bounds;
	vector<double> v_upper_bounds;

	v_lower_bounds.reserve((size_t)cRealEvaluation.iGetSize());
	v_upper_bounds.reserve((size_t)cRealEvaluation.iGetSize());

	IConstraint<double> &c_real_constraint = cRealEvaluation.cGetConstraint();

	for (int i = 0; i < cRealEvaluation.iGetSize(); i++)
	{
		v_lower_bounds.push_back(c_real_constraint.tGetLowerBound(i) * vFactors[i]);
		v_upper_bounds.push_back(c_real_constraint.tGetUpperBound(i) * vFactors[i]);
	}//for (int i = 0; i < cRealEvaluation.iGetSize(); i++)

	pc_constraint = new CRealBoundingBoxConstraint(v_lower_bounds, v_upper_bounds);
}//CRealHorizontalScalingEvaluation::CRealHorizontalScalingEvaluation(IEvaluation<double> &cRealEvaluation, vector<double> &vFactors)

CRealHorizontalScalingEvaluation::~CRealHorizontalScalingEvaluation()
{
	delete pc_constraint;
}//CRealHorizontalScalingEvaluation::~CRealHorizontalScalingEvaluation()

double CRealHorizontalScalingEvaluation::d_evaluate(vector<double> &vSolution)
{
	vector<double> v_scaled_solution;
	v_scaled_solution.reserve(vSolution.size());

	for (size_t i = 0; i < vSolution.size(); i++)
	{
		v_scaled_solution.push_back(vSolution[i] / v_factors[i]);
	}//for (size_t i = 0; i < vSolution.size(); i++)

	return c_real_evaluation.dEvaluate(v_scaled_solution);
}//double CRealHorizontalScalingEvaluation::d_evaluate(vector<double> &vSolution)


CRealStepEvaluation::CRealStepEvaluation(IEvaluation<double> &cRealEvaluation, vector<int> &vStepSizes)
	: CEvaluation<double>(cRealEvaluation.iGetSize(), cRealEvaluation.dGetMaxValue()), c_real_evaluation(cRealEvaluation), v_step_sizes(vStepSizes)
{

}//CRealStepEvaluation::CRealStepEvaluation(IEvaluation<double> &cRealEvaluation, vector<int> &vStepSizes)

double CRealStepEvaluation::d_evaluate(vector<double> &vSolution)
{
	vector<double> v_solution_with_steps;
	v_solution_with_steps.reserve(vSolution.size());

	for (size_t i = 0; i < vSolution.size(); i++)
	{
		v_solution_with_steps.push_back(v_step_sizes[i] * floor(vSolution[i] / v_step_sizes[i] + 0.5));
	}//for (size_t i = 0; i < vSolution.size(); i++)

	double d_value = c_real_evaluation.dEvaluate(v_solution_with_steps);

	if (d_value == dGetMaxValue())
	{
		d_value = c_real_evaluation.dEvaluate(vSolution);
	}//if (d_value == dGetMaxValue())

	return d_value;
}//double CRealStepEvaluation::d_evaluate(vector<double> &vSolution)


CRealSphereEvaluation::CRealSphereEvaluation(int iSize)
	: CRealEvaluation(iSize, 0, -20, 20)
{

}//CRealSphereEvaluation::CRealSphereEvaluation(int iSize)

double CRealSphereEvaluation::d_evaluate(vector<double> &vSolution)
{
	double d_value = 0;

	for (int i = 0; i < iGetSize(); i++)
	{
		d_value -= vSolution[i] * vSolution[i];
	}//for (int i = 0; i < iGetSize(); i++)

	return d_value;
}//double CRealSphereEvaluation::d_evaluate(vector<double> &vSolution)


CRealSphere10Evaluation::CRealSphere10Evaluation(int iSize)
	: CProxyEvaluation<double>((IEvaluation<double>**)&pc_vertical_scaling_evaluation)
{
	pc_sphere_evaluation = new CRealSphereEvaluation(iSize);
	pc_vertical_scaling_evaluation = new CVerticalScalingEvaluation<double>(*pc_sphere_evaluation, 10);
}//CRealSphere10Evaluation::CRealSphere10Evaluation(int iSize)

CRealSphere10Evaluation::~CRealSphere10Evaluation()
{
	delete pc_sphere_evaluation;
	delete pc_vertical_scaling_evaluation;
}//CRealSphere10Evaluation::~CRealSphere10Evaluation()


CRealEllipsoidEvaluation::CRealEllipsoidEvaluation(int iSize)
	: CProxyEvaluation<double>((IEvaluation<double>**)&pc_horizontal_scaling_evaluation)
{
	pc_sphere_evaluation = new CRealSphereEvaluation(iSize);

	vector<double> v_factors((size_t)pc_sphere_evaluation->iGetSize());
	double d_factor = 1;

	for (size_t i = 0; i < v_factors.size(); i++)
	{
		v_factors[i] = d_factor;
		d_factor *= 3;
	}//for (size_t i = 0; i < v_factors.size(); i++)

	pc_horizontal_scaling_evaluation = new CRealHorizontalScalingEvaluation(*pc_sphere_evaluation, v_factors);
}//CRealEllipsoidEvaluation::CRealEllipsoidEvaluation(int iSize)

CRealEllipsoidEvaluation::~CRealEllipsoidEvaluation()
{
	delete pc_sphere_evaluation;
	delete pc_horizontal_scaling_evaluation;
}//CRealEllipsoidEvaluation::~CRealEllipsoidEvaluation()


CRealStep2SphereEvaluation::CRealStep2SphereEvaluation(int iSize)
	: CProxyEvaluation<double>((IEvaluation<double>**)&pc_step_evaluation)
{
	vector<int> v_step_sizes((size_t)iSize, 2);

	pc_sphere_evaluation = new CRealSphereEvaluation(iSize);
	pc_step_evaluation = new CRealStepEvaluation(*pc_sphere_evaluation, v_step_sizes);
}//CRealStep2SphereEvaluation::CRealStep2SphereEvaluation(int iSize)

CRealStep2SphereEvaluation::~CRealStep2SphereEvaluation()
{
	delete pc_sphere_evaluation;
	delete pc_step_evaluation;
}//CRealStep2SphereEvaluation::~CRealStep2SphereEvaluation()


CRealRastriginEvaluation::CRealRastriginEvaluation(int iSize)
	: CRealEvaluation(iSize, 0, -5.12, 5.12)
{

}//CRealRastriginEvaluation::CRealRastriginEvaluation(int iSize)

double CRealRastriginEvaluation::d_evaluate(vector<double> &vSolution)
{
	double d_value = -10 * iGetSize();

	for (int i = 0; i < iGetSize(); i++)
	{
		d_value -= vSolution[i] * vSolution[i] - 10 * cos(2.0 * M_PI * vSolution[i]);
	}//for (int i = 0; i < iGetSize(); i++)

	return d_value;
}//double CRealRastriginEvaluation::d_evaluate(vector<double> &vSolution)


CRealAckleyEvaluation::CRealAckleyEvaluation(int iSize)
	: CRealEvaluation(iSize, 0, -5, 5)
{

}//CRealAckleyEvaluation::CRealAckleyEvaluation(int iSize)

double CRealAckleyEvaluation::d_evaluate(vector<double> &vSolution)
{
	double d_sum_square = 0;
	double d_sum_cos = 0;

	for (int i = 0; i < iGetSize(); i++)
	{
		d_sum_square += vSolution[i] * vSolution[i];
		d_sum_cos += cos(2.0 * M_PI * vSolution[i]);
	}//for (int i = 0; i < iGetSize(); i++)

	return 20.0 * exp(-0.2 * sqrt(1.0 / iGetSize() * d_sum_square)) + exp(1.0 / iGetSize() * d_sum_cos) - 20.0 - M_E;
}//double CRealAckleyEvaluation::d_evaluate(vector<double> &vSolution)