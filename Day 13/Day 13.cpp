#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void replaceAll(string& s, const string& search, const string& replace)
{
	for (size_t pos = 0; ; pos += replace.length())
	{
		// Locate the substring to replace
		pos = s.find(search, pos);
		if (pos == string::npos) break;
		// Replace by erasing and inserting
		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
}

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

void foldX(map<pair<int, int>, char>& points, int posFold) {
	map<pair<int, int>, char> points2;
	for (auto p : points) {
		if (p.first.second > posFold) {
			if (points.find({ p.first.first,(posFold - (p.first.second - posFold)) }) != points.end()) {
				points2[{ p.first.first, (posFold - (p.first.second - posFold)) }] = '.';
			}
			else {
				points2[{ p.first.first, (posFold - (p.first.second - posFold)) }] = '#';
			}
		}
		else {
			points2.insert(p);
		}
	}
	points.clear();
	points = points2;
}

void foldY(map<pair<int, int>, char>& points, int posFold) {
	map<pair<int, int>, char> points2;
	for (auto p : points) {
		if (p.first.first > posFold) {
			if (points.find({ (posFold - (p.first.first - posFold)),p.first.second }) != points.end()) {
				points2[{ (posFold - (p.first.first - posFold)), p.first.second }] = '#';
			}
			else {
				points2[{ (posFold - (p.first.first - posFold)), p.first.second }] = '#';
			}
		}
		else {
			points2.insert(p);
		}
	}
	points.clear();
	points = points2;
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	string s;
	vector<pair<int, int>> coordonates;
	vector<pair<string, int>> folds;
	map<pair<int, int>, char> points;
	map<pair<int, int>, char >::iterator it;

	while (getline(cin, s)) {
		if (s.find("fold") != std::string::npos) {
			replaceAll(s, "fold along ", "");
			vector<string> temp = split(s, "=");
			folds.push_back({ temp[0],stoi(temp[1]) });
		}
		else if (s.find(",") != std::string::npos) {
			coordonates.push_back({ stoi(s.substr(s.find(",") + 1)),stoi(s.substr(0,s.find(","))) });
		}
	}
	for (int i = 0;i < coordonates.size();i++) {
		points[{coordonates[i].first, coordonates[i].second}] = '#';
	}

	for (int i = 0;i < folds.size();i++) {
		int posFold = folds[i].second;
		string direction = folds[i].first;
		if (direction == "y") {
			foldY(points, posFold);
		}
		else {
			foldX(points, posFold);
		}
		if (i == 0) {
			cout << "Part 1: " << points.size() << endl;
		}
	}
	cout << endl << "Part 2: " << endl;
	for (int i = 0;i <= 50;i++) {
		for (int j = 0;j <= 50;j++) {
			if (points[{i, j}] == 0)
			{
				cout << ".";
			}
			else {
				cout << points[{i, j}];
			}
		}
		cout << endl;
	}

	return 0;
}

