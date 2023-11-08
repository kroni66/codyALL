#include "StdAfx.h"
#include "PythonApplication.h"
#if defined(PYTHON_DYNAMIC_MODULE_NAME)
#include "PythonDynamicModuleNames.h"
#endif
#include "ProcessScanner.h"
#include "PythonExceptionSender.h"
#include "resource.h"
#include "Version.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

#include "../eterPack/EterPackManager.h"
#include "../eterLib/Util.h"
#ifdef CEF_BROWSER
#include "CefWebBrowser.h"
#else
#include "../CWebBrowser/CWebBrowser.h"
#endif
#include "../eterBase/CPostIt.h"

#include "CheckLatestFiles.h"

#include "PythonConfig.h"
#ifdef ENABLE_AUTO_TRANSLATE_WHISPER
#include "CGoogleTranslate.h"
#endif
#include "ProcessCRC.h"
#ifdef ENABLE_HWID
#include "CHwidManager.h"
#endif
#if defined(ENABLE_ANTICHEAT)
#if !defined(ENABLE_BLOCK_MULTIFARM)
#include <stdio.h>
#endif
#include <windows.h>
#include <ThemidaSDK.h>
#include "AntiCheat/AntiCheatSDK.h"
#pragma comment (lib, "AntiCheat.lib")
#endif

extern "C" {
extern int _fltused;
volatile int _AVOID_FLOATING_POINT_LIBRARY_BUG = _fltused;
};

extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }

#pragma comment(linker, "/NODEFAULTLIB:libci.lib")

#pragma comment( lib, "version.lib" )

#ifdef _DEBUG
#pragma comment( lib, "python27_d.lib" )
#else
#pragma comment( lib, "python27.lib" )
#endif
#pragma comment( lib, "imagehlp.lib" )
#pragma comment( lib, "devil.lib" )
#pragma comment( lib, "granny2.lib" )
#pragma comment( lib, "mss32.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "imm32.lib" )
#pragma comment( lib, "oldnames.lib" )
#pragma comment( lib, "SpeedTreeRT.lib" )
#pragma comment( lib, "dinput8.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "strmiids.lib" )
#pragma comment( lib, "ddraw.lib" )
#pragma comment( lib, "dmoguids.lib" )
#if defined(ENABLE_AUTO_TRANSLATE_WHISPER)
#pragma comment( lib, "libcurl_a.lib" )
#endif
#ifdef ENABLE_FOX_FS
#include <iphlpapi.h>

#pragma comment( lib, "iphlpapi.lib" )
#pragma comment( lib, "lz4.lib" )
#pragma comment( lib, "xxhash.lib" )
#pragma comment( lib, "FoxFS.lib" )
#endif

//#pragma comment( lib, "wsock32.lib" )
#include <stdlib.h>
#include <cryptopp/cryptoppLibLink.h>

bool __IS_TEST_SERVER_MODE__=false;

#ifdef __USE_CYTHON__
// don't include these two files .h .cpp if you're implementing cython via .pyd
#include "PythonrootlibManager.h"
// it would be better including such file in the project, but this is easier at this moment:
//#include "PythonrootlibManager.cpp"
#endif

// #define __USE_EXTRA_CYTHON__
#ifdef __USE_EXTRA_CYTHON__
// don't include these two files .h .cpp if you're implementing cython via .pyd
#include "PythonuiscriptlibManager.h"
// it would be better including such file in the project, but this is easier at this moment:
//#include "PythonuiscriptlibManager.cpp"
#endif

// #define ENABLE_DAEMONPROTECTION

#ifdef ENABLE_DAEMONPROTECTION
#define DPDLL_FILENAME	"dpdll.dll"
#define DPDLL_CRC32		0x48104810
#define DPDLL_FILESIZE	1234567+4
#endif

extern bool SetDefaultCodePage(DWORD codePage);

#ifdef USE_OPENID
extern int openid_test;
#endif

static const char * sc_apszPythonLibraryFilenames[] =
{
	"UserDict.pyc",
	"__future__.pyc",
	"copy_reg.pyc",
	"linecache.pyc",
	"ntpath.pyc",
	"os.pyc",
	"site.pyc",
	"stat.pyc",
	"string.pyc",
	"traceback.pyc",
	"types.pyc",
	"\n",
};

#ifdef ENABLE_PYLIB_CHECK
#define PRINT_LEVEL 0
#define PRINTME(level, ...) if(PRINT_LEVEL>=level) TraceError(__VA_ARGS__);
#define PYFOLD "./lib"
// #define PYFORCE

typedef struct PyLibFiles_s
{
	std::string sFileName;
	size_t stSize;
	DWORD dwCRC32;
} PyLibFiles_t;

