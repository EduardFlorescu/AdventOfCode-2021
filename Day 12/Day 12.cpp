#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<string, string>>connections;

vector<string> split(string line, string delimiters = ",./;")
{
	vector<string> words;

	int index = line.find_first_of(delimiters);
	if (!line.substr(0, index).empty()) {
		words.push_back(line.substr(0, index));
	}
	while (index != -1) {
		index++;
		line = line.substr(index, line.length() - index);
		index = line.find_first_of(delimiters);
		auto newWord = line.substr(0, index);
		if (!newWord.empty())
			words.push_back(newWord);
	}
	return words;
}

bool doesPathContainsThisString(vector<string> path, string s) {
	if (find(path.begin(), path.end(), s) != path.end()) {
		return true;
	}
	return false;
}


bool twoOccurrences(vector<string> path) {
	for (int i = 0;i < path.size() - 1;i++)
		for (int j = i + 1;j < path.size();j++)
			if (path[i] == path[j] && islower(path[i][0]))
				return false;
	return true;
}

int nrPart1 = 0;
int nrPart2 = 0;

void getAllPathsPart1(string start, vector<string> path) {
	path.push_back(start);
	if (start == "end")
	{
		nrPart1++;
	}
	for (auto i : connections) {
		if (i.first == start) {
			if (islower(i.second[0])) {
				if (!doesPathContainsThisString(path, i.second)) {
					getAllPathsPart1(i.second, path);
				}
			}
			else {
				getAllPathsPart1(i.second, path);
			}
		}
	}
}

void getAllPathsPart2(string start, vector<string> path) {
	path.push_back(start);
	if (start == "end")
	{
		nrPart2++;
	}
	for (auto i : connections) {
		if (i.first == start) {
			if (islower(i.second[0])) {
				if (!doesPathContainsThisString(path, i.second)) {
					getAllPathsPart2(i.second, path);
				}
				else if (twoOccurrences(path)) {
					getAllPathsPart2(i.second, path);
				}
			}
			else {
				getAllPathsPart2(i.second, path);
			}
		}
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	string s;
	vector<string> lines;

	while (cin >> s) {
		lines = split(s, "-");
		if (lines[1] == "start") {
			connections.push_back({ lines[1],lines[0] });
		}
		else if (lines[0] == "end") {
			connections.push_back({ lines[1],lines[0] });
		}
		else if (lines[0] == "start" || lines[0] == "end" || lines[1] == "start" || lines[1] == "end") {
			connections.push_back({ lines[0],lines[1] });
		}
		else {
			connections.push_back({ lines[0],lines[1] });
			connections.push_back({ lines[1],lines[0] });
		}
	}
	vector<string> path;
	getAllPathsPart1("start", path);
	getAllPathsPart2("start", path);
	cout << "Part1: " << nrPart1 << endl << "Part2: " << nrPart2 << endl;

	return 0;
}