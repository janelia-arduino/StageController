// ----------------------------------------------------------------------------
// 3x2.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "3x2.h"


#if defined(__MK20DX256__)

namespace stage_controller
{
namespace constants
{

// Interrupts

// Units

// Properties
const bool left_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT_MAX] =
  {
   true,
   true,
   true,
  };

const bool right_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT_MAX] =
  {
   true,
   true,
   true,
  };

const long stage_position_min_default[step_dir_controller::constants::CHANNEL_COUNT_MAX] =
  {
   -1000000000,
   -1000000000,
   -1000000000,
  };

const long stage_position_max_default[step_dir_controller::constants::CHANNEL_COUNT_MAX] =
  {
   1000000000,
   1000000000,
   1000000000,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
