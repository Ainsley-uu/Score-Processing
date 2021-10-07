# ifndef STUDENT_H
# define STUDENT_H

#include<iostream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<iomanip>
using namespace std;

// 定义学生结构
struct Student
{
    string name;
    map<string,double> lec_level;
    double aver;
};

// 读入函数
void Read( map<string, Student> &id_stu , set<string> &All_lec , set<string> &All_ID );

// 重置学生没有的科目成绩为-1
void Reset( map<string, Student> &info , const set<string> lec , const set<string> id );

// 计算学生成绩均值及科目均值
void SetAve( map<string, Student> &info , const set<string> lec , const set<string> id , vector<double> &grade);

// 输出函数
void Print(const set<string> lec, const map<string, Student> id_stu, const set<string> id, vector<double> grade);

#endif
