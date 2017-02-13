// Parser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void ReadFile(string const & fileName, vector<pair<string, int>> & authors)
{
	ifstream input("db.csv");
	csv_read_row(input, ',');

	while (!input.eof())
	{
		vector<string> & record = csv_read_row(input, ',');
		authors.push_back(pair<string, int>(record[4], stoi(record[0])));
	}
}

void SortAuthors(vector<pair<string, int>> & authors)
{
	sort(authors.begin(), authors.end(), [](pair<string, int> left, pair<string, int> right)
	{
		if (left.first < right.first)
			return true;
		else if (left.first.compare(right.first) == 0 && left.second < right.second)
			return true;
		return false;
	});
}

void StartSearch(vector<pair<string, int>> & authors)
{
	cout << "Enter author's name: ";
	string name;
	while (getline(cin, name))
	{
		cout << "Record id: ";
		bool found = false;
		for (auto author : authors)
		{
			if (author.first.compare(name) == 0)
			{
				cout << author.second << " ";
				found = true;
			}
			else if (author.first.compare(name) == 1)
			{
				break;
			}
		}
		if (!found)
		{
			cout << "Author not found";
		}
		cout << "\n\nEnter author's name: ";
	}
}

int main(int argc, char *argv[])
{
	vector<pair<string, int>> authors;
	ReadFile("db.csv", authors);
	SortAuthors(authors);
	StartSearch(authors);
    return 0;
}