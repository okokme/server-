/*
采用epoll+线程池
*/

#include "webServer.h"
//#include "task.h"


int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        cout<<"Usage: ./server + port\n"<<endl;
        return -1;
    }

    int port = atoi(argv[1]);
    webServer webServer(port);
   // webServer.a();
    webServer.run();
    
    return 0;
}

// #include "webServer.h"
// #include "task.h"

// int main( int argc, char **argv ) {
//     if( argc != 2 ) {
//         cout << "Usage : ./server + port\n";
//         return -1;
//     }

//     int port = atoi( argv[1] );
//     webServer webServer( port );
//     webServer.run();

//     return 0;
// }