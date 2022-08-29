#include "Server.h"
#include <iostream>

Server::Server() {
}

Server::~Server() {
	closing();
}

bool Server::open(UINT16 port) {

	WSAStartup(MAKEWORD(2,0), &WSAData);
	serveraddr_in.sin_family = AF_INET; // IPv4
	serveraddr_in.sin_port = htons(port);
	serveraddr_in.sin_addr.s_addr = htonl(INADDR_ANY);

	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(server == INVALID_SOCKET){
		MessageBox(
				NULL,
				"Network creation error !",
				NULL,
				MB_ICONERROR | MB_OK);

		CLEANUP_SERVER

			return false;
	}

	if(bind(server, (SOCKADDR*) &serveraddr_in, sizeof(serveraddr_in)) < 0){

		MessageBox(
				NULL,
				"Server open error !",
				NULL,
				MB_ICONERROR | MB_OK);

		CLEANUP_SERVER

			return false;
	}

	is_open = true;

	return true;
}


void Server::Run() {

	listen(server, 0); // en attente zero ...

	int addrlen = sizeof(clientaddr_in);

	while(!STOP) {
		client = accept(server, (SOCKADDR*) &clientaddr_in, &addrlen);
		if(client != INVALID_SOCKET)
			Task();
		closesocket(client);
	}
}

void Server::Task() {

	if(thread_Excec.joinable())
		thread_Excec.detach();
	if(thread_Recv.joinable())
		thread_Recv.detach();

	thread_Excec = std::thread(&Server::Excec, this);
	thread_Recv  = std::thread(&Server::Recv, this);
}

void Server::Excec() {
	std::cout << "Thread_Excec ..." << std::endl;
	while(!STOP || client != INVALID_SOCKET)
		Send();
}

void Server::Recv() {

	std::cout << "Thread_Recv ..." << std::endl;
a:
	int o = recv(client, data_recv, sizeof(data_recv), MSG_PEEK);
	if(o == sizeof(data_recv))
		std::cout << "recv ... :" << Get_recv() << std::endl;
	if((!STOP && o <= sizeof(data_recv)) && (o != ENOTCONN || o != 0))
		goto a;	 
}

void Server::Send() {	
	if(SEND)
		if(send(client, data_send, sizeof(data_send), 0) == sizeof(data_send)) {
			std::cout << "envoyee" << std::endl;
			SEND = false;
		}
}

UINT16 Server::Get_recv(){
	unsigned b = 0;
	b = data_recv[1] & 0b11111111;
	b = (b << 8) | (data_recv[0] & 0b11111111);
	return (UINT16) b;
}

void Server::closing() {

	STOP    = true;
	is_open = false;

	if(thread_Excec.joinable())
		thread_Excec.detach();
	if(thread_Recv.joinable())
		thread_Recv.detach();

	CLEANUP_SERVER
		WSACleanup();
}
