PyLibFiles_t PyLibFilesTable[] =
{
#if PY_VERSION_HEX==0x020706f0
	{ PYFOLD"/abc.pyc", 6443, 0x20104195},
	{ PYFOLD"/bisect.pyc", 3492, 0xa71afb2},
	{ PYFOLD"/codecs.pyc", 37234, 0x936dab69},
	{ PYFOLD"/collections.pyc", 26428, 0x264b97f9},
	{ PYFOLD"/copy.pyc", 13464, 0x293606f2},
	{ PYFOLD"/copy_reg.pyc", 5413, 0x6ccd33e},
	{ PYFOLD"/encodings/aliases.pyc", 9059, 0xe17d58c1},
	{ PYFOLD"/encodings/cp949.pyc", 2265, 0x7da0b06e},
	{ PYFOLD"/encodings/__init__.pyc", 4766, 0xd8ee4a0f},
	{ PYFOLD"/fnmatch.pyc", 3988, 0xce1479c0},
	{ PYFOLD"/functools.pyc", 6449, 0xd467a5eb},
	{ PYFOLD"/genericpath.pyc", 3559, 0x1daf64bf},
	{ PYFOLD"/heapq.pyc", 14152, 0xea4d3160},
	{ PYFOLD"/keyword.pyc", 2425, 0xb2c6331d},
	{ PYFOLD"/linecache.pyc", 3491, 0x55dac12c},
	{ PYFOLD"/locale.pyc", 50097, 0x20bea490},
	{ PYFOLD"/ntpath.pyc", 12217, 0x94a9d505},
	{ PYFOLD"/os.pyc", 26025, 0x26198560},
	{ PYFOLD"/pyexpat.pyd", 127488, 0xa59c6fef},
	{ PYFOLD"/pyexpat_d.pyd", 194560, 0x9a53cb12},
	{ PYFOLD"/re.pyc", 13434, 0x18452359},
	{ PYFOLD"/shutil.pyc", 19529, 0xd6305c27},
	{ PYFOLD"/site.pyc", 20275, 0x6635620d},
	{ PYFOLD"/sre_compile.pyc", 11363, 0xc8ad7f1b},
	{ PYFOLD"/sre_constants.pyc", 6364, 0xbdbccf8b},
	{ PYFOLD"/sre_parse.pyc", 19500, 0xfc5c1e88},
	{ PYFOLD"/stat.pyc", 3047, 0x180a696},
	{ PYFOLD"/string.pyc", 13770, 0x714c8d0f},
	{ PYFOLD"/sysconfig.pyc", 17827, 0xf5921303},
	{ PYFOLD"/traceback.pyc", 11959, 0x38e06c78},
	{ PYFOLD"/types.pyc", 2786, 0xe99d45f2},
	{ PYFOLD"/UserDict.pyc", 9256, 0xb4c8779c},
	{ PYFOLD"/warnings.pyc", 13488, 0xf40c61c2},
	{ PYFOLD"/weakref.pyc", 16293, 0x66fff28d},
	{ PYFOLD"/xml/dom/domreg.pyc", 3762, 0x4dcf2746},
	{ PYFOLD"/xml/dom/expatbuilder.pyc", 36954, 0x6cab8604},
	{ PYFOLD"/xml/dom/minicompat.pyc", 4400, 0x556c5442},
	{ PYFOLD"/xml/dom/minidom.pyc", 74960, 0xbd3616e6},
	{ PYFOLD"/xml/dom/nodefilter.pyc", 1499, 0x76825258},
	{ PYFOLD"/xml/dom/xmlbuilder.pyc", 18915, 0x3ce95642},
	{ PYFOLD"/xml/dom/__init__.pyc", 7593, 0x3ab20834},
	{ PYFOLD"/xml/parsers/expat.pyc", 582, 0x28e4abc},
	{ PYFOLD"/xml/parsers/__init__.pyc", 609, 0x7f929ebc},
	{ PYFOLD"/xml/__init__.pyc", 1373, 0xddb03a03},
	{ PYFOLD"/_abcoll.pyc", 22595, 0xf757e800},
	{ PYFOLD"/_locale.pyc", 50097, 0xa7f4819a},
	{ PYFOLD"/_weakrefset.pyc", 10746, 0xc16e5a0e},
	{ PYFOLD"/__future__.pyc", 4687, 0x11de1c05},
#elif PY_VERSION_HEX==0x020203f0
#else
#error "unknown python version"
#endif
};

bool checkPyLibDir(const std::string szDirName)
{
	bool HasHack = false;

	char szDirNamePath[MAX_PATH];
	sprintf(szDirNamePath, "%s\\*", szDirName.c_str());

	WIN32_FIND_DATA f;
	HANDLE h = FindFirstFile(szDirNamePath, &f);

	if (h == INVALID_HANDLE_VALUE) { return HasHack; }

	do
	{
		if (HasHack)
			break;
		const char * name = f.cFileName;

		if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) { continue; }

		if (f.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			char filePath[MAX_PATH];
			sprintf(filePath, "%s%s%s", szDirName.c_str(), "\\", name);
			PRINTME(1, "sub %s", filePath);
            checkPyLibDir(filePath);
		}
		else
		{
			// start processing file
			PRINTME(1, "starting %s", name);
			std::string sName(name);
			std::string sPathName(szDirName+"/"+name);
			// change \\ to /
			std::replace(sPathName.begin(), sPathName.end(), '\\', '/');
			PRINTME(1, "path %s", sPathName.c_str());
			// lower file name
			std::transform(sName.begin(), sName.end(), sName.begin(), ::tolower);
			{
				PRINTME(1, "verify %s", sName.c_str());
				bool isPyLibFound = false;
				for (PyLibFiles_t *i1=std::begin(PyLibFilesTable), *e1=std::end(PyLibFilesTable); i1<e1; i1++)
				{
					if (!i1->sFileName.compare(sPathName))
					{
						PRINTME(1, "found %s==%s", i1->sFileName.c_str(), sName.c_str());
						DWORD dwCrc32 = GetFileCRC32(sPathName.c_str());
						// assert(dwCrc32);
						DWORD dwFileSize = f.nFileSizeLow;
						if (i1->stSize!=dwFileSize)
						{
							PRINTME(1, "wrong size %u==%u", i1->stSize, dwFileSize);
							HasHack = true;
							PRINTME(0, "wrong size %u for %s", dwFileSize, sPathName.c_str());
							return HasHack;
						}
						else if (i1->dwCRC32 != dwCrc32)
						{
							PRINTME(1, "wrong crc32 %u==%u", i1->dwCRC32, dwCrc32);
							HasHack = true;
							PRINTME(0, "wrong crc32 %u for %s", dwCrc32, sPathName.c_str());
							return HasHack;
						}
						PRINTME(1, "right size %u==%u", i1->stSize, dwFileSize);
						PRINTME(1, "right crc32 %u==%u", i1->dwCRC32, dwCrc32);
						PRINTME(2, "{ \"%s\", %u, %u},", sPathName.c_str(), dwFileSize, dwCrc32);
						isPyLibFound = true;
						break;
					}
				}
				// block ambiguous pyc/d files
				if (!isPyLibFound)
				{
					PRINTME(1, "not found %s", sName.c_str());
#ifdef PYFORCE
					HasHack = true;
					PRINTME(0, "ambiguous file for %s", sPathName.c_str());
					return HasHack;
#endif
				}
				PRINTME(1, "skipping file(%s) hack(%u) found(%u)", sName.c_str(), HasHack, isPyLibFound);
			}
		}

	} while (FindNextFile(h, &f));
	FindClose(h);
	return HasHack;
}

