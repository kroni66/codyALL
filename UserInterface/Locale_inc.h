#pragma once

// #define __USE_CYTHON__
// #define NEEDED_COMMAND_ARGUMENT "DAMnJDABJd"

#define LINK_IN_CHAT
#define PYTHON_DYNAMIC_MODULE_NAME
#define ENABLE_MILES_CHECK
#define ENABLE_PYLIB_CHECK
#define ENABLE_ANTICHEAT
#define ENABLE_SEND_TARGET_INFO_EXTENDED
#define ENABLE_FOX_FS
#ifdef ENABLE_FOX_FS
#define ENABLE_LOAD_PROPERTY_XML
#endif
#define ENABLE_DOGMODE

/* da rimuovere dopo i test */
//#define ENABLE_LITTLE_PACK

/* non usati al momento per via di problemi */
//#define ENABLE_AUTO_TRANSLATE_WHISPER
#define INGAME_WIKI
#ifdef INGAME_WIKI
//#define ENABLE_INGAME_WIKI_HEARDERS_WRONGSIZE
	/*
		Only define this if you have wolfman in you server, for more
			informations reed wikipedia system guide!
	*/
#endif

/* common */
#define ENABLE_EXTRA_INVENTORY

















//#define __USE_EXTRA_CYTHON__

//////////////////////////////////////////////////////////////////////////
// ### Default Ymir Macros ###
#define ENABLE_RANKING
#define LOCALE_SERVICE_EUROPE
#define ENABLE_COSTUME_SYSTEM
#define ENABLE_ENERGY_SYSTEM
#define ENABLE_DRAGON_SOUL_SYSTEM
#define ENABLE_NEW_EQUIPMENT_SYSTEM
#define ENABLE_BUY_WITH_ITEM
#ifdef ENABLE_BUY_WITH_ITEM
	#define MAX_SHOP_PRICES 5
#endif
#define ENABLE_NEW_SECONDARY_SKILLS
// ### Default Ymir Macros ###
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// ### New From LocaleInc ###
#define ENABLE_PACK_GET_CHECK
//#define ENABLE_CANSEEHIDDENTHING_FOR_GM
#define ENABLE_PROTOSTRUCT_AUTODETECT

#define ATTR_LOCK

#define ENABLE_PLAYER_PER_ACCOUNT5
#define ENABLE_LEVEL_IN_TRADE
#define ENABLE_DICE_SYSTEM
#define ENABLE_EXTEND_INVEN_SYSTEM
#define ENABLE_LVL115_ARMOR_EFFECT
#define ENABLE_SLOT_WINDOW_EX
#define ENABLE_TEXT_LEVEL_REFRESH
#define ENABLE_USE_COSTUME_ATTR

#define WJ_SHOW_MOB_INFO
#ifdef WJ_SHOW_MOB_INFO
#define ENABLE_SHOW_MOBAIFLAG
#define ENABLE_SHOW_MOBLEVEL
#endif
//#define ENABLE_WOLFMAN_CHARACTER
#define ENABLE_MAGIC_REDUCTION_SYSTEM
#define ENABLE_MOUNT_COSTUME_SYSTEM
#define ENABLE_WEAPON_COSTUME_SYSTEM
#define ENABLE_SWITCHBOT
#define ENABLE_SEND_TARGET_INFO
#define ENABLE_MAP_TELEPORTER
#define ENABLE_SAVEPOINT_SYSTEM
#define ENABLE_DEFENSE_WAVE
#define VERSION_162_ENABLED
#define NEW_PET_SYSTEM
#define ENABLE_WHISPER_ADMIN_SYSTEM
//#define ENABLE_MELEY_LAIR_DUNGEON
//#ifdef ENABLE_MELEY_LAIR_DUNGEON
	//#define MELEY_LAIR_DUNGEON_STATUE 6118

#define ADVANCED_GUILD_INFO
#define ENABLE_CUBE_RENEWAL_WORLDARD
#ifdef ENABLE_CUBE_RENEWAL_WORLDARD
	// #define ENABLE_CUBE_RENEWAL_GEM_WORLDARD		//Unused - Adapted with ENABLE_GAYA_SYSTEM (Don't Active this define!!)
	#define ENABLE_CUBE_RENEWAL_COPY_WORLDARD
