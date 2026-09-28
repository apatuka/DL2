// FUN_0047d3d8 @ 0047d3d8 size=134 sig=undefined FUN_0047d3d8() cc=unknown
// callers: FUN_00431f6c,FUN_00435f5c,FUN_00431e58,FUN_00436000
// callees: DebugMessage
// strings: \"Not enough room to Log skirineen event.\"

void FUN_0047d3d8(int param_1,int param_2,int param_3,short param_4)

{
  short *psVar1;
  int iVar2;
  
  iVar2 = 0;
  psVar1 = (short *)(&DAT_00654ac2 + param_1 * 200);
  while ((param_2 != *psVar1 || (param_3 != psVar1[1]))) {
    iVar2 = iVar2 + 1;
    psVar1 = psVar1 + 4;
    if (0x18 < iVar2) {
      iVar2 = 0;
      psVar1 = &DAT_00654ac0 + param_1 * 100;
      do {
        if (*psVar1 == -1) {
          *psVar1 = (short)param_1;
          psVar1[1] = (short)param_2;
          psVar1[2] = (short)param_3;
          psVar1[3] = param_4;
          return;
        }
        iVar2 = iVar2 + 1;
        psVar1 = psVar1 + 4;
      } while (iVar2 < 0x19);
      DebugMessage(s_Not_enough_room_to_Log_skirineen_004dcb36);
      return;
    }
  }
  psVar1[2] = psVar1[2] + param_4;
  return;
}

