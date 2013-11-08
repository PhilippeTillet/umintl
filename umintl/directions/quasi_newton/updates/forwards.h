/* ===========================
  Copyright (c) 2013 Philippe Tillet
  UMinTL - Unconstrained Minimization Template Library

  License : MIT X11 - See the LICENSE file in the root folder
 * ===========================*/

#ifndef UMINTL_DIRECTIONS_QUASI_NEWTON_FORWARDS_H
#define UMINTL_DIRECTIONS_QUASI_NEWTON_FORWARDS_H

#include "umintl/optimization_context.hpp"

namespace umintl{

template<class BackendType>
struct qn_update{
    virtual ~qn_update(){ }
    virtual void init(optimization_context<BackendType> &){ }
    virtual void clean(optimization_context<BackendType> &){ }
    virtual void operator()(optimization_context<BackendType> &) = 0;
};

}

#endif
