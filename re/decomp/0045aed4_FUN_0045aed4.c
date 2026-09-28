// FUN_0045aed4 @ 0045aed4 size=446 sig=undefined FUN_0045aed4() cc=unknown
// callers: FUN_0045b094,FUN_0045bc10,FUN_0045cd88,FUN_0045b448
// callees: 

int FUN_0045aed4(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = 0;
  uVar1 = *(ushort *)(DAT_00657de0 + 0x142 + param_1 * 0x34);
  uVar3 = (int)(short)(uVar1 & 0xff00) & 0xf000;
  if (uVar3 < 0x3001) {
    if (uVar3 == 0x3000) {
      if ((uVar1 & 0xf00) == 0x100) {
        iVar2 = *(int *)(DAT_00657de0 + 0x5cc + param_1 * 0x34);
      }
      else {
        iVar2 = *(int *)(DAT_00657de0 + 0x154 + param_1 * 0x34);
        if (iVar2 == 0) {
          iVar2 = *(int *)(DAT_00657de0 + 0x28c + param_1 * 0x34);
        }
      }
    }
    else if (uVar3 == 0x1000) {
      if ((uVar1 & 0xf00) == 0x100) {
        iVar2 = *(int *)(DAT_00657de0 + 0x3c4 + param_1 * 0x34);
      }
      else {
        iVar2 = *(int *)(DAT_00657de0 + 0x154 + param_1 * 0x34);
      }
    }
    else if (uVar3 == 0x2000) {
      if ((uVar1 & 0xf00) == 0x100) {
        iVar2 = *(int *)(DAT_00657de0 + 0xec + param_1 * 0x34);
      }
      else {
        iVar2 = *(int *)(DAT_00657de0 + 0x120 + param_1 * 0x34);
      }
    }
  }
  else if (uVar3 == 0x4000) {
    if ((uVar1 & 0xf00) == 0x100) {
      iVar2 = *(int *)(DAT_00657de0 + 0x2f4 + param_1 * 0x34);
    }
    else {
      iVar2 = *(int *)(DAT_00657de0 + 600 + param_1 * 0x34);
    }
  }
  else if (uVar3 == 0x5000) {
    if ((uVar1 & 0xf00) == 0x100) {
      iVar2 = *(int *)(DAT_00657de0 + 0x35c + param_1 * 0x34);
    }
    else {
      iVar2 = *(int *)(DAT_00657de0 + 0x154 + param_1 * 0x34);
    }
  }
  return iVar2;
}

