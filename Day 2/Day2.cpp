#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	string command;
	long long value;
	long long depthPart1=0;
	long long depthPart2=0;
	long long horizontal=0;
	long long aim=0;
	while (cin >> command >> value) {
		if (command == "forward")
		{
			horizontal += value;
			depthPart2+=value*aim;
		}
		if (command == "down") {
			aim += value;
			depthPart1+=value;
		}
		else if(command=="up"){
			depthPart1 -= value;
			aim -= value;
		}
	}
	cout<<"Part 1: "<< depthPart1* horizontal<<endl;
	cout<<"Part 2: "<< depthPart2* horizontal;

	return 0;
}

