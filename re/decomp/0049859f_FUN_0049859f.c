// FUN_0049859f @ 0049859f size=647 sig=undefined FUN_0049859f() cc=unknown
// callers: FUN_00498826
// callees: FUN_0048f877,GlobalLock,GlobalUnlock,FUN_00488c95,FUN_0048f869,FUN_00488c1c

undefined4 FUN_0049859f(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  LPVOID pvVar3;
  int iVar4;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined1 uVar5;
  byte *pbVar6;
  undefined1 local_350 [768];
  undefined4 local_50;
  undefined4 local_4c;
  undefined2 local_48;
  undefined2 local_46;
  undefined1 local_44;
  undefined1 local_43;
  byte local_42;
  char local_41;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined2 local_2c;
  undefined2 local_2a;
  undefined2 local_28;
  undefined2 local_26;
  char local_24;
  undefined1 local_23;
  undefined1 local_22;
  undefined1 local_21;
  undefined2 local_20;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined2 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_40 = 0x4d524f46;
  local_10 = 0x338;
  if (DAT_0051e170 != 0) {
    local_10 = DAT_0051e170 * 0x10 + 0x338;
  }
  local_3c = FUN_0048f877(local_10 + param_2 + -8);
  local_34 = 0x44484d42;
  local_30 = FUN_0048f877(0x14);
  local_2c = FUN_0048f869(CONCAT22(extraout_var_01,*(undefined2 *)(param_3 + 4)));
  local_1c = local_2c;
  local_2a = FUN_0048f869(CONCAT22(extraout_var,*(undefined2 *)(param_3 + 8)));
  local_28 = 0;
  local_26 = 0;
  local_24 = '\b';
  if (param_4 < 0) {
    local_24 = '\t';
  }
  if (local_24 == '\b') {
    local_24 = '\x01';
    local_38 = 0x204d4250;
  }
  else {
    local_38 = 0x4d424c49;
  }
  DAT_0065ee14 = local_38;
  local_23 = 0;
  local_22 = 1;
  local_21 = 0;
  if (param_4 < 1) {
    uVar2 = 0;
  }
  else {
    uVar2 = CONCAT22(extraout_var_00,(undefined2)param_4);
  }
  local_1c = local_2a;
  local_20 = FUN_0048f869(uVar2);
  local_1e = 10;
  local_1d = 0xb;
  local_18 = 0x50414d43;
  local_14 = FUN_0048f877(0x300);
  iVar1 = FUN_00488c95(param_1,0,0);
  if (iVar1 < 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = FUN_00488c1c(param_1,&local_40,0x30);
    if (iVar1 == 0x30) {
      iVar1 = 0;
      do {
        uVar5 = (undefined1)iVar1;
        local_350[iVar1 * 3] = uVar5;
        local_350[iVar1 * 3 + 1] = uVar5;
        local_350[iVar1 * 3 + 2] = uVar5;
        iVar1 = iVar1 + 1;
      } while (iVar1 < 0x100);
      if (*(int *)(param_3 + 0x3c) != 0) {
        pvVar3 = GlobalLock(*(HGLOBAL *)(param_3 + 0x3c));
        for (iVar1 = 0; iVar1 < *(short *)((int)pvVar3 + 2); iVar1 = iVar1 + 1) {
          local_350[iVar1 * 3] = *(undefined1 *)((int)pvVar3 + iVar1 * 4 + 8);
          local_350[iVar1 * 3 + 1] = *(undefined1 *)((int)pvVar3 + iVar1 * 4 + 9);
          local_350[iVar1 * 3 + 2] = *(undefined1 *)((int)pvVar3 + iVar1 * 4 + 10);
        }
        GlobalUnlock(*(HGLOBAL *)(param_3 + 0x3c));
      }
      iVar1 = FUN_00488c1c(param_1,local_350,0x300);
      pbVar6 = DAT_0065ee10;
      if (iVar1 == 0x300) {
        if (DAT_0051e170 != 0) {
          local_50 = 0x474e5243;
          local_4c = FUN_0048f877(8);
          for (iVar1 = 0; iVar1 < DAT_0051e170; iVar1 = iVar1 + 1) {
            local_44 = 0;
            local_48 = 0;
            local_46 = FUN_0048f869((((int)(uint)pbVar6[1] >> 1) + 0x48cdU) / (uint)pbVar6[1]);
            local_42 = pbVar6[2];
            local_41 = local_42 + pbVar6[3] + -1;
            local_43 = 0;
            if ((*pbVar6 & 1) != 0) {
              local_43 = 2;
            }
            iVar4 = FUN_00488c1c(param_1,&local_50,0x10);
            if (iVar4 != 0x10) {
              return 0;
            }
            pbVar6 = pbVar6 + 4;
          }
        }
        local_c = 0x59444f42;
        local_8 = FUN_0048f877(param_2);
        iVar1 = FUN_00488c1c(param_1,&local_c,8);
        if (iVar1 == 8) {
          uVar2 = 1;
        }
        else {
          uVar2 = 0;
        }
      }
      else {
        uVar2 = 0;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

