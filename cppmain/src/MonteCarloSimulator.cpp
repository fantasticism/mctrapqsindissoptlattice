/*
 * MonteCarloSimulator.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: fakesci
 */

#include <omp.h>
#include <iostream>
#include <cmath>
#include <exception>

#include <mkl_types.h>
#include "include/Model.h"
#include "include/RndNumProvider.h"
#include "include/MonteCarloSimulator.h"
#include "include/precision-definition.h"
#include "include/mkl-constants.h"
#include "include/SimulationResult.h"
#include "include/Solver.h"

#ifdef USE_GPU
#include <cublas_v2.h>
#include <cuda_runtime.h>
#endif

MonteCarloSimulator::MonteCarloSimulator(MKL_INT samplesNumber, int nThreads,
		Model &model, RndNumProvider &rndNumProvider) :
		basisSize(model.getBasisSize()), samplesNumber(samplesNumber), nThreads(
				nThreads), model(model), rndNumProvider(rndNumProvider), zeroVector(
				new COMPLEX_TYPE[basisSize]), groundState(
				new COMPLEX_TYPE[basisSize]) {
	for (int i = 0; i < basisSize; ++i) {
		zeroVector[i].real = 0.0;
		zeroVector[i].imag = 0.0;
	}

	complex_cblas_copy(basisSize, zeroVector, NO_INC, groundState, NO_INC);
	groundState[0].real = 1.0;
}

MonteCarloSimulator::~MonteCarloSimulator() {
	delete[] zeroVector;
	delete[] groundState;
}

SimulationResult *MonteCarloSimulator::simulate(std::ostream &consoleStream,
FLOAT_TYPE timeStep, int nTimeSteps) {
#ifdef USE_GPU
	cublasHandle_t cublasHandle;
	CUDA_COMPLEX_TYPE *devPtrL;
	try {
		cublasStatus_t cublasStatus = cublasCreate(&cublasHandle);
		if (cublasStatus != CUBLAS_STATUS_SUCCESS) {
			throw std::string(
					"Initialization of CuBLAS library failed with error:")
					+ std::to_string(cublasStatus);
		}

		MKL_INT basisSize = model.getBasisSize();

		cudaError_t cudaStatus = cudaMalloc((void**) &devPtrL,
				basisSize * basisSize * sizeof(CUDA_COMPLEX_TYPE));
		if (cudaStatus != cudaSuccess) {
			throw std::string("Device memory allocation failed:")
					+ std::to_string(cudaStatus);
		}

		COMPLEX_TYPE *rowMajorL = model.getL();

		//make it column major
		COMPLEX_TYPE columnMajorL[basisSize * basisSize];
		for (int j = 0; j < basisSize; ++j) {
			for (int i = 0; i < basisSize; ++i) {
				columnMajorL[i] = rowMajorL[i * basisSize + j];
			}
		}

		cublasStatus = cublasSetMatrix(basisSize, basisSize,
				sizeof(COMPLEX_TYPE),
				reinterpret_cast<CUDA_COMPLEX_TYPE *>(columnMajorL), basisSize,
				devPtrL, basisSize);
		if (cublasStatus != CUBLAS_STATUS_SUCCESS) {
			throw std::string("CuBLAS set matrix failed:")
					+ std::to_string(cudaStatus);
		}
#endif

		//A storage of final states of all realizations
		COMPLEX_TYPE ** const result = new COMPLEX_TYPE *[samplesNumber];
		for (int i = 0; i < samplesNumber; ++i) {
			result[i] = new COMPLEX_TYPE[basisSize];
		}

		//to obtain unbiased random numbers for each thread
		int threadId = 0;

#ifdef PRINT_PROGRESS
		int progress = 0;
#endif

#if THREADS_NUM > 1
#pragma omp parallel num_threads(THREADS_NUM) private(threadId)
		{
			threadId = omp_get_thread_num();
#ifdef DEBUG
			consoleStream << "Thread " + std::to_string(threadId) + " started\n";
#endif
#endif
			Solver solver(threadId, timeStep, nTimeSteps, model, rndNumProvider
#ifdef USE_GPU
					, cublasHandle, devPtrL
#endif
					);

#if THREADS_NUM > 1
#pragma omp for
#endif
			for (int sampleIndex = 0; sampleIndex < samplesNumber;
					sampleIndex++) {
				solver.solve(consoleStream, groundState, result[sampleIndex]);
#ifdef PRINT_PROGRESS
				if (progress % SAMPLES_BETWEEN_PROGRESS == 0) {
					consoleStream
							<< "Progress: "
									+ std::to_string(
											std::lround(
													100.0 * progress
															/ samplesNumber))
									+ "%\n";
				}
#pragma omp atomic update
				progress++;
#endif
			}

#if THREADS_NUM > 1
#ifdef DEBUG
			consoleStream << "Thread: " + std::to_string(threadId) + " finished\n";
#endif
		}
#endif
		SimulationResult *simulationResult = new SimulationResult(result,
				samplesNumber, model);

#ifdef USE_GPU
		//freeing resources
		cudaFree(devPtrL);
		cublasDestroy(cublasHandle);
#endif

		return simulationResult;

#ifdef USE_GPU
	} catch (const std::string &message) {
		//freeing resources
		cudaFree(devPtrL);
		cublasDestroy(cublasHandle);

		throw message;
	}
#endif
}

