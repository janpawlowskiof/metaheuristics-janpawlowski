#include "RealCMAES.h"

using namespace Optimizers;


CCMAESIndividual::CCMAESIndividual(IEvaluation<double> &cEvaluation, VectorXd &vSample)
	: c_evaluation(cEvaluation), v_genotype((size_t)vSample.size())
{
	for (size_t i = 0; i < v_genotype.size(); i++)
	{
		v_genotype[i] = vSample((Index)i);
	}//for (size_t i = 0; i < v_genotype.size(); i++)
}//CCMAESIndividual::CCMAESIndividual(IEvaluation<double> &cEvaluation, VectorXd &vSample)

void CCMAESIndividual::vRepairGenotype()
{
	IConstraint<double> &c_constraint = c_evaluation.cGetConstraint();

	double d_lower_bound;
	double d_upper_bound;

	for (size_t i = 0; i < v_genotype.size(); i++)
	{
		d_lower_bound = c_constraint.tGetLowerBound((int)i);
		d_upper_bound = c_constraint.tGetUpperBound((int)i);

		if (v_genotype[i] < d_lower_bound)
		{
			v_genotype[i] = d_lower_bound;
		}//if (v_genotype[i] < d_lower_bound)
		else if (v_genotype[i] > d_upper_bound)
		{
			v_genotype[i] = d_upper_bound;
		}//else if (v_genotype[i] > d_upper_bound)
	}//for (size_t i = 0; i < v_genotype.size(); i++)
}//void CCMAESIndividual::vRepairGenotype()

void CCMAESIndividual::vEvaluate()
{
	d_fitness = c_evaluation.dEvaluate(v_genotype);
}//void CCMAESIndividual::vEvaluate()


CRealCMAES::CRealCMAES(IEvaluation<double> &cEvaluation, IStopCondition &cStopCondition, mt19937 &cRandomEngine, double dInitSigma)
	: COptimizer<double>(cEvaluation, cStopCondition), v_means(cEvaluation.iGetSize()), v_previous_means(v_means), m_covariance_matrix(cEvaluation.iGetSize(), cEvaluation.iGetSize()), d_init_sigma(dInitSigma), c_random_engine(cRandomEngine), v_p_sigma(cEvaluation.iGetSize()), v_p_c(cEvaluation.iGetSize())
{

}//CRealCMAES::CRealCMAES(IEvaluation<double> &cEvaluation, IStopCondition &cStopCondition, mt19937 &cRandomEngine, double dInitSigma)

CRealCMAES::~CRealCMAES()
{
	VectorUtils::vClear(v_population);
}//CRealCMAES::~CRealCMAES()

void CRealCMAES::v_initialize(clock_t tStartTime)
{
	VectorUtils::vClear(v_population);
	v_population.reserve((size_t)i_lambda);

	v_init_means();
	m_covariance_matrix.setIdentity();

	v_init_selection_parameters();
	v_init_adaptation_parameters();
	v_init_step_size_parameters();
}//void CRealCMAES::v_initialize(clock_t tStartTime)

bool CRealCMAES::b_run_iteration(long long iIterationNumber, clock_t tStartTime)
{
	VectorUtils::vClear(v_population);
	
	v_fill_population();
	v_sort_population();

	v_adapt_means();
	v_update_evolution_path();
	v_adapt_covariance_matrix();
	v_adapt_step_size();

	return b_check_new_best(*v_population.front());
}//bool CRealCMAES::b_run_iteration(long long iIterationNumber, clock_t tStartTime)

void CRealCMAES::v_init_means()
{
	CRealRandomGenerator c_random_generator(c_evaluation.cGetConstraint(), c_random_engine);
	vector<double> v_random_solution((size_t)c_evaluation.iGetSize());

	c_random_generator.vFill(v_random_solution);

	for (Index i = 0; i < v_means.size(); i++)
	{
		v_means(i) = v_random_solution[(size_t)i];
	}//for (Index i = 0; i < v_means.size(); i++)
}//void CRealCMAES::v_init_means()

