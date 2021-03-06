/*
 * SolverFactory.h
 *
 *  Created on: Dec 20, 2017
 *      Author: fakesci
 */

#ifndef SRC_SOLVERCONTEXT_H_
#define SRC_SOLVERCONTEXT_H_

#include "vector"

#include "cuda_runtime.h"
#include "helper_cuda.h"

#include "precision-definition.h"
#include "Solver.h"
#include "Model.h"

class SolverContext {

	static constexpr FLOAT_TYPE ONE_SIXTH = 1.0 / 6;
	static constexpr FLOAT_TYPE ONE_TWENTY_FORTH = 1.0 / 24;

	//---------------------global-------------------------------
	const uint maxSolvers;
	const uint basisSize;
	const FLOAT_TYPE timeStep;
	const uint nTimeSteps;

	CUDA_COMPLEX_TYPE *rungeKuttaOperatorDevPtr;

	CUDA_COMPLEX_TYPE * a1CSR3ValuesDevPtr;
	int * a1CSR3ColumnsDevPtr;
	int * a1CSR3RowIndexDevPtr;

	CUDA_COMPLEX_TYPE * a2CSR3ValuesDevPtr;
	int * a2CSR3ColumnsDevPtr;
	int * a2CSR3RowIndexDevPtr;

	CUDA_COMPLEX_TYPE * a3CSR3ValuesDevPtr;
	int * a3CSR3ColumnsDevPtr;
	int * a3CSR3RowIndexDevPtr;

	//----------------solver-local--------------------------------
	std::vector<Solver *> * solverPtrs;
	std::vector<Solver *> * solverDevPtrs;

	std::vector<CUDA_COMPLEX_TYPE *> * k1DevPtrs;
	std::vector<CUDA_COMPLEX_TYPE *> * k2DevPtrs;
	std::vector<CUDA_COMPLEX_TYPE *> * k3DevPtrs;
	std::vector<CUDA_COMPLEX_TYPE *> * k4DevPtrs;

	std::vector<CUDA_COMPLEX_TYPE *> * prevStateDevPtrs;
	std::vector<CUDA_COMPLEX_TYPE *> * curStateDevPtrs; //also holds results

	//----------------Methods declarations------------------------

	template<typename T>
	void freeDevicePtrs(std::vector<T *> * &v);

	template<typename T>
	void freePtrs(std::vector<T *> * &v);

	void addRealConstant2Matrix(const FLOAT_TYPE realConstant,
			CUDA_COMPLEX_TYPE * const matrix);

	CUDA_COMPLEX_TYPE * createRungeKuttaOperatorMatrix(
			const CUDA_COMPLEX_TYPE * const l);

public:
	SolverContext(uint maxSolvers, FLOAT_TYPE timeStep, uint nTimeSteps,
			Model &model);
	~SolverContext();

	Solver * createSolverDev(const CUDA_COMPLEX_TYPE * const initialState);

	Solver ** createSolverDev(const uint count,
			const CUDA_COMPLEX_TYPE * const initialState);

	void initAllSolvers(CUDA_COMPLEX_TYPE * initialState);

	CUDA_COMPLEX_TYPE ** getAllResults();

	void appendAllResults(std::vector<CUDA_COMPLEX_TYPE *> &results);

	template<typename T> void transferState2Device(T * const devPtr,
			const T * const hostPtr);

	template<typename T> T* transferState2Device(const T * const hostPtr);

	template<typename T> void transferState2Host(const T * const devPtr,
			T * const hostPtr);

	template<typename T> T* transferState2Host(const T * const devPtr);

	template<typename T> static T * transferObject2Device(const T * const hostPtr);

	template<typename T> static T* transferArray2Host(const T * const devPtr,
			uint size);

	template<typename T> static void transferArray2Host(const T * const devPtr,
			T * const hostPtr, const uint size);

	template<typename T> static void transferArray2Device(T * const devPtr,
			const T * const hostPtr, const uint size);

	template<typename T> static T* transferArray2Device(const T * const hostPtr,
			const uint size);

	//---------------------------Getters-------------------------------

	const CUDA_COMPLEX_TYPE * getRungeKuttaOperatorDevPtr();

	int getA1CSR3RowsNum();

	const CUDA_COMPLEX_TYPE * const getA1CSR3ValuesDevPtr();
	const int * const getA1CSR3ColumnsDevPtr();
	const int * const getA1CSR3RowIndexDevPtr();

	int getA2CSR3RowsNum();

