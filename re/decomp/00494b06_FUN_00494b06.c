// FUN_00494b06 @ 00494b06 size=101 sig=undefined FUN_00494b06() cc=unknown
// callers: FUN_00494c15,FUN_0049415f,FUN_00494def,FUN_00494fb6,FUN_004941f5
// callees: FUN_00494b6b,FUN_004a60b1

void FUN_00494b06(void)

{
  int iVar1;
  
  if (DAT_0065ec80 == 0) {
    return;
  }
  if (DAT_0051dc9c != 0) {
    if (DAT_0065ec7c != 0) {
      if (DAT_0051dc98 == 0) {
        if ((DAT_0051dc94 == (code *)0x0) ||
           (iVar1 = (*DAT_0051dc94)(DAT_0051dc90,1,0,&DAT_0065ec8c), iVar1 == 0)) {
          FUN_004a60b1(&DAT_0065ec8c,0);
        }
      }
      else {
        FUN_00494b6b();
      }
      DAT_0051dc7c = 0;
      return;
    }
    return;
  }
  return;
}

