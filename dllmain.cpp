// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#pragma pack(1)

HINSTANCE hLThis = 0;
HINSTANCE hL = 0;
FARPROC p[40] = { 0 };
TCHAR systemPath[MAX_PATH * 2] = { 0 };

TCHAR hostname[16] = { 0 };
TCHAR ipList[5];
PTCHAR ipListPtr[1];
HOSTENT hostentMock;
TCHAR configFileSeparators[] = "=\n";
TCHAR ipAddressSeparators[] = ".";

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
		hLThis = hModule;

		// This code ensures that the original version of a DLL library
		// will be read from the system folder. It is not really needed
		// here because 'ws2_32.dll' is on the known DLL list so it will
		// be always read from the system folder.
		if (!GetSystemDirectory(systemPath, MAX_PATH)) return FALSE;
		if (PathAddBackslash(systemPath) == NULL) return FALSE;
		if (StringCchCat(systemPath, MAX_PATH, "webio.org.dll") != S_OK) return FALSE;

		hL = LoadLibrary(systemPath);
		if (0 == hL) return FALSE;

#if 1
		p[0] = GetProcAddress(hL, (LPCSTR)1);
		p[1] = GetProcAddress(hL, (LPCSTR)4);
		p[2] = GetProcAddress(hL, (LPCSTR)5);
		p[3] = GetProcAddress(hL, (LPCSTR)8);
		p[4] = GetProcAddress(hL, (LPCSTR)9);
		p[5] = GetProcAddress(hL, (LPCSTR)10);
		p[6] = GetProcAddress(hL, (LPCSTR)11);
		p[7] = GetProcAddress(hL, (LPCSTR)14);
		p[8] = GetProcAddress(hL, (LPCSTR)15);
		p[9] = GetProcAddress(hL, (LPCSTR)17);
		p[10] = GetProcAddress(hL, (LPCSTR)18);
		p[11] = GetProcAddress(hL, (LPCSTR)19);
		p[12] = GetProcAddress(hL, (LPCSTR)20);
		p[13] = GetProcAddress(hL, (LPCSTR)21);
		p[14] = GetProcAddress(hL, (LPCSTR)22);
		p[15] = GetProcAddress(hL, (LPCSTR)23);
		p[16] = GetProcAddress(hL, (LPCSTR)24);
		p[17] = GetProcAddress(hL, (LPCSTR)25);
		p[18] = GetProcAddress(hL, (LPCSTR)26);
		p[19] = GetProcAddress(hL, (LPCSTR)27);
		p[20] = GetProcAddress(hL, (LPCSTR)28);
		p[21] = GetProcAddress(hL, (LPCSTR)29);
		p[22] = GetProcAddress(hL, (LPCSTR)31);
		p[23] = GetProcAddress(hL, (LPCSTR)32);
		p[24] = GetProcAddress(hL, (LPCSTR)33);
		p[25] = GetProcAddress(hL, (LPCSTR)35);
		p[26] = GetProcAddress(hL, (LPCSTR)36);
		p[27] = GetProcAddress(hL, (LPCSTR)37);
		p[28] = GetProcAddress(hL, (LPCSTR)38);
		p[29] = GetProcAddress(hL, (LPCSTR)39);
		p[30] = GetProcAddress(hL, (LPCSTR)40);
		p[31] = GetProcAddress(hL, (LPCSTR)41);
		p[32] = GetProcAddress(hL, (LPCSTR)42);
		p[33] = GetProcAddress(hL, (LPCSTR)43);
		p[34] = GetProcAddress(hL, (LPCSTR)44);
		p[35] = GetProcAddress(hL, (LPCSTR)45);
		p[36] = GetProcAddress(hL, (LPCSTR)46);
		p[37] = GetProcAddress(hL, (LPCSTR)47);
		p[38] = GetProcAddress(hL, (LPCSTR)48);
		p[39] = GetProcAddress(hL, (LPCSTR)49);
