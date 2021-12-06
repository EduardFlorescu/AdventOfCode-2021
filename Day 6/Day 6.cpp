#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<long long> split(string line, string delimiters = ",./;")
{
	vector<long long> words;

	int index = line.find_first_of(delimiters);
	words.push_back(stoi(line.substr(0, index)));

	while (index != -1) {
		index++;
		line = line.substr(index, line.length() - index);
		index = line.find_first_of(delimiters);
		auto newWord = line.substr(0, index);
		if (!newWord.empty())
			words.push_back(stoi(newWord));
	}
	return words;
}

void solutionPart1Part2(map<int, unsigned long long> lanternfish) {
	int day = 0;
	int stop = 256;
	unsigned long long sum = 0;
	while (day < stop) {
		for (int i = 0; i <= 8; i++)
		{
			lanternfish[i - 1] = lanternfish[i];
		}
		lanternfish[6] += lanternfish[-1];
		lanternfish[8] = lanternfish[-1];
		lanternfish[-1] = 0;
		day++;
		if (day == 80) {
			for (auto i : lanternfish)
				sum += i.second;
			cout << "Part 1: " << sum << endl;
		}
	}
	sum = 0;
	for (auto i : lanternfish)
		sum += i.second;
	cout << "Part 2: " << sum;
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	string x;
	vector<long long>nl;
	map<int, unsigned long long> lanternfish;
	while (getline(cin, x)) {
		nl = split(x);
		for (long i = 0;i < nl.size();i++) {
			lanternfish[nl[i]]++;
		}
	}
	solutionPart1Part2(lanternfish);

	return 0;
}



