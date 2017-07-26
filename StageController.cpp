// ----------------------------------------------------------------------------
// StageController.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "StageController.h"


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

  // Variable Setup
  stage_homing_ = false;
  stage_homed_ = false;

  // Pin Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Interrupts

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);

  // Properties
  modular_server::Property & switch_active_polarity_property = modular_server_.property(step_dir_controller::constants::switch_active_polarity_property_name);
  switch_active_polarity_property.setDefaultValue(constants::switch_active_polarity_default);

  modular_server::Property & left_switch_stop_enabled_property = modular_server_.property(step_dir_controller::constants::left_switch_stop_enabled_property_name);
  left_switch_stop_enabled_property.setDefaultValue(constants::left_switch_stop_enabled_default);

  modular_server::Property & right_switches_enabled_property = modular_server_.property(step_dir_controller::constants::right_switches_enabled_property_name);
  right_switches_enabled_property.setDefaultValue(constants::right_switches_enabled_default);

  modular_server::Property & right_switch_stop_enabled_property = modular_server_.property(step_dir_controller::constants::right_switch_stop_enabled_property_name);
  right_switch_stop_enabled_property.setDefaultValue(constants::right_switch_stop_enabled_default);

  modular_server_.createProperty(constants::stage_positions_min_property_name,constants::stage_positions_min_default);

  modular_server_.createProperty(constants::stage_positions_max_property_name,constants::stage_positions_max_default);

  modular_server::Property & stage_channel_count_property = modular_server_.createProperty(constants::stage_channel_count_property_name,constants::stage_channel_count_default);
  stage_channel_count_property.setRange(constants::stage_channel_count_min,constants::stage_channel_count_max);
  stage_channel_count_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&StageController::setStageChannelCountHandler));

  // Parameters
  modular_server::Parameter & stage_positions_parameter = modular_server_.createParameter(constants::stage_positions_parameter_name);
  stage_positions_parameter.setTypeDouble();

  setStageChannelCountHandler();

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
  move_stage_to_function.addParameter(stage_positions_parameter);
  move_stage_to_function.setResultTypeBool();

  modular_server::Function & move_stage_softly_to_function = modular_server_.createFunction(constants::move_stage_softly_to_function_name);
  move_stage_softly_to_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StageController::moveStageSoftlyToHandler));
  move_stage_softly_to_function.addParameter(stage_positions_parameter);
  move_stage_softly_to_function.setResultTypeBool();

  modular_server::Function & get_stage_positions_function = modular_server_.createFunction(constants::get_stage_positions_function_name);
  get_stage_positions_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StageController::getStagePositionsHandler));
  get_stage_positions_function.setResultTypeArray();
  get_stage_positions_function.setResultTypeDouble();

  modular_server::Function & get_stage_target_positions_function = modular_server_.createFunction(constants::get_stage_target_positions_function_name);
  get_stage_target_positions_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StageController::getStageTargetPositionsHandler));
  get_stage_target_positions_function.setResultTypeArray();
  get_stage_target_positions_function.setResultTypeDouble();

  modular_server::Function & stage_at_target_positions_function = modular_server_.createFunction(constants::stage_at_target_positions_function_name);
  stage_at_target_positions_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StageController::stageAtTargetPositionsHandler));
  stage_at_target_positions_function.setResultTypeBool();

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

  long stage_channel_count;
  modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

  if (stage_homing_)
  {
    bool stage_homing = false;
    bool stage_homed = true;
    for (size_t channel=0; channel<(size_t)stage_channel_count; ++channel)
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

bool StageController::homeStage()
{
  reinitialize();

  long stage_channel_count;
  modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

  bool stage_homing = false;
  bool stage_homed = true;
  for (size_t channel=0; channel<(size_t)stage_channel_count; ++channel)
  {
    bool homing = home(channel);
    if (homing)
    {
      stage_homing = true;
      stage_homed = false;
    }
  }
  stage_homing_ = stage_homing;
  stage_homed_ = stage_homed;
  return stage_homing;
}

bool StageController::stageHoming()
{
  return stage_homing_;
}

bool StageController::stageHomed()
{
  return stage_homed_;
}

bool StageController::moveStageTo(PositionsArray absolute_positions)
{
  if (stage_homed_)
  {
    long stage_channel_count;
    modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

    double position;
    for (size_t channel=0; channel<(size_t)stage_channel_count; ++channel)
    {
      position = limitedPosition(channel,absolute_positions[channel]);
      moveTo(channel,position);
    }
  }
  else
  {
    return false;
  }
  return true;
}

bool StageController::moveStageSoftlyTo(PositionsArray absolute_positions)
{
  if (stage_homed_)
  {
    long stage_channel_count;
    modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

    double position;
    for (size_t channel=0; channel<(size_t)stage_channel_count; ++channel)
    {
      position = limitedPosition(channel,absolute_positions[channel]);
      moveSoftlyTo(channel,position);
    }
  }
  else
  {
    return false;
  }
  return true;
}

bool StageController::moveStageBy(PositionsArray relative_positions)
{
  if (stage_homed_)
  {
    long stage_channel_count;
    modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

    PositionsArray stage_positions = getStagePositions();

    double position;
    for (size_t channel=0; channel<(size_t)stage_channel_count; ++channel)
    {
      position = stage_positions[channel] + relative_positions[channel];
      position = limitedPosition(channel,position);
      moveTo(channel,position);
    }
  }
  else
  {
    return false;
  }
  return true;
}

bool StageController::moveStageSoftlyBy(PositionsArray relative_positions)
{
  if (stage_homed_)
  {
    long stage_channel_count;
    modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

    PositionsArray stage_positions = getStagePositions();

    double position;
    for (size_t channel=0; channel<(size_t)stage_channel_count; ++channel)
    {
      position = stage_positions[channel] + relative_positions[channel];
      position = limitedPosition(channel,position);
      moveSoftlyTo(channel,position);
    }
  }
  else
  {
    return false;
  }
  return true;
}

StageController::PositionsArray StageController::getStagePositions()
{
  long stage_channel_count;
  modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

  PositionsArray stage_positions;
  for (size_t channel=0; channel<(size_t)stage_channel_count; ++channel)
  {
    stage_positions.push_back(getPosition(channel));
  }
  return stage_positions;
}

StageController::PositionsArray StageController::getStageTargetPositions()
{
  long stage_channel_count;
  modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

  PositionsArray stage_positions;
  for (size_t channel=0; channel<(size_t)stage_channel_count; ++channel)
  {
    stage_positions.push_back(getTargetPosition(channel));
  }
  return stage_positions;
}

bool StageController::stageAtTargetPositions()
{

  long stage_channel_count;
  modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

  for (size_t channel=0; channel<(size_t)stage_channel_count; ++channel)
  {
    if (!atTargetPosition(channel))
    {
      return false;
    }
  }
  return true;
}

double StageController::limitedPosition(const size_t channel,
                                        const double position)
{
  double stage_position_min;
  modular_server_.property(constants::stage_positions_min_property_name).getElementValue(channel,stage_position_min);

  double stage_position_max;
  modular_server_.property(constants::stage_positions_max_property_name).getElementValue(channel,stage_position_max);

  double new_position = position;

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

StageController::PositionsArray StageController::jsonArrayToPositionsArray(ArduinoJson::JsonArray & json_array)
{
  long stage_channel_count;
  modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

  PositionsArray positions_array;

  size_t channel = 0;
  for (ArduinoJson::JsonArray::iterator positions_array_it=json_array.begin();
       positions_array_it != json_array.end();
       ++positions_array_it)
  {
    if (channel < (size_t)stage_channel_count)
    {
      double position = *positions_array_it;
      positions_array.push_back(position);
      ++channel;
    }
  }
  return positions_array;
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void StageController::setStageChannelCountHandler()
{
  long stage_channel_count;
  modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

  modular_server::Property & stage_positions_min_property = modular_server_.property(constants::stage_positions_min_property_name);
  stage_positions_min_property.setArrayLengthRange(stage_channel_count,stage_channel_count);

  modular_server::Property & stage_positions_max_property = modular_server_.property(constants::stage_positions_max_property_name);
  stage_positions_max_property.setArrayLengthRange(stage_channel_count,stage_channel_count);

  modular_server::Parameter & stage_positions_parameter = modular_server_.parameter(constants::stage_positions_parameter_name);
  stage_positions_parameter.setArrayLengthRange(stage_channel_count,stage_channel_count);
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
  long stage_channel_count;
  modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

  ArduinoJson::JsonArray * stage_positions_array_ptr;
  modular_server_.parameter(constants::stage_positions_parameter_name).getValue(stage_positions_array_ptr);

  PositionsArray stage_positions = jsonArrayToPositionsArray(*stage_positions_array_ptr);

  bool moving = moveStageTo(stage_positions);
  modular_server_.response().returnResult(moving);
}

void StageController::moveStageSoftlyToHandler()
{
  long stage_channel_count;
  modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

  ArduinoJson::JsonArray * stage_positions_array_ptr;
  modular_server_.parameter(constants::stage_positions_parameter_name).getValue(stage_positions_array_ptr);

  PositionsArray stage_positions = jsonArrayToPositionsArray(*stage_positions_array_ptr);

  bool moving = moveStageSoftlyTo(stage_positions);
  modular_server_.response().returnResult(moving);
}

void StageController::getStagePositionsHandler()
{
  long stage_channel_count;
  modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

  PositionsArray stage_positions = getStagePositions();

  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<stage_positions.size(); ++channel)
  {
    modular_server_.response().write(stage_positions[channel]);
  }
  modular_server_.response().endArray();
}

void StageController::getStageTargetPositionsHandler()
{
  long stage_channel_count;
  modular_server_.property(constants::stage_channel_count_property_name).getValue(stage_channel_count);

  PositionsArray target_positions = getStageTargetPositions();

  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<target_positions.size(); ++channel)
  {
    modular_server_.response().write(target_positions[channel]);
  }
  modular_server_.response().endArray();
}

void StageController::stageAtTargetPositionsHandler()
{
  bool stage_at_target_positions = stageAtTargetPositions();
  modular_server_.response().returnResult(stage_at_target_positions);
}
