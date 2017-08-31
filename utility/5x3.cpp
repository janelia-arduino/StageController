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
// Interrupts

// Units

// Properties
const bool left_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
   true,
   true,
   true,
  };

const bool right_switch_stop_enabled_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
   true,
   true,
   true,
  };

const long stage_position_min_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
   -1000000000,
   -1000000000,
   -1000000000,
  };

const long stage_position_max_default[step_dir_controller::constants::CHANNEL_COUNT] =
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
