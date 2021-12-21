#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	string s;
	vector<string> data;
	vector<int>playerPosition;
	while (getline(cin, s)) {
		data = split(s, " :");
		playerPosition.push_back(stoi(data[4]));
	}
	int dice = 1;
	vector<int> scores;
	scores.push_back(0);
	scores.push_back(0);
	int numberOfDices = 0;
	while (scores[0] < 1000 && scores[1] < 1000) {
		for (int i = 0;i < playerPosition.size();i++) {
			int sum = 0;
			if (dice + 1 <= 100) {
				sum += dice;
				dice++;
			}
			else {
				dice = 1;
			}
			if (dice + 1 <= 100) {
				sum += dice;
				dice++;
			}
			else {
				dice = 1;
			}
			if (dice + 1 <= 100) {
				sum += dice;
				dice++;
			}
			else {
				dice = 1;
			}

			numberOfDices += 3;
			playerPosition[i] += sum;
			while (playerPosition[i] > 10) {
				playerPosition[i] -= 10;
			}
			scores[i] += playerPosition[i];
			if (scores[i] >= 1000) {
				break;
			}
		}
	}
	for (auto i : scores) {
		if (i < 1000) {
			cout << numberOfDices * i;
		}
	}
	return 0;
}