bool __CheckPyLibFiles()
{
	PRINTME(1, "__CheckPyLibFiles processing "PYFOLD);
	if (checkPyLibDir(PYFOLD))
		return false;
	return true;
}
#endif

#ifdef ENABLE_MILES_CHECK
#include <algorithm>
#include "../EterBase/Filename.h"
#define PRINT_LEVEL 0
#define PRINTME(level, ...) if(PRINT_LEVEL>=level) TraceError(__VA_ARGS__);

typedef struct MilesFiles_s
{
	std::string sFileName;
	size_t stSize;
	DWORD dwCRC32;
} MilesFiles_t;

typedef struct MilesExten_s
{
	std::string ExtName;
	bool IsUni;
} MilesExten_t;

MilesExten_t MilesExtenTable[] = {
	{"dll", false},
	{"asi", true},
	{"flt", true},
	{"m3d", true},
	{"mix", true},
};

MilesFiles_t MilesFilesTable[] =
{
	{"mss32.dll", 349952, 4215862425},
	{"mssa3d.m3d", 83712, 0xc5f933e9},
	{"mssds3d.m3d", 70912, 0x769e7c77},
	{"mssdsp.flt", 93952, 0xd4127790},
	{"mssdx7.m3d", 81152, 0x8b1e7649},
	{"msseax.m3d", 103680, 0x52558685},
	{"mssmp3.asi", 126208, 0x4656c875},
	{"mssrsx.m3d", 355072, 0x64f1a475},
	{"msssoft.m3d", 67328, 0x693a7733},
	{"mssvoice.asi", 197376, 0xd46b22b8},
};

#define MSGBOX(x) \
{ \
   std::ostringstream oss; \
   oss << x; \
   MessageBox(NULL, oss.str().c_str(), "WoM2", MB_ICONSTOP); \
}

bool checkMilesDir(const std::string szDirName)
{
	bool HasHack = false;

	char szDirNamePath[MAX_PATH];
	sprintf(szDirNamePath, "%s\\*", szDirName.c_str());

	WIN32_FIND_DATA f;
	HANDLE h = FindFirstFile(szDirNamePath, &f);

	if (h == INVALID_HANDLE_VALUE) {
		return HasHack;
	}

	do
	{
		if (HasHack)
			break;

		const char * name = f.cFileName;
		if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
			continue;
		}

		if (f.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		} else {
			std::string sName(name);
			std::string sPathName(szDirName+"/"+name);
			std::transform(sName.begin(), sName.end(), sName.begin(), ::tolower);
			std::string sNameExt = CFileNameHelper::GetExtension(sName);
			bool isMilesFile = false, isMilesUnique = false;
			for (MilesExten_t *i1=std::begin(MilesExtenTable), *e1=std::end(MilesExtenTable); i1<e1; i1++) {
				if (!sNameExt.compare(0, i1->ExtName.length(), i1->ExtName)) {
					isMilesFile = true;
					isMilesUnique = i1->IsUni;
				}
			}

			if (isMilesFile) {
				bool isMilesFound = false;
				for (MilesFiles_t *i1=std::begin(MilesFilesTable), *e1=std::end(MilesFilesTable); i1<e1; i1++) {
					if (!i1->sFileName.compare(sName)) {
						DWORD dwCrc32 = GetFileCRC32(sPathName.c_str());
						DWORD dwFileSize = f.nFileSizeLow;
						if (i1->stSize!=dwFileSize) {
							HasHack = true;
							MSGBOX("The file " << name << " was edited, please run the autopatcher!");
							return HasHack;
						} else if (i1->dwCRC32 != dwCrc32) {
							HasHack = true;
							MSGBOX("The file " << name << " was edited, please run the autopatcher!");
							return HasHack;
						}

						isMilesFound = true;
						break;
					}
				}

				if (!isMilesFound && isMilesUnique) {
					HasHack = true;
					MSGBOX("The file " << sPathName.c_str() << " is not allowed, please remove it!");
					return HasHack;
				}
			}
		}
	} while (FindNextFile(h, &f));

	FindClose(h);
	return HasHack;
}

bool __CheckMilesFiles()
{
	if (checkMilesDir(".") || checkMilesDir(".\\miles")) {
		return false;
	} else {
		return true;
	}
}
#endif

char gs_szErrorString[512] = "";

void ApplicationSetErrorString(const char* szErrorString)
{
	strcpy(gs_szErrorString, szErrorString);
}

