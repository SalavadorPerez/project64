#include "stdafx.h"
#include "SettingsType-Application.h"
#include "SettingsType-GameSetting.h"

bool     CSettingTypeGame::m_RdbEditor = false;
bool     CSettingTypeGame::m_EraseDefaults = true;
stdstr * CSettingTypeGame::m_SectionIdent = NULL;

CSettingTypeGame::CSettingTypeGame(LPCSTR Name, LPCSTR DefaultValue )	:
	CSettingTypeApplication("",Name,DefaultValue)
{
}

CSettingTypeGame::CSettingTypeGame(LPCSTR Name, DWORD DefaultValue ) :
	CSettingTypeApplication("",Name,DefaultValue)
{
}

CSettingTypeGame::CSettingTypeGame(LPCSTR Name, SettingID DefaultSetting ) :
	CSettingTypeApplication("",Name,DefaultSetting)
{
}

CSettingTypeGame::~CSettingTypeGame()
{
}

void CSettingTypeGame::Initilize ( void )
{
	UpdateSettings(NULL);
	_Settings->RegisterChangeCB(Game_IniKey,NULL,UpdateSettings);
}

void CSettingTypeGame::CleanUp   ( void )
{
	_Settings->UnregisterChangeCB(Game_IniKey,NULL,UpdateSettings);
	if (m_SectionIdent)
	{
		delete m_SectionIdent;
		m_SectionIdent = NULL;
	}
}

LPCSTR CSettingTypeGame::SectionName ( void ) const
{
	return m_SectionIdent ? m_SectionIdent->c_str() : "";
}

void CSettingTypeGame::UpdateSettings ( void * /*Data */ )
{
	m_RdbEditor     = _Settings->LoadBool(Setting_RdbEditor);
	m_EraseDefaults = _Settings->LoadBool(Setting_EraseGameDefaults);
	stdstr SectionIdent = _Settings->LoadString(Game_IniKey);

	if (m_SectionIdent == NULL)
	{
		m_SectionIdent = new stdstr;
	}
	if (SectionIdent != *m_SectionIdent)
	{
		*m_SectionIdent = SectionIdent;
		_Settings->SettingTypeChanged(SettingType_GameSetting);
		_Settings->SettingTypeChanged(SettingType_RomDatabase);
	}

}

bool CSettingTypeGame::Load ( int Index, bool & Value ) const
{
	if (m_RdbEditor && _Settings->GetSettingType(m_DefaultSetting) == SettingType_RomDatabase)
	{
		if (_Settings->IndexBasedSetting(m_DefaultSetting))
		{
			return _Settings->LoadBoolIndex(m_DefaultSetting,Index,Value);
		} else {
			return _Settings->LoadBool(m_DefaultSetting,Value);
		}
	}
	return CSettingTypeApplication::Load(Index,Value);
}

bool CSettingTypeGame::Load ( int Index, ULONG & Value ) const
{
	if (m_RdbEditor && _Settings->GetSettingType(m_DefaultSetting) == SettingType_RomDatabase)
	{
		if (_Settings->IndexBasedSetting(m_DefaultSetting))
		{
			return _Settings->LoadDwordIndex(m_DefaultSetting,Index,Value);
		} else {
			return _Settings->LoadDword(m_DefaultSetting,Value);
		}
	}
	return CSettingTypeApplication::Load(Index,Value);
}

bool CSettingTypeGame::Load ( int Index,  stdstr & Value ) const
{
	if (m_RdbEditor && _Settings->GetSettingType(m_DefaultSetting) == SettingType_RomDatabase)
	{
		if (_Settings->IndexBasedSetting(m_DefaultSetting))
		{
			return _Settings->LoadStringIndex(m_DefaultSetting,Index,Value);
		} else {
			return _Settings->LoadString(m_DefaultSetting,Value);
		}
	}	
	return CSettingTypeApplication::Load(Index,Value);
}

//return the default values
void CSettingTypeGame::LoadDefault ( int Index, bool & Value   ) const
{
	if (m_RdbEditor && _Settings->GetSettingType(m_DefaultSetting) == SettingType_RomDatabase)
	{
		if (_Settings->IndexBasedSetting(m_DefaultSetting))
		{
			_Settings->LoadDefaultBoolIndex(m_DefaultSetting,Index,Value);
		} else {
			_Settings->LoadDefaultBool(m_DefaultSetting,Value);
		}
	} else {
		CSettingTypeApplication::LoadDefault(Index,Value);
	}
}

