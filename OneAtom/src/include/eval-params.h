/*
 * constants.h
 *
 *  Created on: Nov 18, 2017
 *      Author: fake_sci
 */

#ifndef SRC_EVAL_PARAMS_H_
#define SRC_EVAL_PARAMS_H_

#include <precision-definition.h>

//uncomment for extra output
//#define DEBUG_MODE
//#define DEBUG_JUMPS

//the dressed basis
static const int MAX_PHOTON_NUMBER = 1;
static const int DRESSED_BASIS_SIZE = (2 * (MAX_PHOTON_NUMBER + 1));

//Evaluation of each sample is performed beginning at 0s and ending at the end time.
//Increasing the END_TIME value is necessary to caught the stationary evaluation
//phase
static const FLOAT_TYPE TIME_STEP_SIZE = 0.001;
static const int TIME_STEPS_NUMBER = 1000;		//the total number of steps by the time axis
static const int MONTE_CARLO_SAMPLES_NUMBER = 1;

static const FLOAT_TYPE EVAL_TIME = TIME_STEP_SIZE * TIME_STEPS_NUMBER;

//change to use another pseudo random sequence
static const int RANDSEED = 345777;

#endif /* SRC_EVAL_PARAMS_H_ */
