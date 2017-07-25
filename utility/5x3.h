// ----------------------------------------------------------------------------
// 5x3.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STAGE_CONTROLLER_5X3_CONSTANTS_H
#define STAGE_CONTROLLER_5X3_CONSTANTS_H
#include "Constants.h"


#if defined(__MK64FX512__)

namespace stage_controller
{
namespace constants
{

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const double stage_positions_min_default[step_dir_controller::constants::CHANNEL_COUNT];

extern const double stage_positions_max_default[step_dir_controller::constants::CHANNEL_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
