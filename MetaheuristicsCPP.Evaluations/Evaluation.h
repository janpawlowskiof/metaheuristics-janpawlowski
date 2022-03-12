#pragma once

#include "Constraint.h"

#include <vector>

using namespace Constraints;

using namespace std;

namespace Evaluations
{
	template <typename TElement>
	class IEvaluationProfile
	{
	public:
		IEvaluationProfile() = default;

		IEvaluationProfile(const IEvaluationProfile<TElement> &cOther) = delete;
		IEvaluationProfile(IEvaluationProfile<TElement> &&cOther) = delete;

		virtual ~IEvaluationProfile() = default;

		virtual int iGetSize() = 0;
		virtual double dGetMaxValue() = 0;
		virtual IConstraint<TElement> &cGetConstraint() = 0;

		IEvaluationProfile<TElement>& operator=(const IEvaluationProfile<TElement> &cOther) = delete;
		IEvaluationProfile<TElement>& operator=(IEvaluationProfile<TElement> &&cOther) = delete;
	};//class IEvaluationProfile


	template <typename TElement>
	class IEvaluation : public IEvaluationProfile<TElement>
	{
	public:
		virtual double dEvaluate(vector<TElement> &vSolution) = 0;

		virtual long long iGetFFE() = 0;
	};//class IEvaluation : public IEvaluationProfile<TElement>


	template <typename TElement>
	class CEvaluation : public IEvaluation<TElement>
	{
	public:
		CEvaluation(int iSize, double dMaxValue) : i_size(iSize), d_max_value(dMaxValue), i_ffe(0) { }

		virtual double dEvaluate(vector<TElement> &vSolution) final
		{
			double d_value = d_evaluate(vSolution);
			i_ffe++;

			return d_value;
		}//virtual double dEvaluate(vector<TElement> &vSolution) final

		virtual int iGetSize() { return i_size; }
		virtual double dGetMaxValue() { return d_max_value; }
		virtual long long iGetFFE() { return i_ffe; }

		CEvaluation<TElement>& operator=(const CEvaluation<TElement> &cOther) = delete;
		CEvaluation<TElement>& operator=(CEvaluation<TElement> &&cOther) = delete;

	protected:
		virtual double d_evaluate(vector<TElement> &vSolution) = 0;

	private:
		int i_size;
		double d_max_value;
		long long i_ffe;
	};//class CEvaluation : public IEvaluation<TElement>


	template <typename TElement>
	class CProxyEvaluation : public IEvaluation<TElement>
	{
	public:
		CProxyEvaluation(IEvaluation<TElement> **ppcEvaluation)
			: ppc_evaluation(ppcEvaluation)
		{

		}//CProxyEvaluation(IEvaluation<TElement> *ppcEvaluation)

		virtual double dEvaluate(vector<double> &vSolution) { return (*ppc_evaluation)->dEvaluate(vSolution); }

		virtual int iGetSize() { return (*ppc_evaluation)->iGetSize(); };
		virtual double dGetMaxValue() { return (*ppc_evaluation)->dGetMaxValue(); }
		virtual IConstraint<double> &cGetConstraint() { return (*ppc_evaluation)->cGetConstraint(); }

		virtual long long iGetFFE() { return (*ppc_evaluation)->iGetFFE(); }

	private:
		IEvaluation<TElement> **ppc_evaluation;
	};//class CProxyEvaluation : public IEvaluation<TElement>


	template <typename TElement>
	class CVerticalScalingEvaluation : public CEvaluation<TElement>
	{
	public:
		CVerticalScalingEvaluation(IEvaluation<TElement> &cEvaluation, double dFactor)
			: CEvaluation<TElement>(cEvaluation.iGetSize(), dFactor * cEvaluation.dGetMaxValue()), c_evaluation(cEvaluation), d_factor(dFactor)
		{

		}//CVerticalScalingEvaluation(IEvaluation<TElement> &cEvaluation, double dFactor)

		virtual IConstraint<TElement> &cGetConstraint() { return c_evaluation.cGetConstraint(); }

	protected:
		virtual double d_evaluate(vector<TElement> &vSolution)
		{
			return d_factor * c_evaluation.dEvaluate(vSolution);
		}//virtual double d_evaluate(vector<TElement> &vSolution)

	private:
		IEvaluation<TElement> &c_evaluation;
		double d_factor;
	};//class CVerticalScalingEvaluation : public CEvaluation<TElement>
}//namespace Evaluations
