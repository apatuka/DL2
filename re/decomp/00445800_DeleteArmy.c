// DeleteArmy @ 00445800 size=152 sig=undefined DeleteArmy() cc=unknown
// callers: DeleteUnit
// callees: memset,FUN_004455fc,DebugMessage
// strings: \"Freeing invalid army in DeleteArmy\"

/* auto-named from string evidence: DeleteArmy */

void DeleteArmy(int param_1,int *param_2)

{
  int iVar1;
  
  FUN_004455fc(4);
  iVar1 = *param_2;
  while( true ) {
    if (iVar1 == 0) {
      if (DAT_0058f1fc != 0) {
        DebugMessage(s_Freeing_invalid_army_in_DeleteAr_004c52f6);
      }
      return;
    }
    if (param_1 == iVar1) break;
    iVar1 = *(int *)(iVar1 + 0x54);
  }
  if (*(int *)(param_1 + 0x58) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0x58) + 0x54) = *(undefined4 *)(param_1 + 0x54);
  }
  if (*(int *)(param_1 + 0x54) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x58) = *(undefined4 *)(param_1 + 0x58);
  }
  if (param_1 == *param_2) {
    *param_2 = *(int *)(param_1 + 0x54);
  }
  memset(param_1,0,0x5c);
  *(int *)(param_1 + 0x54) = DAT_004c515c;
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(int *)(DAT_004c515c + 0x58) = param_1;
  DAT_004c515c = param_1;
  FUN_004455fc(5);
  return;
}