	const CUDA_COMPLEX_TYPE * const getA2CSR3ValuesDevPtr();
	const int * const getA2CSR3ColumnsDevPtr();
	const int * const getA2CSR3RowIndexDevPtr();

	int getA3CSR3RowsNum();

	const CUDA_COMPLEX_TYPE * const getA3CSR3ValuesDevPtr();
	const int * const getA3CSR3ColumnsDevPtr();
	const int * const getA3CSR3RowIndexDevPtr();
};

template<typename T> inline void SolverContext::transferState2Device(
		T * const devPtr, const T * const hostPtr) {
	checkCudaErrors(
			cudaMemcpy(devPtr, hostPtr, basisSize * sizeof(T),
					cudaMemcpyHostToDevice));
}

template<typename T> inline T* SolverContext::transferState2Device(
		const T * const hostPtr) {
	T * devPtr;
	checkCudaErrors(cudaMalloc((void**) &devPtr, basisSize * sizeof(T)));
	transferState2Device(devPtr, hostPtr);

	return devPtr;
}

template<typename T> inline void SolverContext::transferState2Host(
		const T * const devPtr, T * const hostPtr) {
	transferArray2Host(devPtr, hostPtr, basisSize);
}

template<typename T> inline T* SolverContext::transferState2Host(
		const T * const devPtr) {
	return transferArray2Host(devPtr, basisSize);
}

template<typename T> inline T* SolverContext::transferArray2Host(
		const T * const devPtr, const uint size) {
	T * hostPtr = new T[size];
	transferArray2Host(devPtr, hostPtr, size);

	return hostPtr;
}

template<typename T> inline void SolverContext::transferArray2Host(
		const T * const devPtr, T * const hostPtr, const uint size) {
	checkCudaErrors(
			cudaMemcpy(hostPtr, devPtr, size * sizeof(T),
					cudaMemcpyDeviceToHost));
}

template<typename T> inline void SolverContext::transferArray2Device(
		T * const devPtr, const T * const hostPtr, const uint size) {
	checkCudaErrors(
			cudaMemcpy(devPtr, hostPtr, size * sizeof(T),
					cudaMemcpyHostToDevice));
}

template<typename T> inline T* SolverContext::transferArray2Device(
		const T * const hostPtr, const uint size) {
	T * devPtr;
	checkCudaErrors(cudaMalloc((void**) &devPtr, size * sizeof(T)));
	transferArray2Device(devPtr, hostPtr, size);

	return devPtr;
}

template<typename T> inline T* SolverContext::transferObject2Device(
		const T * const hostPtr) {
	T * devPtr;
	checkCudaErrors(cudaMalloc((void**) &devPtr, sizeof(T)));
	checkCudaErrors(
			cudaMemcpy(devPtr, hostPtr, sizeof(T), cudaMemcpyHostToDevice));

	return devPtr;
}

//-----------------------------Getters---------------------------------

inline const CUDA_COMPLEX_TYPE * SolverContext::getRungeKuttaOperatorDevPtr() {
	return rungeKuttaOperatorDevPtr;
}

inline const CUDA_COMPLEX_TYPE * const SolverContext::getA1CSR3ValuesDevPtr() {
	return a1CSR3ValuesDevPtr;
}

inline const int * const SolverContext::getA1CSR3ColumnsDevPtr() {
	return a1CSR3ColumnsDevPtr;
}

inline const int * const SolverContext::getA1CSR3RowIndexDevPtr() {
	return a1CSR3RowIndexDevPtr;
}

inline const CUDA_COMPLEX_TYPE * const SolverContext::getA2CSR3ValuesDevPtr() {
	return a2CSR3ValuesDevPtr;
}

inline const int * const SolverContext::getA2CSR3ColumnsDevPtr() {
	return a2CSR3ColumnsDevPtr;
}

inline const int * const SolverContext::getA2CSR3RowIndexDevPtr() {
	return a2CSR3RowIndexDevPtr;
}

inline const CUDA_COMPLEX_TYPE * const SolverContext::getA3CSR3ValuesDevPtr() {
	return a3CSR3ValuesDevPtr;
}

inline const int * const SolverContext::getA3CSR3ColumnsDevPtr() {
	return a3CSR3ColumnsDevPtr;
}

inline const int * const SolverContext::getA3CSR3RowIndexDevPtr() {
	return a3CSR3RowIndexDevPtr;
}
#endif /* SRC_SOLVERCONTEXT_H_ */
