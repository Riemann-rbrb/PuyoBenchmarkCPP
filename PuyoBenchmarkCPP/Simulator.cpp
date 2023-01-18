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

            //�ֺ��� ���ػѿ並 ���� ���ش�.
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
                //�ʵ带 �̹� Ȯ���߰ų� ���ػѿ�� ��������
                if (visited[y * 6 + x] || field[y * 6 + x] == OJAMA)
                    continue;

                //�� ���� �ѿ䰡 ����Ǿ� �ִ��� Ȯ���Ѵ�.
                puyos.clear();
                int connectedCount = CheckConnected(field, x, y);
                if (connectedCount >= minPopCount)
                {
                    //������ �߰��Ѵ�.
                    popped->insert(popped->end(), puyos.begin(), puyos.end());
                    calculator.AddPuyo(field[y * 6 + x], connectedCount);
                }
            }
        }

        return calculator.GetScore(chain);
    }

    int Simulator::CheckConnected(PuyoColor* field, int x, int y) {
        //�ش� ��ġ�� �ѿ並 �ӽ� ����Ʈ�� �߰��Ѵ�.
        visited[y * 6 + x] = true;
        puyos.push_back(x << 4 | y);
        int connectedCount = 1;
        PuyoColor color = field[y * 6 + x];

        //�����¿� �� ������ �ѿ並 Ž���Ѵ�.
        for (int i = 0; i < 4; i++)
        {
            int newX = x + DIRECTION_X[i];
            int newY = y + DIRECTION_Y[i];

            //������ ���̸� ����Ѵ�.
            if (newX >= 0 && newX <= 5 && newY >= 1 && newY <= 12
                && !visited[newY * 6 + newX] && field[newY * 6 + newX] == color)
            {
                connectedCount += CheckConnected(field, newX, newY);
            }
        }

        //����� ������ ��ȯ�Ѵ�.
        return connectedCount;
    }
}