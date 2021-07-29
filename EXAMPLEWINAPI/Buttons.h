#pragma once
#include "windows.h"
TCHAR ip_addr[255] ="";
int port = 0;

SOCKET sock = 0;


extern HWND hRichEditChat = NULL;
extern HWND hRichEditChatSend = NULL;

extern HWND hEditIp = NULL;
extern HWND hEditPort = NULL;

extern HWND hButtonConnect = NULL;
extern HWND hButtonSend = NULL;