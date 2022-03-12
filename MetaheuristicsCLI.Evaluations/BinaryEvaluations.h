#pragma once

#include "BinaryConstraints.h"
#include "Evaluation.h"

#include <BinaryEvaluations.h>

using namespace System::Collections::Generic;

namespace EvaluationsCLI
{
	public ref class CBinaryEvaluation : public IEvaluation<bool>
	{
	public:
		CBinaryEvaluation(Evaluations::IEvaluation<bool> *pcNativeBinaryEvaluation);

		virtual ~CBinaryEvaluation();
		!CBinaryEvaluation();

		virtual double dEvaluate(IList<bool> ^lSolution);

		virtual property int iSize
		{
			int get() { return pc_native_binary_evaluation->iGetSize(); }
		}//virtual property int iSize

		virtual property double dMaxValue
		{
			double get() { return pc_native_binary_evaluation->dGetMaxValue(); }
		}//virtual property double dMaxValue

		virtual property ConstraintsCLI::IConstraint<bool>^ pcConstraint
		{
			ConstraintsCLI::IConstraint<bool>^ get() { return gcnew ConstraintsCLI::CBinaryConstraint(pc_native_binary_evaluation->cGetConstraint()); }
		}//virtual property ConstraintsCLI::IConstraint<bool>^ pcConstraint

		virtual property long long iFFE
		{
			long long get() { return pc_native_binary_evaluation->iGetFFE(); }
		}//property long long iFFE

	private:
		Evaluations::IEvaluation<bool> *pc_native_binary_evaluation;
	};//public ref class CBinaryEvaluation : public IEvaluation<bool>


	public ref class CBinaryOneMaxEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryOneMaxEvaluation(int iSize);
	};//public ref class CBinaryOneMaxEvaluation : public CBinaryEvaluation


	public ref class CBinaryStandardDeceptiveConcatenationEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks);
	};//public ref class CBinaryStandardDeceptiveConcatenationEvaluation : public CBinaryEvaluation


	public ref class CBinaryBimodalDeceptiveConcatenationEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryBimodalDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks);
	};//public ref class CBinaryBimodalDeceptiveConcatenationEvaluation : public CBinaryEvaluation


	public ref class CBinaryIsingSpinGlassEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryIsingSpinGlassEvaluation(int iSize);
		CBinaryIsingSpinGlassEvaluation(int iSize, int iProblemSeed);
	};//public ref class CBinaryIsingSpinGlassEvaluation : public CBinaryEvaluation


	public ref class CBinaryMax3SatEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryMax3SatEvaluation(int iSize);
		CBinaryMax3SatEvaluation(int iSize, int iProblemSeed);
		CBinaryMax3SatEvaluation(int iSize, int iProblemSeed, float fClauseRatio);
	};//public ref class CBinaryMax3SatEvaluation : public CBinaryEvaluation


	public ref class CBinaryNKLandscapesEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryNKLandscapesEvaluation(int iSize);
		CBinaryNKLandscapesEvaluation(int iSize, int iProblemSeed);
	};//public ref class CBinaryNKLandscapesEvaluation : public CBinaryEvaluation
}//namespace EvaluationsCLI