// Copyright (C) 2004, International Business Machines and others.
// All Rights Reserved.
// This code is published under the Common Public License.
//
// $Id$
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

#ifndef __IPIPOPTCALCULATEDQUANTITIES_HPP__
#define __IPIPOPTCALCULATEDQUANTITIES_HPP__

#include "IpUtils.hpp"
#include "IpIpoptNLP.hpp"
#include "IpIpoptData.hpp"

namespace Ipopt
{

  /** Class for all IPOPT specific calculated quantities.
   *  
   */
  class IpoptCalculatedQuantities : public ReferencedObject
  {
  public:
    /** Norm types */
    enum ENormType {
      NORM_1,
      NORM_2,
      NORM_MAX
    };

    /**@name Constructors/Destructors */
    //@{
    /** Constructor */
    IpoptCalculatedQuantities(const SmartPtr<IpoptNLP>& ip_nlp,
                              const SmartPtr<IpoptData>& ip_data);
    /** Default destructor */
    virtual ~IpoptCalculatedQuantities();
    //@}

    /** This method must be called to initialize the global
     *  algorithmic parameters.  The parameters are taken from the
     *  OptionsList object. */
    bool Initialize(const Journalist& jnlst,
                    const OptionsList& options,
                    const std::string& prefix);

    /** @name Slacks */
    //@{
    /** Slacks for x_L (at current iterate) */
    SmartPtr<const Vector> curr_slack_x_L();
    /** Slacks for x_U (at current iterate) */
    SmartPtr<const Vector> curr_slack_x_U();
    /** Slacks for s_L (at current iterate) */
    SmartPtr<const Vector> curr_slack_s_L();
    /** Slacks for s_U (at current iterate) */
    SmartPtr<const Vector> curr_slack_s_U();
    /** Slacks for x_L (at trial point) */
    SmartPtr<const Vector> trial_slack_x_L();
    /** Slacks for x_U (at trial point) */
    SmartPtr<const Vector> trial_slack_x_U();
    /** Slacks for s_L (at trial point) */
    SmartPtr<const Vector> trial_slack_s_L();
    /** Slacks for s_U (at trial point) */
    SmartPtr<const Vector> trial_slack_s_U();
    /** Indicating whether or not we "fudged" the slacks */
    Index AdjustedTrialSlacks();
    /** Reset the flags for "fudged" slacks */
    void ResetAdjustedTrialSlacks();
    //@}

    /** @name Objective function */
    //@{
    /** Value of objective function (at current point) */
    Number curr_f();
    /** Value of objective function (at trial point) */
    Number trial_f();
    /** Gradient of objective function (at current point) */
    SmartPtr<const Vector> curr_grad_f();
    //@}

    /** @name Barrier Objective Function */
    //@{
    /** Barrier Objective Function Value
     * (at current iterate with current mu)
     */
    Number curr_barrier_obj();
    /** Barrier Objective Function Value
     * (at trial point with current mu)
     */
    Number trial_barrier_obj();

    /** Gradient of barrier objective function with respect to x
     * (at current point with current mu) */
    SmartPtr<const Vector> curr_grad_barrier_obj_x();
    /** Gradient of barrier objective function with respect to s
     * (at current point with current mu) */
    SmartPtr<const Vector> curr_grad_barrier_obj_s();
    //@}

