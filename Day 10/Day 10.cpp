#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

long long calculateSumPart1(map<char, int>fr) {
	long long sum = 0;
	for (auto f : fr) {
		if (f.first == ')')
		{
			sum = sum + f.second * 3;
		}
		else if (f.first == ']')
		{
			sum = sum + f.second * 57;
		}
		else if (f.first == '}')
		{
			sum = sum + f.second * 1197;
		}
		else if (f.first == '>')
		{
			sum = sum + f.second * 25137;
		}
	}
	return sum;
}

long long calculateSumPart2(string remainingBr) {
	long long sum = 0;
	for (int i = remainingBr.size() - 1;i >= 0;i--) {
		sum = sum * 5;
		if (remainingBr[i] == '(')
		{
			sum = sum + 1;
		}
		else if (remainingBr[i] == '[')
		{
			sum = sum + 2;
		}
		else if (remainingBr[i] == '{')
		{
			sum = sum + 3;
		}
		else if (remainingBr[i] == '<')
		{
			sum = sum + 4;
		}
	}
	return sum;
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	string s;
	vector<char> openBr, closedBr;
	map<char, int>fr;
	vector<string> incompleteLines;
	vector<long long> sumPart2;

	while (getline(cin, s)) {
		for (int i = 0;i < s.size();i++) {
			if (s[i] == '(' || s[i] == '[' || s[i] == '{' || s[i] == '<') {
				openBr.push_back(s[i]);
			}
			else {
				char brLeft = openBr[openBr.size() - 1];
				char brRight = s[i];
				if ((brLeft == '[' && brRight == ']') || (brLeft == '(' && brRight == ')') || (brLeft == '{' && brRight == '}') || (brLeft == '<' && brRight == '>')) {
					openBr.pop_back();
				}
				else {
					closedBr.push_back(brRight);
					break;
				}
			}
		}
		if (closedBr.size() > 0) {
			fr[closedBr[0]]++;
		}
		else {
			string remainingBr = "";
			for (auto i : openBr) {
				remainingBr += i;
			}
			sumPart2.push_back(calculateSumPart2(remainingBr));
		}
		openBr.clear();
		closedBr.clear();
	}
	sort(sumPart2.begin(), sumPart2.end());
	cout << "Part 1: " << calculateSumPart1(fr) << endl << "Part 2: " << sumPart2[(sumPart2.size() / 2)];
	return 0;
}