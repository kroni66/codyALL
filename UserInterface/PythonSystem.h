#pragma once

class CPythonSystem : public CSingleton<CPythonSystem>
{
	public:
		enum EWindow
		{
			WINDOW_STATUS,
			WINDOW_INVENTORY,
			WINDOW_ABILITY,
			WINDOW_SOCIETY,
			WINDOW_JOURNAL,
			WINDOW_COMMAND,

			WINDOW_QUICK,
			WINDOW_GAUGE,
			WINDOW_MINIMAP,
			WINDOW_CHAT,

			WINDOW_MAX_NUM,
		};

		enum
		{
			FREQUENCY_MAX_NUM  = 30,
			RESOLUTION_MAX_NUM = 100
		};

		typedef struct SResolution
		{
			DWORD	width;
			DWORD	height;
			DWORD	bpp;		// bits per pixel (high-color = 16bpp, true-color = 32bpp)

			DWORD	frequency[20];
			BYTE	frequency_count;
		} TResolution;

		typedef struct SWindowStatus
		{
			int		isVisible;
			int		isMinimized;

			int		ixPosition;
			int		iyPosition;
			int		iHeight;
		} TWindowStatus;

		typedef struct SConfig
		{
			DWORD			width;
			DWORD			height;
			DWORD			bpp;
			DWORD			frequency;

			bool			is_software_cursor;
			bool			is_object_culling;
			int				iDistance;
			int				iShadowLevel;

			FLOAT			music_volume;
			BYTE			voice_volume;

			int				gamma;

			int				isSaveID;
			char			SaveID[20];

			bool			bWindowed;
			bool			bDecompressDDS;
			bool			bNoSoundCard;
			bool			bUseDefaultIME;
			BYTE			bSoftwareTiling;
			bool			bViewChat;
			bool			bAlwaysShowName;
			bool			bShowDamage;
			bool			bShowSalesText;
#if defined(WJ_SHOW_MOB_INFO) && defined(ENABLE_SHOW_MOBAIFLAG)
			bool			bShowMobAIFlag;
#endif
#if defined(WJ_SHOW_MOB_INFO) && defined(ENABLE_SHOW_MOBLEVEL)
			bool			bShowMobLevel;
#endif
#ifdef ENABLE_MULTI_LANGUAGE
			std::string		szLanguageFilter;
			bool			bAutoTranslateWhisper;
#endif
#ifdef ENABLE_PERSPECTIVE_VIEW
			float			fField;
#endif
#ifdef ENABLE_BIOLOGIST_UI
			bool biologist_alert;
#endif
#ifdef ENABLE_SAVECAMERA_PREFERENCES
			BYTE			bCameraType;
			float			fCameraHeight;
#endif
#ifdef OUTLINE_NAMES_TEXTLINE
			bool			bNamesOutline;
#endif
#ifdef ENABLE_AUTO_PICKUP
			bool	bPickUpType;
#endif
#ifdef ENABLE_NEW_CHAT
			int		iChatFilter;
#endif
			int		iEnvironment;
			bool	bTimePm;
			bool	bHide1Mode;
			bool	bHide2Mode;
			bool	bHide3Mode;
			bool	bHide4Mode;
			bool	bHide5Mode;
			bool	bHide6Mode;
			bool	bHide7Mode;
			bool	bHide1Mode2;
			bool	bHide2Mode2;
			bool	bHide3Mode2;
			bool	bHide4Mode2;
#ifdef ENABLE_DOGMODE
			bool	bDogMode;
#endif
		} TConfig;

	public:
		CPythonSystem();
		virtual ~CPythonSystem();

		void Clear();
		void SetInterfaceHandler(PyObject * poHandler);
		void DestroyInterfaceHandler();

		// Config
		void							SetDefaultConfig();
		bool							LoadConfig();
		bool							SaveConfig();
		void							ApplyConfig();
		void							SetConfig(TConfig * set_config);
		TConfig *						GetConfig();
		void							ChangeSystem();

		// Interface
		bool							LoadInterfaceStatus();
		void							SaveInterfaceStatus();
		bool							isInterfaceConfig();
		const TWindowStatus &			GetWindowStatusReference(int iIndex);

