#include "StdAfx.h"
#include "../eterBase/Random.h"
#include "../eterlib/StateManager.h"
#include "EffectManager.h"

bool CEffectManager::CanRenderFunction(CEffectInstance* pkEftInst) const
{
	if (GetEffectOption(EFFECT_OPTION_ALL)) {
		return false;
	}

	static const std::vector<std::string> vEffectNames[CEffectManager::EFFECT_OPTION_MAX]
	{
		{
			"d:/ymir work/pc/shaman/effect/3hosin_loop.mse",
			"d:/ymir work/pc/shaman/effect/boho_loop.mse",
			"d:/ymir work/pc/shaman/effect/6gicheon_hand.mse",
			"d:/ymir work/pc/shaman/effect/jeungryeok_hand.mse"
		},
		{
			"d:/ymir work/pc/shaman/effect/10kwaesok_loop.mse",
			"d:/ymir work/pc/sura/effect/gwigeom_loop.mse",
			"d:/ymir work/pc/sura/effect/fear_loop.mse",
			"d:/ymir work/pc/sura/effect/jumagap_loop.mse",
			"d:/ymir work/pc/sura/effect/muyeong_loop.mse",
			"d:/ymir work/pc/sura/effect/heuksin_loop.mse",
			"d:/ymir work/pc/warrior/effect/gyeokgongjang_loop.mse",
			"d:/ymir work/pc/warrior/effect/geom_sword_loop.mse",
			"d:/ymir work/pc/warrior/effect/geom_spear_loop.mse",
			"d:/ymir work/pc/assassin/effect/gyeonggong_loop.mse",
		},
		{
			"d:/ymir work/effect/shining/nero/ridack_armor_black.mse",
			"d:/ymir work/effect/shining/viola/ridack_armor_fushiia.mse",
			"d:/ymir work/effect/shining/orange/ridack_armor_orange.mse",
			"d:/ymir work/effect/shining/verdino/ridack_armor_jade.mse",
			"d:/ymir work/effect/shining1/viola/ridack_armor_purple2.mse",
			"d:/ymir work/effect/shining1/blu/ridack_armor_blue2.mse",
			"d:/ymir work/effect/shining1/rosa/ridack_armor_pink2.mse",
			"d:/ymir work/effect/shining1/bianco/ridack_armor_white2.mse",
			"d:/ymir work/effect/shining2/verde/ridack_armor_green.mse",
			"d:/ymir work/effect/shining2/rosso/ridack_armor_red.mse",
			"d:/ymir work/effect/shining2/blu/ridack_armor_blue.mse",
			"d:/ymir work/effect/shining2/giallo/ridack_armor_yellow.mse",
		},
		{
			"d:/ymir work/effect/shining/nero/ridack_sword_black.mse",
			"d:/ymir work/effect/shining/nero/ridack_spear_black.mse",
			"d:/ymir work/effect/shining/nero/ridack_knife_black.mse",
			"d:/ymir work/effect/shining/nero/ridack_bow_black.mse",
			"d:/ymir work/effect/shining/nero/ridack_bell_black.mse",
			"d:/ymir work/effect/shining/nero/ridack_fan_black.mse",
			"d:/ymir work/effect/shining/viola/ridack_sword_fushiia.mse",
			"d:/ymir work/effect/shining/viola/ridack_spear_fushiia.mse",
			"d:/ymir work/effect/shining/viola/ridack_knife_fushiia.mse",
			"d:/ymir work/effect/shining/viola/ridack_bow_fushiia.mse",
			"d:/ymir work/effect/shining/viola/ridack_bell_fushiia.mse",
			"d:/ymir work/effect/shining/viola/ridack_fan_fushiia.mse",
			"d:/ymir work/effect/shining/viola/ridack_sword_fushiia.mse",
			"d:/ymir work/effect/shining/viola/ridack_sword_fushiia.mse",
			"d:/ymir work/effect/shining/viola/ridack_sword_fushiia.mse",
			"d:/ymir work/effect/shining/viola/ridack_sword_fushiia.mse",
			"d:/ymir work/effect/shining/orange/ridack_sword_orange.mse",
			"d:/ymir work/effect/shining/orange/ridack_spear_orange.mse",
			"d:/ymir work/effect/shining/orange/ridack_knife_orange.mse",
			"d:/ymir work/effect/shining/orange/ridack_bow_orange.mse",
			"d:/ymir work/effect/shining/orange/ridack_bell_orange.mse",
			"d:/ymir work/effect/shining/orange/ridack_fan_orange.mse",
			"d:/ymir work/effect/shining/verdino/ridack_sword_jade.mse",
			"d:/ymir work/effect/shining/verdino/ridack_spear_jade.mse",
			"d:/ymir work/effect/shining/verdino/ridack_knife_jade.mse",
			"d:/ymir work/effect/shining/verdino/ridack_bow_jade.mse",
			"d:/ymir work/effect/shining/verdino/ridack_bell_jade.mse",
			"d:/ymir work/effect/shining/verdino/ridack_fan_jade.mse",
			"d:/ymir work/effect/shining1/viola/ridack_sword_purple2.mse",
			"d:/ymir work/effect/shining1/viola/ridack_spear_purple2.mse",
			"d:/ymir work/effect/shining1/viola/ridack_knife_purple2.mse",
			"d:/ymir work/effect/shining1/viola/ridack_bow_purple2.mse",
			"d:/ymir work/effect/shining1/viola/ridack_bell_purple2.mse",
			"d:/ymir work/effect/shining1/viola/ridack_fan_purple2.mse",
			"d:/ymir work/effect/shining1/blu/ridack_sword_blue2.mse",
			"d:/ymir work/effect/shining1/blu/ridack_spear_blue2.mse",
			"d:/ymir work/effect/shining1/blu/ridack_knife_blue2.mse",
			"d:/ymir work/effect/shining1/blu/ridack_bow_blue2.mse",
			"d:/ymir work/effect/shining1/blu/ridack_bell_blue2.mse",
			"d:/ymir work/effect/shining1/blu/ridack_fan_blue2.mse",
			"d:/ymir work/effect/shining1/rosa/ridack_sword_pink2.mse",
			"d:/ymir work/effect/shining1/rosa/ridack_knife_pink2.mse",
			"d:/ymir work/effect/shining1/rosa/ridack_bow_pink2.mse",
			"d:/ymir work/effect/shining1/rosa/ridack_bell_pink2.mse",
			"d:/ymir work/effect/shining1/rosa/ridack_fan_pink2.mse",
			"d:/ymir work/effect/shining1/rosa/ridack_knife_pink2.mse",
			"d:/ymir work/effect/shining1/bianco/ridack_sword_white2.mse",
			"d:/ymir work/effect/shining1/bianco/ridack_spear_white2.mse",
			"d:/ymir work/effect/shining1/bianco/ridack_knife_white2.mse",
			"d:/ymir work/effect/shining1/bianco/ridack_bow_white2.mse",
			"d:/ymir work/effect/shining1/bianco/ridack_bell_white2.mse",
			"d:/ymir work/effect/shining1/bianco/ridack_fan_white2.mse",
			"d:/ymir work/effect/shining2/verde/ridack_sword_green.mse",
			"d:/ymir work/effect/shining2/verde/ridack_spear_green.mse",
			"d:/ymir work/effect/shining2/verde/ridack_knife_green.mse",
			"d:/ymir work/effect/shining2/verde/ridack_bow_green.mse",
			"d:/ymir work/effect/shining2/verde/ridack_bell_green.mse",
			"d:/ymir work/effect/shining2/verde/ridack_fan_green.mse",
			"d:/ymir work/effect/shining2/rosso/ridack_sword_red.mse",
			"d:/ymir work/effect/shining2/rosso/ridack_spear_red.mse",
			"d:/ymir work/effect/shining2/rosso/ridack_knife_red.mse",
			"d:/ymir work/effect/shining2/rosso/ridack_bow_red.mse",
			"d:/ymir work/effect/shining2/rosso/ridack_bell_red.mse",
			"d:/ymir work/effect/shining2/rosso/ridack_fan_red.mse",
			"d:/ymir work/effect/shining2/blu/ridack_sword_blue.mse",
			"d:/ymir work/effect/shining2/blu/ridack_spear_blue.mse",
			"d:/ymir work/effect/shining2/blu/ridack_knife_blue.mse",
			"d:/ymir work/effect/shining2/blu/ridack_bow_blue.mse",
			"d:/ymir work/effect/shining2/blu/ridack_bell_blue.mse",
			"d:/ymir work/effect/shining2/blu/ridack_fan_blue.mse",
			"d:/ymir work/effect/shining2/giallo/ridack_sword_yellow.mse",
			"d:/ymir work/effect/shining2/giallo/ridack_spear_yellow.mse",
			"d:/ymir work/effect/shining2/giallo/ridack_knife_yellow.mse",
			"d:/ymir work/effect/shining2/giallo/ridack_bow_yellow.mse",
			"d:/ymir work/effect/shining2/giallo/ridack_bell_yellow.mse",
			"d:/ymir work/effect/shining2/giallo/ridack_fan_yellow.mse",
		},
	};

	for (BYTE i = 0; i < CEffectManager::EFFECT_OPTION_MAX - 1; i++)
	{
		if (!GetEffectOption(i))
			continue;

		if (!pkEftInst)
			break;

		CEffectData* EffectData = pkEftInst->GetEffectDataPointer();
		if (!EffectData)
			break;

		auto it = std::find(vEffectNames[i].begin(), vEffectNames[i].end(), EffectData->GetFileName());
		if (it != vEffectNames[i].end())
			return false;
	}

	return true;
}

