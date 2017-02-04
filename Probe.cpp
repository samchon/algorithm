#include <iostream>
#include <vector>
#include <string>

#define BOOL char
#define UNKNOWN -1

using namespace std;

/**
 * Ž�� Ŭ����.
 */
class Probe
{
public:
	/**
	 * Ž�� ���� ����
	 */
	int begin;

	/**
	 * Ž�� �� ���� + 1
	 */
	int end;

	/**
	 * Ž�籸�� �� ��ü�� ��
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
	 * ������ Ž�籸���� ������� �˻��Ѵ�
	 * ������ �ŵ��Ͽ� Ž�籸���� ��� �Ҹ�� ��� true.
	 */
	auto empty() const -> bool
	{
		return begin < 0 || begin == end;
	};

	/**
	 * ���� Ž�� ������ Ÿ ������ �����ϴ°�
	 */
	auto includes(const Probe &obj) const -> bool
	{
		return (begin <= obj.begin && obj.end <= end);
	};

	/**
	 * �� Ž�籸���� ������ �ִ°�
	 */
	auto intersects(const Probe &obj) const -> bool
	{
		return !(begin > obj.end || obj.begin > end);
	};

	/**
	 * �������� ����
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
	 * ���� �Է� �� ������ ����.
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
			// Ž�籸�� �Է�
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
	 * �� ���� Ž�� ������ ���� ������ ��.
	 */
	void query(Probe &probe)
	{
		if (probe.size == 0)
		{
			// Ž�� ���� �� ��ü�� ����
			for (int i = probe.begin; i < probe.end; i++)
				this->determine(i, false);

			change_flag = true;
		}
		else if (probe.end - probe.begin == probe.size)
		{
			// Ž�� ���� ���̿� ���� �� ��ü ���� ��ġ��
			for (int i = probe.begin; i < probe.end; i++)
				this->determine(i, true);

			change_flag = true;
		}
	};

	/**
	 * �� Ž�籸���� ���� ������ ��.
	 * �� Ž�籸�� ������ Ȯ�������� ã�ų� �����ϰų� ��.
	 *
	 * @param left �º�
	 * @param right �캯
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
		//		// ���� �������� 1���� ��ü�� �ְ�, ������ ���� ���� �������� �����Ѵ�
		//		// �� �� ������ ������ ��� ��ü�� ���� (size := 0) ���� �ȴ�
		//		const vector<Probe> &differences = left.difference(right, 0);

		//		probeArray.insert(probeArray.begin(), differences.begin(), differences.end());
		//	}
		//}
		//else 
		if (left.includes(right))
		{
			if (left.size == right.size)
			{
				// ��ü�� ���� (size := 0) �� �������� �����
				const auto &differences = left.difference(right, 0);
				probeArray.insert(probeArray.begin(), differences.begin(), differences.end());

				change_flag = true;
			}
			else if (left.begin == right.begin)
			{
				// left �� ���� ���
				left.begin = right.end;
				left.size -= right.size;

				change_flag = true;
			}
			else if (left.end == right.end)
			{
				// left �� ���� ���
				left.end = right.begin;
				left.size -= right.size;

				change_flag = true;
			}
		}
	};

	/**
	 * index ��° (in indexArray) ������ ��ü ������ Ȯ����
	 *
	 * @param index indexArray�� index ��ȣ
	 * @param value ��ü�� ���� ����
	 */
	void determine(int index, bool value)
	{
		// index ��° ������ Ȯ��
		this->at(indexArray.at(index)) = value;
		
		// ���� ��ȣ �������� ����
		indexArray.erase(indexArray.begin() + index);

		for (int i = 0; i < probeArray.size(); i++)
		{
			// �� Ž�翵���� ����Ű�� ���� ���
			Probe &probe = probeArray.at(i);

			if (probe.begin <= index && index < probe.end)
			{
				// Ȯ�� ������ �� Ž�翵���� �ش���
				if (index == probe.begin)
					probe.begin--;
				probe.end--;

				// ��ü ���� ���
				if (value == true)
					probe.size--;
			}
			else if (probe.begin >= index)
			{
				// �� Ž�翵���� Ȯ���� �������� �� �޹�ȣ
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