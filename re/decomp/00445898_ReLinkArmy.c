// ReLinkArmy @ 00445898 size=168 sig=undefined ReLinkArmy() cc=unknown
// callers: FUN_004471c0,FUN_00446084,FUN_004474b0,FUN_004526b0,FUN_00485668,FUN_00445aac,FUN_0046e6b8
// callees: FUN_004455fc,DebugMessage
// strings: \"Re-linking invalid army in ReLinkArmy\"

/* auto-named from string evidence: ReLinkArmy */

undefined4 ReLinkArmy(int param_1,undefined4 param_2,int *param_3,int *param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_4 == param_3) {
    uVar2 = 1;
  }
  else {
    FUN_004455fc(6);
    for (iVar1 = *param_3; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x54)) {
      if (param_1 == iVar1) {
        if (*(int *)(param_1 + 0x58) != 0) {
          *(undefined4 *)(*(int *)(param_1 + 0x58) + 0x54) = *(undefined4 *)(param_1 + 0x54);
        }
        if (*(int *)(param_1 + 0x54) != 0) {
          *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x58) = *(undefined4 *)(param_1 + 0x58);
        }
        if (param_1 == *param_3) {
          *param_3 = *(int *)(param_1 + 0x54);
        }
        if (*param_4 != 0) {
          *(int *)(*param_4 + 0x58) = param_1;
        }
        *(int *)(param_1 + 0x54) = *param_4;
        *(undefined4 *)(param_1 + 0x58) = 0;
        *param_4 = param_1;
        *(undefined4 *)(param_1 + 0x3c) = param_2;
        FUN_004455fc(7);
        return 1;
      }
    }
    if (DAT_0058f1fc == 0) {
      uVar2 = 0;
    }
    else {
      DebugMessage(s_Re_linking_invalid_army_in_ReLin_004c5319);
      uVar2 = 0;
    }
  }
  return uVar2;
}

