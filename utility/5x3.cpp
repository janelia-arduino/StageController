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
const double stage_positions_min_default[STAGE_CHANNEL_COUNT_MAX] =
  {
    -1E9,
    -1E9,
    -1E9,
  };

const double stage_positions_max_default[STAGE_CHANNEL_COUNT_MAX] =
  {
    1E9,
    1E9,
    1E9,
  };

const long stage_channel_count_default = STAGE_CHANNEL_COUNT_MAX;

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
