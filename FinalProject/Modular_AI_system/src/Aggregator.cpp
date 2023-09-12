#include "Aggregator.h"

// combine all considerations and generate a sum
float Aggregator::evaluate() {
  float sum = 0.0f;
  for (auto consideration : m_considerations) {
    sum += consideration->evaluate(m_cover);
  }
  return sum;
}