bool CheckPythonLibraryFilenames()
{
	for (int i = 0; *sc_apszPythonLibraryFilenames[i] != '\n'; ++i)
	{
		std::string stFilename = "lib\\";
		stFilename += sc_apszPythonLibraryFilenames[i];

		if (_access(stFilename.c_str(), 0) != 0)
		{
			return false;
		}

		MoveFile(stFilename.c_str(), stFilename.c_str());
	}

	return true;
}

struct ApplicationStringTable
{
	HINSTANCE m_hInstance;
	std::map<DWORD, std::string> m_kMap_dwID_stLocale;
} gs_kAppStrTable;

void ApplicationStringTable_Initialize(HINSTANCE hInstance)
{
	gs_kAppStrTable.m_hInstance=hInstance;
}

const std::string& ApplicationStringTable_GetString(DWORD dwID, LPCSTR szKey)
{
	char szBuffer[512];
	char szIniFileName[256];
	char szLocale[256];

	::GetCurrentDirectory(sizeof(szIniFileName), szIniFileName);
	if(szIniFileName[lstrlen(szIniFileName)-1] != '\\')
		strcat(szIniFileName, "\\");
	strcat(szIniFileName, "metin2client.dat");

	strcpy(szLocale, LocaleService_GetLocalePath());
	if(strnicmp(szLocale, "locale/", strlen("locale/")) == 0)
		strcpy(szLocale, LocaleService_GetLocalePath() + strlen("locale/"));
	::GetPrivateProfileString(szLocale, szKey, NULL, szBuffer, sizeof(szBuffer)-1, szIniFileName);
	if(szBuffer[0] == '\0')
		LoadString(gs_kAppStrTable.m_hInstance, dwID, szBuffer, sizeof(szBuffer)-1);
	if(szBuffer[0] == '\0')
		::GetPrivateProfileString("en", szKey, NULL, szBuffer, sizeof(szBuffer)-1, szIniFileName);
	if(szBuffer[0] == '\0')
		strcpy(szBuffer, szKey);

	std::string& rstLocale=gs_kAppStrTable.m_kMap_dwID_stLocale[dwID];
	rstLocale=szBuffer;

	return rstLocale;
}

const std::string& ApplicationStringTable_GetString(DWORD dwID)
{
	char szBuffer[512];

	LoadString(gs_kAppStrTable.m_hInstance, dwID, szBuffer, sizeof(szBuffer)-1);
	std::string& rstLocale=gs_kAppStrTable.m_kMap_dwID_stLocale[dwID];
	rstLocale=szBuffer;

	return rstLocale;
}

const char* ApplicationStringTable_GetStringz(DWORD dwID, LPCSTR szKey)
{
	return ApplicationStringTable_GetString(dwID, szKey).c_str();
}

const char* ApplicationStringTable_GetStringz(DWORD dwID)
{
	return ApplicationStringTable_GetString(dwID).c_str();
}

////////////////////////////////////////////

int Setup(LPSTR lpCmdLine); // Internal function forward

