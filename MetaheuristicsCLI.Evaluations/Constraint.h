#pragma once

namespace ConstraintsCLI
{
	generic <typename TElement>
	public interface class IConstraint
	{
		TElement tGetLowerBound(int iDimension);
		TElement tGetUpperBound(int iDimension);

		bool bIsFeasible(int iDimension, TElement tValue);
	};//public interface class IEvaluationProfile
}//namespace ConstraintsCLI