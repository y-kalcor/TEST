// Basic Task Control Class

#pragma once

class CPlayerPed;

class CTask
{
protected:
	BOOL m_bSelfCreated;

public:
	CPlayerPed *m_pPlayerPed;
	BYTE *m_pTaskType;

	CTask();
	CTask(DWORD dwSize);
	CTask(BYTE *pTaskType);
	virtual ~CTask();

	void Create(DWORD dwSize);
	void Create(BYTE *pTaskType);
	virtual CTask* CreateCopy();	
	virtual void Destroy();

	virtual void ApplyToPed(CPlayerPed *pPed);
	virtual void ApplyToPed(CActorPed *pPed);

	virtual DWORD GetID();

	virtual BOOL IsDestroyed();
	virtual BOOL IsSimple();

};

class CTaskJetpack :
	public CTask
{
public:
	CTaskJetpack();
	CTaskJetpack(BYTE *pTaskType);
	~CTaskJetpack();
};

class CTaskTakeDamageFall :
	public CTask
{
public:
	CTaskTakeDamageFall(DWORD dwFallType, DWORD dwNum);
};

class CTaskGoggles :
	public CTask
{
public:
	CTaskGoggles();
};

class CTaskGoToPoint :
	public CTask
{
public:
	CTaskGoToPoint(int unk, VECTOR* vecPos, float unk2, int unk3, int unk4 );
};

class CTaskKillPedOnFootArmed :
	public CTask
{
public:
	CTaskKillPedOnFootArmed( int unk, int unk2, int unk3, int unk4, PED_TYPE* pToShoot );
};