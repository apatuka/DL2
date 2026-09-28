// FUN_00499dfc @ 00499dfc size=116 sig=undefined FUN_00499dfc() cc=unknown
// callers: FUN_0049a6bb
// callees: FUN_00498ba9

undefined4 FUN_00499dfc(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (DAT_0051e224 == 0) {
    DAT_0051e224 = FUN_00498ba9(0x200);
  }
  if (DAT_0051e224 == 0) {
    uVar1 = 0;
  }
  else {
    iVar4 = 0;
    iVar3 = DAT_0051e224;
    do {
      (&DAT_0069ee70)[iVar4] = iVar3;
      iVar2 = 0;
      do {
        *(short *)(iVar3 + iVar2 * 2) = (short)((iVar2 * param_1) / 100);
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0x40);
      iVar3 = iVar3 + 0x80;
      param_1 = param_1 + param_2;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 4);
    uVar1 = 1;
  }
  return uVar1;
}

