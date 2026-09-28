// FUN_0041beac @ 0041beac size=274 sig=undefined FUN_0041beac() cc=unknown
// callers: FUN_0041c258
// callees: FUN_00490ab3,FUN_00496e80,FUN_00490796,FUN_00496cc3,FUN_00498aab

void FUN_0041beac(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar1 = FUN_00490ab3(0,0x47414d49,0x31305542,0,0);
  if (iVar1 != 0) {
    iVar2 = (int)*(char *)(DAT_0053b850 + 4);
    iVar6 = (int)(char)(&DAT_004f9dc2)[iVar2 * 0x32];
    if (((iVar2 == 0x17) || (iVar2 == 0x25)) || (iVar2 == 0x27)) {
      iVar6 = iVar6 + *(char *)(DAT_0053b850 + 6);
    }
    if (((iVar2 == 1) || (iVar2 == 2)) || (iVar2 == 3)) {
      iVar6 = iVar6 + *(char *)(DAT_0053b850 + 6) * 3;
    }
    uVar3 = FUN_00498aab(iVar1,1);
    iVar2 = FUN_00496cc3(uVar3,9000,iVar6,0,&local_14);
    if (iVar2 != 0) {
      uVar4 = 0x4d - (local_c - local_14);
      iVar2 = (int)uVar4 >> 1;
      if (iVar2 < 0) {
        iVar2 = iVar2 + (uint)((uVar4 & 1) != 0);
      }
      if (iVar2 < 0) {
        iVar2 = 0;
      }
      uVar4 = 0x3f - (local_8 - local_10);
      iVar5 = (int)uVar4 >> 1;
      if (iVar5 < 0) {
        iVar5 = iVar5 + (uint)((uVar4 & 1) != 0);
      }
      if (iVar5 < 0) {
        iVar5 = 0;
      }
      FUN_00496e80(uVar3,9000,iVar6,0,iVar2 + *param_1 + 0x2f,iVar5 + param_1[1] + 0x1d,0xffffffff);
    }
    FUN_00498aab(iVar1,0);
    FUN_00490796(iVar1,0);
  }
  return;
}

