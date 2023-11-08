#pragma once

#include "AbstractPlayer.h"
#include "Packet.h"
#include "PythonSkill.h"

enum
{
	MAIN_RACE_WARRIOR_M,
	MAIN_RACE_ASSASSIN_W,
	MAIN_RACE_SURA_M,
	MAIN_RACE_SHAMAN_W,
	MAIN_RACE_WARRIOR_W,
	MAIN_RACE_ASSASSIN_M,
	MAIN_RACE_SURA_W,
	MAIN_RACE_SHAMAN_M,
#ifdef ENABLE_WOLFMAN_CHARACTER
	MAIN_RACE_WOLFMAN_M,
#endif
	MAIN_RACE_MAX_NUM,
};

class CInstanceBase;

/*
 *	���� ĳ���� (�ڽ��� �����ϴ� ĳ����) �� ���� �������� �����Ѵ�.
 *
 * 2003-01-12 Levites	������ CPythonCharacter�� ������ �־����� �Ը� �ʹ� Ŀ�� ��������
 *						��ġ�� �ָ��ؼ� ���� �и�
 * 2003-07-19 Levites	���� ĳ������ �̵� ó�� CharacterInstance���� ����� ����
 *						������ ����Ÿ ������ ���ҿ��� �Ϻ��� ���� �÷��̾� ���� Ŭ������
 *						Ż�ٲ� ��.
 */

class CPythonPlayer : public CSingleton<CPythonPlayer>, public IAbstractPlayer
{
	public:
		enum
		{
			CATEGORY_NONE		= 0,
			CATEGORY_ACTIVE		= 1,
			CATEGORY_PASSIVE	= 2,
			CATEGORY_MAX_NUM	= 3,

			STATUS_INDEX_ST = 1,
			STATUS_INDEX_DX = 2,
			STATUS_INDEX_IQ = 3,
			STATUS_INDEX_HT = 4,
		};

		enum
		{
			MBT_LEFT,
			MBT_RIGHT,
			MBT_MIDDLE,
			MBT_NUM,
		};

		enum
		{
			MBF_SMART,
			MBF_MOVE,
			MBF_CAMERA,
			MBF_ATTACK,
			MBF_SKILL,
			MBF_AUTO,
		};

		enum
		{
			MBS_CLICK,
			MBS_PRESS,
		};

		enum EMode
		{
			MODE_NONE,
			MODE_CLICK_POSITION,
			MODE_CLICK_ITEM,
			MODE_CLICK_ACTOR,
			MODE_USE_SKILL,
		};

		enum EEffect
		{
			EFFECT_PICK,
			EFFECT_NUM,
		};

		enum EMetinSocketType
		{
			METIN_SOCKET_TYPE_NONE,
			METIN_SOCKET_TYPE_SILVER,
			METIN_SOCKET_TYPE_GOLD,
		};

		typedef struct SSkillInstance
		{
			DWORD dwIndex;
			int iType;
			int iGrade;
			int iLevel;
			float fcurEfficientPercentage;
			float fnextEfficientPercentage;
			BOOL isCoolTime;

			float fCoolTime;			// NOTE : ��Ÿ�� ���� ��ų ������
			float fLastUsedTime;		//        ��â�� ����� �� ����ϴ� ����
			BOOL bActive;
		} TSkillInstance;

		enum EKeyBoard_UD
		{
			KEYBOARD_UD_NONE,
			KEYBOARD_UD_UP,
			KEYBOARD_UD_DOWN,
		};

		enum EKeyBoard_LR
		{
			KEYBOARD_LR_NONE,
			KEYBOARD_LR_LEFT,
			KEYBOARD_LR_RIGHT,
		};

		enum
		{
			DIR_UP,
			DIR_DOWN,
			DIR_LEFT,
			DIR_RIGHT,
		};