void CRealCMAES::v_init_selection_parameters()
{
	i_lambda = 4 + (int)floor(3.0 * log(c_evaluation.iGetSize()));
	i_mu = i_lambda / 2;

	v_weights.resize((Index)i_mu);

	for (Index i = 0; i < v_weights.size(); i++)
	{
		v_weights(i) = log(i_lambda / 2.0 + 0.5) - log((int)i + 1);
	}//for (Index i = 0; i < v_weights.size(); i++)

	v_weights /= v_weights.sum();

	d_mu_eff = 1.0 / v_weights.squaredNorm();
}//void CRealCMAES::v_init_selection_parameters()

void CRealCMAES::v_init_adaptation_parameters()
{
	d_c_c = (4.0 + d_mu_eff / c_evaluation.iGetSize()) / (c_evaluation.iGetSize() + 4.0 + 2.0 * d_mu_eff / c_evaluation.iGetSize());
	d_c_sigma = (d_mu_eff + 2.0) / (c_evaluation.iGetSize() + d_mu_eff + 5.0);
	d_c_1 = 2.0 / ((c_evaluation.iGetSize() + 1.3) * (c_evaluation.iGetSize() + 1.3) + d_mu_eff);
	d_c_mu = min(1 - d_c_1, 2.0 * (d_mu_eff - 2.0 + 1.0 / d_mu_eff) / ((c_evaluation.iGetSize() + 2.0) * (c_evaluation.iGetSize() + 2.0) + d_mu_eff));
	d_damping = 1.0 + 2.0 * max(0.0, sqrt((d_mu_eff - 1.0) / (c_evaluation.iGetSize() + 1.0)) - 1.0) + d_c_sigma;
	d_chi_n = sqrt(c_evaluation.iGetSize()) * (1.0 - 1.0 / (4.0 * c_evaluation.iGetSize()) + 1.0 / (21.0 * c_evaluation.iGetSize() * c_evaluation.iGetSize()));
}//void CRealCMAES::v_init_adaptation_parameters()

void CRealCMAES::v_init_step_size_parameters()
{
	v_p_sigma.setZero();
	v_p_c.setZero();
	i_h_sigma = 0;
	d_sigma = d_init_sigma;
}//void CRealCMAES::v_init_step_size_parameters()

void CRealCMAES::v_fill_population()
{
	VectorXd *pv_sample;

	CCMAESIndividual *pc_individual;

	for (int i = 0; i < i_lambda; i++)
	{
		pv_sample = pv_sample_normal_distribution();

		pc_individual = new CCMAESIndividual(c_evaluation, *pv_sample);
		pc_individual->vRepairGenotype();
		pc_individual->vEvaluate();

		v_population.push_back(pc_individual);

		delete pv_sample;
	}//for (int i = 0; i < i_lambda; i++)
}//void CRealCMAES::v_fill_population()

void CRealCMAES::v_sort_population()
{
	sort(v_population.begin(), v_population.end(), [](CCMAESIndividual *pcIndividual0, CCMAESIndividual *pcIndividual1)
	{
		return pcIndividual0->dGetFitness() > pcIndividual1->dGetFitness();
	});//sort(v_population.begin(), v_population.end(), [](CCMAESIndividual *pcIndividual0, CCMAESIndividual *pcIndividual1)
}//void CRealCMAES::v_sort_population()

bool CRealCMAES::b_check_new_best(CCMAESIndividual &cIndividual)
{
	return COptimizer<double>::b_check_new_best(cIndividual.vGetGenotype(), cIndividual.dGetFitness());
}//bool CRealCMAES::b_check_new_best(CCMAESIndividual &cIndividual)

//https://stackoverflow.com/questions/6142576/sample-from-multivariate-normal-gaussian-distribution-in-c
VectorXd * CRealCMAES::pv_sample_normal_distribution()
{
	SelfAdjointEigenSolver<MatrixXd> c_eigen_solver(m_covariance_matrix);
	MatrixXd m_transform = c_eigen_solver.eigenvectors() * c_eigen_solver.eigenvalues().cwiseMax(0).cwiseSqrt().asDiagonal();

	normal_distribution<> c_normal_dist;

	VectorXd v_random_vector(c_evaluation.iGetSize());
	
	v_random_vector = v_random_vector.unaryExpr([&](double dValue)
	{
		return c_normal_dist(c_random_engine);
	});//v_random_vector.unaryExpr([&](double dValue)

	return new VectorXd(v_means + d_sigma * m_transform * v_random_vector);
}//VectorXd * CRealCMAES::pv_sample_normal_distribution()

