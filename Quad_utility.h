#ifndef _QUAD_UTILITY_H
#define _QUAD_UTILITY_H

#include <ctime>
#include <vector>
#include <fstream>
#include <filesystem>
#include "resource.h"
#include "processTrack.h"

#ifndef __GLOBAL_STATIC_VAR
#define __GLOBAL_STATIC_VAR \
	HWND    QUAD_STATIC::win[3] = {NULL, NULL, NULL}; \
	Network QUAD_STATIC::network; \
	Gamer <UINT16> QUAD::gamer_1; \
	Gamer <UINT16> QUAD::gamer_2; \

#define WIN(x) QUAD_STATIC::win[x]
#define SERVER QUAD_STATIC::network.server
#define JOIN   QUAD_STATIC::network.client
#define THREAD QUAD_STATIC::network.thread
#endif


// *************************** Conversion ***************************



struct to {

	static std::string str(HWND* hwnd, UINT16 id_Edit, int line = 0){

		if(hwnd == NULL)
			return "";

		HWND hEdit = GetDlgItem(*hwnd, id_Edit);

		size_t length = (size_t) SendMessage(hEdit, EM_LINELENGTH, (WPARAM) line, 0);
		TCHAR* buffer = new TCHAR[std::max(length + 1, sizeof(WORD)) * sizeof(TCHAR)];
		memcpy(buffer, &length, sizeof(WORD));
		SendMessage(hEdit, EM_GETLINE, (WPARAM) line, (LPARAM) buffer);
		buffer[length] = '\0';

		std::string s = std::string(buffer);
		delete[] buffer;
		return s;
	}

};

// *******************************************************************






// ************************ class Data Base ************************

class DB {

	private:
		std::fstream db;

	public:

		int szmemo() {

			if(!db.is_open()) 
				return -1;	

			db.seekg(0, db.end);
			int n = db.tellg();
			db.seekg(0, db.beg);

			return n;
		}

		bool save(std::string str_save) {

			if(!db.is_open()) 
				return false;

			time_t time_0 = time(0);
			db << str_save << ":@_" << ctime(&time_0);

			return true;
		};

		std::vector <std::string> read(char c_stop = '\n') {

			if(!db.is_open())	
				return {};

			db.seekg(0, db.beg);

			std::vector <std::string> str_read;
			std::string nline;

			while (getline(db, nline, c_stop))
				str_read.push_back(nline);
			return str_read;
		};

		bool loadDB(std::string file = "0x0000", std::string path = ".\\data\\game\\") {

			db.open((path + file).c_str(), std::fstream::out | std::fstream::in);

			std::cout << path + file << std::endl;

			if(!db.is_open()) {

				STARTUPINFO StartupInfo;
				PROCESS_INFORMATION ProcessInfo;

				ZeroMemory(&StartupInfo, sizeof(StartupInfo));
				StartupInfo.cb = sizeof(StartupInfo);
				ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));

				std::string cmdLine = "CMD.EXE /C MKDIR" + path + "|| ECHO. > " + path + file;
				CreateProcessA( 
						NULL,
						(LPSTR) const_cast <LPSTR> (cmdLine.c_str()),
						NULL,
						NULL,
						FALSE,
						0,
						NULL,
						NULL,
						&StartupInfo,
						&ProcessInfo);

				WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
				CloseHandle(ProcessInfo.hProcess);
				CloseHandle(ProcessInfo.hThread);

			}

			if(!db.is_open())
				return false;

			std::cout << "file_is_open: "<<db.is_open()<<"\n";

			return true;
		};

		void closeDB() {
			if(db.is_open())
				db.close();
		};

		~DB() {
			closeDB();
		}
};


// *****************************************************************

typedef struct {

	LPDRAWITEMSTRUCT pDrawItem;
	HFONT            hFONT;
	HPEN             hPEN;
	HBRUSH           hBRUSH;
	LPCWSTR          pTextHWND;

} hDesigner, *PhDesigner;

struct Network {

	std::thread thread;
	Server server;
	Client client;
	UINT16   QnPlay = 0;

