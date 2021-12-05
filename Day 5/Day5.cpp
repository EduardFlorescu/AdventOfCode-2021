#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> split(string line, string delimiters = ",./;")
{
	vector<int> words;

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
void calculateMatrixLinear(map<pair<int, int>, int>& matrixTrack, int start, int end, int stay, bool lineC) {
	if (lineC) {
		if (start < end) {
			for (int i = start;i <= end;i++) {
				matrixTrack[{stay, i}] += 1;
			}
		}
		else {
			for (int i = start;i >= end;i--) {
				matrixTrack[{stay, i}] += 1;
			}
		}
	}
	else {
		if (start < end) {
			for (int i = start;i <= end;i++) {
				matrixTrack[{i, stay}] += 1;
			}
		}
		else {
			for (int i = start;i >= end;i--) {
				matrixTrack[{i, stay}] += 1;
			}
		}
	}
}
void calculateMatrixDiagonal(map<pair<int, int>, int>& matrixTrack, pair<int, int>x1y1, pair<int, int>x2y2) {

	if (x1y1.first == x1y1.second && x2y2.first == x2y2.second) {
		if (x1y1.first < x2y2.first) {
			for (int i = x1y1.first;i <= x2y2.first;i++) {
				matrixTrack[{i, i}]++;
			}
		}
		else {
			for (int i = x2y2.first;i <= x1y1.first;i++) {
				matrixTrack[{i, i}]++;
			}
		}
	}
	else {
		int x, y;
		x = x1y1.first;
		y = x1y1.second;
		if (x1y1.first > x2y2.first && x1y1.second > x2y2.second) {
			for (int i = 0;i <= abs(x1y1.first - x2y2.first);i++) {
				matrixTrack[{y - i, x - i}]++;
			}
		}
		else if (x1y1.first < x2y2.first && x1y1.second < x2y2.second) {
			for (int i = 0;i <= abs(x1y1.first - x2y2.first);i++) {
				matrixTrack[{ y + i, x + i}]++;
			}
		}
		else if (x1y1.first > x2y2.first && x1y1.second < x2y2.second) {
			for (int i = 0;i <= abs(x1y1.first - x2y2.first);i++) {
				matrixTrack[{y + i, x - i}]++;
			}
		}
		else if (x1y1.first < x2y2.first && x1y1.second > x2y2.second) {
			for (int i = 0;i <= abs(x1y1.first - x2y2.first);i++) {
				matrixTrack[{y - i, x + i}]++;
			}
		}
	}
}
int calculatePart1(vector<pair<int, int>>x1y1, vector<pair<int, int>>x2y2, map<pair<int, int>, int> matrixTrack) {
	for (int i = 0;i < x1y1.size();i++) {
		if (x1y1[i].first == x2y2[i].first) {
			calculateMatrixLinear(matrixTrack, x1y1[i].second, x2y2[i].second, x1y1[i].first, false);
		}
		else if (x1y1[i].second == x2y2[i].second) {
			calculateMatrixLinear(matrixTrack, x1y1[i].first, x2y2[i].first, x1y1[i].second, true);
		}
	}
	int count = 0;
	for (auto i : matrixTrack) {
		if (i.second > 1) {
			count++;
		}
	}
	return count;
}
int calculatePart2(vector<pair<int, int>>x1y1, vector<pair<int, int>>x2y2, map<pair<int, int>, int> matrixTrack) {
	for (int i = 0;i < x1y1.size();i++) {
		if (x1y1[i].first == x1y1[i].second && x2y2[i].first == x2y2[i].second) {
			calculateMatrixDiagonal(matrixTrack, x1y1[i], x2y2[i]);
		}
		else {
			if (x1y1[i].first == x2y2[i].first) {
				calculateMatrixLinear(matrixTrack, x1y1[i].second, x2y2[i].second, x1y1[i].first, false);
			}
			else if (x1y1[i].second == x2y2[i].second) {
				calculateMatrixLinear(matrixTrack, x1y1[i].first, x2y2[i].first, x1y1[i].second, true);
			}
			else {
				calculateMatrixDiagonal(matrixTrack, x1y1[i], x2y2[i]);
			}
		}
	}
	int count = 0;
	for (auto i : matrixTrack) {
		if (i.second > 1) {
			count++;
		}
	}
	return count;
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	vector<pair<int, int>>x1y1, x2y2;
	vector<int>numbers;
	string number1, number2, sign;
	map<pair<int, int>, int> matrixTrack;

	while (cin >> number1 >> sign >> number2) {
		numbers = split(number1);
		x1y1.push_back(make_pair(numbers[0], numbers[1]));
		numbers = split(number2);
		x2y2.push_back(make_pair(numbers[0], numbers[1]));
	}
	cout << "Part 1: " << calculatePart1(x1y1, x2y2, matrixTrack) << endl << "Part 2: " << calculatePart2(x1y1, x2y2, matrixTrack);

	return 0;
}