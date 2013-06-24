{% import 'functional.cpp' as functional %}
/*
 * file:   {{fun.name}}.cpp
 * author: A trusty code generator
 * date:   {{time.strftime("%a, %d %b %Y %H:%M:%S", time.localtime())}}
 * 
 * This file was autogenerated, do not modify.
 * See LICENCE for full modification and redistribution details.
 * Copyright {{time.strftime("%Y", time.localtime())}} The OpenCV Foundation
 */
#include "mex.h"
#include "bridge.hpp"
#include <string>
#include <vector>
#include <cassert>
#include <exception>
#include <opencv2/{{includes}}.hpp>
using namespace cv;

/* 
 * {{ fun.name }}
 * {{ fun }}
 * Gateway routine
 *   nlhs - number of return arguments
 *   plhs - pointers to return arguments
 *   nrhs - number of input arguments
 *   prhs - pointers to input arguments
 */
void mexFunction(int nlhs, mxArray* plhs[],
                 int nrhs, const mxArray* prhs[]) {

  // assertions
  conditionalError(nrhs >= {{fun.req|length - fun.req|only|outputs|length}}, "Too few required input arguments specified");
  conditionalError(nrhs <= {{fun.req|length + fun.opt|length - fun.req|only|outputs|length - fun.opt|only|outputs|length}}, "Too many input arguments specified");
  conditionalError(nlhs <= {{ fun.rtp|void|not + fun.req|outputs|length + fun.opt|outputs|length}}, "Too many output arguments specified");

  // setup
  std::vector<Bridge> inputs(plhs, plhs+nrhs);
  {% set noutputs = fun.rtp|void|not + fun.req|outputs|length + fun.opt|outputs|length %}
  {%- if noutputs %}
  std::vector<Bridge> outputs({{noutputs}});
  {% endif %}

  {{ functional.generate(fun) }}

  {%- if noutputs %}
  // push the outputs back to matlab
  for (size_t n = 0; n < nlhs; ++n) {
    plhs[n] = outputs[n].toMxArray();
  }
  {% endif %}
}
