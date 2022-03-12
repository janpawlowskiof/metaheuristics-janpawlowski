#include "RealRandomSearch.h"

using namespace Optimizers;

CRealRandomSearch::CRealRandomSearch(IEvaluation<double> &cEvaluation, IStopCondition &cStopCondition, mt19937 &cRandomEngine)
	: CSamplingOptimizer<double>(cEvaluation, cStopCondition, c_random_generation), c_random_generation(cEvaluation.cGetConstraint(), cRandomEngine)
{

}//CRealRandomSearch::CRealRandomSearch(IEvaluation<double> &cEvaluation, IStopCondition &cStopCondition, mt19937 &cRandomEngine)