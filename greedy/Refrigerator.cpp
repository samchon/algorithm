#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * ���� ������ �µ� ����
 */
class Temperature
{
public:
	/**
	 * �ּ� �µ�
	 */
	int minimum;

	/**
	 * �ִ� �µ�
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
	 * ������ �µ� ������, Ÿ Temperature���� ���� �������� �����
	 */
	void shrinkToIntersect(const Temperature &obj)
	{
		this->minimum = max(this->minimum, obj.minimum);
		this->maximum = min(this->maximum, obj.maximum);
	};

	/**
	 * �µ� ����(max - min)�� ��Һ� �Լ�.
	 */
	auto operator<(const Temperature &obj) const -> bool
	{
		return (maximum - minimum) < (obj.maximum - obj.minimum);
	};
	
	/**
	 * �ٸ� �µ� ������ ��ġ�� ������ �ִ� �� �˻�.
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
	// ������ ����
	//////////////////////////////////////////
	// �� ȭ�� ������ ���� ���� �µ� ����
	vector<Temperature> temperatureArray;

	// ��� ȭ�� ������ �����ϱ� ���� �ʿ��� �µ� ����
	vector<Temperature> standardArray;
	size_t size;
	cin >> size;

	// �� ȭ�й����� �µ� ������ ����
	temperatureArray.reserve(size);
	for (size_t i = 0; i < size; i++)
	{
		int minimum;
		int maximum;
		cin >> minimum >> maximum;

		temperatureArray.push_back(Temperature(minimum, maximum));
	}

	//////////////////////////////////////////
	// ��� �� ���
	//////////////////////////////////////////
	// �� ȭ�й����� �µ� ������, ������ ũ������� ����
	sort(temperatureArray.begin(), temperatureArray.end());
	
	for (size_t i = 0; i < size; i++)
	{
		const Temperature &temparature = temperatureArray[i];
		
		bool included = false;

		// ������ �µ� ������ ���� ������ ��ġ�� �� �˻�
		for (size_t j = 0; j < standardArray.size(); j++)
		{
			Temperature &standard = standardArray[j];
			
			if (standard.intersect(temparature))
			{
				// Ư�� ���� ������ ��ģ�ٸ�, ���� ������ ������ ������ �°� �����
				standard.shrinkToIntersect(temparature);
				included = true;

				break;
			}
		}

		if (included == false)
		{
			// ������ ���� ������ ���ٸ�, �� ������ ����
			standardArray.push_back(temparature);
		}
	}

	cout << standardArray.size() << endl;

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}