    /** @name Constraints */
    //@{
    /** c(x) (at current point) */
    SmartPtr<const Vector> curr_c();
    /** c(x) (at trial point) */
    SmartPtr<const Vector> trial_c();
    /** d(x) (at current point) */
    SmartPtr<const Vector> curr_d();
    /** d(x) (at trial point) */
    SmartPtr<const Vector> trial_d();
    /** d(x) - s (at current point) */
    SmartPtr<const Vector> curr_d_minus_s();
    /** d(x) - s (at trial point) */
    SmartPtr<const Vector> trial_d_minus_s();
    /** Jacobian of c (at current point) */
    SmartPtr<const Matrix> curr_jac_c();
    /** Jacobian of d (at current point) */
    SmartPtr<const Matrix> curr_jac_d();
    /** Product of Jacobian (evaluated at current point) of C
     *  transpose with general vector */
    SmartPtr<const Vector> curr_jac_cT_times_vec(const Vector& vec);
    /** Product of Jacobian (evaluated at current point) of D
     *  transpose with general vector */
    SmartPtr<const Vector> curr_jac_dT_times_vec(const Vector& vec);
    /** Product of Jacobian (evaluated at current point) of C
     *  transpose with current y_c */
    SmartPtr<const Vector> curr_jac_cT_times_curr_y_c();
    /** Product of Jacobian (evaluated at current point) of D
     *  transpose with current y_d */
    SmartPtr<const Vector> curr_jac_dT_times_curr_y_d();
    /** Product of Jacobian (evaluated at current point) of C
     *  with general vector */
    SmartPtr<const Vector> curr_jac_c_times_vec(const Vector& vec);
    /** Product of Jacobian (evaluated at current point) of D
     *  with general vector */
    SmartPtr<const Vector> curr_jac_d_times_vec(const Vector& vec);
    /** Constraint Violation (at current iterate). This value should
     *  be used in the line search, and not curr_primal_infeasibility().
     *  What type of norm is used depends on constr_viol_normtype */
    Number curr_constraint_violation();
    /** Constraint Violation (at trial point). This value should
     *  be used in the line search, and not curr_primal_infeasibility().
     *  What type of norm is used depends on constr_viol_normtype */
    Number trial_constraint_violation();
    //@}

    /** @name Hessian matrices */
    //@{
    /** exact Hessian at current iterate (uncached) */
    SmartPtr<const SymMatrix> curr_exact_hessian();
    /** return a matrix of the same type and structure as the Hessian
     *  matrix, but with all "values" set to zero (uncached) */
    SmartPtr<const SymMatrix> zero_hessian();
    //@}

    /** @name primal-dual error and its components */
    //@{
    /** x-part of gradient of Lagrangian function (at current point) */
    SmartPtr<const Vector> curr_grad_lag_x();
    /** s-part of gradient of Lagrangian function (at current point) */
    SmartPtr<const Vector> curr_grad_lag_s();
    /** Complementarity for x_L (for current iterate) */
    SmartPtr<const Vector> curr_compl_x_L();
    /** Complementarity for x_U (for current iterate) */
    SmartPtr<const Vector> curr_compl_x_U();
    /** Complementarity for s_L (for current iterate) */
    SmartPtr<const Vector> curr_compl_s_L();
    /** Complementarity for s_U (for current iterate) */
    SmartPtr<const Vector> curr_compl_s_U();
    /** Relaxed complementarity for x_L (for current iterate and current mu) */
    SmartPtr<const Vector> curr_relaxed_compl_x_L();
    /** Relaxed complementarity for x_U (for current iterate and current mu) */
    SmartPtr<const Vector> curr_relaxed_compl_x_U();
    /** Relaxed complementarity for s_L (for current iterate and current mu) */
    SmartPtr<const Vector> curr_relaxed_compl_s_L();
    /** Relaxed complementarity for s_U (for current iterate and current mu) */
    SmartPtr<const Vector> curr_relaxed_compl_s_U();

    /** Primal infeasibility in a given norm (at current iterate). */
    Number curr_primal_infeasibility(ENormType NormType);
    /** Primal infeasibility in a given norm (at trial point) */
    Number trial_primal_infeasibility(ENormType NormType);

    /** Dual infeasibility in a given norm (at current iterate) */
    Number curr_dual_infeasibility(ENormType NormType);

    /** Complementarity (for all complementarity conditions together)
     *  in a given norm (at current iterate) */
    Number curr_complementarity(Number mu, ENormType NormType);

    /** Centrality measure (in spirit of the -infinity-neighborhood. */
    Number CalcCentralityMeasure(const Vector& compl_x_L,
                                 const Vector& compl_x_U,
                                 const Vector& compl_s_L,
                                 const Vector& compl_s_U);
    /** Centrality measure at current point */
    Number curr_centrality_measure();

    /** Scaled total optimality error for the original NLP at the
     *  current iterate. */
    Number curr_nlp_error();

    /** Scaled total optimality error for the barrier problem at the
     *  current iterate. */
    Number curr_barrier_error();

    /** Primal-dual optimality error for the original NLP (at current iterate)
     */
    Number curr_primal_dual_error();
    /** Relaxed primal-dual optimality error for the original NLP
     *  (at current iterate and for current mu)
     */
    Number curr_relaxed_primal_dual_error();
    //@}

