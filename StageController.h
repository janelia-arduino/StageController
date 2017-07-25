// ----------------------------------------------------------------------------
// StageController.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STAGE_CONTROLLER_H
#define STAGE_CONTROLLER_H
#include "Flash.h"
#include <EEPROM.h>
#include "Streaming.h"
#include "ArduinoJson.h"
#include "JsonSanitizer.h"
#include "JsonStream.h"
#include "Array.h"
#include "Vector.h"
#include "MemoryFree.h"
#include "ConstantVariable.h"
#include "SavedVariable.h"
#include "Functor.h"
#include "IndexedContainer.h"
#include "FunctorCallbacks.h"

#include "SPI.h"
#include "TMC429.h"
#include "TMC2130.h"

#include "ModularClient.h"

#include "ModularServer.h"
#include "ModularDeviceBase.h"
#include "StepDirController.h"
#include "StepperController.h"

#include "utility/Constants.h"


class StageController : public StepperController
{
public:
  StageController();
  virtual void setup(bool use_drivers=true);
  virtual void update();

  typedef Array<double,step_dir_controller::constants::CHANNEL_COUNT> PositionsArray;

  bool homeStage();
  bool stageHoming();
  bool stageHomed();

  bool moveStageTo(PositionsArray absolute_positions);
  bool moveStageSoftlyTo(PositionsArray absolute_positions);
  bool moveStageBy(PositionsArray relative_positions);
  bool moveStageSoftlyBy(PositionsArray relative_positions);

  PositionsArray getStagePositions();
  PositionsArray getStageTargetPositions();
  bool stageAtTargetPositions();

  double limitedPosition(const size_t channel,
                         const double position);

private:
  modular_server::Property properties_[stage_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[stage_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[stage_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[stage_controller::constants::CALLBACK_COUNT_MAX];

  bool using_drivers_;
  bool stage_homing_;
  bool stage_homed_;

  PositionsArray jsonArrayToPositionsArray(ArduinoJson::JsonArray & json_array);

  // Handlers
  void setStageChannelCountHandler();
  void homeStageHandler();
  void stageHomingHandler();
  void stageHomedHandler();
  void moveStageToHandler();
  void moveStageSoftlyToHandler();
  void moveStageByHandler();
  void moveStageSoftlyByHandler();
  void moveStageAtHandler();
  void getStagePositionsHandler();
  void getStageTargetPositionsHandler();
  void stageAtTargetPositionsHandler();

};

#endif
