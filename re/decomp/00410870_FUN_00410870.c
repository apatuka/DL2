// FUN_00410870 @ 00410870 size=228 sig=undefined FUN_00410870() cc=unknown
// callers: FUN_004059bc
// callees: FUN_0040fbb0,FUN_0040cdfc,FUN_00410720,FUN_00416d08,FUN_0047510c,FUN_0040552c,FUN_004067d0

void FUN_00410870(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_0047510c(*(undefined4 *)(param_2 + 0x1c));
  if ((iVar1 == 0) || (param_1 != *(char *)(iVar1 + 8))) {
    *(undefined4 *)(param_2 + 0x10) = 1;
  }
  else {
    iVar2 = FUN_0040fbb0(param_1,(int)*(char *)(iVar1 + 6));
    if (iVar2 != 0) {
      FUN_0040cdfc(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),iVar2,1);
    }
    iVar2 = FUN_00410720(iVar1,*(undefined4 *)(iVar1 + 0x3c));
    if (iVar2 == 0) {
      *(undefined4 *)(param_2 + 0x10) = 1;
    }
    else {
      iVar3 = FUN_00416d08(iVar1);
      if (iVar3 == 0) {
        *(undefined4 *)(param_2 + 0x10) = 1;
      }
      else {
        iVar2 = FUN_0040552c(iVar2,0x12,0);
        if (iVar2 < 100 - *(short *)(iVar1 + 0x28)) {
          iVar1 = FUN_004067d0(param_1,0,0x12,1,1,0);
          if (iVar1 == 0) {
            iVar1 = FUN_004067d0(param_1,0,0x12,1,1,10000);
          }
          if (iVar1 == 0) {
            *(undefined4 *)(param_2 + 0xc) = 1;
          }
        }
        else {
          *(undefined4 *)(param_2 + 0xc) = 1;
        }
      }
    }
  }
  return;
}

