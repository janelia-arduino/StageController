#include <StageController.h>


StageController dev;

void setup()
{
  const bool use_drivers = true;
  dev.setup(use_drivers);
  dev.startServer();
}

void loop()
{
  dev.update();
}
