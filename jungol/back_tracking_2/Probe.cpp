#include <iostream>
#include <vector>
#include <string>

#define BOOL char
#define UNKNOWN -1

using namespace std;

/**
 * 탐사 클래스.
 */
class Probe
{
public:
	/**
	 * 탐사 시작 구간
	 */
	int begin;

	/**
	 * 탐사 끝 구간 + 1
	 */
	int end;

	/**
	 * 탐사구간 내 물체의 수
	 */
	int size;

public:
	/**
	 * Construct from members
	 */
	Probe(int begin, int end, int size)
	{
		this->begin = begin;
		this->end = end;

		this->size = size;
	};

	/**
	 * 현재의 탐사구간이 비었는지 검사한다
	 * 차감을 거듭하여 탐사구간이 모두 소모된 경우 true.
	 */
	auto empty() const -> bool
	{
		return begin < 0 || begin == end;
	};

	/**
	 * 현재 탐사 구간이 타 구간을 포함하는가
	 */
	auto includes(const Probe &obj) const -> bool
	{
		return (begin <= obj.begin && obj.end <= end);
	};

	/**
	 * 현 탐사구간과 교점이 있는가
	 */
	auto intersects(const Probe &obj) const -> bool
	{
		return !(begin > obj.end || obj.begin > end);
	};

	/**
	 * 차집합을 구함
	 */
	auto difference(const Probe &obj, int size = 0) const -> vector<Probe>
	{
		vector<Probe> differences;

		if (this->intersects(obj) == false)
			return differences; // NOTHING

		if (this->begin < obj.begin)
		{
			/* AAAAAA
				   BBBBBB */
			differences.push_back(Probe(this->begin, obj.begin, size));

			if (this->end > obj.end)
			{
				/* AAAAAAAAAAAAAA
					   BBBBBB */
				differences.push_back(Probe(obj.end, this->end, size));
			}
		}
		else if (this->begin > obj.begin)
		{
			/*	   AAAAAA
			   BBBBBB */
			differences.push_back(Probe(obj.begin, this->begin, size));
			
			if (this->end < obj.end)
			{
				/*	   AAAAAA
				   BBBBBBBBBBBBBB */
				differences.push_back(Probe(this->end, obj.end, size));
			}
		}

		return differences;
	};
};

