#ifndef _Client_H
#define _Client_H

#include <winsock2.h>
#include <thread>

#define CLEANUP_CLIENT  if(client != INVALID_SOCKET) {closesocket(client);} 

typedef class Client {

	private:

		WSADATA WSAData;
		SOCKET client;
		SOCKADDR_IN sockaddr_in;

		std::thread thread_Excec;
		std::thread thread_Recv;

		void Task();
		void Excec();
		void Recv();
		void Send();

	public:

		char data_send[2];
		char data_recv[2];

		bool SEND = false;
		bool STOP = false;
		bool is_bind;
		UINT16 Get_recv();
		void closing();

		bool open(LPCSTR ip, UINT16 port);
		void Run();

		Client();
		~Client();

} *PClient;

#endif



