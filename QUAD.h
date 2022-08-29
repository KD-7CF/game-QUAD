#ifndef _QUAD_H
#define _QUAD_H

#include "Server.h"
#include "Client.h"
#include <windowsx.h>
#include <iostream>
#include <cstdlib>

#define W        720
#define H        720
#define x2Xo     240
#define x2Yo     240
#define Xo       (W-(W-x2Xo))/2
#define Yo       (H-(H-x2Yo))/2
#define N        N_MAX_TRACK
#define L        (W-x2Xo)/N
#define l        (H-x2Yo)/N
#define NAME_APP "QUAD"
#define wc_0x0   "wc_1"

#define NAME_BTN_CONNECT L"\U0001F5A7" // UNICODE 3 ORDI

#define W_H_Btn_connect 50, 50 
#define X_Y_Btn_connect ((W/2)-(50/2)), (Yo-(30+50))

#define _WHITE   RGB(255,255,255)
#define _RED     RGB(255,  0,  0)
#define _GREEN   RGB(  0,255,  0)
#define _BLUE    RGB(  0,  0,255)
#define _BLACK   RGB(  0,  0,  0)
#define _YELLOW  RGB(255,255,  0)
#define _CYAN    RGB(  0,255,255)
#define _MAGENTA RGB(255,  0,255)

#define PEN_SZ_0x0 2
#define PEN_SZ_0x1 5
#define CLRCLICKONBTN  0xAAA0
#define CLRCURSORONBTN 0xAAA1
#define DRAWITEMS_HWND 0xAAA2
#define RESET_BTN      0xAAA3

// ================= PORT =================
#define FILE_IPPORT       "@Socket0x0000"
#define EDIT_DEFAULT_PORT "5050"

// ========================================

#define ID_BTN_CONNECT  0xAAA4
#define CLICK_CONNEXION 0xAAA5
#define TRY_OPEN_SERVER 0xAAA6
#define TRY_JOIN_SERVER 0xAAA7
#define CONNECTED       0xAAA8

#define ID_SYMBOL_BTN_GAMER_1 0xAAA9
#define ID_SYMBOL_BTN_GAMER_2 0xAAAA 
#define ID_EDIT_SCORE_GAMER_1 0xAAAB 
#define ID_EDIT_SCORE_GAMER_2 0xAAAC 
#define ID_EDIT_INFO_IP       0xAAAD
#define REFRESH_SCREEN_INFO   0xAAAE
#define ID_REVERSE_DIRECTION  0xAAAF

#define W_H_SYMBOL_BTNGAMER_1 20, 20
#define X_Y_SYMBOL_BTNGAMER_1 (Xo), (Yo-(30+20+20+8))

#define W_H_SYMBOL_BTNGAMER_2 20, 20
#define X_Y_SYMBOL_BTNGAMER_2 (Xo), (Yo-(30+20+2))

#define W_H_EDIT_SCORE_GAMER_1 55, 20
#define X_Y_EDIT_SCORE_GAMER_1 (Xo+20+5), (Yo-(30+20+20+8))

#define W_H_EDIT_SCORE_GAMER_2 55, 20
#define X_Y_EDIT_SCORE_GAMER_2 (Xo+20+5), (Yo-(30+20+2))

#define W_H_EDIT_INFO_IP 120, 24
#define X_Y_EDIT_INFO_IP (W-120-15), (5)

#define PLAYER_GAMER_1 0xAAB0
#define PLAYER_GAMER_2 0xAAB1
#define REFRESH_SCORE  0xAAB2
#define INIT_TIME_0 std::srand((unsigned int) time(0));
#define REFRESH_Qn_EMPTY if(!Q.Empty_Qn.empty()) Q.rmvX(&(Q.Empty_Qn), (UINT16) GetDlgCtrlID((HWND) lParam));


#include "Quad_utility.h"


class QUAD {

	private:

		HWND*       hQUAD     = nullptr;
		HINSTANCE*  hInstance = nullptr;
		WNDCLASSEX* wcQUAD    = nullptr;

		static Gamer <UINT16> gamer_1;
		static Gamer <UINT16> gamer_2;

		void init(){

			INIT_TIME_0

				hQUAD = new HWND;
			*hQUAD   = CreateWindowEx(
					WS_EX_OVERLAPPEDWINDOW,
					wc_0x0, 
					NAME_APP,
					WS_OVERLAPPEDWINDOW ^ (WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME),
					CW_USEDEFAULT, CW_USEDEFAULT,
					W, H,
					NULL,
					NULL,
					*(this->hInstance),
					NULL);
			if(*hQUAD == NULL)
				return;
			ShowWindow(*hQUAD, SW_SHOW);
		};

	public:

		QUAD(HINSTANCE* hInstance){

			this->hInstance       = hInstance;
			wcQUAD                = new WNDCLASSEX;
			HBRUSH hBRUSH         = CreateSolidBrush(RGB(0, 0, 0));
			wcQUAD->cbSize        = sizeof(WNDCLASSEX);
			wcQUAD->style         = CS_BYTEALIGNWINDOW;
			wcQUAD->lpfnWndProc   = hWndEvent;
			wcQUAD->cbClsExtra    = 0;
			wcQUAD->cbWndExtra    = 0;
			wcQUAD->hInstance     = *(this->hInstance);
			wcQUAD->hIcon         = LoadIconA(NULL, IDI_SHIELD); 
			wcQUAD->hCursor       = LoadCursorA(NULL, IDC_CROSS);
			wcQUAD->hbrBackground = hBRUSH;
			wcQUAD->lpszMenuName  = NULL;
			wcQUAD->lpszClassName = wc_0x0;
			wcQUAD->hIconSm       = LoadIconA(NULL, IDI_SHIELD);

			if(!RegisterClassEx(wcQUAD))
				return;

			init();

			DeleteObject(hBRUSH);

		};

		~QUAD(){
			delete hQUAD;
			delete wcQUAD;
		};


	protected:

		void run_thread(){};
		void exec(){
			MSG msg;
			BOOL ok;
			while(ok = GetMessage(&msg, NULL, 0, 0) != 0)

				if(ok == -1) {
					// handle the error and possibly exit
				} else {
					TranslateMessage(&msg); 
					DispatchMessage(&msg); 
				} 
		};


	private:

