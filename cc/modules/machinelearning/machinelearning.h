#include <nan.h>
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include "macros.h"

#ifndef __FF_MACHINELEARNING_H__
#define __FF_MACHINELEARNING_H__

class MachineLearning {
public:
  static NAN_MODULE_INIT(Init);
};

#endif