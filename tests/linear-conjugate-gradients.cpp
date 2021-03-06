/* ===========================
  Copyright (c) 2013 Philippe Tillet
  UMinTL - Unconstrained Minimization Template Library

  License : MIT X11 - See the LICENSE file in the root folder
 * ===========================*/

#include <cstdlib>
#include <iostream>

#include "umintl/backends/cblas.hpp"
#include "umintl/linear/conjugate_gradient.hpp"


typedef double ScalarType;
typedef umintl::backend::cblas_types<ScalarType> BackendType;

int main(){
  std::size_t N = 142;
  ScalarType * b = new ScalarType[N];
  ScalarType * x = new ScalarType[N];
  ScalarType * x0 = new ScalarType[N];
  ScalarType * sqrtA = new ScalarType[N*N];
  ScalarType * A = new ScalarType[N*N];

  for(std::size_t i = 0 ; i < N ; ++i)
    x0[i] = 0;
  for(std::size_t i = 0 ; i < N ; ++i)
    b[i] = 1;
  for(std::size_t i = 0 ; i < N*N ; ++i)
    sqrtA[i] = (ScalarType)rand()/RAND_MAX;
  for(std::size_t i = 0 ; i < N*N ; ++i)
    A[i] = 0;

  for(std::size_t i = 0 ; i < N ; ++i)
    for(std::size_t j = 0 ; j < N ; ++j)
      for(std::size_t k = 0 ; k < N ; ++k)
        A[i*N+j]+=sqrtA[i*N+k]*sqrtA[j*N+k];

  umintl::linear::conjugate_gradient<BackendType> conjugate_gradient(1000, new umintl::linear::conjugate_gradient_detail::symv<BackendType>(A));
  umintl::linear::conjugate_gradient<BackendType>::optimization_result res = conjugate_gradient(N,x0,b,x);

  if(res.ret==umintl::linear::conjugate_gradient<BackendType>::SUCCESS)
    return EXIT_SUCCESS;

  return EXIT_FAILURE;

}
