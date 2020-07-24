#include"tcp.h"
#include"myqueue.h"

TCPmy::TCPmy(char* address, int port){
    memset(&server, '0', sizeof(server));
    
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    
    SocketCreate();

    if(inet_pton(AF_INET, address, &server.sin_addr) <= 0){
        perror("inet_pton error occured \r\n");
        exit(-1);
    }
}

int TCPmy::SocketCreate(){
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd < 0){
        perror("failed to create socket \r\n");
        exit(-1);
    }
}

TCPmy::TCPmy(int port){
    int yes;    

    memset(&server, '0', sizeof(server));
    memset(&client, '0', sizeof(client));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons((u_short)port);

    SocketCreate();

    if(setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&yes, sizeof yes)){
        perror("setsockopt");
        exit(-1);
    }
    
    if(bind(listen_fd, (struct sockaddr*)&server, sizeof(server)) < 0){
        perror("bind error");
        exit(-1);
    }
}

TCPmy::~TCPmy(void){
    ;;
}

int TCPmy::Listen(int arg){
    return listen(listen_fd, arg);
}

int TCPmy::Connect(void){
    return connect(listen_fd, (struct sockaddr *)&server, sizeof(server));
}

int TCPmy::Accept(void){
    socklen_t client_length = sizeof client;
    conn_fd = accept(listen_fd, (struct sockaddr*)&client, &client_length);
    return conn_fd;
}

int TCPmy::Recv(void* buf, int buf_size){
    return recv(listen_fd, buf, buf_size, 0);
}

int TCPmy::Send(void* buf, int buf_size){
    return send(conn_fd, buf, buf_size, 0);
}
