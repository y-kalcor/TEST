#include <stdio.h>
#include <windows.h>
#include "common.h"
#include "aimstuff.h"
#include "address.h"

CAMERA_AIM * pcaInternalAim = (CAMERA_AIM *)0xB6F32C;
CAMERA_AIM caLocalPlayerAim;
CAMERA_AIM caRemotePlayerAim[PLAYER_PED_SLOTS];
extern BYTE * pbyteCameraMode;

float * pfAspectRatio = (float*)0xC3EFA4;
float * pfCameraExtZoom = (float *)0xB6F250;
float fCameraExtZoom[PLAYER_PED_SLOTS];		// stored as a normalized multiplier float
float fLocalCameraExtZoom;

BYTE byteCameraMode[PLAYER_PED_SLOTS];

//----------------------------------------------------------

void __stdcall GameStoreLocalPlayerCameraExtZoom()
{
	fLocalCameraExtZoom = *pfCameraExtZoom;
}

//----------------------------------------------------------

void __stdcall GameSetLocalPlayerCameraExtZoom()
{
	*pfCameraExtZoom = fLocalCameraExtZoom;
}

//----------------------------------------------------------

void __stdcall GameSetPlayerCameraExtZoom(BYTE bytePlayerID, float fZoom)
{
	fCameraExtZoom[bytePlayerID] = fZoom;
}

//----------------------------------------------------------

float __stdcall GameGetPlayerCameraExtZoom(BYTE bytePlayerID)
{
	return fCameraExtZoom[bytePlayerID];
}

//----------------------------------------------------------

float __stdcall GameGetLocalPlayerCameraExtZoom()
{
	float value = ((*pfCameraExtZoom) - 35.0f) / 35.0f;	// normalize for 35.0 to 70.0
	return value;
}

//----------------------------------------------------------

void __stdcall GameSetRemotePlayerCameraExtZoom(BYTE bytePlayerID)
{
	float fZoom = fCameraExtZoom[bytePlayerID];
	float fValue = fZoom * 35.0f + 35.0f; // unnormalize for 35.0 to 70.0
	*pfCameraExtZoom = fValue;
}

//----------------------------------------------------------

void __stdcall GameSetPlayerCameraMode(BYTE byteMode, BYTE bytePlayerID)
{
	byteCameraMode[bytePlayerID] = byteMode;
}

//----------------------------------------------------------

BYTE __stdcall GameGetPlayerCameraMode(BYTE bytePlayerID)
{
	return byteCameraMode[bytePlayerID];
}

//----------------------------------------------------------

BYTE __stdcall GameGetLocalPlayerCameraMode()
{
	return *pbyteCameraMode;
}

//----------------------------------------------------------

void __stdcall GameAimSyncInit()
{
	memset(&caLocalPlayerAim,0,sizeof(CAMERA_AIM));
	memset(caRemotePlayerAim,0,sizeof(CAMERA_AIM) * PLAYER_PED_SLOTS);
	memset(byteCameraMode,4,PLAYER_PED_SLOTS);
	for(int i=0; i<PLAYER_PED_SLOTS; i++)
		fCameraExtZoom[i] = 1.0f;
}

//----------------------------------------------------------

void __stdcall GameStoreLocalPlayerAim()
{
	memcpy(&caLocalPlayerAim,pcaInternalAim,sizeof(CAMERA_AIM));
}

//----------------------------------------------------------

void __stdcall GameSetLocalPlayerAim()
{
	memcpy(pcaInternalAim,&caLocalPlayerAim,sizeof(CAMERA_AIM));
	//memcpy(pInternalCamera,&SavedCam,sizeof(MATRIX4X4));
}

//----------------------------------------------------------

CAMERA_AIM * __stdcall GameGetInternalAim()
{
	return pcaInternalAim;
}

//----------------------------------------------------------

void __stdcall GameStoreRemotePlayerAim(int iPlayer, CAMERA_AIM * caAim)
{
	memcpy(&caRemotePlayerAim[iPlayer],caAim,sizeof(CAMERA_AIM));
}

//----------------------------------------------------------

void __stdcall GameSetRemotePlayerAim(int iPlayer)
{
	memcpy(pcaInternalAim,&caRemotePlayerAim[iPlayer],sizeof(CAMERA_AIM));
}

//----------------------------------------------------------

CAMERA_AIM * __stdcall GameGetRemotePlayerAim(int iPlayer)
{
    return &caRemotePlayerAim[iPlayer];
}

//----------------------------------------------------------

