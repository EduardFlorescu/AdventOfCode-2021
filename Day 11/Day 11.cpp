#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<int>lin{ -1,+1,0,0,-1,-1,+1,+1 };
vector<int>col{ 0,0,-1,+1,-1,+1,+1,-1 };
int flashesPart1 = 0;
int flashesPart2 = 0;


int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	string x;
	vector<string> lines;
	while (cin >> x) {
		lines.push_back(x);
	}
	vector<vector<int>> matrix(lines.size(), vector<int>(lines[0].size(), 0));
	for (int i = 0;i < lines.size();i++) {
		for (int j = 0;j < lines[i].size();j++) {
			matrix[i][j] = lines[i][j] - '0';
		}
	}

	int count = 0;
	while (true) {
		auto m2 = matrix;
		for (int i = 0;i < matrix.size();i++) {
			for (int j = 0;j < matrix[i].size();j++) {
				if (m2[i][j] != -1) {
					matrix[i][j]++;
				}
				if (matrix[i][j] > 9) {
					m2[i][j] = -1;
					matrix[i][j] = 0;
					flashesPart2++;
					flashesPart1++;
					queue<pair<int, int>> q;
					q.push({ i,j });
					while (!q.empty()) {
						auto pos = q.front();
						q.pop();
						for (int dir = 0;dir < lin.size();dir++) {
							int x = pos.first + lin[dir];
							int y = pos.second + col[dir];
							if (x >= 0 && x < lines.size() && y >= 0 && y < lines[i].size()) {
								if (m2[x][y] != -1) {
									matrix[x][y]++;
								}
								if (matrix[x][y] > 9) {
									matrix[x][y] = 0;
									m2[x][y] = -1;
									flashesPart2++;
									flashesPart1++;
									q.push({ x,y });
								}
							}
						}
					}
				}
			}
		}
		if (count == 99) {
			cout << "Part 1: " << flashesPart1 << endl;
		}
		bool valid = true;
		for (int i = 0;i < m2.size();i++) {
			for (int j = 0;j < m2[0].size();j++) {
				if (m2[i][j] != -1)
				{
					valid = false;
					break;
				}
			}
		}
		if (valid) {
			break;
		}

		count++;
	}

	cout << "Part 2: " << count + 1;

	return 0;
}