		typedef struct SPlayerStatus
		{
			TItemData			aItem[c_Inventory_Count];
			TItemData			aDSItem[c_DragonSoul_Inventory_Count];
#ifdef ENABLE_EXTRA_INVENTORY
			TItemData			aExtraItem[c_Extra_Inventory_Count];
#endif
#ifdef ENABLE_SWITCHBOT
			TItemData			aSwitchbotItem[SWITCHBOT_SLOT_COUNT];
#endif
			TQuickSlot			aQuickSlot[QUICKSLOT_MAX_NUM];
			TSkillInstance		aSkill[SKILL_MAX_NUM];
			long				lQuickPageIndex;
#ifdef ENABLE_LONG_LONG
			long long 			m_alPoint[POINT_MAX_NUM];
#else
			long 			m_alPoint[POINT_MAX_NUM];
#endif

#ifdef ENABLE_LONG_LONG
			void SetPoint(UINT ePoint, long long lPoint);
#else
			void SetPoint(UINT ePoint, long lPoint);
#endif

#ifdef ENABLE_LONG_LONG
			long long GetPoint(UINT ePoint);
#else
			long GetPoint(UINT ePoint);
#endif

		} TPlayerStatus;

		typedef struct SPartyMemberInfo
		{
			SPartyMemberInfo(DWORD _dwPID, const char * c_szName) : dwPID(_dwPID), strName(c_szName), dwVID(0) {}

			DWORD dwVID;
			DWORD dwPID;
			std::string strName;
			BYTE byState;
			BYTE byHPPercentage;
			short sAffects[PARTY_AFFECT_SLOT_MAX_NUM];
		} TPartyMemberInfo;

		enum EPartyRole
		{
			PARTY_ROLE_NORMAL,
			PARTY_ROLE_LEADER,
			PARTY_ROLE_ATTACKER,
			PARTY_ROLE_TANKER,
			PARTY_ROLE_BUFFER,
			PARTY_ROLE_SKILL_MASTER,
			PARTY_ROLE_BERSERKER,
			PARTY_ROLE_DEFENDER,
			PARTY_ROLE_MAX_NUM,
		};

		enum
		{
			SKILL_NORMAL,
			SKILL_MASTER,
			SKILL_GRAND_MASTER,
			SKILL_PERFECT_MASTER,
		};

		// �ڵ����� ���� ���� Ưȭ ����ü.. �̷����� Ưȭ ó�� �۾��� �� �Ϸ��� �ִ��� ��������� �����ϰ� �ᱹ Ưȭó��.
		struct SAutoPotionInfo
		{
			SAutoPotionInfo() : bActivated(false), totalAmount(0), currentAmount(0) {}

			bool bActivated;					// Ȱ��ȭ �Ǿ��°�?
			long currentAmount;					// ���� ���� ��
			long totalAmount;					// ��ü ��
			long inventorySlotIndex;			// ������� �������� �κ��丮�� ���� �ε���
		};

		enum EAutoPotionType
		{
			AUTO_POTION_TYPE_HP = 0,
			AUTO_POTION_TYPE_SP = 1,
			AUTO_POTION_TYPE_NUM
		};

	public:
		CPythonPlayer(void);
		virtual ~CPythonPlayer(void);

		//void	PickCloseMoney();
		void	PickCloseItem();
	public:
		void	SetGameWindow(PyObject * ppyObject);

		void	SetObserverMode(bool isEnable);
		bool	IsObserverMode();

		void	SetQuickCameraMode(bool isEnable);

		void	SetAttackKeyState(bool isPress);

		void	NEW_GetMainActorPosition(TPixelPosition* pkPPosActor);

		bool	RegisterEffect(DWORD dwEID, const char* c_szEftFileName, bool isCache);

		bool	NEW_SetMouseState(int eMBType, int eMBState);
		bool	NEW_SetMouseFunc(int eMBType, int eMBFunc);
		int		NEW_GetMouseFunc(int eMBT);
		void	NEW_SetMouseMiddleButtonState(int eMBState);

#ifdef ATTR_LOCK
		void	SetItemAttrLocked(TItemPos itemPos, short dwIndex);
		short	GetItemAttrLocked(TItemPos itemPos);
#endif

		void	NEW_SetAutoCameraRotationSpeed(float fRotSpd);
		void	NEW_ResetCameraRotation();

		void	NEW_SetSingleDirKeyState(int eDirKey, bool isPress);
		void	NEW_SetSingleDIKKeyState(int eDIKKey, bool isPress);
		void	NEW_SetMultiDirKeyState(bool isLeft, bool isRight, bool isUp, bool isDown);

		void	NEW_Attack();
		void	NEW_Fishing();
		bool	NEW_CancelFishing();

		void	NEW_LookAtFocusActor();
		bool	NEW_IsAttackableDistanceFocusActor();


