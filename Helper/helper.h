#ifndef HEADACHE_HELPER_H
#define HEADACHE_HELPER_H

#include <stdlib.h>
namespace Helper {
static int NextRandom(int max) {
  return rand() % (max + 1);
}
static int NextRandom(int min, int max) {
  return rand() % (max + 1 - min) + min;
}
}

#endif //HEADACHE_HELPER_H
