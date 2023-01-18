#pragma once
#include "Simulator.h"
#include "FieldState.h"

namespace PuyoBenchmark {
	class PuyoField {

	private:
		PuyoColor field[78];
		int countArray[6];
		int checkArray[6];

	public:
		void CopyFrom(PuyoColor* f);
		int CheckPop(Simulator* sim, std::vector<int>* popped, int chain);
		void ApplyPop(std::vector<int>* popped);
		FieldState CheckField();
		void ApplyGravity();
		std::pair<int, int> ApplyChainImmediately(Simulator* sim, std::vector<int>* tempPuyos, bool applyAC);
	};
}