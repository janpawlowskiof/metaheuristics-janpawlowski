#include "BinaryEvaluations.h"

using namespace Evaluations;


CBinaryEvaluation::CBinaryEvaluation(int iSize, double dMaxValue)
	: CEvaluation<bool>(iSize, dMaxValue)
{

}//CBinaryEvaluation::CBinaryEvaluation(int iSize, double dMaxValue)


CBinaryOneMaxEvaluation::CBinaryOneMaxEvaluation(int iSize)
	: CBinaryEvaluation(iSize, iSize)
{

}//CBinaryOneMaxEvaluation::CBinaryOneMaxEvaluation(int iSize)

double CBinaryOneMaxEvaluation::d_evaluate(vector<bool> &vSolution)
{
	double d_value = 0;

	for (int i = 0; i < iGetSize(); i++)
	{
		if (vSolution[i])
		{
			d_value++;
		}//if (vSolution[i])
	}//for (int i = 0; i < iGetSize(); i++)

	return d_value;
}//double CBinaryOneMaxEvaluation::d_evaluate(vector<bool> &cCoding)


CBinaryDeceptiveConcatenationEvaluation::CBinaryDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, double dMaxValue)
	: CBinaryEvaluation(iBlockSize * iNumberOfBlocks, dMaxValue), i_block_size(iBlockSize), i_number_of_blocks(iNumberOfBlocks)
{

}//CBinaryDeceptiveConcatenationEvaluation::CBinaryDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, double dMaxValue)

double CBinaryDeceptiveConcatenationEvaluation::d_evaluate(vector<bool> &vSolution)
{
	double d_value = 0;

	int i_unitation;

	for (int i = 0; i < i_number_of_blocks; i++)
	{
		i_unitation = 0;

		for (int j = 0; j < i_block_size; j++)
		{
			if (vSolution[i * i_block_size + j])
			{
				i_unitation++;
			}//if (vSolution[i * i_block_size + j])
		}//for (int j = 0; j < i_block_size; j++)

		d_value += d_evaluate(i_unitation);
	}//for (int i = 0; i < i_number_of_blocks; i++)

	return d_value;
}//double CBinaryDeceptiveConcatenationEvaluation::d_evaluate(vector<bool> &vSolution)


CBinaryStandardDeceptiveConcatenationEvaluation::CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)
	: CBinaryDeceptiveConcatenationEvaluation(iBlockSize, iNumberOfBlocks, iBlockSize * iNumberOfBlocks)
{

}//CBinaryStandardDeceptiveConcatenationEvaluation::CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)

double CBinaryStandardDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)
{
	double d_value;

	if (iUnitation == i_block_size)
	{
		d_value = i_block_size;
	}//if (iUnitation == i_block_size)
	else
	{
		d_value = i_block_size - 1 - iUnitation;
	}//else if (iUnitation == i_block_size)

	return d_value;
}//double CBinaryStandardDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)


CBinaryBimodalDeceptiveConcatenationEvaluation::CBinaryBimodalDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)
	: CBinaryDeceptiveConcatenationEvaluation(iBlockSize, iNumberOfBlocks, iBlockSize * iNumberOfBlocks / 2.0)
{

}//CBinaryBimodalDeceptiveConcatenationEvaluation::CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)

double CBinaryBimodalDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)
{
	double d_value;

	if (iUnitation == i_block_size || iUnitation == 0)
	{
		d_value = i_block_size / 2.0;
	}//if (iUnitation == i_block_size)
	else
	{
		d_value = i_block_size / 2.0 - abs(iUnitation - i_block_size / 2.0) - 1;
	}//else if (iUnitation == i_block_size)

	return d_value;
}//double CBinaryBimodalDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)


CBinaryIsingSpinGlassEvaluation::CBinaryIsingSpinGlassEvaluation(int iSize, int iProblemSeed)
	: CBinaryEvaluation(iSize, 1.0)
{
	Configuration c_config;

	c_config.set("length", iSize);
	c_config.set("precision", 65536);
	c_config.set("problem_seed", iProblemSeed);
	c_config.set("problem_folder", string("EvaluationsInputs\\"));
	c_config.set("ising_type", string("pm"));

	pc_p3_ising_spin_glass = new IsingSpinGlass(c_config, 0);
}//CBinaryIsingSpinGlassEvaluation::CBinaryIsingSpinGlassEvaluation(int iSize, int iProblemSeed)

CBinaryIsingSpinGlassEvaluation::~CBinaryIsingSpinGlassEvaluation()
{
	delete pc_p3_ising_spin_glass;
}//CBinaryIsingSpinGlassEvaluation::~CBinaryIsingSpinGlassEvaluation()

double CBinaryIsingSpinGlassEvaluation::d_evaluate(vector<bool> &vSolution)
{
	return pc_p3_ising_spin_glass->evaluate(vSolution);
}//double CBinaryIsingSpinGlassEvaluation::d_evaluate(vector<bool> &vSolution)


CBinaryMax3SatEvaluation::CBinaryMax3SatEvaluation(int iSize, int iProblemSeed, float fClauseRatio)
	: CBinaryEvaluation(iSize, 1.0)
{
	Configuration c_config;

	c_config.set("length", iSize);
	c_config.set("precision", 65536);
	c_config.set("problem_seed", iProblemSeed);
	c_config.set("clause_ratio", fClauseRatio);

	pc_p3_max_sat = new MAXSAT(c_config, 0);
}//CBinaryMax3SatEvaluation::CBinaryMax3SatEvaluation(int iSize, int iProblemSeed, float fClauseRatio)

CBinaryMax3SatEvaluation::~CBinaryMax3SatEvaluation()
{
	delete pc_p3_max_sat;
}//CBinaryMax3SatEvaluation::~CBinaryMax3SatEvaluation()

double CBinaryMax3SatEvaluation::d_evaluate(vector<bool> &vSolution)
{
	return pc_p3_max_sat->evaluate(vSolution);
}//double CBinaryMax3SatEvaluation::d_evaluate(vector<bool> &vSolution)


CBinaryNKLandscapesEvaluation::CBinaryNKLandscapesEvaluation(int iSize, int iProblemSeed)
	: CBinaryEvaluation(iSize, 1.0)
{
	Configuration c_config;

	c_config.set("length", iSize);
	c_config.set("precision", 65536);
	c_config.set("problem_seed", iProblemSeed);
	c_config.set("k", 5);
	c_config.set("problem_folder", string("EvaluationsInputs\\"));

	pc_p3_nk_landscapes = new NearestNeighborNK(c_config, 0);
}//CBinaryNKLandscapesEvaluation::CBinaryNKLandscapesEvaluation(int iSize, int iProblemSeed)

CBinaryNKLandscapesEvaluation::~CBinaryNKLandscapesEvaluation()
{
	delete pc_p3_nk_landscapes;
}//CBinaryNKLandscapesEvaluation::~CBinaryNKLandscapesEvaluation()

double CBinaryNKLandscapesEvaluation::d_evaluate(vector<bool> &vSolution)
{
	return pc_p3_nk_landscapes->evaluate(vSolution);
}//double CBinaryNKLandscapesEvaluation::d_evaluate(vector<bool> &vSolution)