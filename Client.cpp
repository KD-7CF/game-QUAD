#include "Client.h"
#include <iostream>

Client::Client() {
}

Client::~Client() {
	closing();
}

bool Client::open(LPCSTR ip, UINT16 port) {

	WSAStartup(MAKEWORD(2,0), &WSAData); 
	sockaddr_in.sin_family = AF_INET; // IPv4
	sockaddr_in.sin_port = htons(port);
	sockaddr_in.sin_addr.s_addr = inet_addr(ip);

	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(client == INVALID_SOCKET){
		MessageBox(
				NULL,
				"Network creation error !",
				NULL,
				MB_ICONERROR | MB_OK);

		CLEANUP_CLIENT
			return false;
	}

	return true;
}

void Client::Run(){

	if(connect(client, (SOCKADDR*) &sockaddr_in, sizeof(sockaddr_in)) == SOCKET_ERROR){
		MessageBox(
				NULL,
				"Error connecting to server !",
				NULL,
				MB_ICONERROR | MB_OK);

		CLEANUP_CLIENT
			return;
	}

	is_bind = true;
	Task();

	CLEANUP_CLIENT
}


void Client::Task() {

	if(thread_Excec.joinable())
		thread_Excec.detach();
	if(thread_Recv.joinable())
		thread_Recv.detach();

	thread_Excec = std::thread(&Client::Excec, this);
	thread_Recv = std::thread(&Client::Recv, this);
}

void Client::Excec() {
	std::cout << "Thread_Excec ..." << std::endl;
	while(!STOP || client != INVALID_SOCKET)
		Send();
}

void Client::Recv() {

	std::cout << "Thread_Recv ..." << std::endl;
a:
	int o = recv(client, data_recv, sizeof(data_recv), MSG_PEEK);
	if(o == sizeof(data_recv))
		std::cout << "recv ... :" << Get_recv() << std::endl;
	if((!STOP && o <= sizeof(data_recv)) && (o != ENOTCONN || o != 0))
		goto a;
}

void Client::Send() {
	if(SEND)
		if(send(client, data_send, sizeof(data_send), 0) == sizeof(data_send)){
			std::cout << "envoyee" << std::endl;
			SEND = false;
		}
}

UINT16 Client::Get_recv() {
	unsigned b = 0;
	b = data_recv[1] & 0b11111111;
	b = (b << 8) | (data_recv[0] & 0b11111111);
	return (UINT16) b;
}

void Client::closing() {

	STOP    = true;
	is_bind = false;

	if(thread_Excec.joinable())
		thread_Excec.detach();
	if(thread_Recv.joinable())
		thread_Recv.detach();

	CLEANUP_CLIENT
		WSACleanup(); 
}









