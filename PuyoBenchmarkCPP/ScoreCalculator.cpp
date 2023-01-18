#include <algorithm>
#include "ScoreCalculator.h"

namespace PuyoBenchmark {
	const int ScoreCalculator::CHAIN_SCORE[] = {
		0, 8, 16, 32, 64, 96, 128, 160,
		192, 224, 256, 288, 320, 352, 384, 416,
		448, 480, 512, 544, 576, 608, 640, 672 };
	const int ScoreCalculator::COLOR_SCORE[] = {
		0, 3, 6, 12, 24 };
	const int ScoreCalculator::COUNT_SCORE[] = {
		0, 2, 3, 4, 5, 6, 7, 10 };
	const int ScoreCalculator::LOOKUP_TABLE[] = {
		0, 1, 1, 2, 1, 2, 2, 3,
		1, 2, 2, 3, 2, 3, 3, 4,
		1, 2, 2, 3, 2, 3, 3, 4,
		2, 3, 3, 4, 3, 4, 4, 5 };


	ScoreCalculator::ScoreCalculator(int pop) {
		minPopCount = pop;
		totalPopCount = 0;
		countScore = 0;
		colors = 0;
	}

	void ScoreCalculator::Reset() {
		totalPopCount = 0;
		countScore = 0;
		colors = 0;
	}

	void ScoreCalculator::AddPuyo(PuyoColor c, int count) {
		totalPopCount += count;
		countScore += COUNT_SCORE[std::min(count - minPopCount, 7)];
		colors |= 1 << ((int)c - 1);
	}

	int ScoreCalculator::GetScore(int chain) {
		if (totalPopCount == 0)
			return 0;

		int chainScore = CHAIN_SCORE[std::min(chain - 1, 23)];
		int colorScore = COLOR_SCORE[LOOKUP_TABLE[colors] - 1];
		int left = totalPopCount * 10;
		int right = std::max(chainScore + colorScore + countScore, 1);
		return left * right;
	}
}