bool PackInitialize(const char * c_pszFolder)
{
	NANOBEGIN

	struct stat st;
	if (stat( "D:\\ymir work", &st) == 0 ) {
		MessageBox(NULL, "Please remove the folder D:\Ymir Work!", "WoM2", MB_ICONSTOP);
		return false;
	}

	if (_access(c_pszFolder, 0) != 0)
		return false;

	std::string stFolder(c_pszFolder);
	stFolder += "/";

	CTextFileLoader::SetCacheMode();

#ifdef ENABLE_FOX_FS
	CEterPackManager::Instance().SetCacheMode();
	CEterPackManager::Instance().SetSearchMode(CEterPackManager::SEARCH_PACK);

	CSoundData::SetPackMode();
	CEterPackManager::Instance().RegisterPack("pack/bgm.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/building.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/effect.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/etc.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/guild.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/icon.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/item.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/locale.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/maps.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/monster.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/monster2.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/npc.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/npc2.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/patch1.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/patch2.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/patch3.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/patch4.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/patch5.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/patch6.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/patch7.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/patch8.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/patch9.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/patch10.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/patch11.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/patch_halloween_2021.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/pc.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/pc2.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/property.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/seasons.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/sound.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/terrain.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/textureset.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/tree.wom2", "");
	CEterPackManager::Instance().RegisterPack("pack/zone.wom2", "");
	CEterPackManager::Instance().RegisterRootPack((stFolder + std::string("root.wom2")).c_str());
#else
#ifdef ENABLE_LITTLE_PACK
#if defined(USE_RELATIVE_PATH)
	CEterPackManager::Instance().SetRelativePathMode();
#endif
	CEterPackManager::Instance().SetCacheMode();
	CEterPackManager::Instance().SetSearchMode(true);

	CSoundData::SetPackMode();
	CEterPackManager::Instance().RegisterPack("pack/effect", "d:/ymir work/effect/");
	CEterPackManager::Instance().RegisterPack("pack/etc", "pack/");
	CEterPackManager::Instance().RegisterPack("pack/guild", "d:/ymir work/guild/");
	CEterPackManager::Instance().RegisterPack("pack/icon", "pack/");
	CEterPackManager::Instance().RegisterPack("pack/item", "d:/ymir work/item/");
	CEterPackManager::Instance().RegisterPack("pack/locale", "pack/");
	CEterPackManager::Instance().RegisterPack("pack/maps", "pack/");
	CEterPackManager::Instance().RegisterPack("pack/monster", "d:/ymir work/monster/");
	CEterPackManager::Instance().RegisterPack("pack/monster2", "d:/ymir work/monster2/");
	CEterPackManager::Instance().RegisterPack("pack/npc", "d:/ymir work/npc/");
	CEterPackManager::Instance().RegisterPack("pack/npc2", "pack/");
	CEterPackManager::Instance().RegisterPack("pack/patch1", "pack/");
	CEterPackManager::Instance().RegisterPack("pack/patch2", "pack/");
	CEterPackManager::Instance().RegisterPack("pack/pc", "d:/ymir work/pc/");
	CEterPackManager::Instance().RegisterPack("pack/pc2", "d:/ymir work/pc2/");
	CEterPackManager::Instance().RegisterPack("pack/property", "pack/");
	CEterPackManager::Instance().RegisterPack("pack/seasons", "pack/");
	CEterPackManager::Instance().RegisterPack("pack/sound", "sound/");
	CEterPackManager::Instance().RegisterPack("pack/terrain", "d:/ymir work/terrainmaps/");
	CEterPackManager::Instance().RegisterPack("pack/textureset", "textureset");
	CEterPackManager::Instance().RegisterPack("pack/tree", "d:/ymir work/tree/");
	CEterPackManager::Instance().RegisterPack("pack/zone", "pack/");
#else
	std::string stFileName(stFolder);
	stFileName += "Index";

	CMappedFile file;
	LPCVOID pvData;

	if (!file.Create(stFileName.c_str(), &pvData, 0, 0))
	{
		LogBoxf("FATAL ERROR! File not exist: %s", stFileName.c_str());
		TraceError("FATAL ERROR! File not exist: %s", stFileName.c_str());
		return true;
	}

	CMemoryTextFileLoader TextLoader;
	TextLoader.Bind(file.Size(), pvData);

	bool bPackFirst = TRUE;

	const std::string& strPackType = TextLoader.GetLineString(0);

	if (strPackType.compare("FILE") && strPackType.compare("PACK"))
	{
		TraceError("Pack/Index has invalid syntax. First line must be 'PACK' or 'FILE'");
		return false;
	}

#ifdef NDEBUG // @warme601 _DISTRIBUTE -> NDEBUG
	Tracef("Note: PackFirst mode enabled. [pack]\n");

	//if (0 == strPackType.compare("FILE"))
	//{
	//	bPackFirst = FALSE;
	//	Tracef("알림: 파일 모드입니다.\n");
	//}
	//else
	//{
	//	Tracef("알림: 팩 모드입니다.\n");
	//}
#else
	bPackFirst = FALSE;
	Tracef("Note: PackFirst mode not enabled. [file]\n");
#endif

#if defined(USE_RELATIVE_PATH)
	CEterPackManager::Instance().SetRelativePathMode();
#endif
	CEterPackManager::Instance().SetCacheMode();
	CEterPackManager::Instance().SetSearchMode(bPackFirst);

	CSoundData::SetPackMode(); // Miles 파일 콜백을 셋팅

	std::string strPackName, strTexCachePackName;
	for (DWORD i = 1; i < TextLoader.GetLineCount() - 1; i += 2)
	{
		const std::string & c_rstFolder = TextLoader.GetLineString(i);
		const std::string & c_rstName = TextLoader.GetLineString(i + 1);

		strPackName = stFolder + c_rstName;
		strTexCachePackName = strPackName + "_texcache";

		CEterPackManager::Instance().RegisterPack(strPackName.c_str(), c_rstFolder.c_str());
		CEterPackManager::Instance().RegisterPack(strTexCachePackName.c_str(), c_rstFolder.c_str());
	}
#endif
	CEterPackManager::Instance().RegisterRootPack((stFolder + std::string("root")).c_str());
#endif
	NANOEND
	return true;
}

