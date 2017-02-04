#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Building
{
public:
	int index;
	int height;
	Building *sight;

public:
	Building(int index, int height)
	{
		this->index = index;
		this->height = height;

		this->sight = nullptr;
	};

	void print() const
	{
		if (sight == nullptr)
			cout << 0 << endl;
		else
			cout << sight->index << endl;
	};
};

int main()
{
	// -------------------------------------
	//	CONSTRUCT BUILDINGS
	// -------------------------------------
	vector<Building> buildingArray;
	int size;

	cin >> size;
	buildingArray.reserve(size);

	for (int i = 1; i <= size; i++)
	{
		int height;
		cin >> height;

		buildingArray.push_back(Building(i, height));
	}

	// -------------------------------------
	//	CALCULATE SIGHT
	// -------------------------------------
	stack<Building*> maxStack;
	maxStack.push(&buildingArray.front());

	for (size_t i = 1; i < buildingArray.size(); i++)
	{
		Building &building = buildingArray[i];
		
		while (maxStack.top()->height < building.height)
		{
			maxStack.top()->sight = &building;
			maxStack.pop();

			if (maxStack.empty() == true)
				break;
		}
		maxStack.push(&building);
	}

	//Building *max = &buildingArray.back();

	//for (int i = size - 1; i >= 0; i--)
	//{
	//	Building &building = buildingArray[i];

	//	if (building.height >= max->height)
	//	{
	//		// CURRENT BUILDING'S HEIGHT IS THE GREATEST
	//		building.sight = nullptr; // SO CANNOT SEE ANYTHING
	//		max = &building; // AND ITS THE MAX
	//	}
	//	else
	//		building.sight = max;
	//}

	// -------------------------------------
	//	PRINT THE RESULT
	// -------------------------------------
	for (int i = 0; i < buildingArray.size(); i++)
		buildingArray[i].print();

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}