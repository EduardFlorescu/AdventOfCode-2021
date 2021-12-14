#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<string> split(string line, string delimiters = ",./;= ->")
{
	vector<string> words;
	if (line.empty())
	{
		return words;
	}

	int index = line.find_first_of(delimiters);
	if (!line.substr(0, index).empty())
	{
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
	string temp;
	map<char, unsigned long long int> fr;
	map<string, string> insertion;
	while (getline(cin, line)) {
		if (line.empty())
		{
			continue;
		}
		auto words = split(line);
		if (words.size() == 1)
		{
			temp = line;
			continue;
		}
		insertion[words[0]] = words[1];
	}

	map<string, unsigned long long> insertionFr;
	for (int i = 0; i < temp.size() - 1; i++)
	{
		string s;
		s += temp[i];
		s += temp[i + 1];
		insertionFr[s] += 1;
	}

	for (int cnt = 0; cnt < 41; cnt++)
	{
		if (cnt == 10 || cnt == 40)
		{
			map<char, unsigned long long > lettersFr;
			for (auto k : insertionFr)
			{
				lettersFr[k.first[0]] += insertionFr[k.first];
			}
			lettersFr[temp[temp.size() - 1]] += 1;
			unsigned long long Min = ULLONG_MAX, Max = 0;

			for (auto i : lettersFr)
			{
				Max = max(i.second, Max);
				Min = min(i.second, Min);
			}
			cout << Max - Min << endl;
		}
		map<string, unsigned long long> insertionFr2;
		for (auto k : insertionFr)
		{
			string s;
			s += k.first[0];
			s += insertion[k.first];
			insertionFr2[s] += insertionFr[k.first];
			string s2 = insertion[k.first];
			s2 += k.first[1];
			insertionFr2[s2] += insertionFr[k.first];
		}
		insertionFr = insertionFr2;
	}
}