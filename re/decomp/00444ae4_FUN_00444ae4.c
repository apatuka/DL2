// FUN_00444ae4 @ 00444ae4 size=142 sig=undefined FUN_00444ae4() cc=unknown
// callers: FUN_00444fd4
// callees: memset,DebugMessage,FUN_00444abc
// strings: \"Freeing an invalid ANIM.\"

void FUN_00444ae4(int param_1)

{
  int iVar1;
  
  if ((param_1 != 0) && (iVar1 = FUN_00444abc(param_1), iVar1 != 0)) {
    if (*(int *)(param_1 + 0x3c) != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x3c) + 0x38) = *(undefined4 *)(param_1 + 0x38);
    }
    if (*(int *)(param_1 + 0x38) != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x38) + 0x3c) = *(undefined4 *)(param_1 + 0x3c);
    }
    if (param_1 == DAT_00563fb4) {
      DAT_00563fb4 = *(int *)(param_1 + 0x3c);
    }
    if (param_1 == DAT_00561a30) {
      DAT_00561a30 = *(int *)(param_1 + 0x38);
    }
    memset(param_1,0,0x40);
    *(int *)(param_1 + 0x38) = DAT_00563fb8;
    *(undefined4 *)(param_1 + 0x3c) = 0;
    *(int *)(DAT_00563fb8 + 0x3c) = param_1;
    DAT_00563fb8 = param_1;
    return;
  }
  DebugMessage(s_Freeing_an_invalid_ANIM__004c50ac);
  return;
}