bool RunMainScript(CPythonLauncher& pyLauncher, const char* lpCmdLine)
{
#if defined(PYTHON_DYNAMIC_MODULE_NAME)
	initPythonApi();
#endif
	initpack();
	initdbg();
	initime();
	initgrp();
	initgrpImage();
	initgrpText();
	initwndMgr();
	/////////////////////////////////////////////
	initudp();
	initapp();
	initsystemSetting();
	initchr();
	initchrmgr();
	initPlayer();
	initItem();
	initNonPlayer();
	initTrade();
	initChat();
	initTextTail();
	initnet();
	initMiniMap();
	initProfiler();
	initEvent();
	initeffect();
	initfly();
	initsnd();
	initeventmgr();
	initshop();
	initskill();
#ifdef NEW_PET_SYSTEM
	initskillpet();
#endif
	initquest();
	initBackground();
	initMessenger();
#ifdef ENABLE_ACCE_SYSTEM
	initAcce();
#endif

#ifdef ENABLE_CONFIG_MODULE
	initcfg();
#endif

	initsafebox();
	initguild();
	initServerStateChecker();
#ifdef ENABLE_SWITCHBOT
	initSwitchbot();
#endif
#ifdef ENABLE_CUBE_RENEWAL_WORLDARD
	intcuberenewal();
#endif
#ifdef INGAME_WIKI
	initWiki();
#endif
#ifdef __USE_CYTHON__
	// don't add this line if you're implementing cython via .pyd:
	initrootlibManager();
#endif
#ifdef __USE_EXTRA_CYTHON__
	// don't add this line if you're implementing cython via .pyd:
	inituiscriptlibManager();
#endif

#ifdef __ENABLE_NEW_OFFLINESHOP__
	initofflineshop();
#endif

	NANOBEGIN

    PyObject * builtins = PyImport_ImportModule("__builtin__");
#ifdef NDEBUG // @warme601 _DISTRIBUTE -> NDEBUG
	PyModule_AddIntConstant(builtins, "__DEBUG__", 1);
#else
	PyModule_AddIntConstant(builtins, "__DEBUG__", 0);
#endif
#ifdef __USE_CYTHON__
	PyModule_AddIntConstant(builtins, "__USE_CYTHON__", 1);
#else
	PyModule_AddIntConstant(builtins, "__USE_CYTHON__", 0);
#endif
#ifdef __USE_EXTRA_CYTHON__
	PyModule_AddIntConstant(builtins, "__USE_EXTRA_CYTHON__", 1);
#else
	PyModule_AddIntConstant(builtins, "__USE_EXTRA_CYTHON__", 0);
#endif
#ifdef PYTHON_DYNAMIC_MODULE_NAME
	PyModule_AddIntConstant(builtins, "__USE_DYNAMIC_MODULE__", 1);
#else
	PyModule_AddIntConstant(builtins, "__USE_DYNAMIC_MODULE__", 0);
#endif

	// RegisterCommandLine
	{
		std::string stRegisterCmdLine;

		const char * loginMark = "-cs";
		const char * loginMark_NonEncode = "-ncs";
		const char * seperator = " ";

		std::string stCmdLine;
		const int CmdSize = 3;
		std::vector<std::string> stVec;
		SplitLine(lpCmdLine,seperator,&stVec);
		if (CmdSize == stVec.size() && stVec[0]==loginMark)
		{
			char buf[MAX_PATH];	//TODO 아래 함수 std::string 형태로 수정
			base64_decode(stVec[2].c_str(),buf);
			stVec[2] = buf;
			string_join(seperator,stVec,&stCmdLine);
		}
		else if (CmdSize <= stVec.size() && stVec[0]==loginMark_NonEncode)
		{
			stVec[0] = loginMark;
			string_join(" ",stVec,&stCmdLine);
		}
		else
			stCmdLine = lpCmdLine;

		PyModule_AddStringConstant(builtins, "__COMMAND_LINE__", stCmdLine.c_str());
	}
	{
		std::vector<std::string> stVec;
		SplitLine(lpCmdLine," " ,&stVec);

		if (stVec.size() != 0 && "--pause-before-create-window" == stVec[0])
		{
			system("pause");
		}
#ifdef ENABLE_DAEMONPROTECTION
		DWORD dwCrc32, dwSize;
		if (!((dwCrc32 = GetFileCRC32(DPDLL_FILENAME))==DPDLL_CRC32))
		{
			TraceError("dpdll wrong crc32 %d", dwCrc32);
			return false;
		}
		if (!((dwSize = GetFileSize(DPDLL_FILENAME))==DPDLL_FILESIZE))
		{
			TraceError("dpdll wrong size %d", dwSize);
			return false;
		}
		if (!LoadLibraryA(DPDLL_FILENAME))
		{
			TraceError("dpdll not loaded");
			return false;
		}
#endif

#ifdef __USE_CYTHON__
		if (!pyLauncher.RunLine("import rootlib\nrootlib.moduleImport('system')"))
#else
		if (!pyLauncher.RunFile("system.py"))
#endif
		{
			TraceError("RunMain Error");
			return false;
		}
	}

	NANOEND
	return true;
}

#if defined(__ENABLE_CH3HP_PROTECTION__)
#include "ch3hp_protection.h"
bool Main(HINSTANCE hInstance, LPSTR lpCmdLine)
{
	if (!CH3HP_CheckWebResponse()) {
		LogBox("Something went wrong, try again!");
		return false;
	}
#else
bool Main(HINSTANCE hInstance, LPSTR lpCmdLine)
{
#endif
#ifdef LOCALE_SERVICE_YMIR
	extern bool g_isScreenShotKey;
	g_isScreenShotKey = true;
#endif

	DWORD dwRandSeed=time(NULL)+DWORD(GetCurrentProcess());
	srandom(dwRandSeed);
	srand(random());

	SetLogLevel(1);

#ifdef LOCALE_SERVICE_VIETNAM_MILD
	extern BOOL USE_VIETNAM_CONVERT_WEAPON_VNUM;
	USE_VIETNAM_CONVERT_WEAPON_VNUM = true;
#endif

	if (_access("perf_game_update.txt", 0)==0)
	{
		DeleteFile("perf_game_update.txt");
	}

	if (_access("newpatch.exe", 0)==0)
	{
		system("patchupdater.exe");
		return false;
	}
#ifndef __VTUNE__
	ilInit();
#endif
	if (!Setup(lpCmdLine))
		return false;

#ifdef _DEBUG
	OpenConsoleWindow();
	OpenLogFile(true); // true == uses syserr.txt and log.txt
#else
	OpenLogFile(false); // false == uses syserr.txt only
#endif

	BuildProcessCRC();

	static CLZO							lzo;
	static CEterPackManager				EterPackManager;
#ifdef ENABLE_AUTO_TRANSLATE_WHISPER
	static CGoogleTranslate				google_translate;
#endif
#ifdef ENABLE_HWID
	static CHwidManager HwidManager;
#endif

	if (!PackInitialize("pack"))
	{
#ifdef ENABLE_LITTLE_PACK
		TraceError("Pack initialization failed.");
#else
		LogBox("Pack Initialization failed. Check log.txt file..");
#endif
		return false;
	}

#ifdef ENABLE_CONFIG_MODULE
	static CPythonConfig m_pyConfig;
	m_pyConfig.Initialize("config.cfg");
#endif

	if(LocaleService_LoadGlobal(hInstance))
		SetDefaultCodePage(LocaleService_GetCodePage());

#ifdef ENABLE_PYLIB_CHECK
	if (!__CheckPyLibFiles())
		return false;
#endif

#ifdef ENABLE_MILES_CHECK
	if (!__CheckMilesFiles())
		return false;
#endif

	CPythonApplication * app = new CPythonApplication;

	app->Initialize(hInstance);

	bool ret=false;
	{
		CPythonLauncher pyLauncher;
		CPythonExceptionSender pyExceptionSender;
		SetExceptionSender(&pyExceptionSender);

		if (pyLauncher.Create()) {
			ret=RunMainScript(pyLauncher, lpCmdLine);	//게임 실행중엔 함수가 끝나지 않는다.
		}

		//ProcessScanner_ReleaseQuitEvent();

		//게임 종료시.
		app->Clear();

		timeEndPeriod(1);
		pyLauncher.Clear();
	}

	app->Destroy();
	delete app;

	return ret;
}

HANDLE CreateMetin2GameMutex()
{
	SECURITY_ATTRIBUTES sa;
	ZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));
	sa.nLength				= sizeof(sa);
	sa.lpSecurityDescriptor	= NULL;
	sa.bInheritHandle		= FALSE;

	return CreateMutex(&sa, FALSE, "Metin2GameMutex");
}

