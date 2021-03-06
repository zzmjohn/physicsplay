/** \file wave1d.h
 */
#if !defined phy1610_ps2_wave1d_h_included
#define phy1610_ps2_wave1d_h_included

#include <vector>
#include "parameters.h"

/**
   \brief 1d wave equation solver.

   The compute method of this class solves the 1-dim wave equation

   \f[
      \frac{\partial^2u}{\partial t^2} - c^2 \frac{\partial^2u}{\partial x^2} + (\frac{1}{\tau}) \frac{\partial u}{\partial t} = 0
   \f]

   with boundary conditions \f[ u(x_1,t)=u(x_2,t)=0 \f],

   and initial conditions of a triangle form:
    \f[u(x,0) = 0 \f] for \f[ x<x_1+L/4  \f]
    \f[u(x,0) = (x-x_1-L/4)/L \f] for \f[ x_1+L/4<(x_1+x_2)/2  \f]
    \f[u(x,0) = 0.5-(x-x_1-L/4)/L \f] for \f[ x_1+L/4<(x_1+x_2)/2 \f]
    \f[u(x,0) = 0 \f] for \f[ x>x_2-L/4 \f]

   where \f[L=x_2-x_1. \f]
 */
class wave1d
{
   std::vector<double> rho_prev ; ///< time step t-1
   std::vector<double> rho      ; ///< time step t
   std::vector<double> rho_next ; ///< time step t+1
   std::vector<double> x        ; ///< x values
   const parameters & p ;

public:
   /**
      Allocate storage for the computational arrays
    */
   wave1d( const parameters & p_ ) ;

   /**
      Set the values of x[], rho[], and rho_prev[] to initial values.
    */
   void initializeAndExcite() ;

   /**
      Show the state of the computation.

      \param time [in]
         N * dt at the time of the display ( or zero ).
     */
   void display( double time ) ;

   /**
      Workhorse of the class.  Does the 1d wave equation solution.
    */
   void compute() ;
} ;

#endif
