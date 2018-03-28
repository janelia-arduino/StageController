#include <StageController.h>


StageController dev;

void setup()
{
  const bool use_drivers = false;
  dev.setup(use_drivers);
  dev.startServer();
}

void loop()
{
  dev.update();
}
