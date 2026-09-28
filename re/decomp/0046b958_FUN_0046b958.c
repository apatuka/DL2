// FUN_0046b958 @ 0046b958 size=72 sig=undefined FUN_0046b958() cc=unknown
// callers: ConsumeFood,FUN_0046ab18,FUN_0046b9a0,FUN_004489e0
// callees: 

int FUN_0046b958(int param_1)

{
  int iVar1;
  
  iVar1 = (int)*(char *)(param_1 + 0x20);
  if ((iVar1 < 0) || (6 < iVar1)) {
    iVar1 = 0;
  }
  else {
    iVar1 = ((int)*(short *)(param_1 + 0x30) *
            (int)(short)(&DAT_0055a156)[(char)(&DAT_0059f162)[iVar1 * 0x2d8]]) / 10000;
  }
  return iVar1;
}

