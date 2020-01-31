// simple random number generator
// create a random value between l and r

#ifndef _RAND_HPP
#define _RAND_HPP

#include <random>

namespace ams562 {
class RandGen {
 public:
  RandGen(double l = -1.0, double r = 1.0)
      : _rng(std::random_device()()), _dist(l, r) {}

  // generate values
  double generate() { return _dist(_rng); }

 private:
  // engine
  std::mt19937 _rng;
  // uniform distributed
  std::uniform_real_distribution<> _dist;
};
}  // namespace ams562

#endif