    /** @name Computing fraction-to-the-boundary step sizes */
    //@{
    /** Fraction to the boundary from (current) primal variables x and s
     *  for a given step */
    Number primal_frac_to_the_bound(Number tau,
                                    const Vector& delta_x,
                                    const Vector& delta_s);
    /** Fraction to the boundary from (current) primal variables x and s
     *  for internal (current) step */
    Number curr_primal_frac_to_the_bound(Number tau);
    /** Fraction to the boundary from (current) dual variables z and v
     *  for a given step */
    Number dual_frac_to_the_bound(Number tau,
                                  const Vector& delta_z_L,
                                  const Vector& delta_z_U,
                                  const Vector& delta_v_L,
                                  const Vector& delta_v_U);
    /** Fraction to the boundary from (current) dual variables z and v
     *  for internal (current) step */
    Number curr_dual_frac_to_the_bound(Number tau);
    /** Fraction to the boundary from (current) slacks for a given
     *  step in the slacks.  Usually, one will use the
     *  primal_frac_to_the_bound method to compute the primal fraction
     *  to the boundary step size, but if it is cheaper to provide the
     *  steps in the slacks directly (e.g. when the primal step sizes
     *  are only temporary), the this method is more efficient. */
    Number slack_frac_to_the_bound(Number tau,
				   const Vector& delta_x_L,
				   const Vector& delta_x_U,
				   const Vector& delta_s_L,
				   const Vector& delta_s_U);
    //@}

    /** @name Sigma matrices */
    //@{
    SmartPtr<const Vector> curr_sigma_x();
    SmartPtr<const Vector> curr_sigma_s();
    //@}

    /** average of current values of the complementarities */
    Number curr_avrg_compl();
    /** average of trial values of the complementarities */
    Number trial_avrg_compl();

    /** inner_product of current barrier obj. fn. gradient with current search direction */
    Number curr_gradBarrTDelta();

    /** Compute the norm of a specific type of a set of vectors (uncached) */
    Number
    CalcNormOfType(IpoptCalculatedQuantities::ENormType NormType,
                   std::vector<SmartPtr<const Vector> > vecs);

    /** Compute the norm of a specific type of two vectors (uncached) */
    Number
    CalcNormOfType(IpoptCalculatedQuantities::ENormType NormType,
                   const Vector& vec1, const Vector& vec2);

    /** Norm type used for calculating constraint violation */
    ENormType constr_viol_normtype() const
    {
      return constr_viol_normtype_;
    }

  private:
    /**@name Default Compiler Generated Methods
     * (Hidden to avoid implicit creation/calling).
     * These methods are not implemented and 
     * we do not want the compiler to implement
     * them for us, so we declare them private
     * and do not define them. This ensures that
     * they will not be implicitly created/called. */
    //@{
    /** Default Constructor */
    IpoptCalculatedQuantities();

    /** Copy Constructor */
    IpoptCalculatedQuantities(const IpoptCalculatedQuantities&);

    /** Overloaded Equals Operator */
    void operator=(const IpoptCalculatedQuantities&);
    //@}

    /** @name Pointers for easy access to data and NLP information */
    //@{
    /** Ipopt NLP object */
    SmartPtr<IpoptNLP> ip_nlp_;
    /** Ipopt Data object */
    SmartPtr<IpoptData> ip_data_;
    //@}

    /** @name Algorithmic Parameters that can be set throught the
     *  options list. Those parameters are initialize by calling the
     *  Initialize method.*/
    //@{
    /** Parameter in formula for computing overall primal-dual
     *  optimality error */
    Number s_max_;
    /** Weighting factor for the linear damping term added to the
     *  barrier objective funciton. */
    Number kappa_d_;
    /** fractional movement allowed in bounds */
    Number s_move_;
    /** Norm type to be used when calculating the constraint violation */
    ENormType constr_viol_normtype_;
    //@}