		bool	NEW_MoveToDestPixelPositionDirection(const TPixelPosition& c_rkPPosDst);
		bool	NEW_MoveToMousePickedDirection();
		bool	NEW_MoveToMouseScreenDirection();
		bool	NEW_MoveToDirection(float fDirRot);
		void	NEW_Stop();


		// Reserved
		bool	NEW_IsEmptyReservedDelayTime(float fElapsedtime);	// ���̹� ���� ���� �ʿ� - [levites]


		// Dungeon
		void	SetDungeonDestinationPosition(int ix, int iy);
		void	AlarmHaveToGo();


		CInstanceBase* NEW_FindActorPtr(DWORD dwVID);
		CInstanceBase* NEW_GetMainActorPtr();

		// flying target set
		void	Clear();
		void	ClearSkillDict(); // �������ų� ClearGame ������ ���Ե� �Լ�
		void	NEW_ClearSkillData(bool bAll = false);

		void	Update();


		// Play Time
		DWORD	GetPlayTime();
		void	SetPlayTime(DWORD dwPlayTime);


		// System
		void	SetMainCharacterIndex(int iIndex);

		DWORD	GetMainCharacterIndex();
		bool	IsMainCharacterIndex(DWORD dwIndex);
		DWORD	GetGuildID();
		void	NotifyDeletingCharacterInstance(DWORD dwVID);
		void	NotifyCharacterDead(DWORD dwVID);
		void	NotifyCharacterUpdate(DWORD dwVID);
		void	NotifyDeadMainCharacter();
		void	NotifyChangePKMode();


		// Player Status
		const char *	GetName();
		void	SetName(const char *name);

		void	SetRace(DWORD dwRace);
		DWORD	GetRace();

		void	SetWeaponPower(DWORD dwMinPower, DWORD dwMaxPower, DWORD dwMinMagicPower, DWORD dwMaxMagicPower, DWORD dwAddPower);
#ifdef ENABLE_LONG_LONG
		void	SetStatus(DWORD dwType, long long lValue);
		long long		GetStatus(DWORD dwType);
#else
		void	SetStatus(DWORD dwType, long lValue);
		int		GetStatus(DWORD dwType);
#endif



		// Item
		void	MoveItemData(TItemPos SrcCell, TItemPos DstCell);
		void	SetItemData(TItemPos Cell, const TItemData & c_rkItemInst);
		const TItemData * GetItemData(TItemPos Cell) const;
		void	SetItemCount(TItemPos Cell,
#ifdef ENABLE_NEW_STACK_LIMIT
		int byCount
#else
		BYTE byCount
#endif
		);
		void	SetItemMetinSocket(TItemPos Cell, DWORD dwMetinSocketIndex, DWORD dwMetinNumber);
		void	SetItemAttribute(TItemPos Cell, DWORD dwAttrIndex, BYTE byType, short sValue);
		DWORD	GetItemIndex(TItemPos Cell);
		DWORD	GetItemFlags(TItemPos Cell);
		DWORD	GetItemAntiFlags(TItemPos Cell);
		BYTE	GetItemTypeBySlot(TItemPos Cell);
		BYTE	GetItemSubTypeBySlot(TItemPos Cell);
		DWORD	GetItemCount(TItemPos Cell);
		DWORD	GetItemCountByVnum(DWORD dwVnum);
#ifdef ENABLE_EXTRA_INVENTORY
		//To fix search item in refine (0)
		WORD	GetItemCountbyVnumExtraInventory(DWORD dwVnum);
#endif
		DWORD	GetItemMetinSocket(TItemPos Cell, DWORD dwMetinSocketIndex);
		void	GetItemAttribute(TItemPos Cell, DWORD dwAttrSlotIndex, BYTE * pbyType, short * psValue);
		void	SendClickItemPacket(DWORD dwIID);

		void	RequestAddLocalQuickSlot(DWORD dwLocalSlotIndex, DWORD dwWndType, DWORD dwWndItemPos);
		void	RequestAddToEmptyLocalQuickSlot(DWORD dwWndType, DWORD dwWndItemPos);
		void	RequestMoveGlobalQuickSlotToLocalQuickSlot(DWORD dwGlobalSrcSlotIndex, DWORD dwLocalDstSlotIndex);
		void	RequestDeleteGlobalQuickSlot(DWORD dwGlobalSlotIndex);
		void	RequestUseLocalQuickSlot(DWORD dwLocalSlotIndex);
		DWORD	LocalQuickSlotIndexToGlobalQuickSlotIndex(DWORD dwLocalSlotIndex);

