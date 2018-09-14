/*
  PinMap.h
*/
#ifndef PIN_MAP_H_INCLUDED
#define PIN_MAP_INCLUDED

#include "main.h"

// GPIO Pins
// Step Pins
#define GPIO_STEP_X_PORT		      X_STP_GPIO_Port
#define GPIO_STEP_Y_PORT		      Y_STP_GPIO_Port
#define GPIO_STEP_Z_PORT		      Z_STP_GPIO_Port
#define GPIO_STEP_X_PIN			      X_STP_Pin
#define GPIO_STEP_Y_PIN			      Y_STP_Pin
#define GPIO_STEP_Z_PIN			      X_STP_Pin

// Direction Pins
#define GPIO_DIR_X_PORT			      X_DIR_GPIO_Port
#define GPIO_DIR_Y_PORT			      Y_DIR_GPIO_Port
#define GPIO_DIR_Z_PORT			      Z_DIR_GPIO_Port
#define GPIO_DIR_X_PIN			      X_DIR_Pin
#define GPIO_DIR_Y_PIN		  	    Y_DIR_Pin
#define GPIO_DIR_Z_PIN			      Z_DIR_Pin

// Enable Pins
#define GPIO_ENABLE_X_PORT		    X_EN_GPIO_Port
#define GPIO_ENABLE_Y_PORT        Y_EN_GPIO_Port
#define GPIO_ENABLE_Z_PORT        Z_EN_GPIO_Port
#define GPIO_ENABLE_X_PIN			    X_EN_Pin
#define GPIO_ENABLE_Y_PIN         Y_EN_Pin
#define GPIO_ENABLE_Z_PIN         Z_EN_Pin

// Limit Pins
#define GPIO_LIM_X_PORT			      X_MIN_GPIO_Port
#define GPIO_LIM_Y_PORT			      Y_MIN_GPIO_Port
#define GPIO_LIM_Z_PORT			      Z_MIN_GPIO_Port
#define GPIO_LIM_X_PIN			      X_MIN_Pin
#define GPIO_LIM_Y_PIN			      Y_MIN_Pin
#define GPIO_LIM_Z_PIN			      Z_MIN_Pin


// Control pins
#define GPIO_CTRL_RST_PORT        DI_0_GPIO_Port
#define GPIO_CTRL_RST_PIN         DI_0_Pin
#define GPIO_CTRL_FEED_PORT       DI_1_GPIO_Port
#define GPIO_CTRL_FEED_PIN        DI_1_Pin
#define GPIO_CTRL_START_PORT      DI_2_GPIO_Port
#define GPIO_CTRL_START_PIN       DI_2_Pin

// Safety door
#define GPIO_DOOR_PORT            DI_3_GPIO_Port
#define GPIO_DOOR_PIN             DI_3_Pin

// Probe
#define GPIO_PROBE_PORT           DI_4_GPIO_Port
#define GPIO_PROBE_PIN            DI_4_Pin


// Coolant
#define GPIO_COOL_FLOOD_PORT      DQ_0_GPIO_Port
#define GPIO_COOL_FLOOD_PIN       DQ_0_Pin
#define GPIO_COOL_MIST_PORT       DQ_1_GPIO_Port
#define GPIO_COOL_MIST_PIN        DQ_1_Pin

// Spindle
#define GPIO_SPINDLE_PWM_PORT	    DQ_2_GPIO_Port
#define GPIO_SPINDLE_PWM_PIN	    DQ_2_Pin
#define GPIO_SPINDLE_DIR_PORT	    DQ_3_GPIO_Port
#define GPIO_SPINDLE_DIR_PIN	    DQ_3_Pin
#define GPIO_SPINDLE_ENA_PORT	    DQ_4_GPIO_Port
#define GPIO_SPINDLE_ENA_PIN	    DQ_4_Pin


#endif /* PIN_MAP_INCLUDED */
