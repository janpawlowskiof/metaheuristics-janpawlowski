#pragma once

#include "Constraint.h"

#include <Evaluation.h>

using namespace System::Collections::Generic;

namespace EvaluationsCLI
{
	generic <typename TElement>
	public interface class IEvaluationProfile
	{
		property int iSize
		{
			int get();
		}//property int iSize

		property double dMaxValue
		{
			double get();
		}//property double dMaxValue

		property ConstraintsCLI::IConstraint<TElement>^ pcConstraint
		{
			ConstraintsCLI::IConstraint<TElement>^ get();
		}//property ConstraintsCLI::IConstraint<TElement>^ pcConstraint
	};//public interface class IEvaluationProfile


	generic <typename TElement>
	public interface class IEvaluation : public IEvaluationProfile<TElement>
	{
		double dEvaluate(IList<TElement> ^lSolution);

		property long long iFFE
		{
			long long get();
		}//property long long iFFE
	};//public interface class IEvaluation
}//namespace EvaluationsCLI