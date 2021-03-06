/*
 * SolverTest0.h
 *
 *  Created on: Dec 20, 2017
 *      Author: fakesci
 */

#ifndef SRC_SOLVERTEST0_H_
#define SRC_SOLVERTEST0_H_

#include "Solver.h"
#include "precision-definition.h"

void testSolverParallelNormalize(Solver * solverDevPtr, uint nThreadsPerBlock,
CUDA_COMPLEX_TYPE * stateVectorDevPtr);

void testSolverParallelMultCSR3MatrixVector(Solver * solverDevPtr,
		const CUDA_COMPLEX_TYPE * const csr3MatrixValuesDevPtr,
		const int * const csr3MatrixColumnsDevPtr,
		const int * const csr3MatrixRowIndexDevPtr,
		CUDA_COMPLEX_TYPE *vectorDevPtr,
		CUDA_COMPLEX_TYPE *resultDevPtr);

void testSolverParallelCopy(Solver * solverDevPtr, uint nThreadsPerBlock,
		const CUDA_COMPLEX_TYPE * const source,
		CUDA_COMPLEX_TYPE * const dest);

void testSolverParallelCalcAlphaVector(Solver * solverDevPtr,
		uint nThreadsPerBlock, const FLOAT_TYPE alpha,
		const CUDA_COMPLEX_TYPE * const vector,
		CUDA_COMPLEX_TYPE * const result);

void testSolverParallelCalcV1PlusAlphaV2(Solver * solverDevPtr,
		uint nThreadsPerBlock, const CUDA_COMPLEX_TYPE * const v1,
		const FLOAT_TYPE alpha, const CUDA_COMPLEX_TYPE * const v2,
		CUDA_COMPLEX_TYPE * const result);

void testSolverSolve(Solver * solverDevPtr, bool noJumps);

void testSolverParallelMakeJump(Solver * solverDevPtr,
FLOAT_TYPE randomNumber);

#endif /* SRC_SOLVERTEST0_H_ */
