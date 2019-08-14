#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
  //  int h1,h2,m1,m2,s1,s2;
    string s;
    int n;
    cin>>n;
    while(n--)
    {
     
        cin>>s;
        string s1;

        int hour = atoi(s.substr(0,2).c_str());
        int min = atoi(s.substr(3,2).c_str());
        int sec = atoi(s.substr(6,2).c_str()) ;
      //  cout<<hour<<" "<<min<<" "<<sec<<endl;
        if(hour > 23)
        {
            s.replace(0,1,"0");
        }
        if(min > 60)
        {
            s.replace(3,1,"0");
        }
        if(sec > 60)
        {
            s.replace(6,1,"0");
        }
        cout<<s<<endl;
    }
    return 0;
}
