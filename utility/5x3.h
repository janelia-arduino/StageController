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
enum {STAGE_CHANNEL_COUNT_MAX=3};

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const double stage_positions_min_default[STAGE_CHANNEL_COUNT_MAX];

extern const double stage_positions_max_default[STAGE_CHANNEL_COUNT_MAX];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
