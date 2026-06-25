#pragma once

#include "window.h"
#include "application.h"

class Engine {
public:
  int init();
  // We now pass the user's application into the run loop
  int run(Application *app);
  int cleanup();

private:
  WindowManager windowManager;
};