void DestroyMetin2GameMutex(HANDLE hMutex)
{
	if (hMutex)
	{
		ReleaseMutex(hMutex);
		hMutex = NULL;
	}
}

void __ErrorPythonLibraryIsNotExist()
{
	LogBoxf("FATAL ERROR!! Python Library file not exist!");
}

bool __IsTimeStampOption(LPSTR lpCmdLine)
{
	const char* TIMESTAMP = "/timestamp";
	return (strncmp(lpCmdLine, TIMESTAMP, strlen(TIMESTAMP))==0);
}

void __PrintTimeStamp()
{
#ifdef	_DEBUG
	if (__IS_TEST_SERVER_MODE__)
		LogBoxf("METIN2 BINARY TEST DEBUG VERSION %s  ( MS C++ %d Compiled )", __TIMESTAMP__, _MSC_VER);
	else
		LogBoxf("METIN2 BINARY DEBUG VERSION %s ( MS C++ %d Compiled )", __TIMESTAMP__, _MSC_VER);

#else
	if (__IS_TEST_SERVER_MODE__)
		LogBoxf("METIN2 BINARY TEST VERSION %s  ( MS C++ %d Compiled )", __TIMESTAMP__, _MSC_VER);
	else
		LogBoxf("METIN2 BINARY DISTRIBUTE VERSION %s ( MS C++ %d Compiled )", __TIMESTAMP__, _MSC_VER);
#endif
}

bool __IsLocaleOption(LPSTR lpCmdLine)
{
	return (strcmp(lpCmdLine, "--locale") == 0);
}

bool __IsLocaleVersion(LPSTR lpCmdLine)
{
	return (strcmp(lpCmdLine, "--perforce-revision") == 0);
}

#ifdef USE_OPENID
//2012.07.16 김용욱
//일본 OpenID 지원. 인증키 인자 추가
bool __IsOpenIDAuthKeyOption(LPSTR lpCmdLine)
{
	return (strcmp(lpCmdLine, "--openid-authkey") == 0);
}

bool __IsOpenIDTestOption(LPSTR lpCmdLine) //클라이언트에서 로그인이 가능하다.
{
	return (strcmp(lpCmdLine, "--openid-test") == 0);
}
#endif /* USE_OPENID */

#ifdef ENABLE_BLOCK_MULTIFARM
#include <stdio.h>
#ifdef _WIN32
#include <intrin.h>
#else
#include <cpuid.h>
#endif

int isHypervisor(void)
{
#ifdef _WIN32
	int cpuinfo[4];
	__cpuid(cpuinfo, 1);
	if (cpuinfo[2] >> 31 & 1)
		return 1;
#else
	unsigned int eax, ebx, ecx, edx;
	__get_cpuid (1, &eax, &ebx, &ecx, &edx);
	if (ecx >> 31 & 1)
		return 1;
#endif
	return 0;
}
#endif

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#if defined(ENABLE_ANTICHEAT)
VM_START
	getchar();
VM_END
#endif

//#ifdef ENABLE_BLOCK_MULTIFARM
//	if (isHypervisor() != 0) {
//		MessageBox(NULL, "You cannot play from Virtual Machines!", "WoM2", MB_ICONSTOP);
//		goto Clean;
//	}
//#endif

#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_CRT_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 110247 );
#endif

	ApplicationStringTable_Initialize(hInstance);
	LocaleService_LoadConfig("locale.cfg");
	SetDefaultCodePage(LocaleService_GetCodePage());

#if defined(CHECK_LATEST_DATA_FILES)
	if (!CheckLatestFiles())
		return 0;
