// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace stage_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"stage_controller");

CONSTANT_STRING(firmware_name,"StageController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=3,
  .version_minor=0,
  .version_patch=0,
};

// Pins

// Units

// Properties
const ConstantString * const switch_active_polarity_element_default = &step_dir_controller::constants::polarity_high;

const bool left_switch_stop_enabled_element_default = true;

const bool right_switches_enabled_element_default = true;

const bool right_switch_stop_enabled_element_default = true;

CONSTANT_STRING(stage_position_min_property_name,"stagePositionMin");
const long stage_position_min_element_default = -1000000000;

CONSTANT_STRING(stage_position_max_property_name,"stagePositionMax");
const long stage_position_max_element_default = 1000000000;

// Parameters
CONSTANT_STRING(stage_position_parameter_name,"stage_position");

// Functions
CONSTANT_STRING(home_stage_function_name,"homeStage");
CONSTANT_STRING(stage_homing_function_name,"stageHoming");
CONSTANT_STRING(stage_homed_function_name,"stageHomed");
CONSTANT_STRING(move_stage_to_function_name,"moveStageTo");
CONSTANT_STRING(move_stage_softly_to_function_name,"moveStageSoftlyTo");
CONSTANT_STRING(move_stage_by_function_name,"moveStageBy");
CONSTANT_STRING(move_stage_softly_by_function_name,"moveStageSoftlyBy");
CONSTANT_STRING(move_stage_at_function_name,"moveStageAt");
CONSTANT_STRING(get_stage_position_function_name,"getStagePosition");
CONSTANT_STRING(get_stage_target_position_function_name,"getStageTargetPosition");
CONSTANT_STRING(stage_at_target_position_function_name,"stageAtTargetPosition");

// Callbacks

// Errors
}
}