void CEffectManager::GetInfo(std::string* pstInfo)
{
	char szInfo[256];

	sprintf(szInfo, "Effect: Inst - ED %d, EI %d Pool - PSI %d, MI %d, LI %d, PI %d, EI %d, ED %d, PSD %d, EM %d, LD %d",
		m_kEftDataMap.size(),
		m_kEftInstMap.size(),
		CParticleSystemInstance::ms_kPool.GetCapacity(),
		CEffectMeshInstance::ms_kPool.GetCapacity(),
		CLightInstance::ms_kPool.GetCapacity(),
		CParticleInstance::ms_kPool.GetCapacity(),
		//CRayParticleInstance::ms_kPool.GetCapacity(),
		CEffectInstance::ms_kPool.GetCapacity(),
		CEffectData::ms_kPool.GetCapacity(),
		CParticleSystemData::ms_kPool.GetCapacity(),
		CEffectMeshScript::ms_kPool.GetCapacity(),
		CLightData::ms_kPool.GetCapacity()
	);
	pstInfo->append(szInfo);
}

void CEffectManager::UpdateSound()
{
	for (TEffectInstanceMap::iterator itor = m_kEftInstMap.begin(); itor != m_kEftInstMap.end(); ++itor)
	{
		CEffectInstance * pEffectInstance = itor->second;

		pEffectInstance->UpdateSound();
	}
}

