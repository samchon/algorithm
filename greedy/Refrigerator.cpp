#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 보관 가능한 온도 영역
 */
class Temperature
{
public:
	/**
	 * 최소 온도
	 */
	int minimum;

	/**
	 * 최대 온도
	 */
	int maximum;

	/**
	 * Construct from members
	 */
	Temperature(int minimum, int maximum)
	{
		this->minimum = minimum;
		this->maximum = maximum;
	};

	/**
	 * 현재의 온도 범위를, 타 Temperature와의 공통 영역까지 축소함
	 */
	void shrinkToIntersect(const Temperature &obj)
	{
		this->minimum = max(this->minimum, obj.minimum);
		this->maximum = min(this->maximum, obj.maximum);
	};

	/**
	 * 온도 구간(max - min)의 대소비교 함수.
	 */
	auto operator<(const Temperature &obj) const -> bool
	{
		return (maximum - minimum) < (obj.maximum - obj.minimum);
	};
	
	/**
	 * 다른 온도 범위와 겹치는 구간이 있는 지 검사.
	 */
	auto intersect(const Temperature &obj) const -> bool
	{
		return (this->minimum <= obj.minimum && obj.minimum <= this->maximum)
			|| (this->minimum <= obj.maximum && obj.maximum <= this->maximum)

			|| (obj.minimum <= this->minimum && this->minimum <= obj.maximum)
			|| (obj.minimum <= this->maximum && this->maximum <= obj.maximum);
	};
};

int main()
{
	//////////////////////////////////////////
	// 데이터 구성
	//////////////////////////////////////////
	// 각 화학 물질의 보관 가능 온도 영역
	vector<Temperature> temperatureArray;

	// 모든 화학 물질을 보관하기 위해 필요한 온도 영역
	vector<Temperature> standardArray;
	size_t size;
	cin >> size;

	// 각 화학물질의 온도 범위를 구성
	temperatureArray.reserve(size);
	for (size_t i = 0; i < size; i++)
	{
		int minimum;
		int maximum;
		cin >> minimum >> maximum;

		temperatureArray.push_back(Temperature(minimum, maximum));
	}

	//////////////////////////////////////////
	// 계산 및 출력
	//////////////////////////////////////////
	// 각 화학물질의 온도 영역을, 영역의 크기순으로 정렬
	sort(temperatureArray.begin(), temperatureArray.end());
	
	for (size_t i = 0; i < size; i++)
	{
		const Temperature &temparature = temperatureArray[i];
		
		bool included = false;

		// 현재의 온도 영역이 기준 영역과 겹치는 지 검사
		for (size_t j = 0; j < standardArray.size(); j++)
		{
			Temperature &standard = standardArray[j];
			
			if (standard.intersect(temparature))
			{
				// 특정 기준 영역과 겹친다면, 기준 영역을 새로이 교점에 맞게 축소함
				standard.shrinkToIntersect(temparature);
				included = true;

				break;
			}
		}

		if (included == false)
		{
			// 기존의 기준 영역에 없다면, 새 기준을 만듦
			standardArray.push_back(temparature);
		}
	}

	cout << standardArray.size() << endl;

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}