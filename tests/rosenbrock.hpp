#ifndef FMINCL_ROSENBROCK_HPP_
#define FMINCL_ROSENBROCK_HPP_

#include "Eigen/Dense"

template<class ScalarType>
class rosenbrock{
    typedef Eigen::Matrix< ScalarType, Eigen::Dynamic, 1 > VectorType;
public:
    ScalarType operator()(VectorType const & x, VectorType * grad) const {
        ScalarType res=0;
        unsigned int dim = x.size();
        VectorType const & x_cpu = x;
        for(unsigned int i=0 ; i<dim-1;++i){
            res = res + 100*(pow(x_cpu[i+1] - x_cpu[i]*x_cpu[i],2)) + pow(1 - x_cpu[i],2);
        }
        if(grad){
            VectorType & grad_cpu = *grad;
            grad_cpu[0] = -400*x_cpu[0]*(x_cpu[1] - pow(x_cpu[0],2)) - 2*(1 - x_cpu[0]);
            for(unsigned int i=1 ; i<dim-1 ; ++i){
                double xi = x_cpu[i];
                double xim1 = x_cpu[i-1];
                double xip1 = x_cpu[i+1];
                grad_cpu[i] = 200*(xi - xim1*xim1) - 400*xi*(xip1-xi*xi) - 2*(1 - xi);
            }
            grad_cpu[dim-1] = 200*(x_cpu[dim-1]-x_cpu[dim-2]*x_cpu[dim-2]);
        }
        return res;
    }
};

#endif