		void	GetGlobalQuickSlotData(DWORD dwGlobalSlotIndex, DWORD* pdwWndType, DWORD* pdwWndItemPos);
		void	GetLocalQuickSlotData(DWORD dwSlotPos, DWORD* pdwWndType, DWORD* pdwWndItemPos);
		void	RemoveQuickSlotByValue(int iType, int iPosition);

		char	IsItem(TItemPos SlotIndex);

#ifdef ENABLE_NEW_EQUIPMENT_SYSTEM
		bool    IsBeltInventorySlot(TItemPos Cell);
#endif
		bool	IsInventorySlot(TItemPos SlotIndex);
		bool	IsEquipmentSlot(TItemPos SlotIndex);

		bool	IsEquipItemInSlot(TItemPos iSlotIndex);


		// Quickslot
		int		GetQuickPage();
		void	SetQuickPage(int nPageIndex);
		void	AddQuickSlot(int QuickslotIndex, char IconType, char IconPosition);
		void	DeleteQuickSlot(int QuickslotIndex);
		void	MoveQuickSlot(int Source, int Target);


		// Skill
		void	SetSkill(DWORD dwSlotIndex, DWORD dwSkillIndex);
		bool	GetSkillSlotIndex(DWORD dwSkillIndex, DWORD* pdwSlotIndex);
		int		GetSkillIndex(DWORD dwSlotIndex);
		int		GetSkillGrade(DWORD dwSlotIndex);
		int		GetSkillLevel(DWORD dwSlotIndex);
		float	GetSkillCurrentEfficientPercentage(DWORD dwSlotIndex);
		float	GetSkillNextEfficientPercentage(DWORD dwSlotIndex);

#ifdef ENABLE_NEW_PASSIVE_SKILLS
		float	GetSkillNextEfficientPercentageByLvl(DWORD dwSlotIndex, DWORD dwLevel);
#endif

		void	SetSkillLevel(DWORD dwSlotIndex, DWORD dwSkillLevel);
		void	SetSkillLevel_(DWORD dwSkillIndex, DWORD dwSkillGrade, DWORD dwSkillLevel);
		BOOL	IsToggleSkill(DWORD dwSlotIndex);
		void	ClickSkillSlot(DWORD dwSlotIndex);
		void	ChangeCurrentSkillNumberOnly(DWORD dwSlotIndex);
		bool	FindSkillSlotIndexBySkillIndex(DWORD dwSkillIndex, DWORD * pdwSkillSlotIndex);

		void	SetSkillCoolTime(DWORD dwSkillIndex);
		void	EndSkillCoolTime(DWORD dwSkillIndex);

		float	GetSkillCoolTime(DWORD dwSlotIndex);
		float	GetSkillElapsedCoolTime(DWORD dwSlotIndex);
		BOOL	IsSkillActive(DWORD dwSlotIndex);
		BOOL	IsSkillCoolTime(DWORD dwSlotIndex);
		void	UseGuildSkill(DWORD dwSkillSlotIndex);
		bool	AffectIndexToSkillSlotIndex(UINT uAffect, DWORD* pdwSkillSlotIndex);
		bool	AffectIndexToSkillIndex(DWORD dwAffectIndex, DWORD * pdwSkillIndex);

		void	SetAffect(UINT uAffect);
		void	ResetAffect(UINT uAffect);
		void	ClearAffects();


		// Target
		void	SetTarget(DWORD dwVID, BOOL bForceChange = TRUE);
		void	OpenCharacterMenu(DWORD dwVictimActorID);
		DWORD	GetTargetVID();


		// Party
		void	ExitParty();
		void	AppendPartyMember(DWORD dwPID, const char * c_szName);
		void	LinkPartyMember(DWORD dwPID, DWORD dwVID);
		void	UnlinkPartyMember(DWORD dwPID);
		void	UpdatePartyMemberInfo(DWORD dwPID, BYTE byState, BYTE byHPPercentage);
		void	UpdatePartyMemberAffect(DWORD dwPID, BYTE byAffectSlotIndex, short sAffectNumber);
		void	RemovePartyMember(DWORD dwPID);
		bool	IsPartyMemberByVID(DWORD dwVID);
		bool	IsPartyMemberByName(const char * c_szName);
		bool	GetPartyMemberPtr(DWORD dwPID, TPartyMemberInfo ** ppPartyMemberInfo);
		bool	PartyMemberPIDToVID(DWORD dwPID, DWORD * pdwVID);
		bool	PartyMemberVIDToPID(DWORD dwVID, DWORD * pdwPID);
		bool	IsSamePartyMember(DWORD dwVID1, DWORD dwVID2);