	static std::vector <LPSTR> GetIPv4() {

		STARTUPINFO StartupInfo;
		PROCESS_INFORMATION ProcessInfo;

		ZeroMemory(&StartupInfo, sizeof(StartupInfo));
		StartupInfo.cb = sizeof(StartupInfo);
		ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));

		CreateProcessA( 
				NULL,
				(LPSTR) "CMD.EXE /C  DEL /Q/F .\\data\\game\\@IP0x0000 & IPCONFIG > .\\data\\game\\@IP0x0000 || MKDIR .\\data\\game",
				NULL,
				NULL,
				FALSE,
				0,
				NULL,
				NULL,
				&StartupInfo,
				&ProcessInfo);

		WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
		CloseHandle(ProcessInfo.hProcess);
		CloseHandle(ProcessInfo.hThread);

		std::fstream file;
		file.open(".\\data\\game\\@IP0x0000", std::fstream::in);			
		if(!file.is_open())
			return {};

		file.seekg(0, file.beg);
		std::vector <std::string> str_read;
		std::string nline;
		short pos1 = 0;
		short pos2 = 0;

		while(!file.eof()) {
			getline(file, nline);
			if((pos1 = nline.find("Adresse IPv4", 0)) != std::string::npos || (pos1 = nline.find("IPv4 Address", 0)) != std::string::npos)
				if((pos2 = nline.find(":", pos1)) != std::string::npos)
					str_read.push_back(nline.erase(0, pos2 + 1));
		}

		if(file.is_open())
			file.close();

		std::vector <LPSTR> ArrayLPStr_IP;

		for (auto str : str_read) {
			std::stringstream sstr;
			std::string tmp_str;

			for(const char& c : str)
				if(
						c == '0' || c == '1' || c == '2' || 
						c == '3' || c == '4' || c == '5' || 
						c == '6' || c == '7' || c == '8' || 
						c == '9' || c == '.'
				  )
					sstr << c;

			sstr >> tmp_str;
			tmp_str += '\0';

			ArrayLPStr_IP.push_back(const_cast <LPSTR> (tmp_str.c_str()));
		}

		return ArrayLPStr_IP;
	}

};


struct hScreenInfo {

	HWND        SYMBOL_BTNGAMER_1;
	HWND        SYMBOL_BTNGAMER_2;
	HWND        EDIT_SCORE_GAMER_1;
	HWND        EDIT_SCORE_GAMER_2;
	HWND        EDIT_INFO_IP;
	HFONT       hFONT_EDIT_SCORE_GAMER;
	HFONT       hFONT_EDIT_INFO_IP;
	HBRUSH      hBRUSH_BTNGAMER_1;
	HBRUSH      hBRUSH_BTNGAMER_2;
	COLORREF    COLOR_RGB_GAMER_1 = 0x00000000;
	COLORREF    COLOR_RGB_GAMER_2 = 0x00000000; 
	bool        DIRECTION_GAMER_1;
	bool        DIRECTION_GAMER_2;


	void LOAD_COLOR_GAMER(COLORREF COLOR_RGB_GAMER_2 = 0x00000000) {

		if(COLOR_RGB_GAMER_2 != 0x00000000) {

			if(COLOR_RGB_GAMER_2 == RGB(255, 0, 0)) {
				this->COLOR_RGB_GAMER_1 = RGB(0, 0, 255);
				return;
			}
			if(COLOR_RGB_GAMER_2 == RGB(0, 0, 255)) {
				this->COLOR_RGB_GAMER_1 = RGB(255, 0, 0);
				return;
			}
		}

		UINT8 choose = std::rand() % 2 + 1;

		switch(choose) {

			case 1:
				DIRECTION_GAMER_1 = Q::VERTICAL;
				DIRECTION_GAMER_2 = Q::HORIZONTAL;
				this->COLOR_RGB_GAMER_1 = RGB(0, 0, 255);
				this->COLOR_RGB_GAMER_2 = RGB(255, 0, 0); 
				break;

			case 2:
				DIRECTION_GAMER_1 = Q::HORIZONTAL;
				DIRECTION_GAMER_2 = Q::VERTICAL;  
				this->COLOR_RGB_GAMER_1 = RGB(255, 0, 0);
				this->COLOR_RGB_GAMER_2 = RGB(0, 0, 255); 
				break;

		};

	}

	void UNLOAD_COLOR_GAMER() {
		COLOR_RGB_GAMER_1 = 0x00000000;
		COLOR_RGB_GAMER_2 = 0x00000000; 

	}
};

struct QUAD_STATIC {

	static Network network;
	static HWND    win[];
	HWND           Btn_connect;
	PhDesigner     phD;
	HWND           BtnQ[N][N];
	UINT16         Qn[N][N];
	HWND           prevBtnQ;
	RECT           RectQ;
	LPRECT         prevRectQ;
	HDC            hDC;
	HPEN           hPEN;
	HBRUSH         hBRUSH;
	HBRUSH         hBRUSH_BLACK;
	hScreenInfo    hScrInfo;

