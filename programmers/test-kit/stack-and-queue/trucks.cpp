// https://programmers.co.kr/learn/courses/30/lessons/42583

#include <string>
#include <vector>
#include <deque>
#include <utility>

using namespace std;

int solution(int bridgeLength, int weightLimit, vector<int> trucks) 
{
    int currentWeight = 0;
    int elapsed = 0;

    deque<int> leftTrucks(trucks.begin(), trucks.end());
    deque<pair<int, int>> enterings; // 트럭 무게 & 진입 시간

    while (true)
    {
        // 마지막 트럭이 도착했나 확인
        if (enterings.empty() == false && bridgeLength == elapsed - enterings.front().second)
        {
            currentWeight -= enterings.front().first;
            enterings.pop_front();
        }

        // 신규 진입 트럭 계산
        if (leftTrucks.empty() == false && currentWeight + leftTrucks.front() <= weightLimit)
        {
            currentWeight += leftTrucks.front();
            enterings.emplace_back(leftTrucks.front(), elapsed);

            leftTrucks.pop_front();
        }

        // 소요 시간 기록
        ++elapsed;
        if (enterings.empty() == true)
            break;
    }
    return elapsed;
}