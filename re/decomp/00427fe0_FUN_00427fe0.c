// FUN_00427fe0 @ 00427fe0 size=529 sig=undefined FUN_00427fe0() cc=unknown
// callers: FUN_004281f4,FUN_00427e80
// callees: FUN_004a19b4,FUN_004493dc,FUN_00414f04,FUN_004a2004,FUN_004a3de6,FUN_0049eb44,FUN_004a60b1

undefined4
FUN_00427fe0(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,int param_6)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  *param_1 = param_5;
  if (param_2 == 0x37333044) {
    uVar2 = FUN_004a3de6(0,0x37333044);
    param_1[1] = uVar2;
  }
  else {
    uVar2 = FUN_004a3de6(0,0x33303044);
    param_1[1] = uVar2;
  }
  if (param_1[1] == 0) {
    uVar2 = 0;
  }
  else {
    FUN_004493dc(1);
    param_1[2] = DAT_004d59b4;
    DAT_004d59b4 = 0x24;
    if (DAT_004d5978 != 0) {
      iVar1 = param_1[1];
      uVar3 = *(int *)(DAT_004d5c28 + 4) - *(int *)(iVar1 + 0x14);
      iVar4 = (int)uVar3 >> 1;
      if (iVar4 < 0) {
        iVar4 = iVar4 + (uint)((uVar3 & 1) != 0);
      }
      *(int *)(iVar1 + 8) = iVar4;
      if (iVar4 < 0) {
        *(undefined4 *)(iVar1 + 8) = 0;
      }
      iVar1 = param_1[1];
      uVar3 = *(int *)(DAT_004d5c28 + 8) - *(int *)(iVar1 + 0x10);
      iVar4 = (int)uVar3 >> 1;
      if (iVar4 < 0) {
        iVar4 = iVar4 + (uint)((uVar3 & 1) != 0);
      }
      *(int *)(iVar1 + 0xc) = iVar4;
      if (iVar4 < 0) {
        *(undefined4 *)(iVar1 + 0xc) = 0;
      }
    }
    FUN_00414f04(param_1[1]);
    local_14 = 0;
    local_10 = 0;
    local_c = 0x280;
    local_8 = 0x1e0;
    FUN_004a60b1(&local_14,0);
    FUN_004a2004(param_1[1]);
    FUN_0049eb44(param_1[1],0x3e9,1,0xf,0,param_3);
    FUN_0049eb44(param_1[1],0x3ea,1,0xf,0,param_4);
    FUN_004a19b4(param_1[1],2,1,0xd,param_6 + 9000);
    if (DAT_004d5a5c == 0) {
      FUN_0049eb44(param_1[1],5,1,10,1,0);
    }
    if (((param_2 == 0x28a2) || (param_2 == 1)) || (param_2 == 0)) {
      local_20 = 1000;
      local_18 = 0xffffffff;
      local_24 = 1000;
      local_1c = 0xffffffff;
      FUN_0049eb44(param_1[1],3,1,0x40,0,0x31305542);
      FUN_0049eb44(param_1[1],3,1,0x42,0,0x40d);
      if ((param_2 == 1) || (param_2 == 0)) {
        FUN_0049eb44(param_1[1],3,1,0xd,0,&local_24);
      }
      else {
        FUN_0049eb44(param_1[1],4,1,0xd,0,&local_24);
      }
      if (param_2 == 0) {
        FUN_0049eb44(param_1[1],4,1,10,1,0);
      }
    }
    param_1[3] = DAT_004b7d94;
    DAT_004b7d94 = param_1;
    uVar2 = 1;
  }
  return uVar2;
}

