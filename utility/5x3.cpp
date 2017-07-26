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
