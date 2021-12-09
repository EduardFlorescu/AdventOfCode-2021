#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int calculatePart1(vector<string> lines) {
	int solutionPart1 = 0;
	for (int i = 0;i < lines.size();i++) {
		for (int j = 0;j < lines[i].size();j++) {
			bool numberIsMin = true;

			if (j - 1 >= 0) {
				if (lines[i][j - 1] < lines[i][j]) {
					numberIsMin = false;
				}
			}
			if (j + 1 < lines[i].size()) {
				if (lines[i][j + 1] < lines[i][j]) {
					numberIsMin = false;
				}
			}
			if (i + 1 < lines.size()) {
				if (lines[i + 1][j] < lines[i][j]) {
					numberIsMin = false;
				}
			}
			if (i - 1 >= 0) {
				if (lines[i - 1][j] < lines[i][j]) {
					numberIsMin = false;
				}
			}
			if (i - 1 >= 0 && j - 1 >= 0) {
				if (lines[i - 1][j - 1] < lines[i][j]) {
					numberIsMin = false;
				}
			}
			if (i - 1 >= 0 && j + 1 < lines[i].size()) {
				if (lines[i - 1][j + 1] < lines[i][j]) {
					numberIsMin = false;
				}
			}
			if (i + 1 < lines.size() && j - 1 >= 0) {
				if (lines[i + 1][j - 1] < lines[i][j]) {
					numberIsMin = false;
				}
			}
			if (i + 1 < lines.size() && j + 1 < lines[i].size()) {
				if (lines[i + 1][j + 1] < lines[i][j]) {
					numberIsMin = false;
				}
			}
			if (numberIsMin) {
				solutionPart1 += (lines[i][j] - '0') + 1;
			}
		}
	}
	return solutionPart1;
}

int calculatePart2(vector<string> lines) {
	vector<int>sizeBasins;
	queue<pair<int, int>> q;
	vector<vector<int>> matrixTrack(lines.size(), vector<int>(lines[0].size(), 0));
	int countElements = 0;
	for (int i = 0;i < lines.size();i++) {
		for (int j = 0;j < lines[i].size();j++) {
			int countElements = 0;
			if (lines[i][j] != '9' && matrixTrack[i][j] == 0) {
				matrixTrack[i][j] == 1;
				q.push(make_pair(i, j));

				while (!q.empty()) {
					pair<int, int> posNumber = q.front();
					int i2 = posNumber.first;
					int j2 = posNumber.second;
					q.pop();
					if (j2 - 1 >= 0 && matrixTrack[i2][j2 - 1] == 0 && lines[i2][j2 - 1] != '9') {
						matrixTrack[i2][j2 - 1] = 1;
						q.push(make_pair(i2, j2 - 1));
						countElements++;
					}
					if (j2 + 1 < lines[i2].size() && matrixTrack[i2][j2 + 1] == 0 && lines[i2][j2 + 1] != '9') {
						matrixTrack[i2][j2 + 1] = 1;
						q.push(make_pair(i2, j2 + 1));
						countElements++;
					}
					if (i2 + 1 < lines.size() && matrixTrack[i2 + 1][j2] == 0 && lines[i2 + 1][j2] != '9') {
						matrixTrack[i2 + 1][j2] = 1;
						q.push(make_pair(i2 + 1, j2));
						countElements++;
					}
					if (i2 - 1 >= 0 && matrixTrack[i2 - 1][j2] == 0 && lines[i2 - 1][j2] != '9') {
						matrixTrack[i2 - 1][j2] = 1;
						q.push(make_pair(i2 - 1, j2));
						countElements++;
					}
				}
				sizeBasins.push_back(countElements);
			}
		}
	}
	sort(sizeBasins.rbegin(), sizeBasins.rend());
	return sizeBasins[0] * sizeBasins[1] * sizeBasins[2];
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	vector<string> lines;
	int solutionPart1, solutionPart2;
	string s;
	while (cin >> s) {
		lines.push_back(s);
	}
	solutionPart1 = calculatePart1(lines);
	solutionPart2 = calculatePart2(lines);

	cout << "Part 1: " << solutionPart1 << endl << "Part 2: " << solutionPart2;
	return 0;
}