#endif
#define ENABLE_GAYA_SYSTEM					// Gaya System Metin2
#define ENABLE_CAPITALE_SYSTEM				// Expanded Capital System
#define	__ENABLE_RANGE_ALCHEMY__			// Open shop everywhere
#define __ENABLE_REFINE_ALCHEMY__			// Open Refine Window everywhere
#define	ENABLE_STRONG_BOSS					// Bonus strong against Boss
#define ENABLE_STRONG_METIN					// Bonus strong against Metin
#define ENABLE_RESIST_MONSTER				// New Bonus Resist Monster
#define ENABLE_MEDI_PVM						// New Bonus Medi Pvm
#define ELEMENT_NEW_BONUSES					// Bonus Elemental Resistence (Fire, Ice, Dark, Earth, Elect, Wind)
#ifdef ELEMENT_NEW_BONUSES					//
#define ENABLE_PENDANT						// New Item Talisman Resistence (Item Metin2 17.5)
#define ENABLE_NEW_BONUS_TALISMAN			// New Bonus DB for Talisman (Metin2 17.5)
#define ENABLE_TALISMAN_EFFECT  // Effect Talisman like Acce
#endif
#define ENABLE_VIEW_TARGET_PLAYER_HP		// Show Decimal HP
#ifdef ENABLE_VIEW_TARGET_PLAYER_HP			//
#define ENABLE_VIEW_TARGET_DECIMAL_HP		//
#endif
#define __CHANNEL_CHANGE_SYSTEM__			// Instant Change Channel
#define ENABLE_DATETIME_UNDER_MINIMAP		// DateTime (ONly PythonApplicationModule.cpp)
#define ENABLE_HIDE_COSTUME_SYSTEM			// Hide costume parts (Only PythonApplicationModule.cpp)
#define ENABLE_SORT_INVEN					// Sort Inventory (Only PythonApplicationModule.cpp)
#define __ENABLE_EXTEND_INVEN_SYSTEM__		// Extend Official Inventory witk Key
#define ENABLE_SOUL_SYSTEM					//System Anima
#define ENABLE_NEW_PASSIVE_SKILLS			//Systemm skill passive
// if is define ENABLE_ACCE_SYSTEM the players can use shoulder sash 
// if you want to use object scaling function you must defined ENABLE_OBJ_SCALLING
#define ENABLE_ACCE_SYSTEM
#define ENABLE_OBJ_SCALLING
//#define ENABLE_PLAYER_PIN_SYSTEM // Player PIN
#define ENABLE_QUEST_RENEWAL				// Quest page renewal
#define	ENABLE_FEATURES_REFINE_SYSTEM		// Refine System
#define __ENABLE_NEW_EFFECT_CIANITE__		// New Effect for Armor Cianite	
#define __ENABLE_NEW_EFFECT_CIANITE_WEAPON__	// New Effect for Weapon Cianite	
#define __ENABLE_NEW_EFFECT_ZODIACO_WEAPON1__	// New Effect for Weapon1 Zodiaco	
#define __ENABLE_NEW_EFFECT_ZODIACO__		// New Effect for Armor Zodiaco	
#define __ENABLE_NEW_EFFECT_ZODIACO1__		// New Effect for Armor1 Zodiaco	
#define __ENABLE_NEW_EFFECT_ZODIACO_WEAPON__	// New Effect for Weapon Zodiaco	
#define ENABLE_SKILL_COLOR_SYSTEM 			// Skill color
#ifdef ENABLE_SKILL_COLOR_SYSTEM
#define ENABLE_5LAYER_SKILL_COLOR 			// Enable 5 layers for skill color
#endif
#define ENABLE_CONFIG_MODULE 					// Enable configuration module for saving settings
#define ENABLE_BATTLE_PASS
#define ENABLE_NEW_EXCHANGE_WINDOW
#define ENABLE_PVP_ADVANCED
#define EQUIP_ENABLE_VIEW_SASH
#define ENABLE_MULTI_LANGUAGE				// MultiLanguage
//OFFSHOP
#define __ENABLE_EMOJI_SYSTEM__
#define __ENABLE_NEW_OFFLINESHOP__
#define ENABLE_OFFLINESHOP_DEBUG
#define ENABLE_NEW_SHOP_IN_CITIES
#define BLOCK_AUTO_ATTACK_PLAYER


//HOTTIES IKARUS STUFFS
#define ENABLE_ITEM_EXTRA_PROTO
#define ENABLE_RARITY_SYSTEM
#define ENABLE_NEW_EXTRA_BONUS

#define ENABLE_ATTR_TRANSFER_SYSTEM
#define ENABLE_ATTR_COSTUMES
#if defined(ENABLE_OFFLINESHOP_DEBUG) && defined(_DEBUG)
#define OFFSHOP_DEBUG(fmt , ...) Tracenf("%s:%d >> " fmt , __FUNCTION__ , __LINE__, __VA_ARGS__)
#else
#define OFFSHOP_DEBUG(...)   
#endif

