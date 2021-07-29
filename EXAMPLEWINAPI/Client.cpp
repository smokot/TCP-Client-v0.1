#include "windows.h"
#include "winsock.h"
#include "Buttons.h"
#include "Func.h"
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
using namespace std;
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
HINSTANCE savehinst = NULL;






LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		
		


		case WM_CREATE:
		{
			LoadLibrary("Riched32.dll");



			hButtonConnect = CreateWindow("BUTTON", "CONNECT", 
				WS_CHILD |WS_VISIBLE| BS_PUSHBUTTON,
				200, 0, 200, 30, hwnd,reinterpret_cast<HMENU>(1), savehinst, NULL);
			
			hButtonSend = CreateWindow("BUTTON", "SEND",
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				483, 470, 100, 80, hwnd, reinterpret_cast<HMENU>(2), savehinst, NULL);



			hEditIp = CreateWindow("edit", "127.0.0.1",
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				0, 0, 150, 20, hwnd, 0, savehinst, NULL);

			hEditPort = CreateWindow("edit", "25565",
				WS_CHILD | WS_VISIBLE | WS_BORDER ,
				0, 22, 150, 20, hwnd, 0, savehinst, NULL);

			hRichEditChat = CreateWindow("richedit", "here chat\n",
				WS_CHILD | WS_VISIBLE | ES_READONLY | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL ,
				0, 50, 583, 400, hwnd, 0, savehinst, NULL);
			

			hRichEditChatSend = CreateWindow("richedit", "",
				WS_CHILD | WS_VISIBLE |  WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
				0, 470, 480, 80, hwnd, 0, savehinst, NULL);
			
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(1);
			break;
		}
		case WM_COMMAND:
		{
			switch (wParam)
			{
				case 1:
				{
					
					EnableWindow(hButtonConnect, false);
					GetWindowText(hEditIp, ip_addr, 255);
					TCHAR buf[256] = "";
					GetWindowText(hEditPort, buf, 255);
					port = atoi(buf);

					WSAData WSD;
					WSAStartup(MAKEWORD(2, 1), &WSD);

					sockaddr_in addr;

					addr.sin_addr.S_un.S_addr = inet_addr(ip_addr);
					addr.sin_family = (AF_INET);
					addr.sin_port = htons(port);

					sock = socket(AF_INET, SOCK_STREAM, 0);

					connect(sock, (sockaddr*)&addr, sizeof(addr));




					CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(client_handler), LPVOID(sock), NULL, NULL);
					CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(press_return), NULL, NULL, NULL);

					
					break;
				}

				case 2:
				{
					char buf[40000]="";

					GetWindowText(hRichEditChatSend, buf, 40000);
					send(sock, buf, sizeof(buf), 0);

					break;
				}
			}
			break;
		}
	}



	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}








int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.lpszClassName = "CLIENT";
	RegisterClassEx(&wc);

	savehinst = hInstance;

	hwnd = CreateWindow(wc.lpszClassName, "Client",
		WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX, 300, 200, 600, 600,
		NULL, NULL, wc.hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}



	return static_cast<int>(msg.wParam);
}