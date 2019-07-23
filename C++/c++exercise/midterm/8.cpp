#include <iostream>
using namespace std;
class People{
private:
    string id;
    string name;
public:
    People(string id, string name){
        this->id = id;
        this->name = name;
    }
    string getId(){
        return this->id;
    }
    string getName(){
        return name;
    }
};
class Student : public People{
private:
    string sid;
    int score;
public:
    Student(string id, string name, string sid, int score):People(id, name),sid(sid),score(score){
		
		/** 你提交的代码将被嵌在这里（替换此行） **/
		
    }
    friend ostream& operator <<(ostream &o, Student &s);
};
ostream& operator <<(ostream &o, Student &s){
    o << "(Name:" << s.getName() << "; id:"
      << s.getId() << "; sid:" << s.sid
      << "; score:" << s.score << ")";
    return o;
}
int main(){
    Student zs("370202X", "Zhang San", "1052102", 96);
    cout << zs  << endl;
    return 0;
}
#include <iostream>
#include <string>
using namespace std;

class Date {
protected:
    int year;
    int month;
    int day;
public:
    Date(int _y, int _m, int _d):year(_y),mouth(_m),day(d) { }
};

class Time {
protected:
    int hour;
    int minute;
    int second;
public:
    Time(int _h, int _m, int _s):hour(_h),minute(_m),second(_s) { }
};
class Schedule : public Date , public Time {
private:
    int ID;
public:
    Schedule():Date(0,0,0),Time(0,0,0) { }
    Schedule(int _y, int _mo, int _d, int _h, int _m, int _s, int _id):year(_y),mouth(_mo),day(_d),hour(_h),minute(_m),second(_s),ID(_id) { }
    bool operator < (const Schedule &s2)
    {
        char timeArr1[15], timeArr2[15];
        sprintf(timeArr1,"%04d%02d%02d%02d%02d%02d",year,mouth,day,hour,minute,second);
        sprintf(timeArr2,"%04d%02d%02d%02d%02d%02d",s2.year,s2.mouth,s2.day,s2.hour,s2.minute,s2.second);
        return atof(timeArr1)<atof(timearr2) //atof 
    }
    void show() {
        cout<<"The urgent schdule is No."<<ID<<": "<<year<<"/"<<month<<"/"<<day<<" "<<hour<<":"<<minute<<":"<<second<<endl;
    }

};
int main() {
    int id, rows=0;
    int y,m,d,h,i,s;
    Schedule min;
    while (cin>>id) {
        if(id==0) break;
        scanf("%d/%d/%d %d:%d:%d", &y, &m, &d, &h, &i, &s);
        Schedule cur(id, y, m, d, h, i, s);
        if(rows++==0) min = cur;
        if(cur<min) min = cur;
    }
    if(rows!=0) min.show();
    
    return 0;
}

