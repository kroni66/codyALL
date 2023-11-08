#pragma once
#ifdef ENABLE_AUTO_TRANSLATE_WHISPER
#include <string>
#ifndef CURL_STATICLIB
#define CURL_STATICLIB
#endif
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>

class CGoogleTranslate : public CSingleton<CGoogleTranslate>
{
	public:
		CGoogleTranslate();
		~CGoogleTranslate();

		int run(int iType, std::string c_szName, std::string c_szChat);
	private:
		void* curl;
};
#endif
