#include "engine.h"

int main() {
  Engine engine;

  if (engine.init() != 0) {
    return 1;
  }

  if (engine.run() != 0) {
    return 2;
  }

  return engine.cleanup();
}