		static LRESULT CALLBACK hWndEvent( 
				HWND hwnd, 
				UINT Msg, 
				WPARAM wParam, 
				LPARAM lParam) {


			static QUAD_STATIC Q_sc;
			static Qn_QUAD Q;

			switch(Msg) {

				case CLRCURSORONBTN:

					if(Q_sc.prevBtnQ != NULL && Q_sc.prevRectQ != NULL){
						Q_sc.hDC = GetDC(Q_sc.prevBtnQ);  
						Q_sc.hBRUSH = CreateSolidBrush(_BLACK);
						SelectObject(Q_sc.hDC, Q_sc.hBRUSH);

						Rectangle(Q_sc.hDC, Q_sc.prevRectQ->left, Q_sc.prevRectQ->top, Q_sc.prevRectQ->right, Q_sc.prevRectQ->bottom);

						ReleaseDC(Q_sc.prevBtnQ, Q_sc.hDC);
						DeleteObject(Q_sc.hBRUSH);

						Q_sc.prevBtnQ = NULL;
						Q_sc.prevRectQ = NULL;
					}

					GetClientRect((HWND) lParam, &Q_sc.RectQ);
					Q_sc.hDC = GetDC((HWND) lParam);
					Q_sc.hPEN = CreatePen(PS_INSIDEFRAME, PEN_SZ_0x1, _WHITE);
					Q_sc.hBRUSH = CreateSolidBrush(_BLACK);
					SelectObject(Q_sc.hDC, Q_sc.hPEN);
					SelectObject(Q_sc.hDC, Q_sc.hBRUSH);

					Rectangle(Q_sc.hDC, Q_sc.RectQ.left, Q_sc.RectQ.top, Q_sc.RectQ.right, Q_sc.RectQ.bottom);

					ReleaseDC((HWND) lParam, Q_sc.hDC);
					DeleteObject(Q_sc.hPEN);
					DeleteObject(Q_sc.hBRUSH);

					Q_sc.prevBtnQ  = (HWND) lParam;
					Q_sc.prevRectQ = &Q_sc.RectQ;

					break;

				case WM_SETCURSOR:

					if((HWND) wParam == Q_sc.Btn_connect)
						SetClassLongPtrA(Q_sc.Btn_connect, GCLP_HCURSOR, (LONG_PTR) LoadCursorA(NULL, IDC_HAND));

					else {
						for(int j=0; j<N; j++)
							for(int k=0; k<N; k++)
								if((HWND) wParam == Q_sc.BtnQ[j][k]) {
									SetClassLongPtrA(Q_sc.BtnQ[j][k], GCLP_HCURSOR, (LONG_PTR) LoadCursorA(NULL, IDC_HAND));	
									SendMessageA(hwnd, CLRCURSORONBTN, -1, (LPARAM) Q_sc.BtnQ[j][k]);
									goto EXIT_WM_SETCURSOR;
								}

						SetClassLongPtrA((HWND) wParam, GCLP_HCURSOR, (LONG_PTR) LoadCursorA(NULL, IDC_CROSS));
					}

EXIT_WM_SETCURSOR:

					break;

				case WM_COMMAND:

					switch(HIWORD(wParam)) {

						case EN_SETFOCUS:
							if(GetFocus() != hwnd)
								SetFocus(hwnd);
							HideCaret(hwnd);					
							break;

						case BN_CLICKED:
							if(LOWORD(wParam) == ID_BTN_CONNECT)
								SendMessageA(hwnd, CLICK_CONNEXION, -1, -1);
							else if(LOWORD(wParam) == ID_SYMBOL_BTN_GAMER_1)
								SendMessageA(hwnd, ID_REVERSE_DIRECTION, -1, -1);
							else if(LOWORD(wParam) == ID_SYMBOL_BTN_GAMER_2)
								SendMessageA(hwnd, ID_REVERSE_DIRECTION, -1, -1);
							else
								for(int j=0; j<N; j++)
									for(int k=0; k<N; k++)
										if(LOWORD(wParam) == GetDlgCtrlID(Q_sc.BtnQ[j][k])) {
											SendMessageA(hwnd, PLAYER_GAMER_1, -1, lParam);
											SendMessageA(hwnd, PLAYER_GAMER_2, -1, (LPARAM) GetDlgItem(hwnd, Q.PLAY_VIRTUAL(Q.vArray_Qn_GAMER_1.back()))); 
											goto EXIT_WM_COMMAND;
										}
							break;
					}

EXIT_WM_COMMAND:
					break;


				case CLRCLICKONBTN:

					Q_sc.hDC = GetDC((HWND) lParam);
					GetClientRect((HWND) lParam, &Q_sc.RectQ);
					Q_sc.hBRUSH = CreateSolidBrush((COLORREF) wParam);
					SelectObject(Q_sc.hDC, Q_sc.hBRUSH);

					Rectangle(Q_sc.hDC, Q_sc.RectQ.left, Q_sc.RectQ.top, Q_sc.RectQ.right, Q_sc.RectQ.bottom);

					ReleaseDC((HWND) lParam, Q_sc.hDC);
					DeleteObject(Q_sc.hBRUSH);

					EnableWindow((HWND) lParam, FALSE);

					Q_sc.prevBtnQ  = NULL;
					Q_sc.prevRectQ = NULL;

					break;


				case PLAYER_GAMER_1: 
					SendMessageA(hwnd, CLRCLICKONBTN, (WPARAM) Q_sc.hScrInfo.COLOR_RGB_GAMER_1, lParam);
					Q.vArray_Qn_GAMER_1.push_back((UINT16) GetDlgCtrlID((HWND) lParam));
					SendMessageA(hwnd, REFRESH_SCORE, (WPARAM) Q::ME_GAMER, -1);


					REFRESH_Qn_EMPTY 

						break;

				case PLAYER_GAMER_2:

					SendMessageA(hwnd, CLRCLICKONBTN, (WPARAM) Q_sc.hScrInfo.COLOR_RGB_GAMER_2, lParam);
					Q.vArray_Qn_GAMER_2.push_back((UINT16) GetDlgCtrlID((HWND) lParam));
					SendMessageA(hwnd, REFRESH_SCORE, (WPARAM) Q::VIRTUAL_GAMER, -1);

					REFRESH_Qn_EMPTY 
						break;


				case REFRESH_SCORE:

					if(wParam == Q::ME_GAMER) {
						gamer_1.update(&Q.vArray_Qn_GAMER_1, &Q_sc.hScrInfo.DIRECTION_GAMER_1, 1000);
						SendMessageA(hwnd, REFRESH_SCREEN_INFO, (WPARAM) 0x000A, -1);
					}

					else if(wParam == Q::VIRTUAL_GAMER) {
						gamer_2.update(&Q.vArray_Qn_GAMER_2, &Q_sc.hScrInfo.DIRECTION_GAMER_2, 1000);
						SendMessageA(hwnd, REFRESH_SCREEN_INFO, (WPARAM) 0x000B, -1);
					}

					else if(wParam == Q::ONLINE_GAMER) {
						gamer_2.update(&Q.vArray_Qn_GAMER_2, &Q_sc.hScrInfo.DIRECTION_GAMER_2, 1000);
						SendMessageA(hwnd, REFRESH_SCREEN_INFO, (WPARAM) 0x000B, -1);
					}

					break;

				case WM_CTLCOLORBTN:

					if ((HWND) lParam == Q_sc.hScrInfo.SYMBOL_BTNGAMER_1) {
						if(Q_sc.hScrInfo.hBRUSH_BTNGAMER_1 == NULL)
							Q_sc.hScrInfo.hBRUSH_BTNGAMER_1 = CreateSolidBrush(Q_sc.hScrInfo.COLOR_RGB_GAMER_1);
						return (LRESULT) Q_sc.hScrInfo.hBRUSH_BTNGAMER_1;
					}

					if ((HWND) lParam == Q_sc.hScrInfo.SYMBOL_BTNGAMER_2) {
						if(Q_sc.hScrInfo.hBRUSH_BTNGAMER_2 == NULL)
							Q_sc.hScrInfo.hBRUSH_BTNGAMER_2 = CreateSolidBrush(Q_sc.hScrInfo.COLOR_RGB_GAMER_2);
						return (LRESULT) Q_sc.hScrInfo.hBRUSH_BTNGAMER_2;
					}

					if(IsWindowEnabled((HWND) lParam)) {
						if(Q_sc.hBRUSH_BLACK == NULL)
							Q_sc.hBRUSH_BLACK =  CreateSolidBrush(_BLACK);
						return (LRESULT) Q_sc.hBRUSH_BLACK;
					}

					break;

				case WM_PAINT:

					if(Q_sc.Btn_connect != NULL)
						SendMessageA(Q_sc.Btn_connect, BM_SETIMAGE, (WPARAM) IMAGE_ICON, (LPARAM) LoadIconA(NULL, IDI_SHIELD));

					SendMessageA(hwnd, REFRESH_SCREEN_INFO, -1, -1);
					for(const auto& i : Q.vArray_Qn_GAMER_1)
						SendMessageA(hwnd, CLRCLICKONBTN, (WPARAM) Q_sc.hScrInfo.COLOR_RGB_GAMER_1, (LPARAM) GetDlgItem(hwnd, i));
					for(const auto& i : Q.vArray_Qn_GAMER_2)
						SendMessageA(hwnd, CLRCLICKONBTN, (WPARAM) Q_sc.hScrInfo.COLOR_RGB_GAMER_2, (LPARAM) GetDlgItem(hwnd, i));

					break;

				case WM_DRAWITEM:

					if(((LPDRAWITEMSTRUCT) lParam)->CtlID == ID_BTN_CONNECT) {

						Q_sc.phD = new hDesigner;

						Q_sc.phD->pDrawItem = (LPDRAWITEMSTRUCT) lParam;

						if(Q_sc.phD->pDrawItem->itemState & ODS_SELECTED)
							Q_sc.phD->hPEN = CreatePen(PS_INSIDEFRAME, PEN_SZ_0x0, _GREEN);
						else
							Q_sc.phD->hPEN = CreatePen(PS_INSIDEFRAME, PEN_SZ_0x0, _WHITE);

						Q_sc.phD->hBRUSH    = CreateSolidBrush(_BLACK);
						Q_sc.phD->pTextHWND = NAME_BTN_CONNECT;

						SendMessageA(hwnd, DRAWITEMS_HWND, (WPARAM) Q_sc.phD, -1);
					} 

					break;

				case DRAWITEMS_HWND:

					Q_sc.phD = (PhDesigner) wParam;
					Q_sc.phD->hFONT = CreateFontA(
							40,
							0,
							0,
							0,
							FW_BLACK,
							FALSE,
							FALSE,
							FALSE,
							ANSI_CHARSET,
							OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,
							CLEARTYPE_QUALITY,
							VARIABLE_PITCH,
							TEXT("Calibri")
							);

					SelectObject(Q_sc.phD->pDrawItem->hDC, Q_sc.phD->hFONT);
					SelectObject(Q_sc.phD->pDrawItem->hDC, Q_sc.phD->hPEN);
					SelectObject(Q_sc.phD->pDrawItem->hDC, Q_sc.phD->hBRUSH);

					SetBkColor(Q_sc.phD->pDrawItem->hDC, _BLACK);

					if(SERVER.is_open)
						SetTextColor(Q_sc.phD->pDrawItem->hDC, _CYAN);
					else if(JOIN.is_bind)
						SetTextColor(Q_sc.phD->pDrawItem->hDC, _YELLOW);
					else
						SetTextColor(Q_sc.phD->pDrawItem->hDC, _WHITE);

					Rectangle(
							Q_sc.phD->pDrawItem->hDC, 
							Q_sc.phD->pDrawItem->rcItem.left, 
							Q_sc.phD->pDrawItem->rcItem.top, 
							Q_sc.phD->pDrawItem->rcItem.right, 
							Q_sc.phD->pDrawItem->rcItem.bottom
							);

					DrawTextW(
							Q_sc.phD->pDrawItem->hDC,
							Q_sc.phD->pTextHWND,
							-1,
							&Q_sc.phD->pDrawItem->rcItem, 
							DT_CENTER | DT_VCENTER | DT_SINGLELINE
							);

					DeleteObject(Q_sc.phD->hFONT);
					DeleteObject(Q_sc.phD->hPEN);
					DeleteObject(Q_sc.phD->hBRUSH);
					delete Q_sc.phD; Q_sc.phD = nullptr;

					break;

				case WM_CTLCOLORSTATIC:

					if ((HWND) lParam == Q_sc.hScrInfo.EDIT_SCORE_GAMER_1) {
						SetBkColor  ((HDC) wParam, _BLACK);
						SetTextColor((HDC) wParam, Q_sc.hScrInfo.COLOR_RGB_GAMER_1);
						if(Q_sc.hBRUSH_BLACK == NULL)
							Q_sc.hBRUSH_BLACK = CreateSolidBrush(_BLACK);
						return (LRESULT) Q_sc.hBRUSH_BLACK;
					}

					if ((HWND) lParam == Q_sc.hScrInfo.EDIT_SCORE_GAMER_2) {
						SetBkColor  ((HDC) wParam, _BLACK);
						SetTextColor((HDC) wParam, Q_sc.hScrInfo.COLOR_RGB_GAMER_2);
						if(Q_sc.hBRUSH_BLACK == NULL)
							Q_sc.hBRUSH_BLACK = CreateSolidBrush(_BLACK);
						return (LRESULT) Q_sc.hBRUSH_BLACK;
					}

					if ((HWND) lParam == Q_sc.hScrInfo.EDIT_INFO_IP) {
						SetBkColor  ((HDC) wParam, _BLACK);
						SetTextColor((HDC) wParam, _GREEN);
						if(Q_sc.hBRUSH_BLACK == NULL)
							Q_sc.hBRUSH_BLACK = CreateSolidBrush(_BLACK);
						return (LRESULT) Q_sc.hBRUSH_BLACK;
					}

					break;

				case RESET_BTN:

					for(const auto& X : Q_sc.BtnQ)
						for(const auto& BTNQ : X) {
							EnableWindow(BTNQ, TRUE);
							GetClientRect((HWND) BTNQ, &Q_sc.RectQ);
							Q_sc.hDC = GetDC((HWND) BTNQ);
							Q_sc.hBRUSH = CreateSolidBrush(_BLACK);
							SelectObject(Q_sc.hDC, Q_sc.hBRUSH);
							Rectangle(Q_sc.hDC, Q_sc.RectQ.left, Q_sc.RectQ.top, Q_sc.RectQ.right, Q_sc.RectQ.bottom);
							ReleaseDC((HWND) BTNQ, Q_sc.hDC);
							DeleteObject(Q_sc.hBRUSH);
						}

					RedrawWindow(Q_sc.Btn_connect, NULL, NULL, RDW_INVALIDATE);

					Q.RESET();

					gamer_1.restart();
					gamer_2.restart(); 

					break;

				case REFRESH_SCREEN_INFO:

					switch((UINT16) wParam) {

						case 0x0000:
							Q_sc.hScrInfo.UNLOAD_COLOR_GAMER();
							Q_sc.hScrInfo.LOAD_COLOR_GAMER();
							break;

						case 0x0001:
							{
								std::vector <LPSTR> vArrayIPv4_LPStr = Network::GetIPv4();	
								for(const auto& IPv4_LPStr : vArrayIPv4_LPStr) {
									SendMessageA(Q_sc.hScrInfo.EDIT_INFO_IP, EM_SETSEL,     (WPARAM) 0,     (LPARAM) -1);
									SendMessageA(Q_sc.hScrInfo.EDIT_INFO_IP, EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) IPv4_LPStr);
								}
							}

							break;

						case 0x000A:

							SendMessageA(Q_sc.hScrInfo.EDIT_SCORE_GAMER_1, EM_SETSEL,     (WPARAM) 0,     (LPARAM) -1);
							SendMessageA(Q_sc.hScrInfo.EDIT_SCORE_GAMER_1, EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) std::to_string(gamer_1.score).c_str());

							break;

						case 0x000B:

							SendMessageA(Q_sc.hScrInfo.EDIT_SCORE_GAMER_2, EM_SETSEL,     (WPARAM) 0,     (LPARAM) -1);
							SendMessageA(Q_sc.hScrInfo.EDIT_SCORE_GAMER_2, EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) std::to_string(gamer_2.score).c_str());

