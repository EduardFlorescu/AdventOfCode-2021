#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <regex>
#include <sstream>

using namespace std;

vector<int> split(string line, string delimiters = ",./;")
{
	vector<int> words;

	int index = line.find_first_of(delimiters);

	if (!line.substr(0, index).empty()) {
		words.push_back(stoi(line.substr(0, index)));
	}

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

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	string s;
	vector<int> crabs;
	vector<int> resultsPart1;
	vector<int> resultsPart2;
	unsigned long long sumPart1 = 0;
	unsigned long long sumPart2 = 0;
	cin >> s;
	crabs = split(s, ",");
	int count = 1;
	for (int i = 0;i < crabs.size();i++) {
		sumPart1 = 0;
		sumPart2 = 0;
		for (int j = 0;j < crabs.size();j++) {
			sumPart1 += abs(crabs[i] - crabs[j]);
			sumPart2 += (abs(crabs[j] - i) * (abs(crabs[j] - i) + 1)) / 2;
		}
		resultsPart1.push_back(sumPart1);
		resultsPart2.push_back(sumPart2);
	}
	sort(resultsPart1.begin(), resultsPart1.end());
	sort(resultsPart2.begin(), resultsPart2.end());
	cout << "Part 1: " << resultsPart1[0] << endl << "Part 2: " << resultsPart2[0];

	return 0;
}


