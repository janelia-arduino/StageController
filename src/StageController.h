// ----------------------------------------------------------------------------
// StageController.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STAGE_CONTROLLER_H
#define STAGE_CONTROLLER_H
#include <Flash.h>
#include <EEPROM.h>
#include <Streaming.h>
#include <ArduinoJson.h>
#include <JsonSanitizer.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <MemoryFree.h>
#include <ConstantVariable.h>
#include <SavedVariable.h>
#include <Functor.h>
#include <IndexedContainer.h>
#include <FunctorCallbacks.h>

#include <SPI.h>
#include <TMC429.h>
#include <TMC2130.h>

#include <ModularClient.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <StepDirController.h>
#include <StepperController.h>

#include "StageController/Constants.h"


class StageController : public StepperController
{
public:
  StageController();
  virtual void setup(bool use_drivers=true);
  virtual void update();

  typedef Array<long,step_dir_controller::constants::CHANNEL_COUNT_MAX> PositionArray;

  bool homeStage();
  bool stageHoming();
  bool stageHomed();

  bool moveStageTo(PositionArray absolute_stage_position);
  bool moveStageSoftlyTo(PositionArray absolute_stage_position);
  bool moveStageBy(PositionArray relative_stage_position);
  bool moveStageSoftlyBy(PositionArray relative_stage_position);

  PositionArray getStagePosition();
  PositionArray getStageTargetPosition();
  bool stageAtTargetPosition();

  long limitedStagePosition(const size_t channel,
                            const long absolute_stage_position);

protected:
  // Handlers
  void setChannelCountHandler();

private:
  modular_server::Property properties_[stage_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[stage_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[stage_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[stage_controller::constants::CALLBACK_COUNT_MAX];

  bool using_drivers_;
  bool stage_homing_;
  bool stage_homed_;

  PositionArray jsonArrayToPositionArray(ArduinoJson::JsonArray & json_array);

  // Handlers
  void homeStageHandler();
  void stageHomingHandler();
  void stageHomedHandler();
  void moveStageToHandler();
  void moveStageSoftlyToHandler();
  void moveStageByHandler();
  void moveStageSoftlyByHandler();
  void moveStageAtHandler();
  void getStagePositionHandler();
  void getStageTargetPositionHandler();
  void stageAtTargetPositionHandler();

};

#endif
