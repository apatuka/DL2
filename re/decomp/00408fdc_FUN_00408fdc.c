// FUN_00408fdc @ 00408fdc size=322 sig=undefined FUN_00408fdc() cc=unknown
// callers: FUN_00409120
// callees: FUN_0046ac44,FUN_004067d0

void FUN_00408fdc(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  undefined1 local_80 [48];
  int local_50;
  int local_48;
  int local_24;
  int local_1c;
  undefined4 local_8;
  
  FUN_0046ac44(local_80,param_1);
  uVar3 = 1 << ((byte)param_1 & 0x1f);
  if (((uVar3 & (int)DAT_004fc156) != 0) && (0 < local_48 + local_1c)) {
    local_8 = DAT_004b6460;
    iVar2 = FUN_004067d0(param_1,0,DAT_004b6460,1,1,0);
    if (iVar2 == 0) {
      iVar2 = FUN_004067d0(param_1,0,local_8,1,1,10000);
    }
    if (iVar2 != 0) {
      return;
    }
  }
  uVar1 = DAT_004b645c;
  if ((uVar3 & (int)DAT_004fbf94) != 0) {
    iVar2 = FUN_004067d0(param_1,0,DAT_004b645c,1,1,0);
    if (iVar2 == 0) {
      iVar2 = FUN_004067d0(param_1,0,uVar1,1,1,10000);
    }
    if (iVar2 != 0) {
      return;
    }
  }
  uVar1 = DAT_004b6458;
  if (((1 << ((byte)param_1 & 0x1f) & (int)DAT_004fbc10) != 0) && (0 < local_50 + local_24)) {
    iVar2 = FUN_004067d0(param_1,0,DAT_004b6458,1,1,0);
    if (iVar2 == 0) {
      iVar2 = FUN_004067d0(param_1,0,uVar1,1,1,10000);
    }
    if (iVar2 != 0) {
      return;
    }
  }
  uVar1 = DAT_004b6454;
  iVar2 = FUN_004067d0(param_1,0,DAT_004b6454,1,1,0);
  if (iVar2 == 0) {
    iVar2 = FUN_004067d0(param_1,0,uVar1,1,1,10000);
  }
  if (iVar2 == 0) {
    *(undefined4 *)(param_2 + 0xc) = 1;
  }
  return;
}

