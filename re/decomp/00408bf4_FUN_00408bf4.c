// FUN_00408bf4 @ 00408bf4 size=582 sig=undefined FUN_00408bf4() cc=unknown
// callers: FUN_00408e3c
// callees: FUN_0046ac44,FUN_004067d0,FUN_004054d8,FUN_00407d60

void FUN_00408bf4(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  undefined1 local_88 [48];
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_10;
  int local_c;
  int local_8;
  
  iVar1 = *(int *)(param_2 + 0x20);
  FUN_0046ac44(local_88,param_1);
  iVar2 = DAT_004b6460;
  local_8 = local_4c + local_20;
  local_c = local_54 + local_28;
  local_10 = local_58 + local_2c;
  if (local_8 * 10 + (local_50 + local_24) * 5 + local_c * 5 + local_10 < iVar1) {
    bVar3 = (byte)param_1;
    if (((1 << (bVar3 & 0x1f) & (int)DAT_004fc156) != 0) && (0 < local_50 + local_24)) {
      iVar1 = FUN_004067d0(param_1,0,DAT_004b6460,1,1,0);
      if (iVar1 == 0) {
        iVar1 = FUN_004067d0(param_1,0,iVar2,1,1,10000);
      }
      if (iVar1 != 0) {
        return;
      }
      iVar1 = FUN_004054d8(iVar2,0);
      if (iVar1 != 0) {
        FUN_00407d60(param_1,DAT_004b648c,*(undefined4 *)(param_2 + 8),
                     *(undefined4 *)(&DAT_004b649c + iVar2 * 4),0xffffffff,iVar2,1);
      }
    }
    iVar1 = DAT_004b645c;
    if ((1 << (bVar3 & 0x1f) & (int)DAT_004fbf94) != 0) {
      iVar2 = FUN_004067d0(param_1,0,DAT_004b645c,1,1,0);
      if (iVar2 == 0) {
        iVar2 = FUN_004067d0(param_1,0,iVar1,1,1,10000);
      }
      if (iVar2 != 0) {
        return;
      }
      iVar2 = FUN_004054d8(iVar1,0);
      if (iVar2 != 0) {
        FUN_00407d60(param_1,DAT_004b6488,*(undefined4 *)(param_2 + 8),
                     *(undefined4 *)(&DAT_004b649c + iVar1 * 4),0xffffffff,iVar1,1);
      }
    }
    iVar1 = DAT_004b6458;
    if (((1 << (bVar3 & 0x1f) & (int)DAT_004fbc10) != 0) && (0 < local_10)) {
      iVar2 = FUN_004067d0(param_1,0,DAT_004b6458,1,1,0);
      if (iVar2 == 0) {
        iVar2 = FUN_004067d0(param_1,0,iVar1,1,1,10000);
      }
      if (iVar2 != 0) {
        return;
      }
      iVar2 = FUN_004054d8(iVar1,0);
      if (iVar2 != 0) {
        FUN_00407d60(param_1,DAT_004b6484,*(undefined4 *)(param_2 + 8),
                     *(undefined4 *)(&DAT_004b649c + iVar1 * 4),0xffffffff,iVar1,1);
      }
    }
    iVar1 = DAT_004b6454;
    iVar2 = FUN_004067d0(param_1,0,DAT_004b6454,1,1,0);
    if (iVar2 == 0) {
      iVar2 = FUN_004067d0(param_1,0,iVar1,1,1,10000);
    }
    if (iVar2 == 0) {
      iVar2 = FUN_004054d8(iVar1,0);
      if (iVar2 == 0) {
        *(undefined4 *)(param_2 + 0xc) = 1;
      }
      else {
        *(undefined4 *)(param_2 + 0xc) = 1;
        FUN_00407d60(param_1,DAT_004b6480,*(undefined4 *)(param_2 + 8),
                     *(undefined4 *)(&DAT_004b649c + iVar1 * 4),0xffffffff,iVar1,1);
      }
    }
  }
  else {
    *(undefined4 *)(param_2 + 0xc) = 1;
  }
  return;
}

