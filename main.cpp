#include<set>
#include<iostream>
#include<fstream>
#include<map>
#include <sstream>
#include<string>
#include"Student.h"
using namespace std;
//录入学生信息，将学号与学生信息关联
//bool
void Set_StudentInfo(ifstream &is, map<int,Student>& s){
	string text;
	while (getline(is, text))
	{
		if (text.at(0) == '#')
			continue;
		else
		{
			istringstream words(text);
			int id_;
			string name_;
			string sex_;
			string birthday_;
			int school_year_;
			string birthplace_;
			words >> id_ >> name_ >> sex_ >> birthday_ >> school_year_ >> birthplace_;
			Student s1(id_, name_, sex_, birthday_, school_year_, birthplace_);
			s.insert(pair<int, Student>(id_,s1));
		}
	}
	/*map<int, Student>::iterator iter;
	map<int, Student>::reverse_iterator iter;
	for (iter = s.rbegin(); iter != s.rend(); iter++)
		cout << iter->first << "  " << endl;*/
}
void Set_StudentCourse(ifstream& is,map<int,Student>&s, multimap<string,int> &sp) {
	string text,coursename;
	while (getline(is, text))
	{
		if (text.at(0) == '#')
			continue;
		else
		{
			auto order1 = text.find_first_of('\t');
			auto order2 = text.find_first_of('\t', order1 + 1);
			coursename = text.substr(order1 + 1, order2 - order1);
			text = text.erase(order1, order2 - order1);
			istringstream words(text);
			int id_;
			double credits_;
			double score_;
			words >> id_>> credits_>> score_;
			sp.insert(make_pair( coursename,id_));
			Course course1(coursename, credits_, score_);
			map<int, Student>::iterator iter;
			iter = s.find(id_);
			iter->second.courses.insert(course1);
			iter->second.total += score_;
			iter->second.total_credits += credits_;
		}
		map< int, Student>::iterator is;
		for (is = s.begin(); is != s.end(); is++)
		{
			is->second.average = is->second.total/is->second.courses.size();
		}
	}
}
void Test(map<int, Student> s) {
	ofstream m(" result.txt ");
	string a = "C Programming Language";
	m<< "打印 2018 级选修 C 语言且成绩小于 60 分的学生" << endl;
	map<int, Student>::iterator it;
	for (it = s.begin(); it != s.end(); it++)
		if (it->second.school_year==2018&&it->second.coursename("C Programming Language"))
			m << it->second << endl;
	m << "统计课程平均分大于 80 的学生个人信息并输出" << endl;
	map<int, Student>::iterator ite;
	for (ite= s.begin(); ite != s.end(); ite++)
	if (ite->second.average>80)
		m << ite->second << endl;
	m<< "查询每个学生是否修满 20 学分" << endl;
	map<int, Student>::iterator iter;
	for (iter = s.begin(); iter != s.end(); iter++)
	{ 
		m << iter->second;
		if (iter->second.get_credits())
			m  << "  修满学分" << endl;
		else m << "  未修满学分" << endl;
	}
}
int main() {
	//学号和学生信息关联
	map<int,Student> s;
	//学科名称和学号关联
	multimap<string, int> sp;
	ifstream file1,file2;
	file1.open("StudentInfo.txt");
	file2.open("StudentCourse.txt");
	if (!file1 || !file2) {
		cout << "No input file!" << endl;
		return -1;
	}
	Set_StudentInfo(file1,s);
	Set_StudentCourse(file2,s,sp);
	SortByName(s);
	SortByTotalScore(s);
	Test(s);
	return 0;
}