	static void execDlg(HWND* pDlg){

		if(*pDlg == NULL)
			return;

		MSG msg;
		BOOL ok;
		HACCEL hAccel = LoadAccelerators(
				(HINSTANCE) GetWindowLongPtrA(*pDlg, GWLP_HINSTANCE),
				MAKEINTRESOURCE(ID_ACCEL)
				);

		while(ok = GetMessage(&msg, NULL, 0, 0) != 0)
			if(ok == -1) {
				// handle the error and possibly exit
			} else if(IsDialogMessage(*pDlg, &msg))
				if(msg.message == WM_KEYDOWN)
					if(msg.wParam == VK_BACK && GetDlgCtrlID(GetFocus()) == ID_EDIT_PORT);
		// no translate accelerator
					else if(TranslateAccelerator(*pDlg, hAccel, &msg) != 0) {
						TranslateMessage(&msg); 
						DispatchMessage(&msg);
					}

	};

};

class Qn_QUAD{

	public:

		std::vector <UINT16> vArray_Qn_GAMER_1; 
		std::vector <UINT16> vArray_Qn_GAMER_2;
		std::vector <UINT16> Empty_Qn;

		void RESET() {
			vArray_Qn_GAMER_1.clear();
			vArray_Qn_GAMER_2.clear();
			Empty_Qn.clear();
		}

		void rmvX (std::vector<UINT16> *v, UINT16 x) {
			if(v == nullptr)
				return;

			for(int n = 0; n < v->size(); n++)
				if((*v)[n] == x){
					for(int m = n; m < v->size() - 1; m++)
						(*v)[m] = (*v)[m+1];
					v->pop_back(); 
					return;
				}
		}

		void init_Qn(UINT16 (*Qn) [N]){
			UINT16 n = 1;
			for(int j = 0; j < N; j++)
				for(int k = 0; k < N; k++){
					Qn[j][k] = n;
					n++;
				}
		}

		UINT16 PLAY_VIRTUAL(UINT16 n_GAMER_1) {

			UINT16 TAB [(1+1+1)*(1+1+1)]; // TABQ = [ 3 x 3 ]
			INT16  x = 0;
			UINT16 n = (UINT16) ((std::rand() % (N*N)) + 1); // 1 ... N²

			for(auto &i : TAB)
				i = n;

			if(n_GAMER_1 <= 1*N)
				x = (n_GAMER_1 - 0*N) - 1;								
			else
				x = (n_GAMER_1 - 1*N) - 1;

			if(x <= 0)
				x = 1;

			for (int i = 0; i < sizeof(TAB)/sizeof(UINT16); i++){

				if(i != 0)
					if(i%(1+1+1) == 0)
						x+=N-(1+1+1);

				if(x >= N*N)
					break;

				if(x == n_GAMER_1)
					x++;
				else
					TAB[i] = x++;
			}

			std::vector <UINT16> TABQ;

			for(const auto &x : TAB){

				for(const auto &y : vArray_Qn_GAMER_1)
					if(x == y)
						goto a;

				for(const auto &y : vArray_Qn_GAMER_2)
					if(x == y)
						goto a;

				TABQ.push_back(x);
a:
				;
			}

			if(!TABQ.empty())
				if((TABQ.size()-1) > 0)
					return TABQ[std::rand() % (TABQ.size()-1)];
				else
					return TABQ.back();

			if(!Empty_Qn.empty())
				if((Empty_Qn.size()-1) > 0)
					return Empty_Qn[std::rand() % (Empty_Qn.size()-1)];
				else
					return Empty_Qn.back();

			return vArray_Qn_GAMER_2.back();
		}
};

template <typename T>   
class Score : protected Track <T> {

	private:
		short lines   = N;
		short columns = N;

	protected:

		bool *ptr_direction = nullptr;
		std::vector <T> *ptr_vArray_Qn_GAMER = nullptr;

		void Calc_score(int *ptr_score = nullptr) {

			if(ptr_vArray_Qn_GAMER == nullptr || ptr_direction == nullptr)
				return;

			if(ptr_score == nullptr)
				return;
			this->track_Process(ptr_vArray_Qn_GAMER, &lines, &columns, ptr_direction);
			*ptr_score = (*ptr_score >= this->nbr_succeed) ? (*ptr_score) : (this->nbr_succeed);
			this->terminate_Process();

		};

};


template <typename T>   
class Gamer : protected Score <T> {

	public:

		int score = 0;

		void update(std::vector <T> *ptr_vArray_Qn_GAMER, bool *ptr_direction, int ms_duration) {
			this->ptr_vArray_Qn_GAMER = ptr_vArray_Qn_GAMER;
			this->ptr_direction       = ptr_direction;
			this->Calc_score(&score); 
		};

		void restart() {
			this->score = 0;
		}
};

#endif