bool CEffectManager::IsAliveEffect(DWORD dwInstanceIndex)
{
	TEffectInstanceMap::iterator f = m_kEftInstMap.find(dwInstanceIndex);
	if (m_kEftInstMap.end()==f)
		return false;

	return f->second->isAlive() ? true : false;
}

void CEffectManager::Update()
{

	// 2004. 3. 1. myevan. 이펙트 모니터링 하는 코드
	/*
	if (GetAsyncKeyState(VK_F9))
	{
		Tracenf("CEffectManager::m_EffectInstancePool %d", m_EffectInstancePool.GetCapacity());
		Tracenf("CEffectManager::m_EffectDataPool %d", m_EffectDataPool.GetCapacity());
		Tracenf("CEffectInstance::ms_LightInstancePool %d", CEffectInstance::ms_LightInstancePool.GetCapacity());
		Tracenf("CEffectInstance::ms_MeshInstancePool %d", CEffectInstance::ms_MeshInstancePool.GetCapacity());
		Tracenf("CEffectInstance::ms_ParticleSystemInstancePool %d", CEffectInstance::ms_ParticleSystemInstancePool.GetCapacity());
		Tracenf("CParticleInstance::ms_ParticleInstancePool %d", CParticleInstance::ms_kPool.GetCapacity());
		Tracenf("CRayParticleInstance::ms_RayParticleInstancePool %d", CRayParticleInstance::ms_kPool.GetCapacity());
		Tracen("---------------------------------------------");
	}
	*/

	for (TEffectInstanceMap::iterator itor = m_kEftInstMap.begin(); itor != m_kEftInstMap.end();)
	{
		CEffectInstance * pEffectInstance = itor->second;

		pEffectInstance->Update(/*fElapsedTime*/);

		if (!pEffectInstance->isAlive())
		{
			itor = m_kEftInstMap.erase(itor);

			CEffectInstance::Delete(pEffectInstance);
		}
		else
		{
			++itor;
		}
	}
}


