// FUN_0040e2f4 @ 0040e2f4 size=81 sig=undefined FUN_0040e2f4() cc=unknown
// callers: 
// callees: FUN_004089d4

void FUN_0040e2f4(int param_1)

{
  short sVar1;
  undefined2 uVar2;
  
  sVar1 = *(short *)(param_1 + 8);
  if (((sVar1 == -1) || ((&DAT_0059f161)[sVar1 * 0x2d8] == '\0')) ||
     ((1 << ((byte)sVar1 & 0x1f) & *(uint *)(&DAT_0052222c + *(short *)(param_1 + 10) * 4)) == 0)) {
    uVar2 = FUN_004089d4((int)*(short *)(param_1 + 10));
    *(undefined2 *)(param_1 + 8) = uVar2;
  }
  return;
}

