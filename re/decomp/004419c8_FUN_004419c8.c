// FUN_004419c8 @ 004419c8 size=123 sig=undefined FUN_004419c8() cc=unknown
// callers: FUN_0042f224,LoadPhaseSpriteFile,FUN_0046a844,FUN_00450b4c,CalculateGameCRC,FUN_0046ce10,FUN_00477f9c,FUN_004835bc,FUN_00483538,FUN_00441a44,FUN_004226a0,FUN_00421fc4,LoadGlobalSprites,FUN_0042e8c0,FUN_00482650,StillPic,NetStartState,FUN_00413428,FUN_0047c53c,NetPlayerDisconnect,LoadPhaseSprites,FUN_0046a700,SendTerritoryData,FUN_00432824
// callees: DebugMessage,GlobalFree,memset
// strings: \"Number of allocations and de-allocations doesn't match!\"

undefined4 FUN_004419c8(HGLOBAL param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = &DAT_0055a192;
  for (iVar2 = 0; (param_1 != (HGLOBAL)0x0 && (iVar2 < 0x40)); iVar2 = iVar2 + 1) {
    if (param_1 == (HGLOBAL)*puVar1) {
      if (*(short *)((int)puVar1 + -0x12) != 0) {
        GlobalFree((HGLOBAL)*puVar1);
        memset(&DAT_0055a180 + iVar2 * 0xd,0,0x1a);
        DAT_0055a800 = DAT_0055a800 + -1;
        *(undefined2 *)((int)puVar1 + -0x12) = 0;
        if (DAT_0055a800 < 0) {
          DebugMessage(s_Number_of_allocations_and_de_all_004c4ae2);
        }
      }
      return 1;
    }
    puVar1 = (undefined4 *)((int)puVar1 + 0x1a);
  }
  return 0;
}

