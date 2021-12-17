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

vector<pair<int, int>> targetPoints;
vector<string> targets;

void highestYPart1(int velocityX, int velocityY) {
	int probX = 0, probY = 0;

	while (true) {
		if (velocityY == 0) {
			cout << "Part 1: " << abs(probY) << endl;
			break;
		}
		probX += velocityX;
		if (velocityY > 0) {
			probY -= velocityY;
		}
		else if (velocityY < 0) {
			probY += abs(velocityY);
		}

		if (velocityX > 0) {
			velocityX--;
		}
		else if (velocityX < 0) {
			velocityX++;
		}
		velocityY--;
	}
}

bool isInTrajectoryPart2(int velocityX, int velocityY) {
	int probX = 0, probY = 0, count = 0;

	while (!(probX >= targetPoints[0].first && probX <= targetPoints[0].second && probY <= targetPoints[1].second && probY >= targetPoints[1].first) && count < 1000) {

		probX += velocityX;
		probY += velocityY;

		if (velocityX < 0)
		{
			velocityX++;
		}
		else if (velocityX > 0)
		{
			velocityX--;
		}
		velocityY--;
		count++;
	}
	if (count < 1000) {
		return true;
	}

	return false;
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	string s;
	int count = 0;

	while (getline(cin, s)) {
		targets = split(s, " :=.,");
		targetPoints.push_back({ stoi(targets[3]),stoi(targets[4]) });
		targetPoints.push_back({ stoi(targets[6]),stoi(targets[7]) });
	}

	for (int i = 1;i <= targetPoints[0].second;i++) {
		for (int j = targetPoints[1].first;j <= abs(targetPoints[1].first);j++) {
			if (isInTrajectoryPart2(i, j)) {
				count++;
			}
		}
	}

	highestYPart1(((targetPoints[0].second - targetPoints[0].first) / 2) + 1, abs(targetPoints[1].first) - 1);
	cout << "Part 2: " << count;

	return 0;
}