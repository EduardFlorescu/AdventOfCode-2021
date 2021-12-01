#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;

int countIncreasedValues(vector<int> measurement) {
	int count = 0;
	for (int i = 1; i < measurement.size(); i++) {

		if (measurement[i] > measurement[i - 1])
		{
			count++;
		}
	}
	return count;
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	int x, count = 0, sum = 0;
	vector<int> measurement, measurementSum;

	while (cin >> x) {
		measurement.push_back(x);
	}

	for (int i = 0; i < measurement.size() - 2; i++) {
		measurementSum.push_back(measurement[i] + measurement[i + 1] + measurement[i + 2]);
	}

	cout << "Part 1: " << countIncreasedValues(measurement) << endl << "Part 2: " << countIncreasedValues(measurementSum);
}
