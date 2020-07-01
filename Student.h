#include<iostream>
#include<string>
#include<map>
#include<set>
using namespace std;


class Course {
private:
	
	string course_name;
	double credits;
	double score;
public:
	Course() {};
	Course(string a, double b, double c) :course_name(a), credits(b), score(c) {};
	~Course() {};
	 string getname()const{ return course_name; }
	 double getscore()const { return score; }
	bool operator<(const Course& p) const {
		if (this->credits < p.credits)return true;
		else
		     return false;
	}
};
class Student {
private:
	int id;
	string name;
	string sex;
	string birthday;
	int school_year;
	string birthplace;
public:
	double total;
	double total_credits;
	double average;
	set<Course> courses;
	//判断学生是否选择某课
	bool coursename(string a) {
		for (set<Course>::iterator it = courses.begin(); it != courses.end();it++)
		{
			if (it->getname() == a)
				return true;
			else 
				return false;
		}
	}
	 double coursescore(string a) {
		for (set<Course>::iterator it = courses.begin(); it != courses.end();it++)
		{
			if (it->getname() == a)return it->getscore();
		}
	}
	Student() {};
	Student(int a, string b, string c, string d, int e, string f) :id(a), name(b), sex(c), birthday(d), school_year(e), birthplace(f) {};
	//double TotalScore;
	~Student() {};
	friend ostream& operator<<(ostream& stream, Student c);
	friend void SortByName(map<int, Student> s);
	bool get_credits();  // 是否修满 20 学分
	friend void Findbyscore(string course_name, map<int, Student>& s);
    friend void Test(map<int, Student> s);
	friend void SortByScore(multimap<string, int>& sp, map<int, Student>& s);//（单项课程分数）
	friend void SortByTotalScore(map<int, Student> s);
	friend void Set_StudentCourse(ifstream& is, map<int, Student>& s, multimap<string, int> &sp);
};


