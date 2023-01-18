#pragma once
#include <vector>
#include "ScoreCalculator.h"

namespace PuyoBenchmark {
	class Simulator {

	private:
		static const int DIRECTION_X[];
		static const int DIRECTION_Y[];
		int minPopCount;
		bool visited[78];
		std::vector<int> puyos;
		ScoreCalculator calculator;
		int CheckConnected(PuyoColor *field, int x, int y);

	public:
		Simulator(int pop);
		int CheckPop(PuyoColor *field, int countArray[], int checkArray[], std::vector<int> *popped, int chain);
		static void ApplyPop(PuyoColor *field, std::vector<int> *popped);
	};
}