		// Fight
		void	RememberChallengeInstance(DWORD dwVID);
		void	RememberRevengeInstance(DWORD dwVID);
		void	RememberCantFightInstance(DWORD dwVID);
		void	ForgetInstance(DWORD dwVID);
		bool	IsChallengeInstance(DWORD dwVID);
		bool	IsRevengeInstance(DWORD dwVID);
		bool	IsCantFightInstance(DWORD dwVID);


		// Private Shop
		void	OpenPrivateShop();
		void	ClosePrivateShop();
		bool	IsOpenPrivateShop();



		// Stamina
		void	StartStaminaConsume(DWORD dwConsumePerSec, DWORD dwCurrentStamina);
		void	StopStaminaConsume(DWORD dwCurrentStamina);


		// PK Mode
		DWORD	GetPKMode();


		// Mobile
		void	SetMobileFlag(BOOL bFlag);
		BOOL	HasMobilePhoneNumber();


		// Combo
		void	SetComboSkillFlag(BOOL bFlag);


		// System
		void	SetMovableGroundDistance(float fDistance);


		// Emotion
		void	ActEmotion(DWORD dwEmotionID);
		void	StartEmotionProcess();
		void	EndEmotionProcess();


		// Function Only For Console System
		BOOL	__ToggleCoolTime();
		BOOL	__ToggleLevelLimit();

		__inline const	SAutoPotionInfo& GetAutoPotionInfo(int type) const	{ return m_kAutoPotionInfo[type]; }
		__inline		SAutoPotionInfo& GetAutoPotionInfo(int type)		{ return m_kAutoPotionInfo[type]; }
		__inline void					 SetAutoPotionInfo(int type, const SAutoPotionInfo& info)	{ m_kAutoPotionInfo[type] = info; }

	protected:
		TQuickSlot &	__RefLocalQuickSlot(int SlotIndex);
		TQuickSlot &	__RefGlobalQuickSlot(int SlotIndex);


		DWORD	__GetLevelAtk();
		DWORD	__GetStatAtk();
		DWORD	__GetWeaponAtk(DWORD dwWeaponPower);
		DWORD	__GetTotalAtk(DWORD dwWeaponPower, DWORD dwRefineBonus);
		DWORD	__GetRaceStat();
		DWORD	__GetHitRate();
		DWORD	__GetEvadeRate();

		void	__UpdateBattleStatus();

		void	__DeactivateSkillSlot(DWORD dwSlotIndex);
		void	__ActivateSkillSlot(DWORD dwSlotIndex);

		void	__OnPressSmart(CInstanceBase& rkInstMain, bool isAuto);
		void	__OnClickSmart(CInstanceBase& rkInstMain, bool isAuto);

		void	__OnPressItem(CInstanceBase& rkInstMain, DWORD dwPickedItemID);
		void	__OnPressActor(CInstanceBase& rkInstMain, DWORD dwPickedActorID, bool isAuto);
		void	__OnPressGround(CInstanceBase& rkInstMain, const TPixelPosition& c_rkPPosPickedGround);
		void	__OnPressScreen(CInstanceBase& rkInstMain);

		void	__OnClickActor(CInstanceBase& rkInstMain, DWORD dwPickedActorID, bool isAuto);
		void	__OnClickItem(CInstanceBase& rkInstMain, DWORD dwPickedItemID);
		void	__OnClickGround(CInstanceBase& rkInstMain, const TPixelPosition& c_rkPPosPickedGround);

		bool	__IsMovableGroundDistance(CInstanceBase& rkInstMain, const TPixelPosition& c_rkPPosPickedGround);

		bool	__GetPickedActorPtr(CInstanceBase** pkInstPicked);

		bool	__GetPickedActorID(DWORD* pdwActorID);
		bool	__GetPickedItemID(DWORD* pdwItemID);
		bool	__GetPickedGroundPos(TPixelPosition* pkPPosPicked);

