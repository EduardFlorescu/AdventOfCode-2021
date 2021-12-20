#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string imageEnh;

vector<int> lin{ -1, -1, -1, 0, 0, 0, 1, 1, 1 };
vector<int> col{ -1, 0 , 1, -1, 0, 1, -1, 0 , 1 };

vector<string> input;
vector<string> output;

void Solution() {
	int count = 0;
	for (int i = 0;i < input.size(); i++) {
		for (int j = 0;j < input[i].size(); j++)
		{
			if (input[i][j] == '#')
			{
				count++;
			}
		}
	}
	cout << count << endl;
}

void trimMatrix(vector<string>& input, int i1, int i2, int j1, int j2)
{
	vector<string> newInput;
	int line = 0;
	for (auto& i : input)
	{
		if (line >= i1 && line <= i2)
		{
			newInput.push_back(i.substr(j1, j2 - j1 + 1));
		}
		line++;
	}
	input = newInput;
}

void addPadding(vector<string>& input, int n)
{
	string paddingMargin(n, '.');
	string paddingLine(n * 2 + input[0].size(), '.');
	for (auto& i : input)
	{
		i = paddingMargin + i + paddingMargin;
	}

	for (int i = 0; i < n; i++)
	{
		input.insert(input.begin(), paddingLine);
		input.push_back(paddingLine);
	}
}
int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	string s;
	cin >> imageEnh;

	while (getline(cin, s)) {
		if (!s.empty()) {
			input.push_back(s);
		}
	}

	int cnt = 0;
	addPadding(input, 100);
	while (cnt < 50) {
		output = input;
		for (int i = 0;i < input.size();i++) {
			for (int j = 0;j < input[i].size();j++)
			{
				string binary = "";
				for (int k = 0;k < lin.size();k++) {
					int x = i + lin[k];
					int y = j + col[k];
					if (x >= 0 && x < input.size() && y >= 0 && y < input[i].size()) {
						if (input[x][y] == '.') {
							binary += "0";
						}
						else if (input[x][y] == '#') {
							binary += "1";
						}
					}
				}
				int pos = stoi(binary, 0, 2);

				output[i][j] = imageEnh[pos];

			}
		}

		cnt++;
		input = output;
		trimMatrix(input, 1, input.size() - 2, 1, input[0].size() - 2);
		if (cnt == 2 || cnt == 50) {
			Solution();
		}
	}

	return 0;
}