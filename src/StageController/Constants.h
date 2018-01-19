// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STAGE_CONTROLLER_CONSTANTS_H
#define STAGE_CONTROLLER_CONSTANTS_H
#include <ConstantVariable.h>
#include <StepDirController.h>
#include <StepperController.h>


namespace stage_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=2};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=11};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const ConstantString * const switch_active_polarity_default;

extern const bool left_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT_MAX];
extern const bool left_switch_stop_enabled_element_default;

extern const bool right_switches_enabled_default;

extern const bool right_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT_MAX];
extern const bool right_switch_stop_enabled_element_default;

extern ConstantString stage_position_min_property_name;
extern const long stage_position_min_default[step_dir_controller::constants::CHANNEL_COUNT_MAX];
extern const long stage_position_min_element_default;

extern ConstantString stage_position_max_property_name;
extern const long stage_position_max_default[step_dir_controller::constants::CHANNEL_COUNT_MAX];
extern const long stage_position_max_element_default;

// Parameters
extern ConstantString stage_position_parameter_name;

// Functions
extern ConstantString home_stage_function_name;
extern ConstantString stage_homing_function_name;
extern ConstantString stage_homed_function_name;
extern ConstantString move_stage_to_function_name;
extern ConstantString move_stage_softly_to_function_name;
extern ConstantString move_stage_by_function_name;
extern ConstantString move_stage_softly_by_function_name;
extern ConstantString move_stage_at_function_name;
extern ConstantString get_stage_position_function_name;
extern ConstantString get_stage_target_position_function_name;
extern ConstantString stage_at_target_position_function_name;

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