//#define ENABLE_DUNGEON_INFO_SYSTEM
#define ENABLE_LOCKED_EXTRA_INVENTORY
#define ENABLE_DS_SET
#define ENABLE_DS_ENCHANT
#define ENABLE_HIGHLIGHT_SYSTEM
#define ENABLE_NEW_PET_EDITS
#define ENABLE_REMOTE_ATTR_SASH_REMOVE
#define __ENABLE_NEW_EFFECT_STOLE__
#define ENABLE_ATLAS_BOSS
#define ENABLE_STOLE_REAL
#define ENABLE_STOLE_COSTUME
#define ENABLE_COSTUME_PET
#define ENABLE_COSTUME_MOUNT
#define ENABLE_COSTUME_EFFECT
#define ENABLE_LONG_LONG
#define KASMIR_PAKET_SYSTEM
#define ENABLE_EFFECT_WEAPON_COSTUME
#define ENABLE_BUGFIX_EFFECT_FAN
#define ENABLE_DS_RUNE
#define ENABLE_BLOCK_MULTIFARM
#define ENABLE_BUGFIXES_NOTDONE
#define BL_OFFLINE_MESSAGE
#define ENABLE_RUNE_SYSTEM
#define ENABLE_NEW_USE_POTION
#define __EFFETTO_MANTELLO__
#define ENABLE_LIMIT_PUSH_DEST
#define ENABLE_NEW_RESTART
#define ENABLE_RACE_HEIGHT
#define DISABLE_MENU_IF_KEY_F10
#define ENABLE_NEW_STACK_LIMIT
#define ENABLE_DISCORD_RPC
#define ENABLE_VIEW_ELEMENT
#define ENABLE_RECALL
#define ENABLE_NEW_COMMON_BONUSES
#define ENABLE_PERSPECTIVE_VIEW
#define ENABLE_UI_EXTRA
#define ENABLE_NEW_CHAT
#define ENABLE_DS_GRADE_MYTH
#define ENABLE_NO_COLLISION
#define TEXTS_IMPROVEMENT
#define __ENABLE_LARGE_DYNAMIC_PACKET__
#define ENABLE_INFINITE_RAFINES
#define ENABLE_BIOLOGIST_UI
#define ENABLE_EMPIRE_EFFECT_LIMITED
#define ENABLE_DS_POTION_DIFFRENT
#define ENABLE_NEW_FISHING_SYSTEM
#define ENABLE_NEW_BUGFIXES
#define WJ_ENABLE_TRADABLE_ICON
#define ENABLE_3D_MODELS_TEXTURE_FIX
#define ENABLE_NEW_GYEONGGONG_SKILL
#define ENABLE_SAVECAMERA_PREFERENCES
//#define ENABLE_MAP_PERFORMANCE
#define ENABLE_GENDER_ALIGNMENT
#define DISABLE_CRITICAL_EFFECT
#define OUTLINE_NAMES_TEXTLINE
#define ENABLE_MULTI_NAMES
#define NORMAL_ROTATION_SPEED 2400.0f
#define MOUNT_ROTATION_SPEED 1200.0f
#define ENABLE_CHOOSE_DOCTRINE_GUI
#define ENABLE_ITEMSHOP_ITEM
#define ENABLE_BUGFIXES
#define ENABLE_CONQUEROR_LEVEL
#define SPECIAL_ACTION_START_INDEX 101

//#define __ENABLE_CH3HP_PROTECTION__
//#if defined(__ENABLE_CH3HP_PROTECTION__)
//#define REGIST_WEBSITE_LINK "http://146.59.82.108:54691/"
//#endif
//#define CEF_BROWSER
#define ENABLE_AUTO_PICKUP
#define ENABLE_INSTANT_PICKUP
#define ENABLE_DS_REFINE_ALL
#define ENABLE_NEW_ATTACK_METHOD
#define ENABLE_BUY_STACK_FROM_SHOP
#ifdef ENABLE_BUY_STACK_FROM_SHOP
#define MULTIPLE_BUY_LIMIT 100
#else
#define MULTIPLE_BUY_LIMIT 0
#endif
#define ENABLE_OPENSHOP_PACKET
#define ENABLE_HWID
#define ENABLE_VOTE_FOR_BONUS
#define ENABLE_MESSENGER_TEAM
#define ENABLE_MESSENGER_HELPER
#define ENABLE_CHRISTMAS_2021
#ifdef ENABLE_CHRISTMAS_2021
#define ENABLE_CHRISTMAS_WHEEL_OF_DESTINY
#endif
/* debug
#define __PERFORMANCE_CHECKER__
#define _PACKETDUMP
*/

/* unused
#define ENABLE_SEQUENCE
*/