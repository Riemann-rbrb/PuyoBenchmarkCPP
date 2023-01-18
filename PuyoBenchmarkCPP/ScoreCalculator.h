#pragma once
#include "PuyoColor.h"

namespace PuyoBenchmark {
	class ScoreCalculator {

	private:
		static const int CHAIN_SCORE[];
		static const int COLOR_SCORE[];
		static const int COUNT_SCORE[];
		static const int LOOKUP_TABLE[];
		int minPopCount;
		int totalPopCount;
		int countScore;
		int colors;

	public:
		ScoreCalculator(int pop);
		void Reset();
		void AddPuyo(PuyoColor c, int count);
		int GetScore(int chain);
	};
}