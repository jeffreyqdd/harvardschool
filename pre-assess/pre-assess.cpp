/*
Name: Jeffrey Qian
Language: C++
*/

#include <iostream>
#include <vector>
#include <limits>
#include <ios>
#include <algorithm>
using namespace std;


void SolveWithArray()
{
	//dynamic array
	vector<double> user_num;

	while (true)
	{
		double n;
		cout << "Enter a positive number or -1 to exit\n";

		//limits input to numbers only
		if(!(cin >> n))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again\n";
			continue;
		}
		
		//case handling, -1, invalid number, and positive number	
		if (n == -1)
			break;
		else if (n < 0)
			cout << "Not a positive number\n";
		else
			user_num.push_back(n);			

	}
	
	//sort
	sort(user_num.begin(), user_num.end());

	//print
	if(user_num.size() == 0)
		cout << "Sorry, the array is empty\n";
	else
		cout << "You entered " << user_num.size() << " numbers. "
		<< "smallest number entered: " << user_num.front() <<
		" largest number entered: "<< user_num.back() << endl;

	return;
}

void SolveWithoutArray()
{
	//max and min
	double max_num = -1;
	double min_num = -1;
	double entered = 0;

	while (true)
	{
		double n;
		cout << "Enter a positive number or -1 to exit\n";
		
		if(!(cin >> n))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again\n";
			continue;
		}
		
		if (n == -1)
			break;
		else if (n < 0)
			cout << "Not a positive number\n";
		else
		{
			max_num = max(max_num, n);

			if(min_num == -1)
				min_num = n;
			else 
				min_num = min(min_num, n);

			entered++;
		}
			
	}
	
	if(entered == 0)
		cout << "Sorry, you entered 0 valid numbers\n";
	else
		cout << "You entered " << entered << " numbers. "
		<< "smallest number entered: " << min_num <<
		" largest number entered: "<< max_num << endl;


	return;
}

int main()
{
	//ask user for positive numbers, repeat until user enters -1

	SolveWithArray();

	SolveWithoutArray();

	return 0;
}
