// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__MK64FX512__)

namespace stage_controller
{
namespace constants
{
// Pins

// Units

// Properties
const bool left_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT_MAX] =
{
  left_switch_stop_enabled_element_default,
  left_switch_stop_enabled_element_default,
  left_switch_stop_enabled_element_default,
  left_switch_stop_enabled_element_default,
  left_switch_stop_enabled_element_default,
  left_switch_stop_enabled_element_default,
};

const bool right_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT_MAX] =
{
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
};

const long stage_position_min_default[step_dir_controller::constants::CHANNEL_COUNT_MAX] =
{
  stage_position_min_element_default,
  stage_position_min_element_default,
  stage_position_min_element_default,
  stage_position_min_element_default,
  stage_position_min_element_default,
  stage_position_min_element_default,
};

const long stage_position_max_default[step_dir_controller::constants::CHANNEL_COUNT_MAX] =
{
  stage_position_max_element_default,
  stage_position_max_element_default,
  stage_position_max_element_default,
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
