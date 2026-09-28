// FUN_004a5c60 @ 004a5c60 size=195 sig=undefined FUN_004a5c60() cc=unknown
// callers: FUN_0044b544,FUN_004a5d23
// callees: FUN_004a3d26,FUN_004a58ce,FUN_004a2004

int FUN_004a5c60(int param_1,int param_2,int param_3,int param_4,int param_5,byte param_6)

{
  int iVar1;
  
  iVar1 = 0;
  if (param_1 != 0) {
    FUN_004a58ce(param_1);
    iVar1 = FUN_004a3d26(&DAT_0069efb4,0,0xffffffff);
    if (iVar1 != 0) {
      if ((param_6 & 2) == 0) {
        param_3 = param_3 - *(int *)(iVar1 + 0x10);
      }
      if ((param_6 & 4) != 0) {
        param_2 = param_2 - *(int *)(DAT_0051e528 + 0x14);
      }
      if (param_4 != 0) {
        if (param_2 < 0) {
          param_2 = 0;
        }
        else if (*(int *)(param_4 + 4) < *(int *)(iVar1 + 0x14) + param_2) {
          param_2 = *(int *)(param_4 + 4) - *(int *)(iVar1 + 0x14);
        }
        if (param_3 < 0) {
          param_3 = 0;
        }
        else if (*(int *)(param_4 + 8) < param_3 + *(int *)(iVar1 + 0x10)) {
          param_3 = *(int *)(param_4 + 8) - *(int *)(iVar1 + 0x10);
        }
      }
      *(int *)(iVar1 + 8) = param_2;
      *(int *)(iVar1 + 0xc) = param_3;
      if (param_5 == 0) {
        *(uint *)(iVar1 + 0x1c) = *(uint *)(iVar1 + 0x1c) | 2;
      }
      else {
        *(int *)(iVar1 + 0x60) = param_5;
      }
      *(code **)(iVar1 + 0x5c) = FUN_004a5a0b;
      *(int *)(iVar1 + 0x3c) = param_4;
      FUN_004a2004(iVar1);
    }
  }
  return iVar1;
}