    /** @name Caches for slacks */
    //@{
    CachedResults< SmartPtr<Vector> > curr_slack_x_L_cache_;
    CachedResults< SmartPtr<Vector> > curr_slack_x_U_cache_;
    CachedResults< SmartPtr<Vector> > curr_slack_s_L_cache_;
    CachedResults< SmartPtr<Vector> > curr_slack_s_U_cache_;
    CachedResults< SmartPtr<Vector> > trial_slack_x_L_cache_;
    CachedResults< SmartPtr<Vector> > trial_slack_x_U_cache_;
    CachedResults< SmartPtr<Vector> > trial_slack_s_L_cache_;
    CachedResults< SmartPtr<Vector> > trial_slack_s_U_cache_;
    Index num_adjusted_slack_x_L_;
    Index num_adjusted_slack_x_U_;
    Index num_adjusted_slack_s_L_;
    Index num_adjusted_slack_s_U_;
    //@}

    /** @name Cached for objective function stuff */
    //@{
    CachedResults<Number> curr_f_cache_;
    CachedResults<Number> trial_f_cache_;
    CachedResults< SmartPtr<const Vector> > curr_grad_f_cache_;
    //@}

    /** @name Caches for barrier function stuff */
    //@{
    CachedResults<Number> curr_barrier_obj_cache_;
    CachedResults<Number> trial_barrier_obj_cache_;
    CachedResults< SmartPtr<const Vector> > curr_grad_barrier_obj_x_cache_;
    CachedResults< SmartPtr<const Vector> > curr_grad_barrier_obj_s_cache_;
    //@}

    /** @name Caches for constraint stuff */
    //@{
    CachedResults< SmartPtr<const Vector> > curr_c_cache_;
    CachedResults< SmartPtr<const Vector> > trial_c_cache_;
    CachedResults< SmartPtr<const Vector> > curr_d_cache_;
    CachedResults< SmartPtr<const Vector> > trial_d_cache_;
    CachedResults< SmartPtr<const Vector> > curr_d_minus_s_cache_;
    CachedResults< SmartPtr<const Vector> > trial_d_minus_s_cache_;
    CachedResults< SmartPtr<const Matrix> > curr_jac_c_cache_;
    CachedResults< SmartPtr<const Matrix> > curr_jac_d_cache_;
    CachedResults< SmartPtr<const Vector> > curr_jac_cT_times_vec_cache_;
    CachedResults< SmartPtr<const Vector> > curr_jac_dT_times_vec_cache_;
    CachedResults< SmartPtr<const Vector> > curr_jac_c_times_vec_cache_;
    CachedResults< SmartPtr<const Vector> > curr_jac_d_times_vec_cache_;
    CachedResults<Number> curr_constraint_violation_cache_;
    CachedResults<Number> trial_constraint_violation_cache_;
    //@}

    /** Cache for the exact Hessian */
    CachedResults< SmartPtr<const SymMatrix> > curr_exact_hessian_cache_;

    /** @name Components of primal-dual error */
    //@{
    CachedResults< SmartPtr<const Vector> > curr_grad_lag_x_cache_;
    CachedResults< SmartPtr<const Vector> > curr_grad_lag_s_cache_;
    CachedResults< SmartPtr<const Vector> > curr_compl_x_L_cache_;
    CachedResults< SmartPtr<const Vector> > curr_compl_x_U_cache_;
    CachedResults< SmartPtr<const Vector> > curr_compl_s_L_cache_;
    CachedResults< SmartPtr<const Vector> > curr_compl_s_U_cache_;
    CachedResults< SmartPtr<const Vector> > curr_relaxed_compl_x_L_cache_;
    CachedResults< SmartPtr<const Vector> > curr_relaxed_compl_x_U_cache_;
    CachedResults< SmartPtr<const Vector> > curr_relaxed_compl_s_L_cache_;
    CachedResults< SmartPtr<const Vector> > curr_relaxed_compl_s_U_cache_;
    CachedResults<Number> curr_primal_infeasibility_cache_;
    CachedResults<Number> trial_primal_infeasibility_cache_;
    CachedResults<Number> curr_dual_infeasibility_cache_;
    CachedResults<Number> curr_complementarity_cache_;
    CachedResults<Number> curr_centrality_measure_cache_;
    CachedResults<Number> curr_nlp_error_cache_;
    CachedResults<Number> curr_barrier_error_cache_;
    CachedResults<Number> curr_primal_dual_error_cache_;
    CachedResults<Number> curr_relaxed_primal_dual_error_cache_;
    //@}

