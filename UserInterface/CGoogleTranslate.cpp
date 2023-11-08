#include "stdafx.h"
#ifdef ENABLE_AUTO_TRANSLATE_WHISPER
#include "CGoogleTranslate.h"
#include "PythonChat.h"
#include <boost/algorithm/string/replace.hpp>
#include <sys/timeb.h>

size_t write_data2(void *ptr, size_t size, size_t nmemb, void *stream) {
	std::string data((const char*) ptr, (size_t) size * nmemb);
	*((std::stringstream*) stream) << data;
	return size * nmemb;
}

CGoogleTranslate::CGoogleTranslate() {
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
}

CGoogleTranslate::~CGoogleTranslate() {
	curl_easy_cleanup(curl);
	curl_global_cleanup();
}

int CGoogleTranslate::run(int iType, std::string c_szName, std::string c_szChat) {
	std::string old_text = c_szChat;
	size_t p = old_text.find(":"), p2 = 0;
	std::string name = old_text.substr(0, p + 2);
	std::string new_text = old_text.substr(p + 2);

	std::vector<std::string> item;
	std::string newarg = "";
	p = new_text.find("|cffffc700|Hitem:");
	int j = 0;
	while (p != std::string::npos) {
		p2 = new_text.find("|h|r") + 4;
		newarg = new_text.substr(p, p2 - p);
		boost::replace_all(new_text, newarg.c_str(), "");
		item.push_back(newarg.c_str());
		p = new_text.find("|cffffc700|Hitem:");
		j += 1;
	}

	p = new_text.find("|cfff1e6c0|Hitem:");
	j = 0;
	while (p != std::string::npos) {
		p2 = new_text.find("|h|r") + 4;
		newarg = new_text.substr(p, p2 - p);
		boost::replace_all(new_text, newarg.c_str(), "");
		item.push_back(newarg.c_str());
		p = new_text.find("|cfff1e6c0|Hitem:");
		j += 1;
	}

	boost::replace_all(new_text, " ", "%20");

	if (new_text.size() > 0) {
		std::string lang = LocaleService_GetLocaleName();
		std::string strURL = "https://www.googleapis.com/language/translate/v2?key=AIzaSyBU_I0tRn6H5JVrjV6udqu259YBg939yVU&target=";
		strURL += lang;
		strURL += "&q=";
		strURL += new_text;

		curl_easy_setopt(curl, CURLOPT_URL, strURL.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");
		std::stringstream out;
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data2);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "\n");
		CURLcode res = curl_easy_perform(curl);
		if (res == CURLE_OK) {
			int i = 0;
			std::string new_text_trans = "";
			while(out.good()) {
				std::string SingleLine;
				getline(out, SingleLine, '\n');

				i++;
				if (i == 5) {
					size_t f = SingleLine.find("translatedText");
					if (f != std::string::npos) {
						std::string tmp = SingleLine.substr(f + 18);
						new_text_trans = tmp.substr(0, tmp.length() - 2);
					}
				}
			}

			name += new_text_trans.c_str();
			for (auto& it : item) {
				name += " ";
				name += it;
			}

			CPythonChat::Instance().AppendWhisper(iType, c_szName.c_str(), c_szChat.c_str(), true, false);
			CPythonChat::Instance().AppendWhisper(iType, c_szName.c_str(), name.c_str(), true, true, 65001);
			return 1;
		}
	}

	CPythonChat::Instance().AppendWhisper(iType, c_szName.c_str(), c_szChat.c_str(), true, false);
	CPythonChat::Instance().AppendWhisper(iType, c_szName.c_str(), c_szChat.c_str(), true, true);
	return 1;
}
#endif