#endif

	bool bQuit = false;
	bool bAuthKeyChecked = false;	//OpenID 버전에서 인증키가 들어왔는지 알기 위한 인자.
	int nArgc = 0;
	PCHAR* szArgv = CommandLineToArgv( lpCmdLine, &nArgc );

	for( int i=0; i < nArgc; i++ ) {
		if(szArgv[i] == 0)
			continue;
		if (__IsLocaleVersion(szArgv[i])) // #0000829: [M2EU] 버전 파일이 항상 생기지 않도록 수정
		{
			char szModuleName[MAX_PATH];
			char szVersionPath[MAX_PATH];
			GetModuleFileName(NULL, szModuleName, sizeof(szModuleName));
			sprintf(szVersionPath, "%s.version", szModuleName);
			FILE* fp = fopen(szVersionPath, "wt");
			if (fp)
			{
				extern int METIN2_GET_VERSION();
				fprintf(fp, "r%d\n", METIN2_GET_VERSION());
				fclose(fp);
			}
			bQuit = true;
		} else if (__IsLocaleOption(szArgv[i]))
		{
			FILE* fp=fopen("locale.txt", "wt");
			fprintf(fp, "service[%s] code_page[%d]",
				LocaleService_GetName(), LocaleService_GetCodePage());
			fclose(fp);
			bQuit = true;
		} else if (__IsTimeStampOption(szArgv[i]))
		{
			__PrintTimeStamp();
			bQuit = true;
		} else if ((strcmp(szArgv[i], "--force-set-locale") == 0))
		{
			// locale 설정엔 인자가 두 개 더 필요함 (로케일 명칭, 데이터 경로)
			if (nArgc <= i + 2)
			{
				MessageBox(NULL, "Invalid arguments", ApplicationStringTable_GetStringz(IDS_APP_NAME, "APP_NAME"), MB_ICONSTOP);
				goto Clean;
			}

			const char* localeName = szArgv[++i];
			const char* localePath = szArgv[++i];

			LocaleService_ForceSetLocale(localeName, localePath);
		}
#ifdef USE_OPENID
		else if (__IsOpenIDAuthKeyOption(szArgv[i]))	//2012.07.16 OpenID : 김용욱
		{
			// 인증키 설정엔 인자가 한 개 더 필요함 (인증키)
			if (nArgc <= i + 1)
			{
				MessageBox(NULL, "Invalid arguments", ApplicationStringTable_GetStringz(IDS_APP_NAME, "APP_NAME"), MB_ICONSTOP);
				goto Clean;
			}

			const char* authKey = szArgv[++i];

			//ongoing (2012.07.16)
			//인증키 저장하는 부분
			LocaleService_SetOpenIDAuthKey(authKey);

			bAuthKeyChecked = true;
		}
		else if (__IsOpenIDTestOption(szArgv[i]))
		{
			openid_test = 1;

		}
#endif /* USE_OPENID */
	}

#ifdef USE_OPENID
	//OpenID
	//OpenID 클라이언트의 경우인증키를 받아오지 않을 경우 (웹을 제외하고 실행 시) 클라이언트 종료.

	if (false == bAuthKeyChecked && !openid_test)
	{
		MessageBox(NULL, "Invalid execution", ApplicationStringTable_GetStringz(IDS_APP_NAME, "APP_NAME"), MB_ICONSTOP);
		goto Clean;
	}
#endif /* USE_OPENID */


	if(bQuit)
		goto Clean;

#if defined(NEEDED_COMMAND_ARGUMENT)
	// 옵션이 없으면 비정상 실행으로 간주, 프로그램 종료
	if (strstr(lpCmdLine, NEEDED_COMMAND_ARGUMENT) == 0) {
		MessageBox(NULL, ApplicationStringTable_GetStringz(IDS_ERR_MUST_LAUNCH_FROM_PATCHER, "ERR_MUST_LAUNCH_FROM_PATCHER"), ApplicationStringTable_GetStringz(IDS_APP_NAME, "APP_NAME"), MB_ICONSTOP);
			goto Clean;
	}
#endif

#if defined(NEEDED_COMMAND_CLIPBOARD)
	{
		CHAR szSecKey[256];
		CPostIt cPostIt( "VOLUME1" );

		if( cPostIt.Get( "SEC_KEY", szSecKey, sizeof(szSecKey) ) == FALSE ) {
			MessageBox(NULL, ApplicationStringTable_GetStringz(IDS_ERR_MUST_LAUNCH_FROM_PATCHER, "ERR_MUST_LAUNCH_FROM_PATCHER"), ApplicationStringTable_GetStringz(IDS_APP_NAME, "APP_NAME"), MB_ICONSTOP);
			goto Clean;
		}
		if( strstr(szSecKey, NEEDED_COMMAND_CLIPBOARD) == 0 ) {
			MessageBox(NULL, ApplicationStringTable_GetStringz(IDS_ERR_MUST_LAUNCH_FROM_PATCHER, "ERR_MUST_LAUNCH_FROM_PATCHER"), ApplicationStringTable_GetStringz(IDS_APP_NAME, "APP_NAME"), MB_ICONSTOP);
			goto Clean;
		}
		cPostIt.Empty();
	}
#endif

#ifdef CEF_BROWSER
	CefWebBrowser_Startup(hInstance);
#else
	WebBrowser_Startup(hInstance);
#endif

#ifndef ENABLE_PYLIB_CHECK
	if (!CheckPythonLibraryFilenames())
	{
		__ErrorPythonLibraryIsNotExist();
		goto Clean;
	}
#endif

	Main(hInstance, lpCmdLine);

#ifdef CEF_BROWSER
	CefWebBrowser_Cleanup();
#else
	WebBrowser_Cleanup();
#endif


	::CoUninitialize();

	if(gs_szErrorString[0])
		MessageBox(NULL, gs_szErrorString, ApplicationStringTable_GetStringz(IDS_APP_NAME, "APP_NAME"), MB_ICONSTOP);

Clean:
	SAFE_FREE_GLOBAL(szArgv);

	return 0;
}

static void GrannyError(granny_log_message_type Type,
						granny_log_message_origin Origin,
						char const* File,
						granny_int32x Line,
						char const *Error,
						void *UserData)
{
    /*TraceError("GRANNY: %s", Error);*/
}

int Setup(LPSTR lpCmdLine)
{
	/*
	 *	타이머 정밀도를 올린다.
	 */
	TIMECAPS tc;
	UINT wTimerRes;

	if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR)
		return 0;

	wTimerRes = MINMAX(tc.wPeriodMin, 1, tc.wPeriodMax);
	timeBeginPeriod(wTimerRes);

	/*
	 *	그래니 에러 핸들링
	 */

/*	granny_log_callback Callback;
    Callback.Function = GrannyError;
    Callback.UserData = 0;
    GrannySetLogCallback(&Callback);
*/
	return 1;
}
