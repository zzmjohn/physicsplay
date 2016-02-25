/** \file minimizer.h
 */
#if !defined phy1610_minimizer_h_included
#define phy1610_minimizer_h_included

#include "integers.h"
#include <string>
#include <vector>
#include <cmath>

/**
   Output parameters from a gsl minimizer run.
 */
struct oneMinimumResult
{
   std::string m_solvername ; ///< gsl_min_fminimizer_name().
   int         m_status ;     ///< The last successful or unsuccessful gsl function return code.
   std::string m_strerror ;   ///< gsl_strerror() output for m_status.
   bool        m_converged ;  ///< did the iteration converge in the specfied number of iterations.
   Uint        m_iter ;       ///< the final iteration count at the point of convergence, error, or non-convergence.
   double      m_initial_a ;  ///< initial lower bound for the bracket
   double      m_initial_b ;  ///< initial upper bound for the bracket
   double      m_a ;          ///< final lower bound for the bracket
   double      m_b ;          ///< final upper bound for the bracket
   double      m_xmin ;       ///< final position value found by the min search
   double      m_fmin ;       ///< value of the function at m_xmin, provided m_status is not an error.

public:
   oneMinimumResult() :
      m_solvername{},
      m_status{},
      m_strerror{},
      m_converged{},
      m_iter{},
      m_initial_a{},
      m_initial_b{},
      m_a{},
      m_b{},
      m_xmin{}
   {
   }
} ;

/**
   The function object for the gsl minimization code.
 */
struct gsl_spring_min_function
{
   double a ; ///< J (energy scale)
   double b ; ///< m (length scale)
   double c ; ///< N/m (spring constant)
   double d ; ///< m(maximum spring extension)
   double f ; ///< dimensionless (stiffness at maximum extension)
   double g ; ///< m/s^2 (gravitational accelleration).
   double m ; ///< mass (kg)

   // pre-calculate some of the products and ratios required to evaluate the function:
   double c1 ;
   double c2 ;
   double c3 ;

   /**
      constructor.  set physical parameters for the energy functions
    */
   gsl_spring_min_function( const double mass ) :
      a{1},
      b{0.1},
      c{100},
      d{0.5},
      f{2500},
      g{9.8},
      m{mass},
      c1{a * b},
      c2{a * d * d/f},
      c3{- c/(2 * a)}
   {
   }

   /**
      Kinetic energy of the spring function
    */
   static double es( const double x, const gsl_spring_min_function & p )
   {
      double xdSq = (x-p.d)*(x-p.d) ;
      double xbSq = (x-p.b)*(x-p.b) ;
      return p.c1 /x + p.c2 / xdSq - p.a * std::exp( p.c3 * xbSq ) ;
   }

   /**
      Potential energy of the spring function
    */
   static double ew( const double x, const gsl_spring_min_function & p )
   {
      return - p.g * p.m * x ;
   }

   /**
      Total energy of the spring function to pass to the gsl minimization code.
    */
   static double function( double x, void *param )
   {
      gsl_spring_min_function & p = *(gsl_spring_min_function *)param ;

      return es( x, p ) + ew( x, p ) ;
   }

   /**
      Evaluate the energy of the spring at the specified point.
    */
   double operator() ( const double x ) const
   {
      // gsl functions take void *, not const void *, so this needs coersion:
      return function( x, const_cast<gsl_spring_min_function*>(this) ) ;
   }
} ;

/**
   Interval related parameters for gsl minimizer run.
 */
struct minimizerParameters
{
   const Uint              m_max_iter ;   ///< Maximum number of iterations before giving up.
   const double            m_abserr ;     ///< the absolute error criteria for convergence.
   const double            m_relerr ;     ///< the relative error criteria for convergence.
   const bool              m_verbose ;    ///< verbose output
   gsl_spring_min_function m_f ;          ///< minimization function
   double                  m_a ;          ///< initial lower bound for the bracket
   double                  m_b ;          ///< initial upper bound for the bracket

   minimizerParameters( const double   mass,
                        const Uint     max_iter = 100,
                        const double   abserr   = 1e-6,
                        const double   relerr   = 1e-6,
                        const bool     verbose  = false ) :
         m_max_iter{max_iter},
         m_abserr{abserr},
         m_relerr{relerr},
         m_verbose{verbose},
         m_f{mass}
   {
      m_a = m_f.b/10 ;
      m_b = m_f.d - m_f.b/10 ;
   }
} ;

/**
   Specific results for each minimum that is found, and aggregate info about the biggest and smallest minimum found.
 */
class minimizerResults
{
   Sint    m_minIndex ;                 ///< vector postion for the smallest local minimum
   Sint    m_maxIndex ;                 ///< vector postion for the largest local minimum
public:
   std::vector<oneMinimumResult> m_rv ; ///< iteration counts, minimum value, and other info for each min found.

   minimizerResults() :
      m_minIndex{(Sint)-1},
      m_maxIndex{(Sint)-1},
      m_rv{}
   {
   }

   /**
      determine the local and global minimum.  Run this before diff(), xmin(), xmax(), fmin(), fmax().
    */
   void f_min_all( minimizerParameters & p ) ;

   /**
      difference in x position of the smallest local minimum compared to the largest local minimum
    */
   double diff() const ;

   /**
      position of the smallest local minimum found
    */
   double xmin() const ;

   /**
      position of the largest local minimum found
    */
   double xmax() const ;

   /**
      value of the function at the position of the smallest local minimum found
    */
   double fmin() const ;

   /**
      value of the function at the position of the largest local minimum found
    */
   double fmax() const ;
} ;

#endif