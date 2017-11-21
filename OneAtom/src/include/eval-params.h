/*
 * constants.h
 *
 *  Created on: Nov 18, 2017
 *      Author: fake_sci
 */

#ifndef SRC_EVAL_PARAMS_H_
#define SRC_EVAL_PARAMS_H_

//the dressed basis macros
static const int MAX_PHOTON_NUMBER = 5;
static const int DRESSED_BASIS_SIZE = (2 * (MAX_PHOTON_NUMBER + 1));

//Evaluation of each sample is performed beginning at 0s and ending at the end time.
//Increasing the END_TIME value is necessary to caught the stationary evaluation
//phase
static const float T_STEP_SIZE = 0.01;
static const int TIME_STEPS_NUMBER = 150;		//the total number of steps by the time axis
static const int MONTE_CARLO_SAMPLES_NUMBER = 100;

static const float EVAL_TIME = T_STEP_SIZE * TIME_STEPS_NUMBER;

// Use typed constants instead of #define
static const int RND_NUM_BUFF_SIZE = 8 * 1024;
static const int SIMDALIGN = 1024; //an alignment for memory in a multithreaded environment
//a constant - initializer of a pseudorandom numbers generator
#define RANDSEED 345777

#endif /* SRC_EVAL_PARAMS_H_ */