///*
// * solver-tests.cpp
// *
// *  Created on: Dec 8, 2017
// *      Author: fakesci
// */
//
//#include "definitions.h"
//#include "Model.h"
//#include "Solver.h"
//#include "RndNumProviderImpl.h"
//
//TEST (Solver, normalize) {
//	std::ostringstream output;
//
//	const int basisSize = 64;
//
//	Model model(2, 2, 2, 2, 2, 2, 1.0, 20.0, 50.0, 2.0, 0.1);
//	RndNumProviderImpl rndNumProvider(345777, 1);
//
//	//the ground state
//	COMPLEX_TYPE initialState[basisSize];
//	for (int i = 0; i < basisSize; ++i) {
//		initialState[i]= {i,i};
//	}
//
//	Solver solver(0, 0.1, 1, model, NO_JUMP_RND_NUM_PROVIDER);
//	solver.normalizeVector(initialState);
//
//	COMPLEX_TYPE expectedResultState[] = { { 0., 0 }, { 0.002420463317,
//			0.002420463317 }, { 0.004840926634, 0.004840926634 }, {
//			0.007261389951, 0.007261389951 },
//			{ 0.009681853269, 0.009681853269 },
//			{ 0.01210231659, 0.01210231659 }, { 0.0145227799, 0.0145227799 }, {
//					0.01694324322, 0.01694324322 }, { 0.01936370654,
//					0.01936370654 }, { 0.02178416985, 0.02178416985 }, {
//					0.02420463317, 0.02420463317 }, { 0.02662509649,
//					0.02662509649 }, { 0.02904555981, 0.02904555981 }, {
//					0.03146602312, 0.03146602312 }, { 0.03388648644,
//					0.03388648644 }, { 0.03630694976, 0.03630694976 }, {
//					0.03872741307, 0.03872741307 }, { 0.04114787639,
//					0.04114787639 }, { 0.04356833971, 0.04356833971 }, {
//					0.04598880303, 0.04598880303 }, { 0.04840926634,
//					0.04840926634 }, { 0.05082972966, 0.05082972966 }, {
//					0.05325019298, 0.05325019298 }, { 0.05567065629,
//					0.05567065629 }, { 0.05809111961, 0.05809111961 }, {
//					0.06051158293, 0.06051158293 }, { 0.06293204625,
//					0.06293204625 }, { 0.06535250956, 0.06535250956 }, {
//					0.06777297288, 0.06777297288 },
//			{ 0.0701934362, 0.0701934362 }, { 0.07261389951, 0.07261389951 }, {
//					0.07503436283, 0.07503436283 }, { 0.07745482615,
//					0.07745482615 }, { 0.07987528947, 0.07987528947 }, {
//					0.08229575278, 0.08229575278 },
//			{ 0.0847162161, 0.0847162161 }, { 0.08713667942, 0.08713667942 }, {
//					0.08955714273, 0.08955714273 }, { 0.09197760605,
//					0.09197760605 }, { 0.09439806937, 0.09439806937 }, {
//					0.09681853269, 0.09681853269 },
//			{ 0.099238996, 0.099238996 }, { 0.1016594593, 0.1016594593 }, {
//					0.1040799226, 0.1040799226 }, { 0.106500386, 0.106500386 },
//			{ 0.1089208493, 0.1089208493 }, { 0.1113413126, 0.1113413126 }, {
//					0.1137617759, 0.1137617759 },
//			{ 0.1161822392, 0.1161822392 }, { 0.1186027025, 0.1186027025 }, {
//					0.1210231659, 0.1210231659 },
//			{ 0.1234436292, 0.1234436292 }, { 0.1258640925, 0.1258640925 }, {
//					0.1282845558, 0.1282845558 },
//			{ 0.1307050191, 0.1307050191 }, { 0.1331254824, 0.1331254824 }, {
//					0.1355459458, 0.1355459458 },
//			{ 0.1379664091, 0.1379664091 }, { 0.1403868724, 0.1403868724 }, {
//					0.1428073357, 0.1428073357 }, { 0.145227799, 0.145227799 },
//			{ 0.1476482623, 0.1476482623 }, { 0.1500687257, 0.1500687257 }, {
//					0.152489189, 0.152489189 } };
//
//	std::cout << output.str();
//
//	//check the matrix
//	for (int i = 0; i < basisSize; ++i) {
//		ASSERT_THAT(initialState[i],
//				EqArrayComplexElementAt(expectedResultState, i, 8));
//	}
//}
//
///**
// *	KAPPA = 1.0
// *	DELTA_OMEGA = 20.0
// *	G = 50.0
// *	LATIN_E = 2.0
// *	J = 0.1
// *
// *	atom1SSize = atom2SSize = atom3SSize = 2
// *	field1SSize = field2SSize = field3SSize = 2
// *
// *	timeStep = 0.1
// *	timeStepsNumber = 1
// *
// *	No jumps
// *
// */
//TEST (Solver, oneLargeStepNoJumps) {
//	std::ostringstream output;
//
//	Model model(2, 2, 2, 2, 2, 2, 1.0, 20.0, 50.0, 2.0, 0.1);
//
//	const int basisSize = 64;
//
//	//the ground state
//	COMPLEX_TYPE initialState[basisSize] = { { 1.0, 0.0 } };
//	//the previous step vector
//	COMPLEX_TYPE resultState[basisSize];
//
//	Solver solver(0, 0.1, 1, model, NO_JUMP_RND_NUM_PROVIDER);
//	solver.solve(output, initialState, resultState);
//
//	COMPLEX_TYPE expectedResultState[] = { { 0.000349369043, -7.202438254e-6 },
//			{ 0.06482572244, -0.001276296314 },
//			{ 0.06368721055, -0.002093697532 },
//			{ 0.02654036179, -0.001320134677 },
//			{ 0.06482380468, -0.00127622661 },
//			{ 0.1293001584, -0.002545320486 },
//			{ 0.1281616465, -0.003362721703 },
//			{ 0.09101479772, -0.002589158849 },
//			{ 0.06365083056, -0.002092799412 },
//			{ 0.1281271842, -0.003361893288 },
//			{ 0.1269886724, -0.004179294505 },
//			{ 0.08984182359, -0.003405731651 },
//			{ 0.02649483119, -0.001319004521 },
//			{ 0.09097118488, -0.002588098396 },
//			{ 0.08983267299, -0.003405499614 },
//			{ 0.05268582423, -0.002631936759 },
//			{ 0.06482572244, -0.001276296314 },
//			{ 0.1293020761, -0.00254539019 }, { 0.1281635642, -0.003362791407 },
//			{ 0.09101671547, -0.002589228553 },
//			{ 0.1293001584, -0.002545320486 }, { 0.193776512, -0.003814414361 },
//			{ 0.1926380002, -0.004631815579 },
//			{ 0.1554911514, -0.003858252725 },
//			{ 0.1281271842, -0.003361893288 },
//			{ 0.1926035379, -0.004630987163 }, { 0.191465026, -0.005448388381 },
//			{ 0.1543181773, -0.004674825526 },
//			{ 0.09097118488, -0.002588098396 },
//			{ 0.1554475386, -0.003857192272 }, { 0.1543090267, -0.00467459349 },
//			{ 0.1171621779, -0.003901030635 },
//			{ 0.06368721055, -0.002093697532 },
//			{ 0.1281635642, -0.003362791407 },
//			{ 0.1270250523, -0.004180192625 },
//			{ 0.08987820359, -0.00340662977 },
//			{ 0.1281616465, -0.003362721703 },
//			{ 0.1926380002, -0.004631815579 },
//			{ 0.1914994883, -0.005449216797 },
//			{ 0.1543526395, -0.004675653942 },
//			{ 0.1269886724, -0.004179294505 }, { 0.191465026, -0.005448388381 },
//			{ 0.1903265141, -0.006265789598 },
//			{ 0.1531796654, -0.005492226744 },
//			{ 0.08983267299, -0.003405499614 },
//			{ 0.1543090267, -0.00467459349 }, { 0.1531705148, -0.005491994707 },
//			{ 0.116023666, -0.004718431853 },
//			{ 0.02654036179, -0.001320134677 },
//			{ 0.09101671547, -0.002589228553 },
//			{ 0.08987820359, -0.00340662977 },
//			{ 0.05273135483, -0.002633066916 },
//			{ 0.09101479772, -0.002589158849 },
//			{ 0.1554911514, -0.003858252725 },
//			{ 0.1543526395, -0.004675653942 },
//			{ 0.1172057908, -0.003902091088 },
//			{ 0.08984182359, -0.003405731651 },
//			{ 0.1543181773, -0.004674825526 },
//			{ 0.1531796654, -0.005492226744 },
//			{ 0.1160328166, -0.004718663889 },
//			{ 0.05268582423, -0.002631936759 },
//			{ 0.1171621779, -0.003901030635 }, { 0.116023666, -0.004718431853 },
//			{ 0.07887681726, -0.003944868998 } };
//
//	std::cout << output.str();
//
//	//check the matrix
//	for (int i = 0; i < basisSize; ++i) {
//		ASSERT_THAT(resultState[i],
//				EqArrayComplexElementAt(expectedResultState, i, 8));
//	}
//}
//
///**
// *	KAPPA = 1.0
// *	DELTA_OMEGA = 20.0
// *	G = 50.0
// *	LATIN_E = 2.0
// *	J = 0.1
// *
// *	atom1SSize = atom2SSize = atom3SSize = 2
// *	field1SSize = field2SSize = field3SSize = 2
// *
// *	timeStep = 0.1
// *	timeStepsNumber = 10
// *
// *	No jumps
// *
// */
//TEST (Solver, tenLargeStepsNoJump) {
//	std::ostringstream output;
//
//	Model model(2, 2, 2, 2, 2, 2, 1.0, 20.0, 50.0, 2.0, 0.1);
//
//	const int basisSize = 64;
//
//	//the ground state
//	COMPLEX_TYPE initialState[basisSize] = { { 1.0, 0.0 } };
//	//the previous step vector
//	COMPLEX_TYPE resultState[basisSize];
//
//	Solver solver(0, 0.1, 10, model, NO_JUMP_RND_NUM_PROVIDER);
//	solver.solve(output, initialState, resultState);
//
//	COMPLEX_TYPE expectedResultState[] = {
//			{ 0.0003200423989, -0.0001189381358 }, { 0.06007516714,
//					-0.02222127625 }, { 0.05976037166, -0.02291756896 }, {
//					0.02524626149, -0.01023308877 }, { 0.06007303556,
//					-0.02222048967 }, { 0.1198281603, -0.04432282779 }, {
//					0.1195133648, -0.0450191205 }, { 0.08499925465,
//					-0.03233464031 }, { 0.05972723662, -0.02290505236 }, {
//					0.1194823614, -0.04500739048 }, { 0.1191675659,
//					-0.04570368319 }, { 0.08465345572, -0.033019203 }, {
//					0.02520316002, -0.01021685067 }, { 0.08495828476,
//					-0.03231918878 }, { 0.08464348927, -0.03301548149 }, {
//					0.05012937911, -0.0203310013 }, { 0.06007516714,
//					-0.02222127625 }, { 0.1198302919, -0.04432361437 }, {
//					0.1195154964, -0.04501990708 }, { 0.08500138624,
//					-0.03233542688 }, { 0.1198281603, -0.04432282779 }, {
//					0.179583285, -0.0664251659 },
//			{ 0.1792684896, -0.06712145861 }, { 0.1447543794, -0.05443697842 },
//			{ 0.1194823614, -0.04500739048 }, { 0.1792374861, -0.06710972859 },
//			{ 0.1789226906, -0.06780602131 }, { 0.1444085805, -0.05512154111 },
//			{ 0.08495828476, -0.03231918878 }, { 0.1447134095, -0.0544215269 },
//			{ 0.144398614, -0.05511781961 }, { 0.1098845039, -0.04243333942 }, {
//					0.05976037166, -0.02291756896 }, { 0.1195154964,
//					-0.04501990708 }, { 0.1192007009, -0.04571619979 }, {
//					0.08468659075, -0.0330317196 }, { 0.1195133648,
//					-0.0450191205 }, { 0.1792684896, -0.06712145861 }, {
//					0.1789536941, -0.06781775133 }, { 0.1444395839,
//					-0.05513327113 }, { 0.1191675659, -0.04570368319 }, {
//					0.1789226906, -0.06780602131 }, { 0.1786078951,
//					-0.06850231402 }, { 0.144093785, -0.05581783383 }, {
//					0.08464348927, -0.03301548149 }, { 0.144398614,
//					-0.05511781961 }, { 0.1440838185, -0.05581411232 }, {
//					0.1095697084, -0.04312963213 }, { 0.02524626149,
//					-0.01023308877 }, { 0.08500138624, -0.03233542688 }, {
//					0.08468659075, -0.0330317196 }, { 0.05017248059,
//					-0.0203472394 }, { 0.08499925465, -0.03233464031 }, {
//					0.1447543794, -0.05443697842 }, { 0.1444395839,
//					-0.05513327113 }, { 0.1099254737, -0.04244879094 }, {
//					0.08465345572, -0.033019203 }, { 0.1444085805,
//					-0.05512154111 }, { 0.144093785, -0.05581783383 }, {
//					0.1095796748, -0.04313335363 }, { 0.05012937911,
//					-0.0203310013 }, { 0.1098845039, -0.04243333942 }, {
//					0.1095697084, -0.04312963213 }, { 0.07505559821,
//					-0.03044515193 } };
//
//	std::cout << output.str();
//
//	//check the matrix
//	for (int i = 0; i < basisSize; ++i) {
//		ASSERT_THAT(resultState[i],
//				EqArrayComplexElementAt(expectedResultState, i, 8));
//	}
//}
//
///**
// *	KAPPA = 1.0
// *	DELTA_OMEGA = 20.0
// *	G = 50.0
// *	LATIN_E = 2.0
// *	J = 0.1
// *
// *	atom1SSize = atom2SSize = atom3SSize = 2
// *	field1SSize = field2SSize = field3SSize = 2
// *
// *	timeStep = 0.00001
// *	timeStepsNumber = 10000
// *
// *	No jumps
// *
// */
//TEST (Solver, manyStepsNoJump) {
//	std::ostringstream output;
//
//	Model model(2, 2, 2, 2, 2, 2, 1.0, 20.0, 50.0, 2.0, 0.1);
//
//	const int basisSize = 64;
//
//	//the ground state
//	COMPLEX_TYPE initialState[basisSize] = { { 1.0, 0.0 } };
//	//the previous step vector
//	COMPLEX_TYPE resultState[basisSize];
//
//	Solver solver(0, 0.00001, 10000, model, NO_JUMP_RND_NUM_PROVIDER);
//	solver.solve(output, initialState, resultState);
//
//	COMPLEX_TYPE expectedResultState[] = { { 0.9999974684, -0.0007133884112 }, {
//			-0.0001698548704, -0.0004257306108 }, { 0.00009035319367,
//			-0.0004293953169 }, { 0.00001661724137, -0.0004283421335 }, {
//			-0.000169736761, -0.00042573174 }, { -0.0003293697535,
//			-0.0001380739396 }, { -0.00006916168945, -0.0001417386457 }, {
//			-0.0001428976417, -0.0001406854623 }, { 0.0000904086453,
//			-0.0004293950161 }, { -0.00006922434718, -0.0001417372158 }, {
//			0.0001909837168, -0.0001454019219 }, { 0.0001172477645,
//			-0.0001443487385 }, { 0.00001673727456, -0.0004283417117 }, {
//			-0.0001428957179, -0.0001406839113 }, { 0.0001173123461,
//			-0.0001443486174 }, { 0.00004357639379, -0.000143295434 }, {
//			-0.0001698548704, -0.0004257306108 }, { -0.0003294878628,
//			-0.0001380728104 }, { -0.00006927979882, -0.0001417375165 }, {
//			-0.0001430157511, -0.0001406843331 }, { -0.0003293697535,
//			-0.0001380739396 }, { -0.000489002746, 0.0001495838607 }, {
//			-0.0002287946819, 0.0001459191546 }, { -0.0003025306342,
//			0.000146972338 }, { -0.00006922434718, -0.0001417372158 }, {
//			-0.0002288573397, 0.0001459205846 }, { 0.00003135072436,
//			0.0001422558785 }, { -0.00004238522794, 0.0001433090619 }, {
//			-0.0001428957179, -0.0001406839113 }, { -0.0003025287104,
//			0.000146973889 }, { -0.00004232064639, 0.000143309183 }, {
//			-0.0001160565987, 0.0001443623664 }, { 0.00009035319367,
//			-0.0004293953169 }, { -0.00006927979882, -0.0001417375165 }, {
//			0.0001909282652, -0.0001454022226 }, { 0.0001171923129,
//			-0.0001443490392 }, { -0.00006916168945, -0.0001417386457 }, {
//			-0.0002287946819, 0.0001459191546 }, { 0.00003141338209,
//			0.0001422544485 }, { -0.00004232257021, 0.0001433076319 }, {
//			0.0001909837168, -0.0001454019219 }, { 0.00003135072436,
//			0.0001422558785 }, { 0.0002915587884, 0.0001385911724 }, {
//			0.0002178228361, 0.0001396443558 }, { 0.0001173123461,
//			-0.0001443486174 }, { -0.00004232064639, 0.000143309183 }, {
//			0.0002178874176, 0.0001396444769 }, { 0.0001441514653,
//			0.0001406976603 }, { 0.00001661724137, -0.0004283421335 }, {
//			-0.0001430157511, -0.0001406843331 }, { 0.0001171923129,
//			-0.0001443490392 }, { 0.0000434563606, -0.0001432958558 }, {
//			-0.0001428976417, -0.0001406854623 }, { -0.0003025306342,
//			0.000146972338 }, { -0.00004232257021, 0.0001433076319 }, {
//			-0.0001160585225, 0.0001443608153 }, { 0.0001172477645,
//			-0.0001443487385 }, { -0.00004238522794, 0.0001433090619 }, {
//			0.0002178228361, 0.0001396443558 }, { 0.0001440868838,
//			0.0001406975392 }, { 0.00004357639379, -0.000143295434 }, {
//			-0.0001160565987, 0.0001443623664 }, { 0.0001441514653,
//			0.0001406976603 }, { 0.00007041551303, 0.0001417508437 } };
//
//	std::cout << output.str();
//
//	//check the matrix
//	for (int i = 0; i < basisSize; ++i) {
//		ASSERT_THAT(resultState[i],
//				EqArrayComplexElementAt(expectedResultState, i, 8));
//	}
//}
//
///**
// *	KAPPA = 1.0
// *	DELTA_OMEGA = 20.0
// *	G = 50.0
// *	LATIN_E = 2.0
// *	J = 0.1
// *
// *	atom1SSize = atom2SSize = atom3SSize = 2
// *	field1SSize = field2SSize = field3SSize = 2
// *
// *	timeStep = 0.0001
// *	timeStepsNumber = 100000
// *
// */
//TEST (Solver, makeJump) {
//	std::ostringstream output;
//	output << std::setprecision(12);
//
//	Model model(2, 2, 2, 2, 2, 2, 1.0, 20.0, 50.0, 30.0, 0.1);
//
//	const int basisSize = 64;
//
//	COMPLEX_TYPE stateBeforeJump[basisSize];
//	for (int i = 0; i < basisSize; ++i) {
//		stateBeforeJump[i]= {1.0-1.0/basisSize*i};
//	}
//	COMPLEX_TYPE stateAfterJump1[basisSize];
//	COMPLEX_TYPE stateAfterJump2[basisSize];
//	COMPLEX_TYPE stateAfterJump3[basisSize];
//
//	class MockRndNumProvider: public RndNumProvider {
//	public:
//		void initBuffer(int streamId, FLOAT_TYPE *buffer, int bufferSize)
//				override {
//			int i = 0;
//			buffer[i++] = 0.1; // the first cavity wins
//			buffer[i++] = 0.8; // the third cavity wins
//			buffer[i++] = 0.5; // the second cavity wins
//		}
//	} rndNumProviderMock;
//
//	Solver solver(0, 0.0001, 10000, model, rndNumProviderMock);
//
//	//jumps in the first cavity
//	solver.makeJump(output, stateBeforeJump, stateAfterJump1);
//
//	COMPLEX_TYPE stateAfterJumpInFirst[] = { { 0.236189153, 0 }, { 0.236189153,
//			0 }, { 0.236189153, 0 }, { 0.236189153, 0 }, { 0.236189153, 0 }, {
//			0.236189153, 0 }, { 0.236189153, 0 }, { 0.236189153, 0 }, {
//			0.236189153, 0 }, { 0.236189153, 0 }, { 0.236189153, 0 }, {
//			0.236189153, 0 }, { 0.236189153, 0 }, { 0.236189153, 0 }, {
//			0.236189153, 0 }, { 0.236189153, 0 }, { 0.08194317552, 0 }, {
//			0.08194317552, 0 }, { 0.08194317552, 0 }, { 0.08194317552, 0 }, {
//			0.08194317552, 0 }, { 0.08194317552, 0 }, { 0.08194317552, 0 }, {
//			0.08194317552, 0 }, { 0.08194317552, 0 }, { 0.08194317552, 0 }, {
//			0.08194317552, 0 }, { 0.08194317552, 0 }, { 0.08194317552, 0 }, {
//			0.08194317552, 0 }, { 0.08194317552, 0 }, { 0.08194317552, 0 }, {
//			0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, {
//			0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, {
//			0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, {
//			0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, {
//			0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, {
//			0., 0 }, { 0., 0 } };
//
//	//jumps in the third cavity
//	solver.makeJump(output, stateBeforeJump, stateAfterJump2);
//
//	COMPLEX_TYPE stateAfterJumpInThird[] = { { 0.1795600557, 0 }, { 0.173948804,
//			0 }, { 0., 0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 },
//			{ 0., 0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 }, { 0.,
//					0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 }, {
//					0., 0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 },
//			{ 0., 0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 }, { 0.,
//					0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 }, {
//					0., 0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 },
//			{ 0., 0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 }, { 0.,
//					0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 }, {
//					0., 0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 },
//			{ 0., 0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 }, { 0.,
//					0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 }, {
//					0., 0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 },
//			{ 0., 0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 }, { 0.,
//					0 }, { 0., 0 }, { 0.1795600557, 0 }, { 0.173948804, 0 }, {
//					0., 0 }, { 0., 0 } };
//
//	//jumps in the second cavity
//	solver.makeJump(output, stateBeforeJump, stateAfterJump3);
//
//	COMPLEX_TYPE stateAfterJumpInSecond[] = { { 0.1887179686, 0 }, {
//			0.1887179686, 0 }, { 0.1887179686, 0 }, { 0.1887179686, 0 }, {
//			0.1639680711, 0 }, { 0.1639680711, 0 }, { 0.1639680711, 0 }, {
//			0.1639680711, 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0.,
//			0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0.1887179686, 0 }, {
//			0.1887179686, 0 }, { 0.1887179686, 0 }, { 0.1887179686, 0 }, {
//			0.1639680711, 0 }, { 0.1639680711, 0 }, { 0.1639680711, 0 }, {
//			0.1639680711, 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0.,
//			0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0.1887179686, 0 }, {
//			0.1887179686, 0 }, { 0.1887179686, 0 }, { 0.1887179686, 0 }, {
//			0.1639680711, 0 }, { 0.1639680711, 0 }, { 0.1639680711, 0 }, {
//			0.1639680711, 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0.,
//			0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0.1887179686, 0 }, {
//			0.1887179686, 0 }, { 0.1887179686, 0 }, { 0.1887179686, 0 }, {
//			0.1639680711, 0 }, { 0.1639680711, 0 }, { 0.1639680711, 0 }, {
//			0.1639680711, 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0., 0 }, { 0.,
//			0 }, { 0., 0 }, { 0., 0 }, { 0., 0 } };
//
//	std::cout << output.str();
//
//	//checks
//	for (int i = 0; i < basisSize; ++i) {
//		ASSERT_THAT(stateAfterJump1[i],
//				EqArrayComplexElementAt(stateAfterJumpInFirst, i, 8));
//	}
//
//	for (int i = 0; i < basisSize; ++i) {
//		ASSERT_THAT(stateAfterJump2[i],
//				EqArrayComplexElementAt(stateAfterJumpInThird, i, 8));
//	}
//
//	for (int i = 0; i < basisSize; ++i) {
//		ASSERT_THAT(stateAfterJump3[i],
//				EqArrayComplexElementAt(stateAfterJumpInSecond, i, 8));
//	}
//}
//
///**
// *	KAPPA = 1.0
// *	DELTA_OMEGA = 20.0
// *	G = 50.0
// *	LATIN_E = 2.0
// *	J = 0.1
// *
// *	atom1SSize = atom2SSize = atom3SSize = 2
// *	field1SSize = field2SSize = field3SSize = 2
// *
// *	timeStep = 0.00001
// *	timeStepsNumber = 1000000
// *
// *	Makes several jumps
// *
// */
//TEST (Solver, severalJumps_simpleBasis) {
//	std::ostringstream output;
//	output << std::setprecision(12);
//
//	Model model(2, 2, 2, 2, 2, 2, 1.0, 20.0, 50.0, 30.0, 0.1);
//
//	const int basisSize = 64;
//
//	class MockRndNumProvider: public RndNumProvider {
//	public:
//		void initBuffer(int streamId, FLOAT_TYPE *buffer, int bufferSize)
//				override {
//			int i = 0;
//			buffer[i++] = 0.99; // a jump
//			buffer[i++] = 0.5; // the second cavity wins
//			buffer[i++] = 0.98; // a jump
//			buffer[i++] = 0.1; // the first cavity wins
//			buffer[i++] = 0.99; // a jump
//			buffer[i++] = 0.9; // the third cavity wins
//			buffer[i++] = 0.0; // next threshold (is not possible to reach)
//		}
//	} rndNumProviderMock;
//
//	//the ground state
//	COMPLEX_TYPE initialState[basisSize] = { { 1.0, 0.0 } };
//	//the previous step vector
//	COMPLEX_TYPE resultState[basisSize];
//
//	Solver solver(0, 0.00001, 100000, model, rndNumProviderMock);
//	solver.solve(output, initialState, resultState);
//
//	COMPLEX_TYPE expectedResultState[] = { { -0.203470718, 0.3382981526 }, {
//			-0.1189207813, 0.197612049 }, { -0.1238852873, 0.2060443142 }, {
//			-0.1226421734, 0.203917448 }, { -0.1189232601, 0.1976162071 }, {
//			-0.03437332346, 0.05693010357 }, { -0.03933782942, 0.06536236879 },
//			{ -0.03809471556, 0.06323550262 }, { -0.1238863355, 0.206046008 }, {
//					-0.03933639886, 0.06535990442 }, { -0.04430090482,
//					0.07379216964 }, { -0.04305779096, 0.07166530347 }, {
//					-0.1226446185, 0.2039214226 }, { -0.0380946818,
//					0.06323531901 }, { -0.04305918777, 0.07166758423 }, {
//					-0.0418160739, 0.06954071807 },
//			{ -0.1189207813, 0.197612049 }, { -0.03437084461, 0.05692594543 }, {
//					-0.03933535058, 0.06535821065 }, { -0.03809223672,
//					0.06323134448 }, { -0.03437332346, 0.05693010357 }, {
//					0.05017661323, -0.08375599999 }, { 0.04521210726,
//					-0.07532373477 }, { 0.04645522113, -0.07745060094 }, {
//					-0.03933639886, 0.06535990442 }, { 0.04521353783,
//					-0.07532619914 }, { 0.04024903186, -0.06689393393 }, {
//					0.04149214572, -0.06902080009 }, { -0.0380946818,
//					0.06323531901 }, { 0.04645525488, -0.07745078455 }, {
//					0.04149074892, -0.06901851933 }, { 0.04273386278,
//					-0.0711453855 }, { -0.1238852873, 0.2060443142 }, {
//					-0.03933535058, 0.06535821065 }, { -0.04429985654,
//					0.07379047587 }, { -0.04305674268, 0.0716636097 }, {
//					-0.03933782942, 0.06536236879 }, { 0.04521210726,
//					-0.07532373477 }, { 0.0402476013, -0.06689146956 }, {
//					0.04149071516, -0.06901833572 }, { -0.04430090482,
//					0.07379216964 }, { 0.04024903186, -0.06689393393 }, {
//					0.0352845259, -0.05846166871 }, { 0.03652763976,
//					-0.06058853487 }, { -0.04305918777, 0.07166758423 }, {
//					0.04149074892, -0.06901851933 }, { 0.03652624295,
//					-0.06058625411 }, { 0.03776935682, -0.06271312028 }, {
//					-0.1226421734, 0.203917448 }, { -0.03809223672,
//					0.06323134448 }, { -0.04305674268, 0.0716636097 }, {
//					-0.04181362882, 0.06953674354 }, { -0.03809471556,
//					0.06323550262 }, { 0.04645522113, -0.07745060094 }, {
//					0.04149071516, -0.06901833572 }, { 0.04273382902,
//					-0.07114520189 }, { -0.04305779096, 0.07166530347 }, {
//					0.04149214572, -0.06902080009 }, { 0.03652763976,
//					-0.06058853487 }, { 0.03777075362, -0.06271540104 }, {
//					-0.0418160739, 0.06954071807 }, { 0.04273386278,
//					-0.0711453855 }, { 0.03776935682, -0.06271312028 }, {
//					0.03901247068, -0.06483998645 } };
//
//	std::cout << output.str();
//
//	//check the matrix
//	for (int i = 0; i < basisSize; ++i) {
//		ASSERT_THAT(resultState[i],
//				EqArrayComplexElementAt(expectedResultState, i, 8));
//	}
//}
//