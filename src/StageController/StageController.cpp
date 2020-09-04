// ----------------------------------------------------------------------------
// StageController.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "../StageController.h"


using namespace stage_controller;

StageController::StageController()
{
}

void StageController::setup(bool use_drivers)
{
  using_drivers_ = use_drivers;

  // Parent Setup
  if (using_drivers_)
  {
    StepperController::setup();
  }
  else
  {
    StepDirController::setup();
  }

  // Reset Watchdog
  resetWatchdog();

  // Variable Setup
  stage_homing_ = false;
  stage_homed_ = false;

  // Pin Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Pins

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & channel_count_property = modular_server_.property(step_dir_controller::constants::channel_count_property_name);
  channel_count_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&StageController::setChannelCountHandler));

  modular_server::Property & switch_active_polarity_property = modular_server_.property(step_dir_controller::constants::switch_active_polarity_property_name);
  switch_active_polarity_property.setDefaultValue(constants::switch_active_polarity_default);

  modular_server::Property & left_switch_stop_enabled_property = modular_server_.property(step_dir_controller::constants::left_switch_stop_enabled_property_name);
  left_switch_stop_enabled_property.setDefaultValue(constants::left_switch_stop_enabled_default);

  modular_server::Property & right_switches_enabled_property = modular_server_.property(step_dir_controller::constants::right_switches_enabled_property_name);
  right_switches_enabled_property.setDefaultValue(constants::right_switches_enabled_default);

  modular_server::Property & right_switch_stop_enabled_property = modular_server_.property(step_dir_controller::constants::right_switch_stop_enabled_property_name);
  right_switch_stop_enabled_property.setDefaultValue(constants::right_switch_stop_enabled_default);

  modular_server_.createProperty(constants::stage_position_min_property_name,constants::stage_position_min_default);

  modular_server_.createProperty(constants::stage_position_max_property_name,constants::stage_position_max_default);

  // Parameters
  modular_server::Parameter & stage_position_parameter = modular_server_.createParameter(constants::stage_position_parameter_name);
  stage_position_parameter.setTypeLong();

  setChannelCountHandler();

  // Functions
  modular_server::Function & home_stage_function = modular_server_.createFunction(constants::home_stage_function_name);
  home_stage_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StageController::homeStageHandler));
  home_stage_function.setResultTypeBool();

  modular_server::Function & stage_homing_function = modular_server_.createFunction(constants::stage_homing_function_name);
  stage_homing_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StageController::stageHomingHandler));
  stage_homing_function.setResultTypeBool();

  modular_server::Function & stage_homed_function = modular_server_.createFunction(constants::stage_homed_function_name);
  stage_homed_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StageController::stageHomedHandler));
  stage_homed_function.setResultTypeBool();

  modular_server::Function & move_stage_to_function = modular_server_.createFunction(constants::move_stage_to_function_name);
  move_stage_to_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StageController::moveStageToHandler));
  move_stage_to_function.addParameter(stage_position_parameter);
  move_stage_to_function.setResultTypeBool();

  modular_server::Function & move_stage_softly_to_function = modular_server_.createFunction(constants::move_stage_softly_to_function_name);
  move_stage_softly_to_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StageController::moveStageSoftlyToHandler));
  move_stage_softly_to_function.addParameter(stage_position_parameter);
  move_stage_softly_to_function.setResultTypeBool();

  modular_server::Function & get_stage_position_function = modular_server_.createFunction(constants::get_stage_position_function_name);
  get_stage_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StageController::getStagePositionHandler));
  get_stage_position_function.setResultTypeArray();
  get_stage_position_function.setResultTypeLong();

  modular_server::Function & get_stage_target_position_function = modular_server_.createFunction(constants::get_stage_target_position_function_name);
  get_stage_target_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StageController::getStageTargetPositionHandler));
  get_stage_target_position_function.setResultTypeArray();
  get_stage_target_position_function.setResultTypeLong();

  modular_server::Function & stage_at_target_position_function = modular_server_.createFunction(constants::stage_at_target_position_function_name);
  stage_at_target_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StageController::stageAtTargetPositionHandler));
  stage_at_target_position_function.setResultTypeBool();

  // Callbacks
}

void StageController::update()
{
  // Parent Update
  if (using_drivers_)
  {
    StepperController::update();
  }
  else
  {
    StepDirController::update();
  }

  if (stage_homing_)
  {
    bool stage_homing = false;
    bool stage_homed = true;
    for (size_t channel=0; channel<getChannelCount(); ++channel)
    {
      if (!homed(channel))
      {
        stage_homing = true;
        stage_homed = false;
      }
    }
    stage_homing_ = stage_homing;
    stage_homed_ = stage_homed;
  }
}

void StageController::reinitialize()
{
  if (using_drivers_)
  {
    StepperController::reinitialize();
  }
  else
  {
    StepDirController::reinitialize();
  }
}

size_t StageController::getChannelCount()
{
  if (using_drivers_)
  {
    return StepperController::getChannelCount();
  }
  else
  {
    return StepDirController::getChannelCount();
  }
}

bool StageController::home(size_t channel)
{
  bool homing = StepDirController::home(channel);
  if (homing)
  {
    stage_homing_ = true;
    stage_homed_ = false;
  }
  return homing;
}

bool StageController::homeStage()
{
  reinitialize();
  bool all_homed = true;
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    home(channel);
    if (!homed(channel))
    {
      all_homed = false;
    }
  }
  if (all_homed)
  {
    stage_homed_ = true;
  }
  return stage_homing_;
}

bool StageController::stageHoming()
{
  return stage_homing_;
}

bool StageController::stageHomed()
{
  return stage_homed_;
}

