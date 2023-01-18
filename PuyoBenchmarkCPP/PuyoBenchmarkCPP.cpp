#include <iostream>
#include <chrono>
#include "PuyoField.h"
using namespace PuyoBenchmark;

int main()
{
    PuyoColor testField[] = {
        PuyoColor(0), PuyoColor(0), PuyoColor(4), PuyoColor(5), PuyoColor(2), PuyoColor(2),
        PuyoColor(4), PuyoColor(3), PuyoColor(3), PuyoColor(4), PuyoColor(5), PuyoColor(3),
        PuyoColor(5), PuyoColor(3), PuyoColor(4), PuyoColor(5), PuyoColor(2), PuyoColor(2),
        PuyoColor(4), PuyoColor(3), PuyoColor(4), PuyoColor(5), PuyoColor(2), PuyoColor(3),
        PuyoColor(5), PuyoColor(2), PuyoColor(3), PuyoColor(4), PuyoColor(5), PuyoColor(3),
        PuyoColor(2), PuyoColor(3), PuyoColor(4), PuyoColor(5), PuyoColor(2), PuyoColor(3),
        PuyoColor(5), PuyoColor(2), PuyoColor(3), PuyoColor(4), PuyoColor(5), PuyoColor(2),
        PuyoColor(5), PuyoColor(2), PuyoColor(3), PuyoColor(4), PuyoColor(5), PuyoColor(2),
        PuyoColor(5), PuyoColor(4), PuyoColor(4), PuyoColor(3), PuyoColor(4), PuyoColor(3),
        PuyoColor(4), PuyoColor(2), PuyoColor(3), PuyoColor(5), PuyoColor(3), PuyoColor(3),
        PuyoColor(5), PuyoColor(4), PuyoColor(2), PuyoColor(3), PuyoColor(5), PuyoColor(4),
        PuyoColor(5), PuyoColor(4), PuyoColor(2), PuyoColor(3), PuyoColor(5), PuyoColor(4),
        PuyoColor(5), PuyoColor(4), PuyoColor(2), PuyoColor(3), PuyoColor(5), PuyoColor(4),
    };
    int count = 5000000;

    PuyoBenchmark::PuyoField field;
    PuyoBenchmark::Simulator sim = PuyoBenchmark::Simulator(4);
    std::vector<int> popped;
    int chain;
    int score;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++)
    {
        field.CopyFrom(testField);
        auto pair = field.ApplyChainImmediately(&sim, &popped, true);
        chain = pair.first;
        score = pair.second;
    }

    auto finish = std::chrono::high_resolution_clock::now();
    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << chain << "연쇄 " << score << "점 모형입니다." << std::endl;
    std::cout << count << "번의 테스트에 걸린 시간은 " << msec << " 밀리초입니다." << std::endl;
    std::cout << "초당 " << std::lround((double)count * 1000 / msec) << "번의 속도입니다." << std::endl;
    std::cin.get();
    return 0;
}