#else
		p[0] = GetProcAddress(hL, "WebCancelHttpRequest");
		p[1] = GetProcAddress(hL, "WebCloseHttpRequest");
		p[2] = GetProcAddress(hL, "WebCloseSession");
		p[3] = GetProcAddress(hL, "WebCreateHttpRequest");
		p[4] = GetProcAddress(hL, "WebCreateSession");
		p[5] = GetProcAddress(hL, "WebCreateUri");
		p[6] = GetProcAddress(hL, "WebDeleteUri");
		p[7] = GetProcAddress(hL, "WebFlushCookies");
		p[8] = GetProcAddress(hL, "WebGetCookies");
		p[9] = GetProcAddress(hL, "WebInitialize");
		p[10] = GetProcAddress(hL, "WebQueryHttpRequestOption");
		p[11] = GetProcAddress(hL, "WebQueryHttpResponseHeaders");
		p[12] = GetProcAddress(hL, "WebQueryHttpResponseReasonPhrase");
		p[13] = GetProcAddress(hL, "WebQueryHttpResponseStatusCode");
		p[14] = GetProcAddress(hL, "WebQueryHttpResponseVersion");
		p[15] = GetProcAddress(hL, "WebReceiveHttpResponse");
		p[16] = GetProcAddress(hL, "WebReceiveHttpResponseEntity");
		p[17] = GetProcAddress(hL, "WebSendHttpRequest");
		p[18] = GetProcAddress(hL, "WebSendHttpRequestEntity");
		p[19] = GetProcAddress(hL, "WebSetCookie");
		p[20] = GetProcAddress(hL, "WebSetHttpRequestHeader");
		p[21] = GetProcAddress(hL, "WebSetHttpRequestOption");
		p[22] = GetProcAddress(hL, "WebTerminate");
		p[23] = GetProcAddress(hL, "WebSetHttpRequestInformationRoutine");
		p[24] = GetProcAddress(hL, "WebRemoveHttpRequestInformationRoutine");
		p[25] = GetProcAddress(hL, "WebCompleteProtocolUpgrade");
		p[26] = GetProcAddress(hL, "WebSendProtocolData");
		p[27] = GetProcAddress(hL, "WebReceiveProtocolData");
		p[28] = GetProcAddress(hL, "WebCloseProtocolHandle");
		p[29] = GetProcAddress(hL, "WebCancelProtocolHandle");
		p[30] = GetProcAddress(hL, "WebQueryProtocolOption");
		p[31] = GetProcAddress(hL, "WebSetProtocolOption");
		p[32] = GetProcAddress(hL, "WebPurgeKeepAlives");
		p[33] = GetProcAddress(hL, "WebCreateStaticResolverCacheEntry");
		p[34] = GetProcAddress(hL, "WebGetTunnelSocket");
		p[35] = GetProcAddress(hL, "WebSetHeapExtensionInterfaces");
		p[36] = GetProcAddress(hL, "WebQueryHttpResponseTrailers");
		p[37] = GetProcAddress(hL, "WebSetResolverCacheProperties");
		p[38] = GetProcAddress(hL, "WebQueryConnectionGroup");
		p[39] = GetProcAddress(hL, "WebQueryConnectionGroupForRequest");
#endif
	}
    case DLL_THREAD_ATTACH:
	
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		FreeLibrary(hL);
        break;
    }
    return TRUE;
}


