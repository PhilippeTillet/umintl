/* ===========================
 *
 * Copyright (c) 2013 Philippe Tillet - National Chiao Tung University
 *
 * FMinCL - Unconstrained Function Minimization on OpenCL
 *
 * License : MIT X11 - See the LICENSE file in the root folder
 * ===========================*/


#ifndef FMINCL_STOPPING_CRITERION_HPP_
#define FMINCL_STOPPING_CRITERION_HPP_

#include <cmath>

#include "fmincl/mapping.hpp"

namespace fmincl{

struct stopping_criterion_tag{ virtual ~stopping_criterion_tag(){ } };
template<class BackendType>
struct stopping_criterion_implementation{
    virtual bool operator()(detail::state<BackendType> & state) = 0;
};

struct gradient_based_stopping_tag : public stopping_criterion_tag{
    gradient_based_stopping_tag(double _tolerance = 1e-5) : tolerance(_tolerance){ }
    double tolerance;
};
template<class BackendType>
struct gradient_based_stopping_implementation : public stopping_criterion_implementation<BackendType>{
    gradient_based_stopping_implementation(gradient_based_stopping_tag const & _tag) : tag(_tag){ }
    bool operator()(detail::state<BackendType> & state){
        return BackendType::norm_2(state.g()) < static_cast<typename BackendType::ScalarType>(tag.tolerance);
    }
private:
    gradient_based_stopping_tag const & tag;
};


struct value_based_stopping_tag : public stopping_criterion_tag{
    value_based_stopping_tag(double _tolerance = 1e-5) : tolerance(_tolerance){ }
    double tolerance;
};
template<class BackendType>
struct value_based_stopping_implementation : public stopping_criterion_implementation<BackendType>{
    value_based_stopping_implementation(value_based_stopping_tag const & _tag) : tag(_tag){ }
    bool operator()(detail::state<BackendType> & state){
        return std::fabs(state.val() - state.valm1()) < static_cast<typename BackendType::ScalarType>(tag.tolerance);
    }
private:
    value_based_stopping_tag const & tag;
};


template<class BackendType>
struct stopping_criterion_mapping{
    typedef implementation_from_tag<typename make_typelist<FMINCL_CREATE_MAPPING(gradient_based_stopping),FMINCL_CREATE_MAPPING(value_based_stopping)>::type
                                   ,stopping_criterion_tag, stopping_criterion_implementation<BackendType> > type;
};


}

#endif