bool StageController::moveStageTo(PositionArray absolute_stage_position)
{
  if (stage_homed_)
  {
    long position;
    for (size_t channel=0; channel<getChannelCount(); ++channel)
    {
      position = limitedStagePosition(channel,absolute_stage_position[channel]);
      moveTo(channel,position);
    }
  }
  else
  {
    return false;
  }
  return true;
}

bool StageController::moveStageSoftlyTo(PositionArray absolute_stage_position)
{
  if (stage_homed_)
  {
    long position;
    for (size_t channel=0; channel<getChannelCount(); ++channel)
    {
      position = limitedStagePosition(channel,absolute_stage_position[channel]);
      moveSoftlyTo(channel,position);
    }
  }
  else
  {
    return false;
  }
  return true;
}

bool StageController::moveStageBy(PositionArray relative_stage_position)
{
  if (stage_homed_)
  {
    PositionArray stage_position = getStagePosition();

    long position;
    for (size_t channel=0; channel<getChannelCount(); ++channel)
    {
      position = stage_position[channel] + relative_stage_position[channel];
      position = limitedStagePosition(channel,position);
      moveTo(channel,position);
    }
  }
  else
  {
    return false;
  }
  return true;
}

bool StageController::moveStageSoftlyBy(PositionArray relative_stage_position)
{
  if (stage_homed_)
  {
    PositionArray stage_position = getStagePosition();

    long position;
    for (size_t channel=0; channel<getChannelCount(); ++channel)
    {
      position = stage_position[channel] + relative_stage_position[channel];
      position = limitedStagePosition(channel,position);
      moveSoftlyTo(channel,position);
    }
  }
  else
  {
    return false;
  }
  return true;
}

StageController::PositionArray StageController::getStagePosition()
{
  PositionArray stage_position;
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    stage_position.push_back(getPosition(channel));
  }
  return stage_position;
}

StageController::PositionArray StageController::getStageTargetPosition()
{
  PositionArray stage_position;
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    stage_position.push_back(getTargetPosition(channel));
  }
  return stage_position;
}

bool StageController::stageAtTargetPosition()
{

  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    if (!atTargetPosition(channel))
    {
      return false;
    }
  }
  return true;
}

long StageController::limitedStagePosition(size_t channel,
  long absolute_stage_position)
{
  long stage_position_min;
  modular_server_.property(constants::stage_position_min_property_name).getElementValue(channel,stage_position_min);

  long stage_position_max;
  modular_server_.property(constants::stage_position_max_property_name).getElementValue(channel,stage_position_max);

  long new_position = absolute_stage_position;

  if (new_position < stage_position_min)
  {
    new_position = stage_position_min;
  }
  else if (new_position > stage_position_max)
  {
    new_position = stage_position_max;
  }
  return new_position;
}

StageController::PositionArray StageController::jsonArrayToPositionArray(ArduinoJson::JsonArray json_array)
{
  PositionArray position_array;

  size_t channel = 0;
  for (long position : json_array)
  {
    if (channel < getChannelCount())
    {
      position_array.push_back(position);
      ++channel;
    }
  }
  return position_array;
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray
// ArduinoJson::JsonObject
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void StageController::setChannelCountHandler()
{
  if (using_drivers_)
  {
    StepperController::setChannelCountHandler();
  }
  else
  {
    StepDirController::setChannelCountHandler();
  }

  size_t channel_count = getChannelCount();

  modular_server::Property & stage_position_min_property = modular_server_.property(constants::stage_position_min_property_name);
  stage_position_min_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & stage_position_max_property = modular_server_.property(constants::stage_position_max_property_name);
  stage_position_max_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Parameter & stage_position_parameter = modular_server_.parameter(constants::stage_position_parameter_name);
  stage_position_parameter.setArrayLengthRange(channel_count,channel_count);
}

void StageController::homeStageHandler()
{
  bool homing = homeStage();
  modular_server_.response().returnResult(homing);
}

void StageController::stageHomingHandler()
{
  bool homing = stageHoming();
  modular_server_.response().returnResult(homing);
}

void StageController::stageHomedHandler()
{
  bool homed = stageHomed();
  modular_server_.response().returnResult(homed);
}

void StageController::moveStageToHandler()
{
  ArduinoJson::JsonArray stage_position_array;
  modular_server_.parameter(constants::stage_position_parameter_name).getValue(stage_position_array);

  PositionArray stage_position = jsonArrayToPositionArray(stage_position_array);

  bool moving = moveStageTo(stage_position);
  modular_server_.response().returnResult(moving);
}

void StageController::moveStageSoftlyToHandler()
{
  ArduinoJson::JsonArray stage_position_array;
  modular_server_.parameter(constants::stage_position_parameter_name).getValue(stage_position_array);

  PositionArray stage_position = jsonArrayToPositionArray(stage_position_array);

  bool moving = moveStageSoftlyTo(stage_position);
  modular_server_.response().returnResult(moving);
}

void StageController::getStagePositionHandler()
{
  PositionArray stage_position = getStagePosition();

  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<stage_position.size(); ++channel)
  {
    modular_server_.response().write(stage_position[channel]);
  }
  modular_server_.response().endArray();
}

void StageController::getStageTargetPositionHandler()
{
  PositionArray target_position = getStageTargetPosition();

  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<target_position.size(); ++channel)
  {
    modular_server_.response().write(target_position[channel]);
  }
  modular_server_.response().endArray();
}

void StageController::stageAtTargetPositionHandler()
{
  bool stage_at_target_position = stageAtTargetPosition();
  modular_server_.response().returnResult(stage_at_target_position);
}
