// FUN_0049b604 @ 0049b604 size=102 sig=undefined FUN_0049b604() cc=unknown
// callers: FUN_0049b66a
// callees: FUN_0048f72d

void FUN_0049b604(int param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  
  if ((*(byte *)(param_1 + 8) & 3) == 0) {
    iVar3 = param_1 + 0x1a;
    sVar1 = *(short *)(param_1 + 8);
    sVar2 = *(short *)(param_1 + 4);
    if ((-1 < *(short *)(param_1 + 10)) && (*(short *)(param_1 + 10) <= *(short *)(param_1 + 4))) {
      *(short *)(param_1 + 10) = *(short *)(param_1 + 4) - *(short *)(param_1 + 10);
    }
    *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) ^ 0x10;
    iVar4 = (int)*(short *)(param_1 + 2);
    while (iVar4 = iVar4 + -1, -1 < iVar4) {
      FUN_0048f72d(iVar3,(((int)sVar1 & 3U) + 1) * (int)sVar2);
      iVar3 = iVar3 + *(short *)(param_1 + 6);
    }
  }
  return;
}

