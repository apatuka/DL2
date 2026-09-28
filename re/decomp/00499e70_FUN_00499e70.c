// FUN_00499e70 @ 00499e70 size=148 sig=undefined FUN_00499e70() cc=unknown
// callers: FUN_0049a6bb
// callees: FUN_00498ba9

undefined4 FUN_00499e70(int param_1,int param_2)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (DAT_0051e228 == 0) {
    DAT_0051e228 = FUN_00498ba9(0x400);
  }
  if (DAT_0051e228 == 0) {
    uVar2 = 0;
  }
  else {
    iVar5 = 0;
    iVar4 = DAT_0051e228;
    do {
      (&DAT_0069ee50)[iVar5] = iVar4;
      iVar3 = 0;
      do {
        if ((param_1 << 5) / 100 + iVar3 < 0x3f) {
          sVar1 = (short)((param_1 << 5) / 100) + (short)iVar3;
        }
        else {
          sVar1 = 0x3f;
        }
        *(short *)(iVar4 + iVar3 * 2) = sVar1;
        iVar3 = iVar3 + 1;
      } while (iVar3 < 0x40);
      iVar4 = iVar4 + 0x80;
      param_1 = param_1 + param_2;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 8);
    uVar2 = 1;
  }
  return uVar2;
}