// WebCancelHttpRequest
extern "C" __declspec(naked) void __stdcall WebCancelHttpRequest()
{
	__asm
	{
		jmp p[0 * 4];
	}
}
// WebCloseHttpRequest
extern "C" __declspec(naked) void __stdcall WebCloseHttpRequest()
{
	__asm
	{
		jmp p[1 * 4];
	}
}
// WebCloseSession
extern "C" __declspec(naked) void __stdcall WebCloseSession()
{
	__asm
	{
		jmp p[2 * 4];
	}
}
// WebCreateHttpRequest
extern "C" __declspec(naked) void __stdcall WebCreateHttpRequest()
{
	__asm
	{
		jmp p[3 * 4];
	}
}
// WebCreateSession
extern "C" __declspec(naked) void __stdcall WebCreateSession()
{
	__asm
	{
		jmp p[4 * 4];
	}
}
// WebCreateUri
extern "C" __declspec(naked) void __stdcall WebCreateUri()
{
	__asm
	{
		jmp p[5 * 4];
	}
}
// WebDeleteUri
extern "C" __declspec(naked) void __stdcall WebDeleteUri()
{
	__asm
	{
		jmp p[6 * 4];
	}
}
// WebFlushCookies
extern "C" __declspec(naked) void __stdcall WebFlushCookies()
{
	__asm
	{
		jmp p[7 * 4];
	}
}
// WebGetCookies
extern "C" __declspec(naked) void __stdcall WebGetCookies()
{
	__asm
	{
		jmp p[8 * 4];
	}
}
// WebInitialize
extern "C" __declspec(naked) void __stdcall WebInitialize()
{
	__asm
	{
		jmp p[9 * 4];
	}
}
// WebQueryHttpRequestOption
extern "C" __declspec(naked) void __stdcall WebQueryHttpRequestOption()
{
	__asm
	{
		jmp p[10 * 4];
	}
}
// WebQueryHttpResponseHeaders
extern "C" __declspec(naked) void __stdcall WebQueryHttpResponseHeaders()
{
	__asm
	{
		jmp p[11 * 4];
	}
}
// WebQueryHttpResponseReasonPhrase
extern "C" __declspec(naked) void __stdcall WebQueryHttpResponseReasonPhrase()
{
	__asm
	{
		jmp p[12 * 4];
	}
}
// WebQueryHttpResponseStatusCode
extern "C" __declspec(naked) void __stdcall WebQueryHttpResponseStatusCode()
{
	__asm
	{
		jmp p[13 * 4];
	}
}
// WebQueryHttpResponseVersion
extern "C" __declspec(naked) void __stdcall WebQueryHttpResponseVersion()
{
	__asm
	{
		jmp p[14 * 4];
	}
}
// WebReceiveHttpResponse
extern "C" __declspec(naked) void __stdcall WebReceiveHttpResponse()
{
	__asm
	{
		jmp p[15 * 4];
	}
}
// WebReceiveHttpResponseEntity
extern "C" __declspec(naked) void __stdcall WebReceiveHttpResponseEntity()
{
	__asm
	{
		jmp p[16 * 4];
	}
}
// WebSendHttpRequest
extern "C" __declspec(naked) void __stdcall WebSendHttpRequest()
{
	__asm
	{
		jmp p[17 * 4];
	}
}
// WebSendHttpRequestEntity
extern "C" __declspec(naked) void __stdcall WebSendHttpRequestEntity()
{
	__asm
	{
		jmp p[18 * 4];
	}
}
// WebSetCookie
extern "C" __declspec(naked) void __stdcall WebSetCookie()
{
	__asm
	{
		jmp p[19 * 4];
	}
}
// WebSetHttpRequestHeader
extern "C" __declspec(naked) void __stdcall WebSetHttpRequestHeader()
{
	__asm
	{
		jmp p[20 * 4];
	}
}
// WebSetHttpRequestOption
extern "C" __declspec(naked) void __stdcall WebSetHttpRequestOption()
{
	__asm
	{
		jmp p[21 * 4];
	}
}
// WebTerminate
extern "C" __declspec(naked) void __stdcall WebTerminate()
{
	__asm
	{
		jmp p[22 * 4];
	}
}
// WebSetHttpRequestInformationRoutine
extern "C" __declspec(naked) void __stdcall WebSetHttpRequestInformationRoutine()
{
	__asm
	{
		jmp p[23 * 4];
	}
}
// WebRemoveHttpRequestInformationRoutine
extern "C" __declspec(naked) void __stdcall WebRemoveHttpRequestInformationRoutine()
{
	__asm
	{
		jmp p[24 * 4];
	}
}
// WebCompleteProtocolUpgrade
extern "C" __declspec(naked) void __stdcall WebCompleteProtocolUpgrade()
{
	__asm
	{
		jmp p[25 * 4];
	}
}
// WebSendProtocolData
extern "C" __declspec(naked) void __stdcall WebSendProtocolData()
{
	__asm
	{
		jmp p[26 * 4];
	}
}
// WebReceiveProtocolData
extern "C" __declspec(naked) void __stdcall WebReceiveProtocolData()
{
	__asm
	{
		jmp p[27 * 4];
	}
}
// WebCloseProtocolHandle
extern "C" __declspec(naked) void __stdcall WebCloseProtocolHandle()
{
	__asm
	{
		jmp p[28 * 4];
	}
}
// WebCancelProtocolHandle
extern "C" __declspec(naked) void __stdcall WebCancelProtocolHandle()
{
	__asm
	{
		jmp p[29 * 4];
	}
}
// WebQueryProtocolOption
extern "C" __declspec(naked) void __stdcall WebQueryProtocolOption()
{
	__asm
	{
		jmp p[30 * 4];
	}
}
// WebSetProtocolOption
extern "C" __declspec(naked) void __stdcall WebSetProtocolOption()
{
	__asm
	{
		jmp p[31 * 4];
	}
}
// WebPurgeKeepAlives
extern "C" __declspec(naked) void __stdcall WebPurgeKeepAlives()
{
	__asm
	{
		jmp p[32 * 4];
	}
}
// WebCreateStaticResolverCacheEntry
extern "C" __declspec(naked) void __stdcall WebCreateStaticResolverCacheEntry()
{
	__asm
	{
		jmp p[33 * 4];
	}
}
// WebGetTunnelSocket
extern "C" __declspec(naked) void __stdcall WebGetTunnelSocket()
{
	__asm
	{
		jmp p[34 * 4];
	}
}
// WebSetHeapExtensionInterfaces
extern "C" __declspec(naked) void __stdcall WebSetHeapExtensionInterfaces()
{
	__asm
	{
		jmp p[35 * 4];
	}
}
// WebQueryHttpResponseTrailers
extern "C" __declspec(naked) void __stdcall WebQueryHttpResponseTrailers()
{
	__asm
	{
		jmp p[36 * 4];
	}
}
// WebSetResolverCacheProperties
extern "C" __declspec(naked) void __stdcall WebSetResolverCacheProperties()
{
	__asm
	{
		jmp p[37 * 4];
	}
}
// WebQueryConnectionGroup
extern "C" __declspec(naked) void __stdcall WebQueryConnectionGroup()
{
	__asm
	{
		jmp p[38 * 4];
	}
}
// WebQueryConnectionGroupForRequest
extern "C" __declspec(naked) void __stdcall WebQueryConnectionGroupForRequest()
{
	__asm
	{
		jmp p[39 * 4];
	}
}
