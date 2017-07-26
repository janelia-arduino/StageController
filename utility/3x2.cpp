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

const double stage_positions_min_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    -1E9,
    -1E9,
    -1E9,
  };

const double stage_positions_max_default[step_dir_controller::constants::CHANNEL_COUNT] =
  {
    1E9,
    1E9,
    1E9,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
