// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
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
    .version_major=1,
    .version_minor=0,
    .version_patch=0,
  };

// Interrupts

// Units

// Properties
CONSTANT_STRING(stage_positions_min_property_name,"stagePositionMin");

CONSTANT_STRING(stage_positions_max_property_name,"stagePositionMax");

CONSTANT_STRING(stage_channel_count_property_name,"stageChannelCount");
const long stage_channel_count_min = 1;
const long stage_channel_count_max = step_dir_controller::constants::CHANNEL_COUNT;
const long stage_channel_count_default = step_dir_controller::constants::CHANNEL_COUNT;

// Parameters
CONSTANT_STRING(stage_positions_parameter_name,"stage_positions");

// Functions
CONSTANT_STRING(home_stage_function_name,"homeStage");
CONSTANT_STRING(stage_homing_function_name,"stageHoming");
CONSTANT_STRING(stage_homed_function_name,"stageHomed");
CONSTANT_STRING(move_stage_to_function_name,"moveStageTo");
CONSTANT_STRING(move_stage_softly_to_function_name,"moveStageSoftlyTo");
CONSTANT_STRING(move_stage_by_function_name,"moveStageBy");
CONSTANT_STRING(move_stage_softly_by_function_name,"moveStageSoftlyBy");
CONSTANT_STRING(move_stage_at_function_name,"moveStageAt");
CONSTANT_STRING(get_stage_positions_function_name,"getStagePositions");
CONSTANT_STRING(get_stage_target_positions_function_name,"getStageTargetPositions");
CONSTANT_STRING(stage_at_target_positions_function_name,"stageAtTargetPositions");

// Callbacks

// Errors
}
}
