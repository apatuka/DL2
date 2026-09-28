// FUN_0048fee9 @ 0048fee9 size=324 sig=undefined FUN_0048fee9() cc=unknown
// callers: FUN_004a52db
// callees: FUN_0048fe90,FUN_00498b98,GlobalUnlock,FUN_00495162,FUN_004989de,FUN_00498ba9,FUN_004906e3,FUN_004989cf,GlobalLock
// strings: \"WARNING:CYLib handle of unknown type dispose of.\\r\\n\"|\"WARNING:Default CYLib translator ask to load unknow subtype\\r\\n\"

undefined4
FUN_0048fee9(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5,
            int param_6)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  LPVOID local_14;
  HGLOBAL local_10;
  
  uVar4 = 1;
  if (param_5 == 2) {
    if (*(int *)(param_4 + 0x1c) != 0) {
      if (*(int *)(param_4 + 0x24) == 0) {
        FUN_004989de(*(undefined4 *)(param_4 + 0x1c));
      }
      else if (*(int *)(param_4 + 0x24) == 1) {
        FUN_004989cf(*(undefined4 *)(param_4 + 0x1c));
      }
      else if ((DAT_0051dcc5 & 0x20) != 0) {
        FUN_00495162(s_WARNING_CYLib_handle_of_unknown_t_0051db00);
      }
      FUN_0048fe90(param_4);
    }
  }
  else if (param_5 == 3) {
    uVar1 = *(undefined4 *)(param_4 + 0x18);
    uVar2 = *(undefined4 *)(param_4 + 0x14);
    local_14 = (LPVOID)0x0;
    if (param_6 == 0) {
      local_10 = (HGLOBAL)FUN_00498b98(uVar1);
      if (local_10 != (HGLOBAL)0x0) {
        local_14 = GlobalLock(local_10);
      }
    }
    else if (param_6 == 1) {
      local_14 = (LPVOID)FUN_00498ba9(uVar1);
    }
    else if ((DAT_0051dcc5 & 0x20) != 0) {
      FUN_00495162(s_WARNING_Default_CYLib_translator_0051db33);
      return 0;
    }
    if (local_14 != (LPVOID)0x0) {
      iVar3 = FUN_004906e3(param_1,uVar2,uVar1,local_14);
      if (iVar3 == 0) {
        FUN_0048fe90(param_4);
        if (param_6 == 0) {
          GlobalUnlock(local_10);
          *(HGLOBAL *)(param_4 + 0x1c) = local_10;
        }
        else if (param_6 == 1) {
          *(LPVOID *)(param_4 + 0x1c) = local_14;
        }
        *(int *)(param_4 + 0x24) = param_6;
        uVar4 = 1;
      }
      else {
        if (param_6 == 0) {
          GlobalUnlock(local_10);
          FUN_004989de(local_10);
        }
        else if (param_6 == 1) {
          FUN_004989cf(local_14);
        }
        uVar4 = 0;
      }
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

