#include "StdAfx.h"

#include "WtObjectDb.h"

CWtObjectDb::CWtObjectDb()
{
}

CWtObjectDb::~CWtObjectDb()
{
}

CWtObjectDb& CWtObjectDb::Instance()
{
	static CWtObjectDb _wtoDb;
	
	return _wtoDb;
}

WtoHandle CWtObjectDb::AddObject(CWtObject* obj)
{
	if (!obj)
	{
		return WTOBJECT_HND_NULL;
	}
	
	WtoHandle hnd = GetNextObjHandle();
	if ( !m_wtObjs.insert(std::make_pair(hnd, obj)).second)
	{
		return WTOBJECT_HND_NULL;
	}
	return hnd;
}

void CWtObjectDb::RemoveObject(WtoHandle hnd)
{
	WtObjectsMap::iterator wit = m_wtObjs.find(hnd);
	if (wit != m_wtObjs.end())
	{
		/*We do not delete the object. That is the job of caller*/
		m_wtObjs.erase(wit);
	}
}

CWtObject* CWtObjectDb::GetObject(WtoHandle hnd)
{
	WtObjectsMap::iterator wit = m_wtObjs.find(hnd);
	if (wit != m_wtObjs.end())
	{
		return wit->second ;
	}

	return NULL;
}


///////// Private helpers

WtoHandle CWtObjectDb::GetNextObjHandle()
{
	static WtoHandle _objHnd = 100;
	++_objHnd;
	
	if (_objHnd == 0)
		_objHnd = 101;
	
	do 
	{
		if (m_wtObjs.find(_objHnd) == m_wtObjs.end())
		{
			//Hnd not in Db. Can be used.
			break;
		}
		else
		{
			++_objHnd;
		}
	} while (1);

	return _objHnd;
}

