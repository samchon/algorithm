#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* ===========================================
	10번째에서 시간초과 (3.3초)
		백트레킹으로 유효하지 않은 걸 
		중도에 거를 수 있어야 함
=========================================== */

#ifndef INT_MAX
#	define INT_MAX (-1U/2)
#endif

/**
 * 경우의 수 中 N! 생성기
 */
class FactorialGenerator
{
private:
	size_t n;
	size_t size_;
	vector<size_t> atomArray;

public:
	FactorialGenerator(size_t n)
	{
		this->n = n;

		size_ = n;
		for (size_t i = n - 1; i >= 1; i--)
			size_ *= i;

		atomArray.assign(n, 0);
		for (size_t i = 0; i < n; i++)
			atomArray[i] = i;
	};

	auto size() const -> size_t
	{
		return size_;
	};

	/**
	 * Index번째 경우의 수를 받아온다.
	 */
	auto at(size_t index) const -> vector<size_t>
	{
		// 일단 0 ~ n-1 까지 번호가 담긴 원소 배열을 만들고
		vector<size_t> atomArray = this->atomArray;
		vector<size_t> row(n, 0);

		for (size_t i = 0; i < n; i++)
		{
			size_t item = index % atomArray.size(); // index와 #원소의 나머지를 받아와
			row[i] = atomArray[item]; // 그 번호대로 경우의 수를 확정함

			index = index / atomArray.size(); // 다음 과정을 위해 index를 조정
			atomArray.erase(atomArray.begin() + item); // 현재 사용한 번호 item도 없앰
		}

		return move(row); // 약간의 최적화를 위해 이동생성자 사용
	};
};

int main()
{
	vector<vector<int>> costMatrix;
	size_t size;

	// 먼저 행렬을 읽어 구성한다.
	cin >> size;
	costMatrix.assign(size, vector<int>(size, 1));

	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			cin >> costMatrix[i][j];

	////////////////////////////////////////////
	// 모든 경우의 수를 계산
	////////////////////////////////////////////
	FactorialGenerator factorial(size - 1);
	vector<size_t> row(size - 1, 0);
	int minCost = 9999;

	for (size_t i = 0; i < factorial.size(); i++)
	{
		// indexed 경우의 수
		// 0 번에서 출발하니 row[i] + 1을 해 줘야 함
		const vector<size_t> &row = factorial.at(i); 

		int cost = 0; // 현재 비용
		bool valid = true; // 유효성 여부

		size_t prev = 0; // 이전 index

		for (size_t j = 0; j < row.size(); j++)
		{
			size_t next = row[j] + 1;

			// 이전 index에서 그 다음으로 향하는 길이 유효한가 검사
			if (costMatrix[prev][next] == 0)
			{
				// 무효시 끝
				valid = false;
				break;
			}
			else
			{
				// 유효하다면 비용에 가산
				cost += costMatrix[prev][next];
			}
			prev = next;
		}

		// 그간 유효했을 뿐 아니라,
		// 0번 지점으로 다시 돌아올 수 있기까지 해야 한다.
		if (valid == true && costMatrix[prev][0] != 0)
		{
			// 최소비용 재산정
			minCost = min(minCost, cost + costMatrix[prev][0]);
		}
	}

	cout << minCost;

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}