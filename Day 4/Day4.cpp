#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> split(string line, string delimiters = ",./;")
{
	vector<int> numbers;

	int index = line.find_first_of(delimiters);
	numbers.push_back(stoi(line.substr(0, index)));

	while (index != -1) {
		index++;
		line = line.substr(index, line.length() - index);
		index = line.find_first_of(delimiters);
		auto newWord = line.substr(0, index);
		if (!newWord.empty())
			numbers.push_back(stoi(newWord));
	}
	return numbers;
}

bool checkWinner(vector<vector<int>> matrix) {
	int sumLine = 0, sumColumn = 0;
	for (int i = 0;i < matrix.size();i++)
	{
		sumLine = 0;
		sumColumn = 0;
		for (int j = 0;j < matrix.size();j++) {
			sumLine += matrix[i][j];
			sumColumn += matrix[j][i];
		}
		if (sumLine == 5 || sumColumn == 5) {
			return 1;
		}
	}
	return 0;
}

vector<pair<int, int>> resultPerMatrix(vector<int> numbersFirstLine, vector< vector<vector<int>>> allMatrix) {
	int sum = 0;
	vector<pair<int, int>> allWins, pos;
	vector<vector<int>>matrix;

	for (int ii = 0;ii < allMatrix.size();ii++) {
		pos.clear();
		sum = 0;
		matrix = allMatrix[ii];
		vector<vector<int>> matrixTrack(5, vector<int>(5, 0));
		for (int i = 0;i < numbersFirstLine.size();i++) {
			for (int j = 0;j < matrix[0].size();j++) {
				for (int k = 0;k < matrix[0].size();k++) {
					if (matrix[j][k] == numbersFirstLine[i]) {
						matrixTrack[j][k] = 1;
					}
				}
			}
			if (checkWinner(matrixTrack)) {
				sum = 0;
				for (int j = 0;j < matrixTrack[0].size();j++) {
					for (int k = 0;k < matrixTrack[0].size();k++) {
						if (matrixTrack[j][k] != 1) {
							sum += matrix[j][k];
						}
					}
				}
				allWins.push_back(make_pair(sum * numbersFirstLine[i], i));
				break;
			}
		}
	}
	return allWins;
}

pair<int, int> getProblemResults(vector<pair<int, int>>allwins) {
	int max = allwins[0].second, min = allwins[0].second, resultPart1, resultPart2;

	for (auto wins : allwins) {
		if (max < wins.second) {
			resultPart2 = wins.first;
			max = wins.second;
		}
		if (min > wins.second) {
			resultPart1 = wins.first;
			min = wins.second;
		}
	}
	return make_pair(resultPart1, resultPart2);
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	string s;
	vector<int> numbersFirstLine;
	vector<vector<int>>matrix;
	vector< vector<vector<int>>> allMatrix;
	vector<pair<int, int>>allWins;
	int count = 0;
	int countMatrix = 0;
	int line = 0;

	getline(cin, s);
	numbersFirstLine = split(s, ",");
	matrix.push_back(vector<int>());
	while (cin >> s) {
		if (count % 5 == 0 && count != 0) {
			matrix.push_back(vector<int>());
			line++;
		}
		matrix[line].push_back(stoi(s));

		count++;
		countMatrix++;
		if (countMatrix == 25) {
			countMatrix = 0;
			allMatrix.push_back(matrix);
			matrix.clear();
			line = -1;
		}
	}

	//store all the values per matrix when it gets to bingo and also the position of the number 
	allWins = resultPerMatrix(numbersFirstLine, allMatrix);

	//store the results for Part 1 and Part 2
	pair<int, int>resultsProblem = getProblemResults(allWins);

	cout << "Part 1: " << resultsProblem.first << endl << "Part 2: " << resultsProblem.second;
	return 0;
}