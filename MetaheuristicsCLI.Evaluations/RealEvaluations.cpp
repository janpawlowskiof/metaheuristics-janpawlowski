#include "RealEvaluations.h"

using namespace EvaluationsCLI;


CRealEvaluation::CRealEvaluation(Evaluations::IEvaluation<double> *pcNativeBinaryEvaluation)
{
	pc_native_real_evaluation = pcNativeBinaryEvaluation;
}//CRealEvaluation::CRealEvaluation(Evaluations::IEvaluation<double> *pcNativeBinaryEvaluation)

CRealEvaluation::~CRealEvaluation()
{
	delete pc_native_real_evaluation;
}//CRealEvaluation::~CRealEvaluation()

CRealEvaluation::!CRealEvaluation()
{
	delete pc_native_real_evaluation;
}//CRealEvaluation::!CRealEvaluation()

double CRealEvaluation::dEvaluate(IList<double> ^lSolution)
{
	vector<double> v_solution(0);
	v_solution.reserve(lSolution->Count);

	for (int i = 0; i < lSolution->Count; i++)
	{
		v_solution.push_back(lSolution[i]);
	}//for (int i = 0; i < lSolution->Count; i++)

	return pc_native_real_evaluation->dEvaluate(v_solution);
}//double CRealEvaluation::dEvaluate(IList<double> ^lSolution) 


CRealSphereEvaluation::CRealSphereEvaluation(int iSize)
	: CRealEvaluation(new Evaluations::CRealSphereEvaluation(iSize))
{

}//CRealSphereEvaluation::CRealSphereEvaluation(int iSize)


CRealSphere10Evaluation::CRealSphere10Evaluation(int iSize)
	: CRealEvaluation(new Evaluations::CRealSphere10Evaluation(iSize))
{

}//CRealSphere10Evaluation::CRealSphere10Evaluation(int iSize)


CRealEllipsoidEvaluation::CRealEllipsoidEvaluation(int iSize)
	: CRealEvaluation(new Evaluations::CRealEllipsoidEvaluation(iSize))
{

}//CRealEllipsoidEvaluation::CRealEllipsoidEvaluation(int iSize)


CRealStep2SphereEvaluation::CRealStep2SphereEvaluation(int iSize)
	: CRealEvaluation(new Evaluations::CRealStep2SphereEvaluation(iSize))
{

}//CRealSphereEvaluation::CRealStep2SphereEvaluation(int iSize)


CRealRastriginEvaluation::CRealRastriginEvaluation(int iSize)
	: CRealEvaluation(new Evaluations::CRealRastriginEvaluation(iSize))
{

}//CRealRastriginEvaluation::CRealRastriginEvaluation(int iSize)


CRealAckleyEvaluation::CRealAckleyEvaluation(int iSize)
	: CRealEvaluation(new Evaluations::CRealAckleyEvaluation(iSize))
{

}//CRealAckleyEvaluation::CRealAckleyEvaluation(int iSize)