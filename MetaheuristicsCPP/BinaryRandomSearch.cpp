#include "BinaryRandomSearch.h"

using namespace Optimizers;

CBinaryRandomSearch::CBinaryRandomSearch(IEvaluation<bool> &cEvaluation, IStopCondition &cStopCondition, mt19937 &cRandomEngine)
	: CSamplingOptimizer<bool>(cEvaluation, cStopCondition, c_random_generation), c_random_generation(cEvaluation.cGetConstraint(), cRandomEngine)
{

}//CBinaryRandomSearch::CBinaryRandomSearch(IEvaluation<bool> &cEvaluation, IStopCondition &cStopCondition, mt19937 &cRandomEngine)