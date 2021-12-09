#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<int>lin{ -1,+1,0,0 };
vector<int>col{ 0,0,-1,+1 };

int calculatePart1(vector<string> lines) {
	int solutionPart1 = 0;
	for (int i = 0;i < lines.size();i++) {
		for (int j = 0;j < lines[i].size();j++) {
			bool numberIsMin = true;
			for (int k = 0;k < lin.size();k++) {
				int x = i + lin[k];
				int y = j + col[k];
				if (x >= 0 && x < lines.size() && y >= 0 && y < lines[i].size()) {
					if (lines[x][y] <= lines[i][j]) {
						numberIsMin = false;
					}
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
					for (int k = 0;k < lin.size();k++) {
						int x = i2 + lin[k];
						int y = j2 + col[k];
						if (x >= 0 && x < lines.size() && y >= 0 && y < lines[i].size() && lines[x][y] != '9' && matrixTrack[x][y] == 0) {
							matrixTrack[x][y] = 1;
							q.push(make_pair(x, y));
							countElements++;
						}
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