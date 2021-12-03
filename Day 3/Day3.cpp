#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int convertBinaryToNumber(string s) {
	int power = s.size()-1;
	int sum = 0;
	for (int i = 0;i < s.size();i++) {
		if (s[i] == '1') {
			sum += pow(2, power);
		}
		power--;
	}
	return sum;
}
string getGamaRate(vector<string> numbers) {
	map<int, int> mZero;
	map<int, int> mOnes;
	string gammaRate = "";

	for (auto num : numbers) {
		for (int i = 0;i < num.length();i++) {
			if (num[i] == '0') {
				mZero[i]++;
			}
			else {
				mOnes[i]++;
			}
		}
	}
	for (int i = 0;i < mZero.size();i++) {
		if (mZero[i] <= mOnes[i]) {
			gammaRate += '1';
		}
		else {
			gammaRate += '0';
		}
	}

	return gammaRate;
}

string getEpsilonRate(vector<string> numbers) {
	map<int, int> mZero;
	map<int, int> mOnes;
	string epsilonRate = "";

	for (auto num : numbers) {
		for (int i = 0;i < num.length();i++) {
			if (num[i] == '0') {
				mZero[i]++;
			}
			else {
				mOnes[i]++;
			}

		}
	}
	for (int i = 0;i < mZero.size();i++) {
		if (mZero[i] > mOnes[i]) {
			epsilonRate += '1';
		}
		else {
			epsilonRate += '0';
		}
	}


	return epsilonRate;
}

string oxygenRating(vector<string> numbers) {
	vector<string> numbersModify;
	string most;
	char ch;
	int pos = 0;
	while (numbers.size() > 1) {
		most = getGamaRate(numbers);
		for (auto num : numbers) {
			if (num[pos] == most[pos]) {
				numbersModify.push_back(num);
			}
		}
		numbers.clear();
		numbers = numbersModify;
		numbersModify.clear();
		pos++;
	}
	return numbers[0];
}

string scrubberRating(vector<string> numbers) {
	vector<string> numbersModify;
	string least;
	char ch;
	int pos = 0;
	while (numbers.size() > 1) {
		least = getEpsilonRate(numbers);
		for (auto num : numbers) {
			if (num[pos] == least[pos]) {
				numbersModify.push_back(num);
			}
		}
		numbers.clear();
		numbers = numbersModify;
		numbersModify.clear();
		pos++;
	}
	return numbers[0];
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	int lines = 0;

	vector<string> numbers;

	string s;

	while (cin >> s) {
		numbers.push_back(s);
	}

	string oxygen = oxygenRating(numbers);
	string scrubber = scrubberRating(numbers);
	cout << "Part 1: " << convertBinaryToNumber(getGamaRate(numbers)) * convertBinaryToNumber(getEpsilonRate(numbers)) << endl;
	cout << "Part 2: " << convertBinaryToNumber(oxygenRating(numbers)) * convertBinaryToNumber(scrubberRating(numbers)) << endl;
	
	return 0;
}