		void	__ClearReservedAction();
		void	__ReserveClickItem(DWORD dwItemID);
		void	__ReserveClickActor(DWORD dwActorID);
		void	__ReserveClickGround(const TPixelPosition& c_rkPPosPickedGround);
		void	__ReserveUseSkill(DWORD dwActorID, DWORD dwSkillSlotIndex, DWORD dwRange);

		void	__ReserveProcess_ClickActor();

		void	__ShowPickedEffect(const TPixelPosition& c_rkPPosPickedGround);
		void	__SendClickActorPacket(CInstanceBase& rkInstVictim);

		void	__ClearAutoAttackTargetActorID();
		void	__SetAutoAttackTargetActorID(DWORD dwActorID);

		void	NEW_ShowEffect(int dwEID, TPixelPosition kPPosDst);

		void	NEW_SetMouseSmartState(int eMBS, bool isAuto);
		void	NEW_SetMouseMoveState(int eMBS);
		void	NEW_SetMouseCameraState(int eMBS);
		void	NEW_GetMouseDirRotation(float fScrX, float fScrY, float* pfDirRot);
		void	NEW_GetMultiKeyDirRotation(bool isLeft, bool isRight, bool isUp, bool isDown, float* pfDirRot);

		float	GetDegreeFromDirection(int iUD, int iLR);
		float	GetDegreeFromPosition(int ix, int iy, int iHalfWidth, int iHalfHeight);

		bool	CheckCategory(int iCategory);
		bool	CheckAbilitySlot(int iSlotIndex);

		void	RefreshKeyWalkingDirection();
		void	NEW_RefreshMouseWalkingDirection();


		// Instances
		void	RefreshInstances();

		bool	__CanShot(CInstanceBase& rkInstMain, CInstanceBase& rkInstTarget);
		bool	__CanUseSkill();

		bool	__CanMove();

		bool	__CanAttack();
		bool	__CanChangeTarget();

		bool	__CheckSkillUsable(DWORD dwSlotIndex);
		void	__UseCurrentSkill();
		void	__UseChargeSkill(DWORD dwSkillSlotIndex);
		bool	__UseSkill(DWORD dwSlotIndex);
		bool	__CheckSpecialSkill(DWORD dwSkillIndex);

		bool	__CheckRestSkillCoolTime(DWORD dwSkillSlotIndex);
		bool	__CheckShortLife(TSkillInstance & rkSkillInst, CPythonSkill::TSkillData& rkSkillData);
		bool	__CheckShortMana(TSkillInstance & rkSkillInst, CPythonSkill::TSkillData& rkSkillData);
		bool	__CheckShortArrow(TSkillInstance & rkSkillInst, CPythonSkill::TSkillData& rkSkillData);
		bool	__CheckDashAffect(CInstanceBase& rkInstMain);

		void	__SendUseSkill(DWORD dwSkillSlotIndex, DWORD dwTargetVID);
		void	__RunCoolTime(DWORD dwSkillSlotIndex);

		BYTE	__GetSkillType(DWORD dwSkillSlotIndex);

		bool	__IsReservedUseSkill(DWORD dwSkillSlotIndex);
		bool	__IsMeleeSkill(CPythonSkill::TSkillData& rkSkillData);
		bool	__IsChargeSkill(CPythonSkill::TSkillData& rkSkillData);
		DWORD	__GetSkillTargetRange(CPythonSkill::TSkillData& rkSkillData);
		bool	__SearchNearTarget();
		bool	__IsUsingChargeSkill();

		bool	__ProcessEnemySkillTargetRange(CInstanceBase& rkInstMain, CInstanceBase& rkInstTarget, CPythonSkill::TSkillData& rkSkillData, DWORD dwSkillSlotIndex);


		// Item
		bool	__HasEnoughArrow();
		bool	__HasItem(DWORD dwItemID);
#ifndef ENABLE_INSTANT_PICKUP
		DWORD	__GetPickableDistance();
#endif

		// Target
		CInstanceBase*		__GetTargetActorPtr();
		void				__ClearTarget();
		DWORD				__GetTargetVID();
		void				__SetTargetVID(DWORD dwVID);
		bool				__IsSameTargetVID(DWORD dwVID);
		bool				__IsTarget();
		bool				__ChangeTargetToPickedInstance();

		CInstanceBase *		__GetSkillTargetInstancePtr(CPythonSkill::TSkillData& rkSkillData);
		CInstanceBase *		__GetAliveTargetInstancePtr();
		CInstanceBase *		__GetDeadTargetInstancePtr();