struct CEffectManager_LessEffectInstancePtrRenderOrder
{
	bool operator() (CEffectInstance* pkLeft, CEffectInstance* pkRight)
	{
		return pkLeft->LessRenderOrder(pkRight);
	}
};

struct CEffectManager_FEffectInstanceRender
{
	inline void operator () (CEffectInstance * pkEftInst)
	{
		if (CEffectManager::Instance().CanRenderFunction(pkEftInst)) {
			pkEftInst->Render();
		}
	}
};

void CEffectManager::Render()
{
	STATEMANAGER.SetTexture(0, NULL);
	STATEMANAGER.SetTexture(1, NULL);

	if (m_isDisableSortRendering)
	{
		for (TEffectInstanceMap::iterator itor = m_kEftInstMap.begin(); itor != m_kEftInstMap.end();)
		{
			CEffectInstance * pEffectInstance = itor->second;
			pEffectInstance->Render();
			++itor;
		}
	}
	else
	{
		static std::vector<CEffectInstance*> s_kVct_pkEftInstSort;
		s_kVct_pkEftInstSort.clear();

		TEffectInstanceMap& rkMap_pkEftInstSrc=m_kEftInstMap;
		TEffectInstanceMap::iterator i;
		for (i=rkMap_pkEftInstSrc.begin(); i!=rkMap_pkEftInstSrc.end(); ++i)
			s_kVct_pkEftInstSort.push_back(i->second);

		std::sort(s_kVct_pkEftInstSort.begin(), s_kVct_pkEftInstSort.end(), CEffectManager_LessEffectInstancePtrRenderOrder());
		std::for_each(s_kVct_pkEftInstSort.begin(), s_kVct_pkEftInstSort.end(), CEffectManager_FEffectInstanceRender());
	}
}

void CEffectManager::RenderOne(DWORD id)
{
#ifdef INGAME_WIKI
	WikiModuleRenderOneEffect(id);
#else
	STATEMANAGER.SetTexture(0, NULL);
	STATEMANAGER.SetTexture(1, NULL);
	
	const auto& pEffectInstance = m_kEftInstMap.find(id);

	if (pEffectInstance != m_kEftInstMap.end())
	{
		pEffectInstance->second->SetIgnoreFrustum(true);
		pEffectInstance->second->Show();
		pEffectInstance->second->Render();
	}
	else
		TraceError("!RenderOne, not found");
#endif
}

#ifdef INGAME_WIKI
void CEffectManager::WikiModuleRenderOneEffect(DWORD id)
{
	STATEMANAGER.SetTexture(0, NULL);
	STATEMANAGER.SetTexture(1, NULL);
	
	const auto& pEffectInstance = m_kEftInstMap.find(id);
	
	if (pEffectInstance != m_kEftInstMap.end())
	{
		pEffectInstance->second->SetWikiIgnoreFrustum(true);
		pEffectInstance->second->Show();
		pEffectInstance->second->Render();
	}
	else
		TraceError("!RenderOne, not found");
}
#endif

