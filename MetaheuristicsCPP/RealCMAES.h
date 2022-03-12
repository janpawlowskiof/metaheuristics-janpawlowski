#pragma once

#include "Optimizer.h"
#include "RealGenerators.h"
#include "VectorUtils.h"

#include <algorithm>
#include <cmath>
#include <Constraint.h>
#include <Eigen/Dense>
#include <random>
#include <vector>

using namespace Generators;

using namespace Constraints;
using namespace Eigen;
using namespace std;

namespace Optimizers
{
	class CCMAESIndividual
	{
	public:
		CCMAESIndividual(IEvaluation<double> &cEvaluation, VectorXd &vSample);

		void vRepairGenotype();
		void vEvaluate();

		double dGetFitness() { return d_fitness; }
		vector<double> &vGetGenotype() { return v_genotype; }

	private:
		double d_fitness;
		vector<double> v_genotype;

		IEvaluation<double> &c_evaluation;
	};//class CCMAESIndividual


	class CRealCMAES : public COptimizer<double>
	{
	public:
		CRealCMAES(IEvaluation<double> &cEvaluation, IStopCondition &cStopCondition, mt19937 &cRandomEngine, double dInitSigma);

		virtual ~CRealCMAES();

	protected:
		virtual void v_initialize(clock_t tStartTime);
		virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime);

	private:
		void v_init_means();
		void v_init_selection_parameters();
		void v_init_adaptation_parameters();
		void v_init_step_size_parameters();

		void v_fill_population();
		void v_sort_population();

		VectorXd *pv_sample_normal_distribution();

		void v_adapt_means();
		void v_update_evolution_path();
		void v_adapt_covariance_matrix();
		void v_adapt_step_size();

		bool b_check_new_best(CCMAESIndividual &cIndividual);

		vector<CCMAESIndividual*> v_population;

		VectorXd v_previous_means;
		VectorXd v_means;
		MatrixXd m_covariance_matrix;

		int i_lambda;
		VectorXd v_weights;
		int i_mu;
		double d_mu_eff;

		double d_c_c;
		double d_c_sigma;
		double d_c_1;
		double d_c_mu;
		double d_damping;
		double d_chi_n;

		VectorXd v_p_sigma;
		VectorXd v_p_c;
		int i_h_sigma;
		double d_init_sigma;
		double d_sigma;

		mt19937 &c_random_engine;
	};//class CRealCMAES : public COptimizer<double>
}//namespace Optimizers