		BOOL				__IsRightButtonSkillMode();


		// Update
		void				__Update_AutoAttack();
		void				__Update_NotifyGuildAreaEvent();



		// Emotion
		BOOL				__IsProcessingEmotion();


	protected:
		PyObject *				m_ppyGameWindow;

		// Client Player Data
		std::map<DWORD, DWORD>	m_skillSlotDict;
		std::string				m_stName;
		DWORD					m_dwMainCharacterIndex;
		DWORD					m_dwRace;
		DWORD					m_dwWeaponMinPower;
		DWORD					m_dwWeaponMaxPower;
		DWORD					m_dwWeaponMinMagicPower;
		DWORD					m_dwWeaponMaxMagicPower;
		DWORD					m_dwWeaponAddPower;

		// Todo
		DWORD					m_dwSendingTargetVID;
		float					m_fTargetUpdateTime;

		// Attack
		DWORD					m_dwAutoAttackTargetVID;

		// NEW_Move
		EMode					m_eReservedMode;
		float					m_fReservedDelayTime;

		float					m_fMovDirRot;

		bool					m_isUp;
		bool					m_isDown;
		bool					m_isLeft;
		bool					m_isRight;
		bool					m_isAtkKey;
		bool					m_isDirKey;
		bool					m_isCmrRot;
		bool					m_isSmtMov;
		bool					m_isDirMov;

		float					m_fCmrRotSpd;

		TPlayerStatus			m_playerStatus;

		UINT					m_iComboOld;
		DWORD					m_dwVIDReserved;
		DWORD					m_dwIIDReserved;

		DWORD					m_dwcurSkillSlotIndex;
		DWORD					m_dwSkillSlotIndexReserved;
		DWORD					m_dwSkillRangeReserved;

		TPixelPosition			m_kPPosInstPrev;
		TPixelPosition			m_kPPosReserved;

		// Emotion
		BOOL					m_bisProcessingEmotion;

		// Dungeon
		BOOL					m_isDestPosition;
		int						m_ixDestPos;
		int						m_iyDestPos;
		int						m_iLastAlarmTime;

		// Party
		std::map<DWORD, TPartyMemberInfo>	m_PartyMemberMap;

		// PVP
		std::set<DWORD>			m_ChallengeInstanceSet;
		std::set<DWORD>			m_RevengeInstanceSet;
		std::set<DWORD>			m_CantFightInstanceSet;

		// Private Shop
		bool					m_isOpenPrivateShop;
		bool					m_isObserverMode;

		// Stamina
		BOOL					m_isConsumingStamina;
		float					m_fCurrentStamina;
		float					m_fConsumeStaminaPerSec;

		// Guild
		DWORD					m_inGuildAreaID;

		// Mobile
		BOOL					m_bMobileFlag;

		// System
		BOOL					m_sysIsCoolTime;
		BOOL					m_sysIsLevelLimit;

	protected:
		// Game Cursor Data
		TPixelPosition			m_MovingCursorPosition;
		float					m_fMovingCursorSettingTime;
		DWORD					m_adwEffect[EFFECT_NUM];

		DWORD					m_dwVIDPicked;
		DWORD					m_dwIIDPicked;
		int						m_aeMBFButton[MBT_NUM];

		DWORD					m_dwTargetVID;
		DWORD					m_dwTargetEndTime;
		DWORD					m_dwPlayTime;

		SAutoPotionInfo			m_kAutoPotionInfo[AUTO_POTION_TYPE_NUM];

	protected:
		float					MOVABLE_GROUND_DISTANCE;

	private:
		std::map<DWORD, DWORD> m_kMap_dwAffectIndexToSkillIndex;

#ifdef ENABLE_AUTO_PICKUP
	private:
		Event::EventHandle m_PickupEventHandle;
	public:
		void SetPickUpEventHandle(const Event::EventHandle& Handle) {
			m_PickupEventHandle = Handle;
		}
#endif
};

extern const int c_iFastestSendingCount;
extern const int c_iSlowestSendingCount;
extern const float c_fFastestSendingDelay;
extern const float c_fSlowestSendingDelay;
extern const float c_fRotatingStepTime;

extern const float c_fComboDistance;
extern const float c_fPickupDistance;
extern const float c_fClickDistance;