#ifdef ENABLE_SKILL_COLOR_SYSTEM
BOOL CEffectManager::RegisterEffect(const char * c_szFileName,bool isExistDelete,bool isNeedCache, const char * name)
#else
BOOL CEffectManager::RegisterEffect(const char * c_szFileName,bool isExistDelete,bool isNeedCache)
#endif
{
	std::string strFileName;
	StringPath(c_szFileName, strFileName);
#ifdef ENABLE_SKILL_COLOR_SYSTEM
	DWORD dwCRC = GetCaseCRC32(strFileName.c_str(), strFileName.length(), name);
#else
	DWORD dwCRC = GetCaseCRC32(strFileName.c_str(), strFileName.length());
#endif

	TEffectDataMap::iterator itor = m_kEftDataMap.find(dwCRC);
	if (m_kEftDataMap.end() != itor)
	{
		if (isExistDelete)
		{
			CEffectData* pkEftData=itor->second;
			CEffectData::Delete(pkEftData);
			m_kEftDataMap.erase(itor);
		}
		else
		{
			//TraceError("CEffectManager::RegisterEffect - m_kEftDataMap.find [%s] Already Exist", c_szFileName);
			return TRUE;
		}
	}

	CEffectData * pkEftData = CEffectData::New();

	if (!pkEftData->LoadScript(c_szFileName))
	{
		TraceError("CEffectManager::RegisterEffect - LoadScript(%s) Error", c_szFileName);
		CEffectData::Delete(pkEftData);
		return FALSE;
	}

	m_kEftDataMap.insert(TEffectDataMap::value_type(dwCRC, pkEftData));

	if (isNeedCache)
	{
		if (m_kEftCacheMap.find(dwCRC)==m_kEftCacheMap.end())
		{
			CEffectInstance* pkNewEftInst=CEffectInstance::New();
			pkNewEftInst->SetEffectDataPointer(pkEftData);
			m_kEftCacheMap.insert(TEffectInstanceMap::value_type(dwCRC, pkNewEftInst));
		}
	}

	return TRUE;
}
// CEffectData 를 포인터형으로 리턴하게 하고..
// CEffectData에서 CRC를 얻을수 있게 한다
#ifdef ENABLE_SKILL_COLOR_SYSTEM
BOOL CEffectManager::RegisterEffect2(const char * c_szFileName, DWORD* pdwRetCRC, bool isNeedCache, const char * name)
#else
BOOL CEffectManager::RegisterEffect2(const char * c_szFileName, DWORD* pdwRetCRC, bool isNeedCache)
#endif
{
	std::string strFileName;
	StringPath(c_szFileName, strFileName);
#ifdef ENABLE_SKILL_COLOR_SYSTEM
	DWORD dwCRC = GetCaseCRC32(strFileName.c_str(), strFileName.length(), name);
#else
	DWORD dwCRC = GetCaseCRC32(strFileName.c_str(), strFileName.length());
#endif
	*pdwRetCRC=dwCRC;

#ifdef ENABLE_SKILL_COLOR_SYSTEM
	return RegisterEffect(c_szFileName,false,isNeedCache, name);
#else
	return RegisterEffect(c_szFileName,false,isNeedCache);
#endif
}

int CEffectManager::CreateEffect(const char * c_szFileName, const D3DXVECTOR3 & c_rv3Position, const D3DXVECTOR3 & c_rv3Rotation)
{
	DWORD dwID = GetCaseCRC32(c_szFileName, strlen(c_szFileName));
	return CreateEffect(dwID, c_rv3Position, c_rv3Rotation);
}

#ifdef ENABLE_SKILL_COLOR_SYSTEM
int CEffectManager::CreateEffect(DWORD dwID, const D3DXVECTOR3 & c_rv3Position, const D3DXVECTOR3 & c_rv3Rotation, DWORD * dwSkillColor)
#else
int CEffectManager::CreateEffect(DWORD dwID, const D3DXVECTOR3 & c_rv3Position, const D3DXVECTOR3 & c_rv3Rotation)
#endif
{
	int iInstanceIndex = GetEmptyIndex();

#ifdef ENABLE_SKILL_COLOR_SYSTEM
	CreateEffectInstance(iInstanceIndex, dwID, dwSkillColor);
#else
	CreateEffectInstance(iInstanceIndex, dwID);
#endif
	SelectEffectInstance(iInstanceIndex);
	D3DXMATRIX mat;
	D3DXMatrixRotationYawPitchRoll(&mat,D3DXToRadian(c_rv3Rotation.x),D3DXToRadian(c_rv3Rotation.y),D3DXToRadian(c_rv3Rotation.z));
	mat._41 = c_rv3Position.x;
	mat._42 = c_rv3Position.y;
	mat._43 = c_rv3Position.z;
	SetEffectInstanceGlobalMatrix(mat);

	return iInstanceIndex;
}

