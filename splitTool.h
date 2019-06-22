#pragma once

#include <iostream>
using std::cout; using std::getline;
#include <iterator>
using std::ostream_iterator;
#include <string>
using std::string;
#include <sstream>
using std::istringstream;
#include <vector>
using std::vector;
#include <algorithm>
using std::copy;

/*************************************************************
 * 工程实用版
 * 按单个字符标准，进行分割
 *************************************************************/

// int main()
// {
// 	string str("Windows,Linux,,MacOS,");
// 	vector<string> result;
// 	split(str, ',', result);
// 	copy(result.begin(), result.end(), ostream_iterator<string>(cout, "\n"));
// 	return 0;
// }

vector<string>& split(const string& str, char delim, vector<string>& elems, bool skip_empty = true)
{
	istringstream iss(str);

	// 	delim ：char类型的变量，所设置的截断字符；在不自定义设置的情况下，遇到’\n’，则终止输入。
	for (string item; getline(iss, item, delim); )
	{
		if (skip_empty && item.empty())
			continue;
		else
			elems.push_back(item);
	}

	return elems;

}

/*************************************************************
 * 工程改进版  (利用 find_first_of 来实现)
 * 按多种字符来分隔,如按照 ,,|以及空格，来分割字符串。
 *************************************************************/

//int main()
//{
//	string str("Windows,Linux||MacOS All");
//	vector<string> result;
//	for (const auto& s : split(str, ",| ", result))
//		std::cout << s << " ";
//	std::cout << std::endl;
//}


vector<string> &split(const string &str, const string &delimiters, vector<string> &elems, bool skip_empty = true) 
{
	string::size_type pos, prev = 0;

	while ((pos = str.find_first_of(delimiters, prev)) != string::npos) 
	{
		if (pos > prev) 
		{
			if (skip_empty && 1 == pos - prev) 
				break;
			elems.emplace_back(str, prev, pos - prev);
		}
		prev = pos + 1;
	}
	if (prev < str.size()) 
		elems.emplace_back(str, prev, str.size() - prev);

	return elems;
}