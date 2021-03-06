Usage:

   $ cd ps5
   $ make springmodel
   $ ./springmodel  --help
   usage: springmodel
           [--file=p|-f p]
             The path to the output filename.  Stdout will be used if unspecified.
           [--csv|-c [--mass=m|-m m]]
             Evaluate the minimization function at a
             set of points in the interval and output a csv format file with these points for plotting.
           [--verbose|-v]
             Instead of the output required for the problem, show some detailed diagnositic state.
           [--xmax]
             Show the x position of the largest local min instead of the (default) smallest local min for each value of m in [0,0,5].
           [--fmax]
             Show E(x_max) for the the largest local min for each value of the mass in [0,0.5]
           [--fmin]
             Show E(x_min) for the the smallest local min (global min) for each value of the mass in [0,0.5]
           [--fmin]
             Show the difference between the two local minumums or zero for each value of the mass in [0,0.5]
           [--help]

Note that the --csv/xmax/fmin/fmax/diff options were for debugging during development.

To invoke:

   $ ./springmodel --file x.out

This writes the output for the mass vs. global minimum energy position location to the file ps5/x.out, and 
produces output:

   Maximum load: 0.368317 (kg)

What's included in this tarball:

   - This file:

      README.ps5.txt

   - git log:

      ps5.git.log

   - Makefiles for ps5:

      ps5/GNUmakefile
      make.vars
      make.rules

   - Output of 'springmodel --file x.out' :

      ps5/x.out

     This output is plotted in ps5/massextensionFig1.pdf

   - Helper defines/methods for integer operations:

      inc/integers.h

   - A class to open a file with method to return either the handle for that stream 
     or std::cout:

      inc/stdoutfilestream.h

   - Common inline utilities for calls to GSL solver and minimizer routines:

      inc/gslhelper.h

   - Interface and implementation of a GSL minimizer:

      ps5/minimizer.h
      ps5/minimizer.cc

   - GSL minimization function for the spring kinetic energy function:

      ps5/springfunction.h

   - Driver function for the minimizer and solver code:

      ps5/springmodel.cc

   - GSL brents method solver code:

      ps5/solver.h
      ps5/solver.cc

   - Generate plots (Julia code):

      ps5/spring.jl
         -- model parameters for the non-linear kinetic energy function.

      ps5/csvplot.jl
         -- plot the spring energy function using springmodel output.
         
      ps5/vplotspring.jl

         -- plot the spring energy function using Julia code.  This generates:

            ps5/energyVsPositionFig1.pdf
            ps5/DeltaEnergyVsPositionFig1.pdf
            ps5/SignDeltaEnergyVsPositionFig1.pdf

      ps5/plotmassextension.jl

         -- plot the mass extension relation using output from springmodel:

            ps5/massextensionFig1.pdf
