/*
  grbl.h - main Grbl include file
  Part of Grbl

  Copyright (c) 2015-2016 Sungeun K. Jeon for Gnea Research LLC

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.

    reworked for Maslow-Due (Arduino Due) by Larry D O'Cull  Mar 2019
*/

#ifndef grbl_h
#define grbl_h

// Grbl versioning system
#define GRBL_VERSION "1.1g"


// Enable Maslow CNC kinematics. Use ONLY with Maslow machines.
// NOTE: This configuration option alters the motion of the X and Y axes to principle of operation
// defined at (https://en.wikipedia.org/wiki/Maslow_CNC). Motors are assumed to positioned and wired exactly as
// described, if not, motions may move in strange directions. Grbl requires the Maslow LEFT and RIGHT motors
// have the same steps per mm internally.
#define MASLOWCNC // Default disabled. Uncomment to enable.

#ifdef MASLOWCNC
  #define GRBL_VERSION_BUILD "20200915.MaslowDue"
  #include "Arduino.h"

  // Matches Maslow Classic:
  #define GRBL_CHAIN_ELONGATION_FACTOR          45
  #define GRBL_SLED_WEIGHT                      46

  #define GRBL_CHAIN_OVER_SPROCKET              80
  #define GRBL_MACHINE_WIDTH                    81
  #define GRBL_MACHINE_HEIGHT                   82
  #define GRBL_DIST_BETWEEN_MOTORS              83
  #define GRBL_MOTOR_OFFSET_Y                   84
  #define GRBL_X_CORR_SCALING                   85
  #define GRBL_Y_CORR_SCALING                   86
  #define GRBL_CHAIN_SAG_CORRECTION             87
  #define GRBL_LEFT_CHAIN_TOLERANCE             88
  #define GRBL_RIGHT_CHAIN_TOLERANCE            89
  #define GRBL_ROTATION_DISK_RADIUS             90
  #define GRBL_CHAIN_LENGTH                     91
  #define GRBL_Z_TRAVEL_MIN                     92
  #define GRBL_KINEMATICS_SIMPLE                93
  #define GRBL_HOME_CHAIN_LENGTHS               94
#else
  #define GRBL_VERSION_BUILD "20180813.Mega"
  #include <avr/io.h>
  #include <avr/pgmspace.h>
  #include <avr/interrupt.h>
  #include <avr/wdt.h>
  #include <util/delay.h>
#endif

// Define standard libraries used by Grbl.
#include <cstdint>
#include <math.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Define the Grbl system include files. NOTE: Do not alter organization.
#include "config.h"
#include "nuts_bolts.h"
#include "settings.h"
#include "system.h"
#include "defaults.h"
#include "cpu_map.h"
#include "planner.h"
#include "coolant_control.h"
#include "eeprom.h"
#include "gcode.h"
#include "limits.h"
#include "motion_control.h"
#include "planner.h"
#include "print.h"
#include "probe.h"
#include "protocol.h"
#include "report.h"
#include "serial.h"
#include "spindle_control.h"
#include "stepper.h"
#include "jog.h"
#include "sleep.h"

// ---------------------------------------------------------------------------------------
// COMPILE-TIME ERROR CHECKING OF DEFINE VALUES:

#ifndef HOMING_CYCLE_0
  #error "Required HOMING_CYCLE_0 not defined."
#endif

#if defined(PARKING_ENABLE)
  #if defined(HOMING_FORCE_SET_ORIGIN)
    #error "HOMING_FORCE_SET_ORIGIN is not supported with PARKING_ENABLE at this time."
  #endif
#endif

#if defined(ENABLE_PARKING_OVERRIDE_CONTROL)
  #if !defined(PARKING_ENABLE)
    #error "ENABLE_PARKING_OVERRIDE_CONTROL must be enabled with PARKING_ENABLE."
  #endif
#endif

#if defined(SPINDLE_PWM_MIN_VALUE)
  #if !(SPINDLE_PWM_MIN_VALUE > 0)
    #error "SPINDLE_PWM_MIN_VALUE must be greater than zero."
  #endif
#endif

#if (REPORT_WCO_REFRESH_BUSY_COUNT < REPORT_WCO_REFRESH_IDLE_COUNT)
  #error "WCO busy refresh is less than idle refresh."
#endif
#if (REPORT_OVR_REFRESH_BUSY_COUNT < REPORT_OVR_REFRESH_IDLE_COUNT)
  #error "Override busy refresh is less than idle refresh."
#endif
#if (REPORT_WCO_REFRESH_IDLE_COUNT < 2)
  #error "WCO refresh must be greater than one."
#endif
#if (REPORT_OVR_REFRESH_IDLE_COUNT < 1)
  #error "Override refresh must be greater than zero."
#endif

// ---------------------------------------------------------------------------------------

#endif