#ifdef ENABLE_SKILL_COLOR_SYSTEM
void CEffectManager::CreateEffectInstance(DWORD dwInstanceIndex, DWORD dwID, DWORD * dwSkillColor)
#else
void CEffectManager::CreateEffectInstance(DWORD dwInstanceIndex, DWORD dwID)
#endif
{
	if (!dwID)
		return;

	CEffectData * pEffect;
	if (!GetEffectData(dwID, &pEffect))
	{
		Tracef("CEffectManager::CreateEffectInstance - NO DATA :%d\n", dwID);
		return;
	}

	CEffectInstance * pEffectInstance = CEffectInstance::New();
#ifdef ENABLE_SKILL_COLOR_SYSTEM
	pEffectInstance->SetEffectDataPointer(pEffect, dwSkillColor, dwID);
#else
	pEffectInstance->SetEffectDataPointer(pEffect);
#endif

	m_kEftInstMap.insert(TEffectInstanceMap::value_type(dwInstanceIndex, pEffectInstance));
}

bool CEffectManager::DestroyEffectInstance(DWORD dwInstanceIndex)
{
	TEffectInstanceMap::iterator itor = m_kEftInstMap.find(dwInstanceIndex);

	if (itor == m_kEftInstMap.end())
		return false;

	CEffectInstance * pEffectInstance = itor->second;

	m_kEftInstMap.erase(itor);

	CEffectInstance::Delete(pEffectInstance);

	return true;
}

void CEffectManager::DeactiveEffectInstance(DWORD dwInstanceIndex)
{
	TEffectInstanceMap::iterator itor = m_kEftInstMap.find(dwInstanceIndex);

	if (itor == m_kEftInstMap.end())
		return;

	CEffectInstance * pEffectInstance = itor->second;
	pEffectInstance->SetDeactive();
}

void CEffectManager::CreateUnsafeEffectInstance(DWORD dwEffectDataID, CEffectInstance ** ppEffectInstance)
{
	CEffectData * pEffect;
	if (!GetEffectData(dwEffectDataID, &pEffect))
	{
		Tracef("CEffectManager::CreateEffectInstance - NO DATA :%d\n", dwEffectDataID);
		return;
	}

	CEffectInstance* pkEftInstNew=CEffectInstance::New();
	pkEftInstNew->SetEffectDataPointer(pEffect);

	*ppEffectInstance = pkEftInstNew;
}

bool CEffectManager::DestroyUnsafeEffectInstance(CEffectInstance * pEffectInstance)
{
	if (!pEffectInstance)
		return false;

	CEffectInstance::Delete(pEffectInstance);

	return true;
}

BOOL CEffectManager::SelectEffectInstance(DWORD dwInstanceIndex)
{
	TEffectInstanceMap::iterator itor = m_kEftInstMap.find(dwInstanceIndex);

	m_pSelectedEffectInstance = NULL;

	if (m_kEftInstMap.end() == itor)
		return FALSE;

	m_pSelectedEffectInstance = itor->second;

	return TRUE;
}

void CEffectManager::SetEffectTextures(DWORD dwID, std::vector<std::string> textures)
{
	CEffectData * pEffectData;
	if (!GetEffectData(dwID, &pEffectData))
	{
		Tracef("CEffectManager::CreateEffectInstance - NO DATA :%d\n", dwID);
		return;
	}

	for(DWORD i = 0; i < textures.size(); i++)
	{
		CParticleSystemData * pParticle = pEffectData->GetParticlePointer(i);
		pParticle->ChangeTexture(textures.at(i).c_str());
	}
}

