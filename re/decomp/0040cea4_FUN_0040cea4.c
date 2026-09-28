// FUN_0040cea4 @ 0040cea4 size=337 sig=undefined FUN_0040cea4() cc=unknown
// callers: FUN_004059bc
// callees: FUN_004764dc,FUN_0040a1c0,FUN_0040cda0,FUN_0040cdfc,FUN_004054d8,FUN_0040a37c,FUN_004067d0,FUN_0040a338,FUN_00407d60

void FUN_0040cea4(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_2 + 0x1c);
  if ((iVar1 == 0) ||
     ((1 << ((byte)param_1 & 0x1f) & (int)(short)(&DAT_004fbbac)[iVar1 * 0x19]) != 0)) {
    *(undefined4 *)(param_2 + 0x10) = 1;
  }
  else if (((char)(&DAT_0059f19e)[param_1 * 0x2d8] == 0) ||
          ((1 << ((byte)param_1 & 0x1f) &
           (int)(short)(&DAT_004fbbac)[(char)(&DAT_0059f19e)[param_1 * 0x2d8] * 0x19]) != 0)) {
    iVar2 = FUN_0040a37c(param_1,iVar1);
    if ((iVar2 != 0) && (iVar2 = FUN_0040a338(param_1,iVar1), iVar2 == 0)) {
      *(undefined4 *)(param_2 + 0x10) = 1;
      return;
    }
    iVar2 = FUN_0040a1c0(param_1,iVar1);
    if (iVar1 == iVar2) {
      FUN_004764dc(param_1,iVar1);
    }
    else if (iVar2 == 0) {
      *(undefined4 *)(param_2 + 0x10) = 1;
    }
    else {
      FUN_0040cdfc(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),iVar2,1);
      *(undefined4 *)(param_2 + 0xc) = 1;
    }
  }
  else {
    iVar1 = FUN_0040cda0(param_1);
    if (iVar1 == 0) {
      iVar1 = FUN_004067d0(param_1,0,5,10000,1,0);
      if (iVar1 == 0) {
        iVar1 = FUN_004067d0(param_1,0,5,10000,1,10000);
      }
      if (iVar1 == 0) {
        iVar1 = FUN_004054d8(5,0);
        if (iVar1 == 0) {
          *(undefined4 *)(param_2 + 0xc) = 1;
        }
        else {
          FUN_00407d60(param_1,4,*(undefined4 *)(param_2 + 8),0x12,0xffffffff,5,1);
          *(undefined4 *)(param_2 + 0x10) = 1;
        }
      }
    }
    else {
      *(undefined4 *)(param_2 + 0xc) = 1;
    }
  }
  return;
}

