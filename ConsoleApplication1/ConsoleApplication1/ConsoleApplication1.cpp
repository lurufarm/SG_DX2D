#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


void func(vector<int> v)
{
	static int index = 0;
	static bool back = false;
	cout << v[index] << endl;

	if (index == v.size() - 1)
	{
		back = true;
	}

	if (back == false)
	{
		index++;
		func(v);
	}
	else
	{
		index--;
		if (index < 0)
			return;
		func(v);
	}

}


void main()
{
	vector<int>v = { 3,5,4,6,2,9 };
	func(v);
}