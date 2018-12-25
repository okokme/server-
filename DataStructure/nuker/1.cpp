#include<iostream>
using namespace std;
int main()
{
     int S,T,q,t;
    cin>>T;
    cin>>S;
    cin>>q;
    t = S/q;
    if(t < 1)
        S = S;
    if(t == 1)
        S = q-1;
    if(t > S)
        S = S-t;
    float n;
    n = T/S;
    cout<<n<<endl;
    if(n > (int)n ) n += 1;
    cout<< (int)n <<endl;
}