void CEffectManager::SetEffectInstancePosition(const D3DXVECTOR3 & c_rv3Position)
{
	if (!m_pSelectedEffectInstance)
	{
//		assert(!"Instance to use is not yet set!");
		return;
	}

	m_pSelectedEffectInstance->SetPosition(c_rv3Position);
}

void CEffectManager::SetEffectInstanceRotation(const D3DXVECTOR3 & c_rv3Rotation)
{
	if (!m_pSelectedEffectInstance)
	{
//		assert(!"Instance to use is not yet set!");
		return;
	}

	m_pSelectedEffectInstance->SetRotation(c_rv3Rotation.x,c_rv3Rotation.y,c_rv3Rotation.z);
}

void CEffectManager::SetEffectInstanceGlobalMatrix(const D3DXMATRIX & c_rmatGlobal)
{
	if (!m_pSelectedEffectInstance)
		return;

	m_pSelectedEffectInstance->SetGlobalMatrix(c_rmatGlobal);
}

void CEffectManager::ShowEffect()
{
	if (!m_pSelectedEffectInstance)
		return;

	m_pSelectedEffectInstance->Show();
}

void CEffectManager::HideEffect()
{
	if (!m_pSelectedEffectInstance)
		return;

	m_pSelectedEffectInstance->Hide();
}

bool CEffectManager::GetEffectData(DWORD dwID, CEffectData ** ppEffect)
{
	TEffectDataMap::iterator itor = m_kEftDataMap.find(dwID);

	if (itor == m_kEftDataMap.end())
		return false;

	*ppEffect = itor->second;

	return true;
}

bool CEffectManager::GetEffectData(DWORD dwID, const CEffectData ** c_ppEffect)
{
	TEffectDataMap::iterator itor = m_kEftDataMap.find(dwID);

	if (itor == m_kEftDataMap.end())
		return false;

	*c_ppEffect = itor->second;

	return true;
}

DWORD CEffectManager::GetRandomEffect()
{
	int iIndex = random() % m_kEftDataMap.size();

	TEffectDataMap::iterator itor = m_kEftDataMap.begin();
	for (int i = 0; i < iIndex; ++i, ++itor);

	return itor->first;
}

int CEffectManager::GetEmptyIndex()
{
	static int iMaxIndex=1;

	if (iMaxIndex>2100000000)
		iMaxIndex = 1;

	int iNextIndex = iMaxIndex++;
	while(m_kEftInstMap.find(iNextIndex) != m_kEftInstMap.end())
		iNextIndex++;

	return iNextIndex;
}

void CEffectManager::DeleteAllInstances()
{
	__DestroyEffectInstanceMap();
}

void CEffectManager::__DestroyEffectInstanceMap()
{
	for (TEffectInstanceMap::iterator i = m_kEftInstMap.begin(); i != m_kEftInstMap.end(); ++i)
	{
		CEffectInstance * pkEftInst = i->second;
		CEffectInstance::Delete(pkEftInst);
	}

	m_kEftInstMap.clear();
}

void CEffectManager::__DestroyEffectCacheMap()
{
	for (TEffectInstanceMap::iterator i = m_kEftCacheMap.begin(); i != m_kEftCacheMap.end(); ++i)
	{
		CEffectInstance * pkEftInst = i->second;
		CEffectInstance::Delete(pkEftInst);
	}

	m_kEftCacheMap.clear();
}

void CEffectManager::__DestroyEffectDataMap()
{
	for (TEffectDataMap::iterator i = m_kEftDataMap.begin(); i != m_kEftDataMap.end(); ++i)
	{
		CEffectData * pData = i->second;
		CEffectData::Delete(pData);
	}

	m_kEftDataMap.clear();
}

void CEffectManager::Destroy()
{
	__DestroyEffectInstanceMap();
	__DestroyEffectCacheMap();
	__DestroyEffectDataMap();

	__Initialize();
}

void CEffectManager::__Initialize()
{
	m_pSelectedEffectInstance = NULL;
	m_isDisableSortRendering = false;
}

CEffectManager::CEffectManager()
{
	__Initialize();
}

CEffectManager::~CEffectManager()
{
	Destroy();
}

// just for map effect

