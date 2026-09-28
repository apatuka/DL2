// FUN_0040cda0 @ 0040cda0 size=90 sig=undefined FUN_0040cda0() cc=unknown
// callers: FUN_0040cea4
// callees: FUN_004055c4

undefined4 FUN_0040cda0(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = (int)(char)(&DAT_0059f19e)[param_1 * 0x2d8];
  if ((iVar3 != 0) &&
     (sVar1 = (&DAT_004fbbb2)[iVar3 * 0x19 + param_1], iVar2 = FUN_004055c4(5,0),
     (int)*(short *)(&DAT_004fbbce + iVar3 * 0x32) < sVar1 + iVar2)) {
    return 1;
  }
  return 0;
}