    /** @name Caches for fraction to the boundary step sizes */
    //@{
    CachedResults<Number> primal_frac_to_the_bound_cache_;
    CachedResults<Number> dual_frac_to_the_bound_cache_;
    CachedResults<Number> slack_frac_to_the_bound_cache_;
    //@}

    /** @name Caches for sigma matrices */
    //@{
    CachedResults< SmartPtr<const Vector> > curr_sigma_x_cache_;
    CachedResults< SmartPtr<const Vector> > curr_sigma_s_cache_;
    //@}

    /** Cache for average of current complementarity */
    CachedResults<Number> curr_avrg_compl_cache_;
    /** Cache for average of trial complementarity */
    CachedResults<Number> trial_avrg_compl_cache_;

    /** Cache for grad barrier obj. fn inner product with step */
    CachedResults<Number> curr_gradBarrTDelta_cache_;

    /** @name Indicator vectors required for the linear damping terms
     *  to handle unbounded solution sets. */
    //@{
    /** Indicator vector for selecting the elements in x that have
     *  only lower bounds. */
    SmartPtr<Vector> dampind_x_L_;
    /** Indicator vector for selecting the elements in x that have
     *  only upper bounds. */
    SmartPtr<Vector> dampind_x_U_;
    /** Indicator vector for selecting the elements in s that have
     *  only lower bounds. */
    SmartPtr<Vector> dampind_s_L_;
    /** Indicator vector for selecting the elements in s that have
     *  only upper bounds. */
    SmartPtr<Vector> dampind_s_U_;
    //@}

    /** flag indicating if Initialize method has been called (for
     *  debugging) */
    bool initialize_called_;

    /** @name Auxiliary functions */
    //@{
    /** Compute new vector containing the slack to a lower bound
     *  (uncached)
     */
    SmartPtr<Vector> CalcSlack_L(const Matrix& P,
                                 const Vector& x,
                                 const Vector& x_bound);
    /** Compute new vector containing the slack to a upper bound
     *  (uncached)
     */
    SmartPtr<Vector> CalcSlack_U(const Matrix& P,
                                 const Vector& x,
                                 const Vector& x_bound);
    /** Compute barrier term at given point
     *  (uncached)
     */
    Number CalcBarrierTerm(Number mu,
                           const Vector& slack_x_L,
                           const Vector& slack_x_U,
                           const Vector& slack_s_L,
                           const Vector& slack_s_U);

    /** Compute complementarity for slack / multiplier pair */
    SmartPtr<const Vector> CalcCompl(const Vector& slack,
                                     const Vector& mult);

    /** Compute fraction to the boundary parameter for lower bounds 0 */
    Number CalcFracToZeroBound(const Vector& x,
                               const Vector& delta,
                               Number tau);

    /** Compute fraction to the boundary parameter for lower and upper bounds */
    Number CalcFracToBound(const Vector& slack_L,
                           const Matrix& P_L,
                           const Vector& slack_U,
                           const Matrix& P_U,
                           const Vector& delta,
                           Number tau);

    /** Compute the scaling factors for the optimality error. */
    void ComputeOptimalityErrorScaling(const Vector& y_c, const Vector& y_d,
                                       const Vector& z_L, const Vector& z_U,
                                       const Vector& v_L, const Vector& v_U,
                                       Number s_max,
                                       Number& s_d, Number& s_c);

    /** Check if slacks are becoming too small.  If slacks are
     *  becoming too small, they are change.  The return value is the
     *  number of corrected slacks. */
    Index CalculateSafeSlack(SmartPtr<Vector>& slack,
                             const SmartPtr<const Vector>& bound,
                             const SmartPtr<const Vector>& curr_point,
                             const SmartPtr<const Vector>& multiplier);

    /** Computes the indicator vectors that can be used to filter out
     *  those entries in the slack_... variables, that correspond to
     *  variables with only lower and upper bounds.  This is required
     *  for the linear damping term in the barrier objective function
     *  to handle unbounded solution sets.  */
    void ComputeDampingIndicators(SmartPtr<const Vector>& dampind_x_L,
                                  SmartPtr<const Vector>& dampind_x_U,
                                  SmartPtr<const Vector>& dampind_s_L,
                                  SmartPtr<const Vector>& dampind_s_U);

    //@}
  };

} // namespace Ipopt

#endif