void CSettingTypeGame::LoadDefault ( int Index, ULONG & Value  ) const
{
	if (m_RdbEditor && _Settings->GetSettingType(m_DefaultSetting) == SettingType_RomDatabase)
	{
		if (_Settings->IndexBasedSetting(m_DefaultSetting))
		{
			_Settings->LoadDefaultDwordIndex(m_DefaultSetting,Index,Value);
		} else {
			_Settings->LoadDefaultDword(m_DefaultSetting,Value);
		}
	} else {
		CSettingTypeApplication::LoadDefault(Index,Value);
	}
}

void CSettingTypeGame::LoadDefault ( int Index, stdstr & Value ) const
{
	if (m_RdbEditor && _Settings->GetSettingType(m_DefaultSetting) == SettingType_RomDatabase)
	{
		if (_Settings->IndexBasedSetting(m_DefaultSetting))
		{
			_Settings->LoadDefaultStringIndex(m_DefaultSetting,Index,Value);
		} else {
			_Settings->LoadDefaultString(m_DefaultSetting,Value);
		}
	} else {
		CSettingTypeApplication::LoadDefault(Index,Value);
	}
}

//Update the settings
void CSettingTypeGame::Save ( int Index, bool Value )
{
	if (m_EraseDefaults)
	{
		bool bDefault;
		LoadDefault(Index,bDefault);
		if (bDefault == Value)
		{
			Delete(Index);
			return;
		}
	}
	if (m_RdbEditor && _Settings->GetSettingType(m_DefaultSetting) == SettingType_RomDatabase)
	{
		if (_Settings->IndexBasedSetting(m_DefaultSetting))
		{
			_Settings->SaveBoolIndex(m_DefaultSetting,Index,Value);
		} else {
			 _Settings->SaveBool(m_DefaultSetting,Value);
		}
	} else {
		CSettingTypeApplication::Save(Index,Value);
	}
}

void CSettingTypeGame::Save ( int Index, ULONG Value )
{
	if (m_EraseDefaults)
	{
		ULONG ulDefault;
		CSettingTypeGame::LoadDefault(Index,ulDefault);
		if (ulDefault == Value)
		{
			Delete(Index);
			return;
		}
	}
	if (m_RdbEditor && _Settings->GetSettingType(m_DefaultSetting) == SettingType_RomDatabase)
	{
		if (_Settings->IndexBasedSetting(m_DefaultSetting))
		{
			_Settings->SaveDwordIndex(m_DefaultSetting,Index,Value);
		} else {
			 _Settings->SaveDword(m_DefaultSetting,Value);
		}
	} else {
		CSettingTypeApplication::Save(Index,Value);
	}
}

void CSettingTypeGame::Save ( int Index, const stdstr & Value )
{
	Save(Index,Value.c_str()); 
}

void CSettingTypeGame::Save ( int Index, const char * Value )
{
	if (m_EraseDefaults)
	{
		stdstr szDefault;
		CSettingTypeGame::LoadDefault(Index,szDefault);
		if (_stricmp(szDefault.c_str(),Value) == 0)
		{
			Delete(Index);
			return;
		}
	}
	if (m_RdbEditor && _Settings->GetSettingType(m_DefaultSetting) == SettingType_RomDatabase)
	{
		if (_Settings->IndexBasedSetting(m_DefaultSetting))
		{
			_Settings->SaveStringIndex(m_DefaultSetting,Index,Value);
		} else {
			 _Settings->SaveString(m_DefaultSetting,Value);
		}
	} else {
		CSettingTypeApplication::Save(Index,Value);
	}
}

void CSettingTypeGame::Delete ( int Index )
{
	if (m_RdbEditor && _Settings->GetSettingType(m_DefaultSetting) == SettingType_RomDatabase)
	{
		if (_Settings->IndexBasedSetting(m_DefaultSetting))
		{
			_Settings->DeleteSettingIndex(m_DefaultSetting,Index);
		} else {
			_Settings->DeleteSetting(m_DefaultSetting);
		}
	} else {
		CSettingTypeApplication::Delete(Index);
	}
}