void CRealCMAES::v_adapt_means()
{
	v_previous_means = v_means;

	double d_weighted_mean;

	for (int i = 0; i < c_evaluation.iGetSize(); i++)
	{
		d_weighted_mean = 0;

		for (int j = 0; j < i_mu; j++)
		{
			d_weighted_mean += v_population[j]->vGetGenotype()[(size_t)i] * v_weights((Index)j);
		}//for (int j = 0; j < i_mu; j++)

		v_means((Index)i) = d_weighted_mean;
	}//for (int i = 0; i < c_evaluation.iGetSize(); i++)
}//void CRealCMAES::v_adapt_means()

void CRealCMAES::v_update_evolution_path()
{
	SelfAdjointEigenSolver<MatrixXd> c_eigen_solver(m_covariance_matrix);
	MatrixXd m_inversed_sqrt_covariance_matrix = c_eigen_solver.operatorInverseSqrt();

	v_p_sigma = (1 - d_c_sigma) * v_p_sigma + sqrt(d_c_sigma * (2.0 - d_c_sigma) * d_mu_eff) * m_inversed_sqrt_covariance_matrix * ((v_means - v_previous_means) / d_sigma);

	if (v_p_sigma.squaredNorm() / (1.0 - pow(1.0 - d_c_sigma, 2.0 * c_evaluation.iGetFFE() / i_lambda)) / c_evaluation.iGetSize() < 2.0 + 4.0 / (c_evaluation.iGetSize() + 1.0))
	{
		i_h_sigma = 1;
	}//if (v_p_sigma.squaredNorm() / (1.0 - pow(1.0 - d_c_sigma, 2.0 * c_evaluation.iGetFFE() / i_lambda)) / c_evaluation.iGetSize() < 2.0 + 4.0 / (c_evaluation.iGetSize() + 1.0))
	else
	{
		i_h_sigma = 0;
	}//else if (v_p_sigma.squaredNorm() / (1.0 - pow(1.0 - d_c_sigma, 2.0 * c_evaluation.iGetFFE() / i_lambda)) / c_evaluation.iGetSize() < 2.0 + 4.0 / (c_evaluation.iGetSize() + 1.0))

	v_p_c = (1.0 - d_c_c) * v_p_c + i_h_sigma * sqrt(d_c_c * (2.0 - d_c_c) * d_mu_eff) * ((v_means - v_previous_means) / d_sigma);
}//void CRealCMAES::v_update_evolution_path()

void CRealCMAES::v_adapt_covariance_matrix()
{
	MatrixXd m_rank_mu_update_matrix(m_covariance_matrix);

	m_rank_mu_update_matrix.setZero();

	for (int i = 0; i < i_mu; i++)
	{
		VectorXd v_x((Index)v_population[i]->vGetGenotype().size());

		for (Index j = 0; j < v_x.size(); j++)
		{
			v_x(j) = v_population[i]->vGetGenotype()[(size_t)j];
		}//for (Index j = 0; j < v_x.size(); j++)

		VectorXd v_y = (v_x - v_previous_means) / d_sigma;

		m_rank_mu_update_matrix += v_weights((Index)i) * v_y * v_y.transpose();
	}//for (int i = 0; i < i_mu; i++)

	m_covariance_matrix = (1.0 - d_c_1 - d_c_mu) * m_covariance_matrix + d_c_1 * (v_p_c * v_p_c.transpose() + (1 - i_h_sigma) * d_c_c * (2.0 - d_c_c) * m_covariance_matrix) + d_c_mu * m_rank_mu_update_matrix;
}//void CRealCMAES::v_adapt_covariance_matrix()

void CRealCMAES::v_adapt_step_size()
{
	d_sigma *= exp(d_c_sigma / d_damping * (v_p_sigma.norm() / d_chi_n - 1.0));
}//void CRealCMAES::v_adapt_step_size()