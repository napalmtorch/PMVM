#include "Utility/StringUtil.hpp"

namespace StringUtil
{
	std::string FromDecimal(int64_t num)
	{
		char str[32];
		sprintf_s(str, "%li", (int)num);
		return std::string(str);
	}

	std::string FromHex(uint64_t num, bool prefix)
	{
		char str[16];
		sprintf_s(str, "%li", (int)num);
		std::string output;
		if (prefix) { output += "0x"; }
		if (strlen(str) == 1) { output += "0"; }
		output.append(str);
		return output;
	}

	int64_t ToDecimal(std::string val)
	{
		for (size_t i = 0; i < val.length(); i++) { if (!std::isdigit(val[i])) { return 0; } }
		int64_t num = stoi(val);
		return num;
	}

	std::vector<std::string> Split(std::string text, char delim)
	{
		std::vector<std::string> output;
		size_t start;
		size_t end = 0;

		while ((start = text.find_first_not_of(delim, end)) != std::string::npos)
		{
			end = text.find(delim, start);
		    output.push_back(text.substr(start, end - start));
		}
		return output;
	}

	bool Equals(std::string str1, std::string str2)
	{
		bool equals = !strcmp(str1.c_str(), str2.c_str());
		return equals;
	}

	std::string ToUpper(std::string text)
	{
		std::string output = std::string("");
		for (size_t i = 0; i < text.length(); i++)
		{
			if (text[i] >= 97 && text[i] <= 122) { output += text[i] - 32; }
		}
		return output;
	}

	std::string ToLower(std::string text)
	{
		std::string output = std::string("");
		for (size_t i = 0; i < text.length(); i++)
		{
			if (text[i] >= 65 && text[i] <= 90) { output += text[i] + 32; }
		}
		return output;
	}
}