#ifndef _Server_H
#define _Server_H

#include <winsock2.h>
#include <thread>

#define CLEANUP_SERVER if(server != INVALID_SOCKET) {closesocket(server);} 

typedef class Server {

	private:

		WSADATA WSAData;
		SOCKET server;
		SOCKET client;
		SOCKADDR_IN serveraddr_in;
		SOCKADDR_IN clientaddr_in;

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
		bool is_open;
		UINT16 Get_recv();
		void closing();

		bool open(UINT16 port);
		void Run();
		
		Server();
	   ~Server();

} *PServer;

#endif
