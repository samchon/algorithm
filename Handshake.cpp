#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * 정올, 악수
 * http://jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=518&sca=30a0
 *
 * @author Samchon <http://samchon.org>
 */
class Handshake
{
private:
	/**
	 * 선호 브랜드를 담은 배열.
	 *
	 * index: 참가자 번호
	 * value: 선호 브랜드
	 */
	vector<size_t> brandArray;

	/**
	 * Dynamic 계산을 위한 매트릭스.
	 *
	 * 각각의 악수 결과를 저장해둔다.
	 */
	vector<vector<size_t>> handshakeMatrix;

public:
	/**
	 * Default Constructor.
	 */
	Handshake()
	{
		size_t brandSize;
		cin >> brandSize;

		brandArray.assign(brandSize, 0);
		handshakeMatrix.assign(brandSize, vector<size_t>(brandSize, -1));

		for (size_t i = 0; i < brandSize; i++)
			cin >> brandArray[i];
	};

	/**
	 * 같은 브랜드 간 악수할 수 있는 최대값을 구함
	 */
	auto calc() const -> size_t
	{
		return calc(0, brandArray.size());
	};

private:
	/**
	 * 일정 범위 내 같은 브랜드 간 악수할 수 있는 최대값을 구함.
	 *
	 * 팔이 교차하여 악수하는 경우가 생기지 않게끔
	 * 분할하여 악수 횟수를 계산한다.
	 */
	auto calc(size_t begin, size_t end) const -> size_t
	{
		if (begin >= end)
		{
			// 범위를 벗어나는 계산
			return 0;
		}
		else  if (handshakeMatrix[begin][end - 1] != -1)
		{
			// 이미 계산한 결과
			return handshakeMatrix[begin][end - 1];
		}

		size_t handshake = 0;
		for (size_t i = begin + 1; i < end; i += 2)
		{
			size_t myHandshake =
				(brandArray[begin] == brandArray[i] ? 1 : 0) // 같은 브랜드이니 악수함, 1회.
				+ calc(begin + 1, i) + calc(i + 1, end);
					// i를 기준으로 양쪽으로 쪼개어 계산해나감
					// 악수가 교차하여 생기지 않게 하기 위하여, 양쪽으로 쪼개어
					// 재귀적으로 계산해나가는 것이다.

			handshake = max(handshake, myHandshake);
		}

		// 미세한 시간초과 (1.018초) 를 피하기 위해 const와 함께 달아놓은 장치일 뿐,
		// 실제로는 { handleshake[begin][end-1] = handshake; } 이다.
		((vector<vector<size_t>>&)handshakeMatrix)[begin][end - 1] = handshake;
		return handshake;
	};
};

int main()
{
	Handshake handshake;

	cout << handshake.calc() << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}