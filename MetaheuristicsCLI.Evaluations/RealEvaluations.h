#pragma once

#include "RealConstraints.h"
#include "Evaluation.h"

#include <RealEvaluations.h>

using namespace System::Collections::Generic;

namespace EvaluationsCLI
{
	public ref class CRealEvaluation : public IEvaluation<double>
	{
	public:
		CRealEvaluation(Evaluations::IEvaluation<double> *pcNativeRealEvaluation);

		virtual ~CRealEvaluation();
		!CRealEvaluation();

		virtual double dEvaluate(IList<double> ^lSolution);

		virtual property int iSize
		{
			int get() { return pc_native_real_evaluation->iGetSize(); }
		}//virtual property int iSize

		virtual property double dMaxValue
		{
			double get() { return pc_native_real_evaluation->dGetMaxValue(); }
		}//virtual property double dMaxValue

		virtual property ConstraintsCLI::IConstraint<double>^ pcConstraint
		{
			ConstraintsCLI::IConstraint<double>^ get() { return gcnew ConstraintsCLI::CRealConstraint(pc_native_real_evaluation->cGetConstraint()); }
		}//virtual property ConstraintsCLI::IConstraint<double>^ pcConstraint

		virtual property long long iFFE
		{
			long long get() { return pc_native_real_evaluation->iGetFFE(); }
		}//property long long iFFE

	private:
		Evaluations::IEvaluation<double> *pc_native_real_evaluation;
	};//public ref class CRealEvaluation : public IEvaluation<double>


	public ref class CRealSphereEvaluation : public CRealEvaluation
	{
	public:
		CRealSphereEvaluation(int iSize);
	};//public ref class CRealSphereEvaluation : public CRealEvaluation


	public ref class CRealSphere10Evaluation : public CRealEvaluation
	{
	public:
		CRealSphere10Evaluation(int iSize);
	};//public ref class CRealSphere10Evaluation : public CRealEvaluation


	public ref class CRealEllipsoidEvaluation : public CRealEvaluation
	{
	public:
		CRealEllipsoidEvaluation(int iSize);
	};//public ref class CRealEllipsoidEvaluation : public CRealEvaluation


	public ref class CRealStep2SphereEvaluation : public CRealEvaluation
	{
	public:
		CRealStep2SphereEvaluation(int iSize);
	};//public ref class CRealStep2SphereEvaluation : public CRealEvaluation


	public ref class CRealRastriginEvaluation : public CRealEvaluation
	{
	public:
		CRealRastriginEvaluation(int iSize);
	};//public ref class CRealRastriginEvaluation : public CRealEvaluation


	public ref class CRealAckleyEvaluation : public CRealEvaluation
	{
	public:
		CRealAckleyEvaluation(int iSize);
	};//public ref class CRealAckleyEvaluation : public CRealEvaluation
}//namespace EvaluationsCLI