class Road
	: protected vector<BOOL>
{
private:
	int instance;

	vector<int> indexArray;
	vector<Probe> probeArray;

	bool change_flag;

public:
	/**
	 * Default Constructor.
	 *
	 * 퀴즈 입력 및 데이터 구성.
	 */
	Road() : vector<BOOL>()
	{
		int size;
		cin >> size >> instance;

		this->assign(size, UNKNOWN);
		indexArray.reserve(size);

		probeArray.reserve(instance);

		for (int i = 0; i < instance; i++)
		{
			// 탐사구간 입력
			int begin, end, size;
			cin >> begin >> end >> size;

			probeArray.push_back(Probe(begin - 1, end, size));
		}

		for (int i = 0; i < size; i++)
			indexArray.push_back(i);
	};

	void probe()
	{
		change_flag = true;

		while (change_flag == true)
		{
			change_flag = false;

			for (int i = 0; i < probeArray.size(); i++)
				for (int j = 0; j < probeArray.size(); j++)
					if (i == j)
						continue;
					else
						query(probeArray[i], probeArray[j]);

			for (int i = 0; i < probeArray.size(); i++)
				query(probeArray[i]);

			for (int i = probeArray.size() - 1; i >= 0; i--)
				if (probeArray[i].empty() == true)
				{
					probeArray.erase(probeArray.begin() + i);
					change_flag = true;
				}
		}

		int size_of_instance = 0;
		vector<int> unknown_index_array;

		for (int i = 0; i < this->size(); i++)
		{
			BOOL &val = this->at(i);

			if (val == true)
				size_of_instance++;
			else if (val == UNKNOWN)
				unknown_index_array.push_back(i);
		}

		if (size_of_instance + unknown_index_array.size() == instance)
			for (int i = 0; i < unknown_index_array.size(); i++)
				this->at(unknown_index_array[i]) = true;
	};

	void print() const
	{
		string str;

		for (int i = 0; i < this->size(); i++)
			if (this->at(i) == UNKNOWN)
			{
				str = "NONE";
				break;
			}
			else
				str += (at(i) == true) ? "#" : "-";
		
		cout << str << endl;
	}

	void debug() const
	{
		for (int i = 0; i < this->size(); i++)
		{
			const BOOL &val = this->at(i);

			if (val == UNKNOWN)
				cout << '?';
			else if (val == false)
				cout << '-';
			else
				cout << '#';
		}
		cout << endl;
	};

private:
	/**
	 * 한 개의 탐사 구간에 대해 질의해 봄.
	 */
	void query(Probe &probe)
	{
		if (probe.size == 0)
		{
			// 탐사 구간 내 물체가 없음
			for (int i = probe.begin; i < probe.end; i++)
				this->determine(i, false);

			change_flag = true;
		}
		else if (probe.end - probe.begin == probe.size)
		{
			// 탐사 구간 길이와 구간 내 물체 수가 일치함
			for (int i = probe.begin; i < probe.end; i++)
				this->determine(i, true);

			change_flag = true;
		}
	};

	/**
	 * 두 탐사구간에 대해 질의해 봄.
	 * 두 탐사구간 내에서 확정사항을 찾거나 병합하거나 함.
	 *
	 * @param left 좌변
	 * @param right 우변
	 */
	void query(Probe &left, Probe &right)
	{
		//if (left.size == 1)
		//{
		//	if (left.begin == right.end - 1)
		//		this->determine(left.begin, true);
		//	else if (right.begin == left.end - 1)
		//		this->determine(right.begin, true);
		//	else if (right.size == 1 && left.intersects(right))
		//	{
		//		// 우측 영역에도 1개의 물체가 있고, 좌측과 우측 간에 교집합이 존재한다
		//		// 이 때 차집합 구간은 모두 물체가 없는 (size := 0) 것이 된다
		//		const vector<Probe> &differences = left.difference(right, 0);

		//		probeArray.insert(probeArray.begin(), differences.begin(), differences.end());
		//	}
		//}
		//else 
		if (left.includes(right))
		{
			if (left.size == right.size)
			{
				// 물체가 없는 (size := 0) 인 차집합을 만든다
				const auto &differences = left.difference(right, 0);
				probeArray.insert(probeArray.begin(), differences.begin(), differences.end());

				change_flag = true;
			}
			else if (left.begin == right.begin)
			{
				// left 의 영역 축소
				left.begin = right.end;
				left.size -= right.size;

				change_flag = true;
			}
			else if (left.end == right.end)
			{
				// left 의 영역 축소
				left.end = right.begin;
				left.size -= right.size;

				change_flag = true;
			}
		}
	};

	/**
	 * index 번째 (in indexArray) 구간의 물체 유무를 확정함
	 *
	 * @param index indexArray의 index 번호
	 * @param value 물체의 존재 여부
	 */
	void determine(int index, bool value)
	{
		// index 번째 구간을 확정
		this->at(indexArray.at(index)) = value;
		
		// 도로 번호 내역에서 지움
		indexArray.erase(indexArray.begin() + index);

		for (int i = 0; i < probeArray.size(); i++)
		{
			// 각 탐사영역이 가르키는 범위 축소
			Probe &probe = probeArray.at(i);

			if (probe.begin <= index && index < probe.end)
			{
				// 확정 구간이 현 탐사영역에 해당함
				if (index == probe.begin)
					probe.begin--;
				probe.end--;

				// 물체 수도 축소
				if (value == true)
					probe.size--;
			}
			else if (probe.begin >= index)
			{
				// 현 탐사영역이 확정된 구간보다 더 뒷번호
				probe.begin--;
				probe.end--;
			}
		}
	}
};

int main()
{
	Road road;
	road.probe();
	road.print();

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}