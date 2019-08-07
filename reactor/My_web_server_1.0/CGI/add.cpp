
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main( int argc, char **argv ) {
    int a, b, accp_fd;
    sscanf( argv[0], "%d+%d,%d", &a, &b, &accp_fd );

    int t = a+b;
    string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html;\r\ncharset=utf-8\r\n\r\n";
    string body = "<html><head><title>okokme's CGI</title></head>";
    body += "<body><p>The result is " + to_string(a) + "+" + to_string(b) + " = " + to_string(t);
    body += "</p></body></html>";
    response += body;
    dup2(accp_fd, STDOUT_FILENO);
    cout << response.c_str();
    return 0;
}