		DWORD							GetWidth();
		DWORD							GetHeight();
		DWORD							GetBPP();
		DWORD							GetFrequency();
		bool							IsSoftwareCursor();
		bool							IsWindowed();
		bool							IsViewChat();
		bool							IsAlwaysShowName();
		bool							IsShowDamage();
		bool							IsShowSalesText();
		bool							IsUseDefaultIME();
		bool							IsNoSoundCard();
		bool							IsAutoTiling();
		bool							IsSoftwareTiling();
		void							SetSoftwareTiling(bool isEnable);
		void							SetViewChatFlag(int iFlag);
		void							SetAlwaysShowNameFlag(int iFlag);
		void							SetShowDamageFlag(int iFlag);
		void							SetShowSalesTextFlag(int iFlag);
#if defined(WJ_SHOW_MOB_INFO) && defined(ENABLE_SHOW_MOBAIFLAG)
		bool							IsShowMobAIFlag();
		void							SetShowMobAIFlagFlag(int iFlag);
#endif
#if defined(WJ_SHOW_MOB_INFO) && defined(ENABLE_SHOW_MOBLEVEL)
		bool							IsShowMobLevel();
		void							SetShowMobLevelFlag(int iFlag);
#endif

#ifdef ENABLE_MULTI_LANGUAGE
		void							SetChatFilterValue(std::string szFilter);
		std::string 					GetChatFilterValue();
		bool							IsAutoTranslateWhisper();
		void							SetAutoTranslateWhisper(int iFlag);
#endif

		// Window
		void							SaveWindowStatus(int iIndex, int iVisible, int iMinimized, int ix, int iy, int iHeight);

		// SaveID
		int								IsSaveID();
		const char *					GetSaveID();
		void							SetSaveID(int iValue, const char * c_szSaveID);

		/// Display
		void							GetDisplaySettings();

		int								GetResolutionCount();
		int								GetFrequencyCount(int index);
		bool							GetResolution(int index, OUT DWORD *width, OUT DWORD *height, OUT DWORD *bpp);
		bool							GetFrequency(int index, int freq_index, OUT DWORD *frequncy);
		int								GetResolutionIndex(DWORD width, DWORD height, DWORD bpp);
		int								GetFrequencyIndex(int res_index, DWORD frequency);
		bool							isViewCulling();

		// Sound
		float							GetMusicVolume();
		int								GetSoundVolume();
		void							SetMusicVolume(float fVolume);
		void							SetSoundVolumef(float fVolume);

		int		GetDistance();
#ifdef ENABLE_PERSPECTIVE_VIEW
		float	GetFieldPerspective();
		void	SetFieldPerspective(float fValue);
#endif
		int								GetShadowLevel();
		void							SetShadowLevel(unsigned int level);
#ifdef ENABLE_BIOLOGIST_UI
		bool	GetBiologistAlert();
		void	SetBiologistAlert(bool value);
#endif
#ifdef ENABLE_SAVECAMERA_PREFERENCES
		BYTE	GetCameraType();
		void	SetCameraType(BYTE value);
		float	GetCameraHeight();
		void	SetCameraHeight(float value);
#endif
#ifdef OUTLINE_NAMES_TEXTLINE
		bool	GetNamesType();
		void	SetNamesType(bool value);
#endif
#ifdef ENABLE_AUTO_PICKUP
		bool	GetPickUpMode();
		void	SetPickUpMode(int value);
#endif
#ifdef ENABLE_NEW_CHAT
		void	SetChatFilter(int value);
		int		GetChatFilter();
#endif
		int		GetEnvironment();
		void	SetEnvironment(int value);
		bool	GetTimePm();
		void	SetTimePm(bool value);
		void	SetHideModeStatus(int type, int value);
		bool	GetHideMode1Status();
		bool	GetHideMode2Status();
		bool	GetHideMode3Status();
		bool	GetHideMode4Status();
		bool	GetHideMode5Status();
		bool	GetHideMode6Status();
		bool	GetHideMode7Status();
		void	SetHideModeStatus2(int type, int value);
		bool	GetHideMode1Status2();
		bool	GetHideMode2Status2();
		bool	GetHideMode3Status2();
		bool	GetHideMode4Status2();
#ifdef ENABLE_DOGMODE
		void	SetDogMode(int value);
		bool	IsDogMode();
#endif

	protected:
		TResolution						m_ResolutionList[RESOLUTION_MAX_NUM];
		int								m_ResolutionCount;

		TConfig							m_Config;
		TConfig							m_OldConfig;

		bool							m_isInterfaceConfig;
		PyObject *						m_poInterfaceHandler;
		TWindowStatus					m_WindowStatus[WINDOW_MAX_NUM];
};