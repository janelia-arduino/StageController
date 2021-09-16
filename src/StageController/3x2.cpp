// ----------------------------------------------------------------------------
// 3x2.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "3x2.h"


#if defined(__MK20DX256__)

namespace stage_controller
{
namespace constants
{

// Pins

// Units

// Properties
const ConstantString * const switch_active_polarity_default[step_dir_controller::constants::CONTROLLER_COUNT_MAX] =
{
  switch_active_polarity_element_default,
};

const bool left_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT_MAX] =
{
  left_switch_stop_enabled_element_default,
  left_switch_stop_enabled_element_default,
  left_switch_stop_enabled_element_default,
};

const bool right_switches_enabled_default[step_dir_controller::constants::CONTROLLER_COUNT_MAX] =
{
  right_switches_enabled_element_default,
};

const bool right_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT_MAX] =
{
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
};

const long stage_position_min_default[step_dir_controller::constants::CHANNEL_COUNT_MAX] =
{
  stage_position_min_element_default,
  stage_position_min_element_default,
  stage_position_min_element_default,
};

const long stage_position_max_default[step_dir_controller::constants::CHANNEL_COUNT_MAX] =
{
  stage_position_max_element_default,
  stage_position_max_element_default,
  stage_position_max_element_default,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
