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
 * ����ʵ�ð�
 * �������ַ���׼�����зָ�
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

	// 	delim ��char���͵ı����������õĽض��ַ����ڲ��Զ������õ�����£�������\n��������ֹ���롣
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
 * ���̸Ľ���  (���� find_first_of ��ʵ��)
 * �������ַ����ָ�,�簴�� ,,|�Լ��ո����ָ��ַ�����
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