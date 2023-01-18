#include "PuyoField.h"

namespace PuyoBenchmark {

	void PuyoField::CopyFrom(PuyoColor* f) {
		std::copy(f, f + 78, field);
		std::fill(checkArray, checkArray + 6, 12);
		for (int x = 0; x < 6; x++)
		{
			countArray[x] = 0;
			for (int y = 0; y < 13; y++)
			{
				if (field[y * 6 + x] != NONE)
				{
					countArray[x] = 13 - y;
					break;
				}
			}
		}
	}

	int PuyoField::CheckPop(Simulator* sim, std::vector<int>* popped, int chain) {
		return sim->CheckPop(field, countArray, checkArray, popped, chain);
	}

	void PuyoField::ApplyPop(std::vector<int>* popped) {
		Simulator::ApplyPop(field, popped);
	}

    FieldState PuyoField::CheckField()
    {
        FieldState result = ALL_CLEAR;
        for (int x = 0; x < 6; x++)
        {
            if (countArray[x] == 0)
                continue;

            bool quick = true;
            int index = 13;
            for (int y = 12; y >= 13 - countArray[x]; y--)
            {
                if (field[y * 6 + x] == NONE)
                    continue;

                index--;
                if (index != y)
                {
                    //ª—ø‰ æ∆∑°ø° ∫Û ∞¯∞£¿Ã ¿÷¿∏∏È ƒ¸¿Ã æ∆¥œ¥Ÿ.
                    quick = false;
                    break;
                }
            }

            //ƒ¸ »Æ¿Œ
            if (quick)
            {
                countArray[x] = 13 - index;
                checkArray[x] = index - 1;
            }
            else
            {
                if (result != UNSTABLE)
                    result = UNSTABLE;
                checkArray[x] = index;
            }

            //Ωœæµ¿Ã »Æ¿Œ
            if (result == ALL_CLEAR && index < 13)
                result = STABLE;
        }

        return result;
    }

    void PuyoField::ApplyGravity()
    {
        for (int x = 0; x < 6; x++)
        {
            if (countArray[x] == 0)
                continue;

            int index = checkArray[x] + 1;
            for (int y = checkArray[x]; y >= 13 - countArray[x]; y--)
            {
                if (field[y * 6 + x] == NONE)
                    continue;

                index--;
                //ª—ø‰ æ∆∑°ø° ∫Û ∞¯∞£¿Ã ¿÷¿∏∏È ª—ø‰∏¶ ∂≥æÓ∂ﬂ∏∞¥Ÿ.
                if (index != y)
                {
                    field[index * 6 + x] = field[y * 6 + x];
                    field[y * 6 + x] = NONE;
                }
            }

            countArray[x] = 13 - index;
        }
    }

    std::pair<int, int> PuyoField::ApplyChainImmediately(Simulator* sim, std::vector<int>* tempPuyos, bool applyAC) {
        int score = 0;
        int chain = 0;

        while (true)
        {
            tempPuyos->clear();
            int add = CheckPop(sim, tempPuyos, chain + 1);
            if (add == 0)
                break;
            chain++;
            score += add;
            ApplyPop(tempPuyos);

            FieldState state = CheckField();
            if (state == ALL_CLEAR && applyAC)
            {
                score += 2100;
                break;
            }
            else if (state != UNSTABLE)
                break;
            ApplyGravity();
        }

        return std::pair<int, int>(chain, score);
    }
}