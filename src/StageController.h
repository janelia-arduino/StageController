// ----------------------------------------------------------------------------
// StageController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef STAGE_CONTROLLER_H
#define STAGE_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

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

  virtual void reinitialize();

  virtual size_t getChannelCount();

  typedef Array<long,step_dir_controller::constants::CHANNEL_COUNT_MAX> PositionArray;

  virtual bool home(size_t channel);
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

  long limitedStagePosition(size_t channel,
    long absolute_stage_position);

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
