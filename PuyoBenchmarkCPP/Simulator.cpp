#include "Simulator.h"

namespace PuyoBenchmark {
	const int Simulator::DIRECTION_X[] = { 1, -1, 0, 0};
	const int Simulator::DIRECTION_Y[] = { 0, 0, 1, -1 };


	Simulator::Simulator(int pop) : calculator(pop) {
		minPopCount = pop;
	}

	void Simulator::ApplyPop(PuyoColor* field, std::vector<int>* popped) {
        for (int loc : *popped)
        {
            int x = loc >> 4;
            int y = loc & 15;
            field[y * 6 + x] = NONE;

            //주변의 방해뿌요를 같이 없앤다.
            for (int i = 0; i < 4; i++)
            {
                int newX = x + DIRECTION_X[i];
                int newY = y + DIRECTION_Y[i];
                if (newX >= 0 && newX <= 5 && newY >= 1 && newY <= 12
                    && field[newY * 6 + newX] == OJAMA)
                {
                    field[newY * 6 + newX] = NONE;
                }
            }
        }
	}

    int Simulator::CheckPop(PuyoColor* field, int countArray[], int checkArray[], std::vector<int>* popped, int chain) {
        std::fill(visited, visited+78, false);
        calculator.Reset();

        for (int x = 0; x < 6; x++)
        {
            for (int y = std::max(13 - countArray[x], 1); y <= checkArray[x]; y++)
            {
                //필드를 이미 확인했거나 방해뿌요면 다음으로
                if (visited[y * 6 + x] || field[y * 6 + x] == OJAMA)
                    continue;

                //몇 개의 뿌요가 연결되어 있는지 확인한다.
                puyos.clear();
                int connectedCount = CheckConnected(field, x, y);
                if (connectedCount >= minPopCount)
                {
                    //점수를 추가한다.
                    popped->insert(popped->end(), puyos.begin(), puyos.end());
                    calculator.AddPuyo(field[y * 6 + x], connectedCount);
                }
            }
        }

        return calculator.GetScore(chain);
    }

    int Simulator::CheckConnected(PuyoColor* field, int x, int y) {
        //해당 위치의 뿌요를 임시 리스트에 추가한다.
        visited[y * 6 + x] = true;
        puyos.push_back(x << 4 | y);
        int connectedCount = 1;
        PuyoColor color = field[y * 6 + x];

        //상하좌우 네 방향의 뿌요를 탐색한다.
        for (int i = 0; i < 4; i++)
        {
            int newX = x + DIRECTION_X[i];
            int newY = y + DIRECTION_Y[i];

            //동일한 색이면 재귀한다.
            if (newX >= 0 && newX <= 5 && newY >= 1 && newY <= 12
                && !visited[newY * 6 + newX] && field[newY * 6 + newX] == color)
            {
                connectedCount += CheckConnected(field, newX, newY);
            }
        }

        //연결된 개수를 반환한다.
        return connectedCount;
    }
}