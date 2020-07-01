#include <iostream>
#include<fstream>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include"Student.h"
using namespace std;

ostream& operator<<(ostream& stream, Student c)
{
    stream << c.id << "\t" << c.name << "\t" << c.sex << "\t" << c.birthday << "\t" << c.school_year <<"\t"<< c.birthplace <<"\t"<<c.total<< "\t"<<c.total_credits<<endl;
    return stream;
}
bool Student::get_credits(){
    if (this->total_credits > 20) return true;
    else return false;
}
//通过id删除学生信息
void Deletebyid(map<int, Student>& s, multimap<string, int>& sp,int a) {
    map<int, Student>::iterator m=s.find(a);
    s.erase(m);
}
//通过单科成绩删除学生信息
void Deletebyid(map<int, Student>& s, multimap<string, int>& sp, string b) {
    sp.erase(b);
}
//通过单科成绩查找
void Findbyscore(string course_name,map<int, Student>& s) {
    double a, b;
    cout << "请输入" << course_name << "查找范围" << endl;
    cin >> a >> b;
        for (map<int, Student>::iterator it = s.begin(); it !=s.end();it++)
        {
            if (it->second.coursename(course_name))
                if(a<it->second.coursescore(course_name)<b)
                     cout << it->second << endl;
        }
}
void SortByName(map<int, Student> s) {
    cout << "按名字排序" << endl;
    vector<pair<int, Student>>vt(s.begin(), s.end());
    struct cmp
    {
        bool operator()(const pair<int, Student >& p1, const pair<int, Student>& p2)
        {
            return p1.second.name> p2.second.name;
        }
    };
    sort(vt.begin(), vt.end(), cmp());

    for (vector<pair<int, Student>>::iterator it = vt.begin();it != vt.end();it++)
    {
        cout << it->first << "  " << it->second << endl;
    }
}
void SortByScore(multimap<string, int> &sp, map<int, Student>& s) {
    //要查找的单科学科成绩与学生信息关联
    map<double, Student> byscore;
    cout << "请输入科目" << endl;
    //string name;
    //getline(cin,name);
    string name("Python");
    multimap<string, int>::iterator beg,end,m;
    map<int, Student>::iterator is;
    beg = sp.lower_bound(name);
    m = sp.find(name);
    end = sp.upper_bound(name);
    while (beg != end)
    {
        cout << beg->second << endl;
        int id = beg->second;
        is = s.find(id);
        byscore.insert(make_pair(is->second.coursescore(name), is->second));
        ++beg;
    }
    cout << "按" << name << "成绩排序" << endl;
    for (map<double, Student>::iterator it = byscore.begin();it != byscore.end();it++)
    {
        cout <<  it->second << endl;
    }
}
void Deletescore(multimap<string, int>& sp, map<int, Student>& s,string m) {
    
}
void SortByTotalScore(map<int, Student> s)
{

    cout << "按总分排序" << endl;
    vector<pair<int, Student>>vt(s.begin(), s.end());
    struct cmp
    {
        bool operator()(const pair<int, Student >& p1, const pair<int, Student>& p2)
        {
            return p1.second.total< p2.second.total;
        }
    };
    sort(vt.begin(), vt.end(), cmp());

    for (vector<pair<int, Student>>::iterator it = vt.begin();it != vt.end();it++)
    {
        cout << it->first << "  " << it->second << endl;
    }
}