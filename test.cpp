#include <assert.h>
#include <iostream>
#include "math.h"
#include "signal.h"
#include <vector>

void testSignalVoid()
{
  Signal<void ()> sig;
  auto id = sig.connect([]() { assert(true); });
  sig();
  sig.emit();
  sig.disconnect(id);
  sig.clear();
}

void testSignalValue()
{
  Signal<int (int)> sig;
  auto id1 = sig.connect([](int x) { return x + x; });
  auto id2 = sig.connect([](int x) { return x * x; });
  auto id3 = sig.connect([](int x) { return pow(x, x); });
  auto op = [](std::vector<int> lhs, int rhs)->std::vector<int>
  {
    lhs.push_back(rhs);
    return lhs;
  };
  auto vals = sig.emit<std::vector<int>>(op, 3);
  assert(vals[0] == 6);
  assert(vals[1] == 9);
  assert(vals[2] == 27);
  sig.clear();
}

int main()
{
  testSignalVoid();
  testSignalValue();
  return 0;
}
