#include "utils.h"

float ClampFloat(float value, float min, float max) {
  const float res = value < min ? min : value;
  return res > max ? max : res;
}