							break;
					};


					if(Q_sc.hScrInfo.DIRECTION_GAMER_1 == Q::VERTICAL && Q_sc.hScrInfo.DIRECTION_GAMER_2 == Q::HORIZONTAL) {

						HDC hDC = GetDC(hwnd); 
						HBRUSH hBRUSH1 = CreateSolidBrush(Q_sc.hScrInfo.COLOR_RGB_GAMER_1);
						HBRUSH hBRUSH2 = CreateSolidBrush(Q_sc.hScrInfo.COLOR_RGB_GAMER_2);
						SelectObject(hDC, hBRUSH1);
						Rectangle(hDC, Xo, Yo-10, Xo+(L*N), Yo);
						Rectangle(hDC, Xo, Yo+(l*N), Xo+(L*N), Yo+(l*N)+10);	
						SelectObject(hDC, hBRUSH2);
						Rectangle(hDC, Xo-10, Yo, Xo, Yo+(l*N));
						Rectangle(hDC, Xo+(L*N), Yo, Xo+(L*N)+10, Yo+(l*N));
						ReleaseDC(hwnd, hDC);
						DeleteObject(hBRUSH1);
						DeleteObject(hBRUSH2);		


					}

					else if(Q_sc.hScrInfo.DIRECTION_GAMER_1 == Q::HORIZONTAL && Q_sc.hScrInfo.DIRECTION_GAMER_2 == Q::VERTICAL) {

						HDC hDC = GetDC(hwnd); 
						HBRUSH hBRUSH1 = CreateSolidBrush(Q_sc.hScrInfo.COLOR_RGB_GAMER_1);
						HBRUSH hBRUSH2 = CreateSolidBrush(Q_sc.hScrInfo.COLOR_RGB_GAMER_2);
						SelectObject(hDC, hBRUSH1);
						Rectangle(hDC, Xo-10, Yo, Xo, Yo+(l*N));
						Rectangle(hDC, Xo+(L*N), Yo, Xo+(L*N)+10, Yo+(l*N));
						SelectObject(hDC, hBRUSH2);	
						Rectangle(hDC, Xo, Yo-10, Xo+(L*N), Yo);
						Rectangle(hDC, Xo, Yo+(l*N), Xo+(L*N), Yo+(l*N)+10);	
						ReleaseDC(hwnd, hDC);
						DeleteObject(hBRUSH1);
						DeleteObject(hBRUSH2);	

					}

					break;

				case ID_REVERSE_DIRECTION:

					{
						int IDmsgBox = MessageBox(hwnd, "Voulez-vous inverser les directions ?", "", MB_ICONQUESTION | MB_YESNO);
						if (IDmsgBox == IDYES) {

							Q_sc.hScrInfo.DIRECTION_GAMER_1 = !Q_sc.hScrInfo.DIRECTION_GAMER_1;
							Q_sc.hScrInfo.DIRECTION_GAMER_2 = !Q_sc.hScrInfo.DIRECTION_GAMER_2;
							SendMessageA(hwnd, REFRESH_SCREEN_INFO, -1, -1);
						}
					}

					break;

				case WM_CREATE:

					WIN(0) = hwnd;
					if(Q_sc.Btn_connect == NULL) {
						Q_sc.Btn_connect = CreateWindowEx(
								WS_EX_OVERLAPPEDWINDOW,
								"BUTTON", 
								NULL,
								WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
								X_Y_Btn_connect,
								W_H_Btn_connect,
								hwnd,
								(HMENU) ID_BTN_CONNECT,
								(HINSTANCE) GetWindowLongPtrA(hwnd, GWLP_HINSTANCE),
								NULL);
					}

					if(Q_sc.hScrInfo.SYMBOL_BTNGAMER_1 == NULL) {
						Q_sc.hScrInfo.SYMBOL_BTNGAMER_1 = CreateWindowEx(
								WS_EX_OVERLAPPEDWINDOW,
								"BUTTON", 
								NULL,
								WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
								X_Y_SYMBOL_BTNGAMER_1,
								W_H_SYMBOL_BTNGAMER_1,
								hwnd,
								(HMENU) ID_SYMBOL_BTN_GAMER_1,
								(HINSTANCE) GetWindowLongPtrA(hwnd, GWLP_HINSTANCE),
								NULL);
					}

					if(Q_sc.hScrInfo.SYMBOL_BTNGAMER_2 == NULL) {
						Q_sc.hScrInfo.SYMBOL_BTNGAMER_2 = CreateWindowEx(
								WS_EX_OVERLAPPEDWINDOW,
								"BUTTON", 
								NULL,
								WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
								X_Y_SYMBOL_BTNGAMER_2,
								W_H_SYMBOL_BTNGAMER_2,
								hwnd,
								(HMENU) ID_SYMBOL_BTN_GAMER_2,
								(HINSTANCE) GetWindowLongPtrA(hwnd, GWLP_HINSTANCE),
								NULL);
					}

					if(Q_sc.hScrInfo.EDIT_SCORE_GAMER_1 == NULL) {
						Q_sc.hScrInfo.EDIT_SCORE_GAMER_1 = CreateWindowEx(
								WS_EX_OVERLAPPEDWINDOW,
								"EDIT",
								NULL,
								WS_VISIBLE | WS_CHILD | ES_CENTER | ES_READONLY, 
								X_Y_EDIT_SCORE_GAMER_1,
								W_H_EDIT_SCORE_GAMER_1,
								hwnd,
								(HMENU) ID_EDIT_SCORE_GAMER_1,
								(HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), 
								NULL);
					}


					if(Q_sc.hScrInfo.EDIT_SCORE_GAMER_2 == NULL) {
						Q_sc.hScrInfo.EDIT_SCORE_GAMER_2 = CreateWindowEx(
								WS_EX_OVERLAPPEDWINDOW,
								"EDIT",
								NULL,
								WS_VISIBLE | WS_CHILD | ES_CENTER | ES_READONLY, 
								X_Y_EDIT_SCORE_GAMER_2,
								W_H_EDIT_SCORE_GAMER_2,
								hwnd,
								(HMENU) ID_EDIT_SCORE_GAMER_2,
								(HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), 
								NULL);
					}


					if(Q_sc.hScrInfo.EDIT_INFO_IP == NULL) {
						Q_sc.hScrInfo.EDIT_INFO_IP = CreateWindowEx(
								WS_EX_OVERLAPPEDWINDOW,
								"EDIT",
								NULL,
								WS_VISIBLE | WS_CHILD | ES_CENTER | ES_READONLY,
								X_Y_EDIT_INFO_IP,
								W_H_EDIT_INFO_IP, 
								hwnd,
								(HMENU) ID_EDIT_INFO_IP,
								(HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), 
								NULL);
					}

					if(Q_sc.hScrInfo.hFONT_EDIT_SCORE_GAMER == NULL)
						Q_sc.hScrInfo.hFONT_EDIT_SCORE_GAMER = CreateFontA(
								12,
								0,
								0,
								0,
								FW_BLACK,
								FALSE,
								FALSE,
								FALSE,
								ANSI_CHARSET,
								OUT_DEFAULT_PRECIS,
								CLIP_DEFAULT_PRECIS,
								CLEARTYPE_QUALITY,
								VARIABLE_PITCH,
								TEXT("Terminal")
								);

					SendMessageA(Q_sc.hScrInfo.EDIT_SCORE_GAMER_1, WM_SETFONT, (WPARAM) Q_sc.hScrInfo.hFONT_EDIT_SCORE_GAMER, TRUE);
					SendMessageA(Q_sc.hScrInfo.EDIT_SCORE_GAMER_2, WM_SETFONT, (WPARAM) Q_sc.hScrInfo.hFONT_EDIT_SCORE_GAMER, TRUE);

					if(Q_sc.hScrInfo.hFONT_EDIT_INFO_IP == NULL)
						Q_sc.hScrInfo.hFONT_EDIT_INFO_IP = CreateFontA(
								14,
								0,
								0,
								0,
								FW_BLACK,
								FALSE,
								FALSE,
								FALSE,
								ANSI_CHARSET,
								OUT_DEFAULT_PRECIS,
								CLIP_DEFAULT_PRECIS,
								CLEARTYPE_QUALITY,
								VARIABLE_PITCH,
								TEXT("MS Shell Dlg 2")
								);

					SendMessageA(Q_sc.hScrInfo.EDIT_INFO_IP, WM_SETFONT, (WPARAM) Q_sc.hScrInfo.hFONT_EDIT_INFO_IP, TRUE);

					if(Q_sc.BtnQ[0][0] == NULL) {
						Q.init_Qn(Q_sc.Qn);
						for(int j=0; j<N; j++)
							for(int k=0; k<N; k++){
								Q_sc.BtnQ[j][k] = CreateWindowEx(
										WS_EX_OVERLAPPEDWINDOW,
										"BUTTON", 
										NULL,
										WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
										(Xo+(L*k)), (Yo+(l*j)),
										L, l,
										hwnd,
										(HMENU) IntToPtr(Q_sc.Qn[j][k]),
										(HINSTANCE) GetWindowLongPtrA(hwnd, GWLP_HINSTANCE),
										NULL);
								Q.Empty_Qn.push_back(Q_sc.Qn[j][k]);
							}
					}

					if(Q_sc.hBRUSH_BLACK == NULL)
						Q_sc.hBRUSH_BLACK = CreateSolidBrush(_BLACK);
					SetClassLongPtrA(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR) Q_sc.hBRUSH_BLACK);

					SendMessageA(hwnd, REFRESH_SCREEN_INFO, (WPARAM) 0x0000, -1);
					SendMessageA(hwnd, REFRESH_SCREEN_INFO, (WPARAM) 0x0001, -1);
					SendMessageA(hwnd, REFRESH_SCREEN_INFO, (WPARAM) 0x000A, -1);
					SendMessageA(hwnd, REFRESH_SCREEN_INFO, (WPARAM) 0x000B, -1);


					break;

				case CLICK_CONNEXION:


				  	MessageBox(hwnd, "Programmation <jouer à 2 en ligne> en cours .... de construction!", "", MB_ICONINFORMATION | MB_OK);
	
					if(THREAD.joinable()) {
						UINT16 msgID = MessageBox(
								hwnd,
								"Voulez-vous eteindre la connexion ouvert ?",
								"",
								MB_ICONQUESTION | MB_YESNO
								);

						if(msgID == IDYES) {
							if(SERVER.is_open)
								SERVER.closing();
							if(JOIN.is_bind)
								JOIN.closing();
							THREAD.detach();
						}

						RedrawWindow(Q_sc.Btn_connect, NULL, NULL, RDW_INVALIDATE);

					} else
						if(WIN(1) == NULL) {
							WIN(1) = CreateDialogA(
									(HINSTANCE) GetWindowLongPtrA(hwnd, GWLP_HINSTANCE),
									MAKEINTRESOURCEA(ID_DIALOG_CHOOSE),
									hwnd,
									(DLGPROC) hDlgEvent_CHOOSE
									);
							ShowWindow(WIN(1), SW_SHOW);
							QUAD_STATIC::execDlg(&WIN(1));

						} else {
							MessageBox(
									NULL,
									"Veuillez réessayer!",
									NULL,
									MB_ICONERROR | MB_OK);
						}

					break;

				case WM_DESTROY:

					DeleteObject(Q_sc.hPEN);                            Q_sc.hPEN = NULL;
					DeleteObject(Q_sc.hBRUSH);                          Q_sc.hBRUSH = NULL;
					DeleteObject(Q_sc.hBRUSH_BLACK);                    Q_sc.hBRUSH_BLACK = NULL;
					DeleteObject(Q_sc.hScrInfo.hBRUSH_BTNGAMER_1);      Q_sc.hScrInfo.hBRUSH_BTNGAMER_1 = NULL; 
					DeleteObject(Q_sc.hScrInfo.hBRUSH_BTNGAMER_2);      Q_sc.hScrInfo.hBRUSH_BTNGAMER_2 = NULL;
					DeleteObject(Q_sc.hScrInfo.hFONT_EDIT_SCORE_GAMER); Q_sc.hScrInfo.hFONT_EDIT_SCORE_GAMER = NULL;
					DeleteObject(Q_sc.hScrInfo.hFONT_EDIT_INFO_IP);     Q_sc.hScrInfo.hFONT_EDIT_INFO_IP = NULL;


					PostQuitMessage(0);

					break;													 
			};

			return DefWindowProcA(
					hwnd, 
					Msg, 
					wParam, 
					lParam);
		};



		// =============================== ID_DIALOG_CHOOSE ===============================

		static BOOL CALLBACK hDlgEvent_CHOOSE(
				HWND hwndDlg,
				UINT Msg,
				WPARAM wParam,
				LPARAM lParam) {

			static PhDesigner phD;
			static HBRUSH hBRUSH_BKG;

			switch(Msg) {

				case WM_CTLCOLORDLG:
					if(hBRUSH_BKG == NULL)
						hBRUSH_BKG = CreateSolidBrush(_BLACK);		
					return (INT_PTR) hBRUSH_BKG;

				case WM_CTLCOLORBTN:
					if(hBRUSH_BKG == NULL)
						hBRUSH_BKG = CreateSolidBrush(_BLACK);		
					return (INT_PTR) hBRUSH_BKG;

				case WM_DRAWITEM:    

					if(((LPDRAWITEMSTRUCT) lParam)->CtlID == ID_BTN_SERVER) {

						phD = new hDesigner;

						phD->pDrawItem = (LPDRAWITEMSTRUCT) lParam;


						if(phD->pDrawItem->itemState & ODS_FOCUS)
							if(phD->pDrawItem->itemState & ODS_SELECTED)
								phD->hPEN = CreatePen(PS_INSIDEFRAME, PEN_SZ_0x0, _GREEN);
							else 
								phD->hPEN = CreatePen(PS_INSIDEFRAME, PEN_SZ_0x0, _RED);	
						else 
							phD->hPEN = CreatePen(PS_INSIDEFRAME, PEN_SZ_0x0, _WHITE);

						phD->hBRUSH    = CreateSolidBrush(_BLACK);
						phD->pTextHWND = L"Serveur";

						SendMessageA(hwndDlg, DRAWITEMS_HWND, (WPARAM) phD, -1);
					}


					if(((LPDRAWITEMSTRUCT) lParam)->CtlID == ID_BTN_JOIN) {

						phD = new hDesigner;

						phD->pDrawItem = (LPDRAWITEMSTRUCT) lParam;


						if(phD->pDrawItem->itemState & ODS_FOCUS)
							if(phD->pDrawItem->itemState & ODS_SELECTED)
								phD->hPEN = CreatePen(PS_INSIDEFRAME, PEN_SZ_0x0, _GREEN);
							else 
								phD->hPEN = CreatePen(PS_INSIDEFRAME, PEN_SZ_0x0, _RED);	
						else 
							phD->hPEN = CreatePen(PS_INSIDEFRAME, PEN_SZ_0x0, _WHITE);

						phD->hBRUSH    = CreateSolidBrush(_BLACK);
						phD->pTextHWND = L"Joindre";

						SendMessageA(hwndDlg, DRAWITEMS_HWND, (WPARAM) phD, -1);
					}

					break;

				case DRAWITEMS_HWND:

					phD = (PhDesigner) wParam;

					phD->hFONT = CreateFontA(
							14,
							0,
							0,
							0,
							FW_BLACK,
							FALSE,
							FALSE,
							FALSE,
							ANSI_CHARSET,
							OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,
							CLEARTYPE_QUALITY,
							VARIABLE_PITCH,
							TEXT("Terminal")
							);

					SelectObject(phD->pDrawItem->hDC, phD->hFONT);
					SelectObject(phD->pDrawItem->hDC, phD->hPEN);
					SelectObject(phD->pDrawItem->hDC, phD->hBRUSH);

					SetBkColor  (phD->pDrawItem->hDC, _BLACK);
					SetTextColor(phD->pDrawItem->hDC, _GREEN);

					Rectangle(
							phD->pDrawItem->hDC, 
							phD->pDrawItem->rcItem.left, 
							phD->pDrawItem->rcItem.top, 
							phD->pDrawItem->rcItem.right, 
							phD->pDrawItem->rcItem.bottom
							);

					DrawTextW(
							phD->pDrawItem->hDC,
							phD->pTextHWND,
							-1,
							&phD->pDrawItem->rcItem, 
							DT_CENTER | DT_VCENTER | DT_SINGLELINE
							);

					DeleteObject(phD->hFONT);
					DeleteObject(phD->hPEN);
					DeleteObject(phD->hBRUSH);
					delete phD; phD = nullptr;

					break;

				case TRY_OPEN_SERVER:

					if(THREAD.joinable())
						THREAD.detach();
					if(SERVER.open((UINT16) lParam))
						THREAD = std::thread(&SERVER.Run, &SERVER);
					break;

				case TRY_JOIN_SERVER:

					if(THREAD.joinable())
						THREAD.detach();					
					if(JOIN.open((LPCSTR) wParam, (UINT16) lParam))
						THREAD = std::thread(&JOIN.Run, &JOIN);
					break;

				case WM_COMMAND:

					switch(LOWORD(wParam)) {

						case ID_BTN_SERVER:
							if(WIN(2) == NULL) {
								WIN(2) = CreateDialogParamA(
										(HINSTANCE) GetWindowLongPtrA(hwndDlg, GWLP_HINSTANCE),
										MAKEINTRESOURCEA(ID_DIALOG_SOCKET),
										hwndDlg,
										(DLGPROC) hDlgEvent_SOCKET,
										(LPARAM) ID_BTN_SERVER
										);

								std::cout << " WIN_socket: "<< WIN(2) << std::endl;

							}

							ShowWindow(WIN(2), SW_SHOW); 
							QUAD_STATIC::execDlg(&WIN(2));
							break;

						case ID_BTN_JOIN:

							if(WIN(2) == NULL) {
								WIN(2) = CreateDialogParamA(
										(HINSTANCE) GetWindowLongPtrA(hwndDlg, GWLP_HINSTANCE),
										MAKEINTRESOURCEA(ID_DIALOG_SOCKET),
										hwndDlg,
										(DLGPROC) hDlgEvent_SOCKET,
										(LPARAM) ID_DIALOG_SOCKET
										);

								std::cout << " WIN_socket: "<< WIN(2) << std::endl;

							}

							ShowWindow(WIN(2), SW_SHOW); 
							QUAD_STATIC::execDlg(&WIN(2));
							break;

						case ID_ESCAPE:
							DestroyWindow(hwndDlg);
							break;

						case ID_BACK:
							DestroyWindow(hwndDlg);
							break;

						case ID_DELETE:
							DestroyWindow(hwndDlg);
							break;
					}

					break;

				case WM_CLOSE: 
					DestroyWindow(hwndDlg);
					break;

				case WM_DESTROY:
					if(SERVER.is_open)
						SendMessageA(WIN(0), RESET_BTN, -1, -1);
					if(JOIN.is_bind)
						SendMessageA(WIN(0), RESET_BTN, -1, -1);

					DeleteObject(hBRUSH_BKG); hBRUSH_BKG = NULL;
					WIN(1) = NULL;
					PostQuitMessage(0);
					break;

				default:
					return FALSE;
			}

			return TRUE;
		};


		// =============================== ID_DIALOG_SOCKET ===============================

		static BOOL CALLBACK hDlgEvent_SOCKET(
				HWND hwndDlg,
				UINT Msg,
				WPARAM wParam,
				LPARAM lParam){

			static PhDesigner phD;
			static HBRUSH     hBRUSH_BKG;

			std::string IP_str;
			std::string PORT_str;
			DB db;

			std::vector <std::string> v_dataDB;

			switch(Msg) {

				case WM_CTLCOLORDLG:
					if(hBRUSH_BKG == NULL)
						hBRUSH_BKG = CreateSolidBrush(_BLACK);		
					return (INT_PTR) hBRUSH_BKG;

				case WM_CTLCOLORBTN:
					if(hBRUSH_BKG == NULL)
						hBRUSH_BKG = CreateSolidBrush(_BLACK);		
					return (INT_PTR) hBRUSH_BKG;

				case WM_DRAWITEM:    

					if(((LPDRAWITEMSTRUCT) lParam)->CtlID == ID_BTN_OK) {

						phD = new hDesigner;

						phD->pDrawItem = (LPDRAWITEMSTRUCT) lParam;


						if(phD->pDrawItem->itemState & ODS_FOCUS)
							if(phD->pDrawItem->itemState & ODS_SELECTED)
								phD->hPEN = CreatePen(PS_INSIDEFRAME, PEN_SZ_0x0, _GREEN);
							else 
								phD->hPEN = CreatePen(PS_INSIDEFRAME, PEN_SZ_0x0, _RED);	
						else 
							phD->hPEN = CreatePen(PS_INSIDEFRAME, PEN_SZ_0x0, _WHITE);

						phD->hBRUSH    = CreateSolidBrush(_BLACK);
						phD->pTextHWND = L"OK";

						SendMessageA(hwndDlg, DRAWITEMS_HWND, (WPARAM) phD, -1);

					}

					break;

				case DRAWITEMS_HWND:

					phD = (PhDesigner) wParam;

					phD->hFONT = CreateFontA(
							12,
							0,
							0,
							0,
							FW_BLACK,
							FALSE,
							FALSE,
							FALSE,
							ANSI_CHARSET,
							OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,
							CLEARTYPE_QUALITY,
							VARIABLE_PITCH,
							TEXT("Terminal")
							);

					SelectObject(phD->pDrawItem->hDC, phD->hFONT);
					SelectObject(phD->pDrawItem->hDC, phD->hPEN);
					SelectObject(phD->pDrawItem->hDC, phD->hBRUSH);

					SetBkColor  (phD->pDrawItem->hDC, _BLACK);
					SetTextColor(phD->pDrawItem->hDC, _GREEN);

					Rectangle(
							phD->pDrawItem->hDC, 
							phD->pDrawItem->rcItem.left, 
							phD->pDrawItem->rcItem.top, 
							phD->pDrawItem->rcItem.right, 
							phD->pDrawItem->rcItem.bottom
							);

					DrawTextW(
							phD->pDrawItem->hDC,
							phD->pTextHWND,
							-1,
							&phD->pDrawItem->rcItem, 
							DT_CENTER | DT_VCENTER | DT_SINGLELINE
							);

					DeleteObject(phD->hFONT);
					DeleteObject(phD->hPEN);
					DeleteObject(phD->hBRUSH);
					delete phD; phD = nullptr;

					break;

				case WM_INITDIALOG:

					SendMessage(GetDlgItem(hwndDlg, ID_EDIT_IP),   EM_SETLIMITTEXT, (WPARAM)  strlen("XXX.XXX.XXX.XXX"), -1);
					SendMessage(GetDlgItem(hwndDlg, ID_EDIT_PORT), EM_SETLIMITTEXT, (WPARAM)  strlen("XXXXX"), -1);

					if((UINT16) lParam == ID_BTN_SERVER) {
						SetFocus  (GetDlgItem(hwndDlg, ID_EDIT_PORT));
						ShowWindow(GetDlgItem(hwndDlg, ID_EDIT_IP), SW_HIDE);
					}

					if(db.loadDB(FILE_IPPORT))
						v_dataDB = db.read(':');
					db.closeDB();

					if(!v_dataDB.empty()) {
						if(!v_dataDB[0].empty()) {
							SendMessageA(GetDlgItem(hwndDlg, ID_EDIT_IP), EM_SETSEL,     (WPARAM) 0,     (LPARAM) -1);
							SendMessageA(GetDlgItem(hwndDlg, ID_EDIT_IP), EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) v_dataDB[0].c_str());
						}

						if(!v_dataDB[1].empty()) {
							SendMessageA(GetDlgItem(hwndDlg, ID_EDIT_PORT), EM_SETSEL,     (WPARAM) 0,     (LPARAM) -1);
							SendMessageA(GetDlgItem(hwndDlg, ID_EDIT_PORT), EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) v_dataDB[1].c_str());
						}
					}
					SendMessageA(GetDlgItem(hwndDlg, ID_EDIT_IP),   EM_SETSEL,     (WPARAM) -1,     (LPARAM) -1);
					SendMessageA(GetDlgItem(hwndDlg, ID_EDIT_PORT), EM_SETSEL,     (WPARAM) -1,     (LPARAM) -1);


					break;

				case WM_CTLCOLOREDIT:
					SetBkColor ((HDC) wParam, _BLACK);
					if((HWND) lParam == GetDlgItem(hwndDlg, ID_EDIT_IP))
						SetTextColor((HDC) wParam, _CYAN);
					if((HWND) lParam == GetDlgItem(hwndDlg, ID_EDIT_PORT))
						SetTextColor((HDC) wParam, _YELLOW);
					break;


				case WM_COMMAND:

					if(HIWORD(wParam) == EN_UPDATE)
						if(LOWORD(wParam) == ID_EDIT_IP) {
							std::string edit;
							edit = to::str(&hwndDlg, ID_EDIT_IP);
							if(strlen(edit.c_str()) == 3) {
								SendMessageA(GetDlgItem(hwndDlg, ID_EDIT_IP), EM_SETSEL,     (WPARAM) 0,     (LPARAM) -1);
								SendMessageA(GetDlgItem(hwndDlg, ID_EDIT_IP), EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) (edit + ".").c_str());	
							}

							else if(strlen(edit.c_str()) == 7) {
								SendMessageA(GetDlgItem(hwndDlg, ID_EDIT_IP), EM_SETSEL,     (WPARAM) 0,     (LPARAM) -1);
								SendMessageA(GetDlgItem(hwndDlg, ID_EDIT_IP), EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) (edit + ".").c_str());	
							}

							else if(strlen(edit.c_str()) == 11) {
								SendMessageA(GetDlgItem(hwndDlg, ID_EDIT_IP), EM_SETSEL,     (WPARAM) 0,     (LPARAM) -1);
								SendMessageA(GetDlgItem(hwndDlg, ID_EDIT_IP), EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) (edit + ".").c_str());	
							}

						}

					switch(LOWORD(wParam)) {

						case ID_BTN_OK:

							IP_str = to::str(&hwndDlg, ID_EDIT_IP);

							if(to::str(&hwndDlg, ID_EDIT_PORT).empty())
								PORT_str = EDIT_DEFAULT_PORT;
							else
								PORT_str = to::str(&hwndDlg, ID_EDIT_PORT);

							if(db.loadDB(FILE_IPPORT))
								db.save(IP_str + ":" + PORT_str);
							db.closeDB();

							std::cout << IP_str << ":" << PORT_str << std::endl;

							if(IsWindowVisible(GetDlgItem(hwndDlg, ID_EDIT_IP)))
								SendMessageA(WIN(1), TRY_JOIN_SERVER, (WPARAM) IP_str.c_str(), (LPARAM) std::stoi(PORT_str));
							else
								SendMessageA(WIN(1), TRY_OPEN_SERVER, -1, (LPARAM) std::stoi(PORT_str));

							DestroyWindow(hwndDlg);

							break;

						case ID_ESCAPE:
							DestroyWindow(hwndDlg);
							break;

						case ID_BACK:
							if(GetFocus() == GetDlgItem(hwndDlg, ID_EDIT_IP))
								SendMessageA(GetDlgItem(hwndDlg, ID_EDIT_IP), WM_SETTEXT, -1, (LPARAM) "");
							break;

						case ID_TAB:
							if(GetFocus() == GetDlgItem(hwndDlg, ID_EDIT_IP))
								SetFocus(GetDlgItem(hwndDlg, ID_EDIT_PORT));
							else if(GetFocus() == GetDlgItem(hwndDlg, ID_EDIT_PORT))
								SetFocus(GetDlgItem(hwndDlg, ID_EDIT_IP));

							break;
					}

					break;

				case WM_CLOSE: 
					DestroyWindow(hwndDlg);
					break;

				case WM_DESTROY:
					DeleteObject(hBRUSH_BKG); hBRUSH_BKG = NULL;
					WIN(2) = NULL;
					PostQuitMessage(0);
					break;
					SetFocus(GetDlgItem(hwndDlg, ID_EDIT_PORT));
				default:
					return FALSE;
			}

			return TRUE;
		};

};

#endif








