/* ===========================
 *
 * Copyright (c) 2013 Philippe Tillet - National Chiao Tung University
 *
 * FMinCL - Unconstrained Function Minimization on OpenCL
 *
 * License : MIT X11 - See the LICENSE file in the root folder
 * ===========================*/

#include <cstdlib>
#include "fmincl/backend.hpp"
#include "fmincl/minimize.hpp"
#include "obj_fun.hpp"

typedef double NumericT;
static const int dim = 10;

int main(){
    rosenbrock<NumericT> fun;
    srand(time(NULL));
    fmincl::backend::VECTOR_TYPE X0(dim);
    for(unsigned int i = 0 ; i < dim ; ++i) X0(i) = 0.01*(double)rand()/RAND_MAX;
    //fmincl::check_grad(fun,X0);

    fmincl::optimization_options options;

//    options.direction = fmincl::cg<fmincl::polak_ribiere, fmincl::no_restart>();
//    options.line_search = fmincl::strong_wolfe_powell(1e-3,0.1);
    options.direction = fmincl::quasi_newton<fmincl::bfgs>();
    options.line_search = fmincl::strong_wolfe_powell(1e-4,0.9);

    options.max_iter = 100;
    options.verbosity_level = 2;

    fmincl::backend::VECTOR_TYPE X =  fmincl::minimize(fun,X0, options);

    //std::cout << "Minimum : " << X << std::endl;
}
