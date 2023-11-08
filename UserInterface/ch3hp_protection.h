#include "StdAfx.h"
#if defined(__ENABLE_CH3HP_PROTECTION__)

#define CURL_STATICLIB
#include <curl/curl.h>

#pragma comment (lib, "crypt32.lib")
#pragma comment (lib, "advapi32")
#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "wldap32.lib")
#pragma comment (lib, "normaliz.lib")

#ifdef _WIN32
	#ifdef _DEBUG
		#pragma comment( lib, "libcurl_a_debug.lib" )
	#else
		#pragma comment( lib, "libcurl_a.lib" )
	#endif
#endif

static size_t CH3HP_WriteResponseCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

bool CH3HP_CheckWebResponse()
{
	CURL* _c;
	if (!(_c = curl_easy_init()))
		return false;
	
	std::string _rBffr;
	curl_easy_setopt(_c, CURLOPT_URL, REGIST_WEBSITE_LINK);
	curl_easy_setopt(_c, CURLOPT_WRITEFUNCTION, CH3HP_WriteResponseCallback);
	curl_easy_setopt(_c, CURLOPT_WRITEDATA, &_rBffr);
	
	CURLcode _r = curl_easy_perform(_c);
	curl_easy_cleanup(_c);
	
	return (_r == CURLE_OK);
}
#endif
