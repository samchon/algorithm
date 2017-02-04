#include <iostream>
#include <stack>
using namespace std;

int counter = 0;
int m;
stack<int> Peg[5];

void Move(int i, int j)
{
	if (Peg[i].top() <= Peg[j].top() /*&& (i*j != 2)*/)
	{
		Peg[j].push(Peg[i].top());
		Peg[i].pop();
		counter++;
		if (m <= 5)
			cout << "move disk " << i << " to " << j << " Moves: " << counter << endl;
	}
	else cout << "invalid";
}

void Hanoi(int n, int from, int to, int aux)
{
	if (n>0)
	{
		Hanoi(n - 1, from, aux, to);
		Move(from, to);
		Hanoi(n - 1, aux, to, from);
	}
}


int main()
{
	int n = 0;
	counter = 0;

	cout << "Please enter a number between 1 and 100: ";
	cin >> n;

	m = n;
	cout << endl;
	cout << "OK. Run Towers of Hanoi puzzle with " << n << " disks:" << endl;
	cout << endl;
	Peg[0].push(n + 1);
	Peg[1].push(n + 1);
	Peg[2].push(n + 1);
	Peg[3].push(n + 1);
	Peg[4].push(n + 1);

	for (int x = n; x > 0; x--)
	{
		Peg[1].push(x);
	}

	Hanoi(n, 1, 2, 3);

	//Simple_long(n,1,2,3,4);

	cout << endl;
	cout << "That took " << counter << " moves." << endl;
	cout << endl;

	system("pause");
	return 0;
}