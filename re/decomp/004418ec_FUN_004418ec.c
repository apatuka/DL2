// FUN_004418ec @ 004418ec size=220 sig=undefined FUN_004418ec() cc=unknown
// callers: FUN_0042f224,LoadPhaseSpriteFile,FUN_0046a844,CalculateGameCRC,FUN_0045093c,FUN_00421fc4,LoadGlobalSprites,NetReceiveCapsule,StillPic,NetStartState,GetHighScores,FUN_00413428,NetPlayerDisconnect,LoadPhaseSprites,SendTerritoryData,FUN_00432824,FUN_004824c4
// callees: DebugMessage,FUN_004418e4,FUN_004a6b48,GlobalAlloc,GetLastError,sprintf,memset
// strings: \"Memory Allocation of %s buffer of %ld bytes failed! Error code %#08x\"|\"On AllocMem error:\\r\\n\"|\"Too many Allocations to record!\"

HGLOBAL FUN_004418ec(undefined4 param_1,SIZE_T param_2)

{
  HGLOBAL pvVar1;
  DWORD DVar2;
  int *piVar3;
  undefined1 local_88 [128];
  int local_8;
  
  piVar3 = &DAT_0055a192;
  local_8 = 0;
  do {
    if (*piVar3 == 0) {
      pvVar1 = GlobalAlloc(0,param_2);
      if (pvVar1 != (HGLOBAL)0x0) {
        FUN_004a6b48(&DAT_0055a182 + local_8 * 0x1a,param_1,0xf);
        *piVar3 = (int)pvVar1;
        piVar3[1] = param_2;
        *(undefined2 *)((int)piVar3 + -0x12) = 1;
        memset(pvVar1,0,param_2);
        DAT_0055a800 = DAT_0055a800 + 1;
        return pvVar1;
      }
      DVar2 = GetLastError();
      sprintf(local_88,s_Memory_Allocation_of__s_buffer_o_004c4a68,param_1,param_2,DVar2);
      DebugMessage(local_88);
      FUN_004418e4(s_On_AllocMem_error__004c4aad);
      return (HGLOBAL)0x0;
    }
    local_8 = local_8 + 1;
    piVar3 = (int *)((int)piVar3 + 0x1a);
  } while (local_8 < 0x40);
  DebugMessage(s_Too_many_Allocations_to_record__004c4ac2);
  pvVar1 = GlobalAlloc(0,param_2);
  return pvVar1;
}

