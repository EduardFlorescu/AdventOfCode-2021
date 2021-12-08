#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

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
		{
			words.push_back(newWord);
		}
	}
	return words;
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	string line;
	vector<string> first10Strings;
	vector<string> last4Strings;
	int count = 0;

	int resultPart1 = 0;

	map<string, int> original{
		{"abcefg",0},{"cf",1},{"acdeg",2},{"acdfg",3},
		{"bcdf",4},{"abdfg",5},{"abdefg",6},{"acf",7},{"abcdefg",8},{"abcdfg",9}
	};
	long long resultPart2 = 0;
	while (getline(cin, line)) {
		map<char, char> m;
		map<char, int> fr;
		//citim clean;
		auto words = split(line, "| ");
		string one, four, seven, eight;
		for (int i = 0;i < 10;i++) {
			for (char letter : words[i])
			{
				fr[letter]++;
			}
			if (words[i].size() == 2)
			{
				one = words[i];
			}
			else if (words[i].size() == 4)
			{
				four = words[i];
			}
			else if (words[i].size() == 3)
			{
				seven = words[i];
			}
			else if (words[i].size() == 7)
			{
				eight = words[i];
			}
			sort(words[i].begin(), words[i].end());
			first10Strings.push_back(words[i]);
		}

		for (auto f : fr) {
			if (f.second == 6) {
				m[f.first] = 'b';
			}
		}
		for (auto c : one) {
			if (fr[c] == 8)
			{
				m[c] = 'c';
			}
			if (fr[c] == 9)
			{
				m[c] = 'f';
			}
		}

		for (auto c : four) {
			if (fr[c] == 8) {
				m[c] = 'c';
				fr[c] = 0;
			}
			if (fr[c] == 7) {
				m[c] = 'd';
				fr[c] = 0;
			}

		}

		for (auto c : eight) {
			if (fr[c] == 7)
			{
				m[c] = 'g';
				fr[c] = 0;
			}
			if (fr[c] == 4)
			{
				m[c] = 'e';
				fr[c] = 0;
			}
			if (fr[c] == 8)
			{
				m[c] = 'a';
				fr[c] = 0;
			}
		}

		int number = 0;
		for (int i = 10;i < 14;i++) {
			string mapped = "";
			for (char letter : words[i]) {
				mapped += m[letter];
			}
			sort(mapped.begin(), mapped.end());
			int x = original[mapped];
			if (x == 1 || x == 4 || x == 7 || x == 8)
			{
				resultPart1++;
			}
			number = number * 10 + original[mapped];

			last4Strings.push_back(words[i]);
		}
		resultPart2 += number;
	}

	cout << "Part 1: " << resultPart1 << endl << "Part 2: " << resultPart2;
	return 0;
}

