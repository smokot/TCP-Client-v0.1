#pragma once
#include "windows.h"
#include "winsock.h"
#include "string"
#include "vector"
#include "Buttons.h"
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
using namespace std;
vector<SOCKET>connections;


void press_return()
{
	while (1)
	{
		int ctrl= GetAsyncKeyState(VK_CONTROL);
		int enter= GetAsyncKeyState(VK_RETURN);

		if (ctrl && enter)
		{
			EnableWindow(hButtonSend, false);
			
			char buf[40000] = "";

			GetWindowText(hRichEditChatSend, buf, 40000);
			send(sock, buf, sizeof(buf), 0);
			SetWindowText(hRichEditChatSend, "");
			
		
			EnableWindow(hButtonSend, true);

		}
		
	}
}



void append_text(HWND hwnd, char * buf)
{
	SendMessage(hwnd, EM_SETSEL, -1, -1);
	SendMessage(hwnd, EM_REPLACESEL, FALSE, LPARAM("\n"));
	SendMessage(hwnd, EM_REPLACESEL, FALSE, LPARAM(buf));
}

void client_handler(SOCKET sock)
{
	char buf[2048]="";
	char buf_two[2048] = "";
	vector<char>buffer;
	while (1)
	{
		
		int res = recv(sock, buf, sizeof(buf), 0);
		
		
		
		if (res>0) {
			
			if (buf[0] == '\0' && buf[1] == '\0')continue;
			append_text(hRichEditChat, buf);
			
			
		}
		if (res <= 0) {
			MessageBox(NULL, "Потеряно соединение с сервером", "ВНИМАНИЕ", MB_OK);
			ExitProcess(1);
			ExitThread(0);
		}
	}
}