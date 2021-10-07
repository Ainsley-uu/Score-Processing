#include "student.h"

int main()
{
    // 把ID和学生信息绑在一起
    map<string, Student> id_stu;
    // 记录所有的ID
    set<string> All_ID;
    // 记录所有的科目
    set<string> All_lec;
    // 记录每门课程的均值
    vector<double> grade;

    Read( id_stu, All_lec, All_ID );

    Reset( id_stu , All_lec , All_ID);
    SetAve( id_stu , All_lec, All_ID , grade );

    Print( All_lec , id_stu , All_ID, grade);
}

// 读取信息
void Read( map<string, Student> &id_stu , set<string> &All_lec , set<string> &All_ID )
{
    string str;

    while( (bool)getline(cin,str) != 0 ){   // 读入一行并判断读入是否结束
        bool IsNew = true;  // 判断是否为新学生
        int start = 0;      // 字符串起始位置
        int end;        // 字符串终止位置
        string s[3];    // 储存被切分的信息
        int index = 0;  // 记录需切分的个数
        while( (end = str.find(',')) != -1 ){   // 直到找不到','为止
            s[index++] = str.substr(start, end-start ); // 切分信息
            str.erase(end, 1);
            start = ++end;  // 逗号不保存
        }
        s[index] = str.substr(start);   // 处理最后一个','后面的信息
        
        if( id_stu.find(s[0]) != id_stu.end() ){    // 判断是否为新学生
            IsNew = false;
            All_ID.insert(s[0]);
        }
        
        if( index == 2 ){       // 存储学号、学科、成绩
            double grade = atof(s[2].c_str());  // 字符串转成double类型
            All_lec.insert(s[1]);

            if( IsNew ){    // 若为新学生，则新建一个Student结构
                Student temp;
                temp.lec_level[s[1]] = grade;
                id_stu[s[0]] = temp;
            }else{  // 不为新学生，添加信息即可
                id_stu[s[0]].lec_level[s[1]] = grade;
            }
        }else{  // 存储学号和姓名
            if( IsNew ){    // 若为新学生，则新建一个Student结构
                Student temp;
                temp.name = s[1];
                id_stu[s[0]] = temp;
            }else{   // 不为新学生，添加信息即可
                id_stu[s[0]].name = s[1];
            }
        }
    }
}

// 计算学生成绩均值及科目均值
void SetAve( map<string, Student> &info , const set<string> lec , const set<string> id , vector<double> &grade)
{
    // 遍历每个学生,求每个学生的平均成绩
    for( set<string>::iterator it_id = id.begin() ; it_id != id.end() ; it_id++){
        int count = 0;  // 记录学科数目
        double sum = 0; // 记录总成绩
        // 遍历每门课
        for( set<string>::iterator it_lec = lec.begin() ; it_lec != lec.end() ; it_lec++){
            // 若有成绩则求和
            if( (int)info[*it_id].lec_level[*it_lec] != -1 ){
                sum += info[*it_id].lec_level[*it_lec];
                count++;
            }
        }
        info[*it_id].aver = 1.0 * sum / count;
    }

    // 遍历每门课，求每门课的平均值
    for( set<string>::iterator it_lec = lec.begin() ; it_lec != lec.end() ; it_lec++ ){
        int count = 0;  // 记录每门课的学生人数
        double sum = 0; // 记录总成绩
        // 遍历每个学生
        for( set<string>::iterator it_id = id.begin() ; it_id != id.end() ; it_id++){
            // 若有成绩则求和
            if( (int)info[*it_id].lec_level[*it_lec] != -1 ){
                sum += info[*it_id].lec_level[*it_lec];
                count++;
            }
        }
        double ave = 1.0 * sum / count;
        grade.push_back(ave);
    }
    
}

// 重置学生没有的科目成绩为-1
void Reset( map<string, Student> &info , const set<string> lec , const set<string> id )
{
    // 遍历每个学生
    for( set<string>::iterator it_id = id.begin() ; it_id != id.end() ; it_id++){
        // 遍历每门课
        for( set<string>::iterator it_lec = lec.begin() ; it_lec != lec.end() ; it_lec++){
            // 找不到成绩则赋值为-1
            if( info[*it_id].lec_level.find(*it_lec) == info[*it_id].lec_level.end() ){
                info[*it_id].lec_level[*it_lec] = -1;
            }
        }
    }
}

// 输出
void Print(const set<string> lec, const map<string, Student> id_stu, const set<string> id, vector<double> grade)
{
    // 输出title
    cout << "student id, name, ";
    for( set<string>::iterator it = lec.begin() ; it != lec.end() ; it++ )
        cout << *it << ", ";
    cout << "average" << endl;
    
    // 输出每个同学的信息
    map<string, Student> info = id_stu;
    for( set<string>::iterator it = id.begin() ; it != id.end() ; it++){
        cout << *it  << ", " << info[*it].name << ", ";
        for(set<string>::iterator it_lec = lec.begin() ; it_lec != lec.end() ; it_lec++ ){
            if( (int)info[*it].lec_level[*it_lec] != -1 ){
                cout <<  fixed << setprecision(1) << info[*it].lec_level[*it_lec] << ", " ;
            }else{
                cout << ", ";
            }
        }
        cout << info[*it].aver << endl;
    }

    // 输出每门课的平均值
    double sum = 0;
    int count = 0;
    cout << ", " << ", ";
    for( vector<double>::iterator it = grade.begin() ; it != grade.end() ; it++ ){
        cout << *it << ", ";
        sum += *it;
        count++;
    }
    cout << fixed << setprecision(1) <<  1.0*sum/count << endl;
}


