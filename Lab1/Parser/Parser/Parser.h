#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <istream>

std::vector<std::string> & csv_read_row(std::istream &in, char delimiter)
{
	std::stringstream ss;
	bool inquotes = false;
	static std::vector<std::string> row;
	row.clear();
	while (in.good())
	{
		char c = in.get();
		if (!inquotes && c == '"') //Quotes begin
		{
			inquotes = true;
		}
		else if (inquotes && c == '"') //Quote char
		{
			if (in.peek() == '"')// 2 quotes = quote escaping
			{
				ss << (char)in.get();
			}
			else // End quote char
			{
				inquotes = false;
			}
		}
		else if (!inquotes && c == delimiter) // End of field
		{
			row.push_back(ss.str());
			ss.str("");
		}
		else if (!inquotes && (c == '\r' || c == '\n'))
		{
			if (in.peek() == '\n') { in.get(); }
			row.push_back(ss.str());
			return row;
		}
		else
		{
			ss << c;
		}
	}
	return row;
}