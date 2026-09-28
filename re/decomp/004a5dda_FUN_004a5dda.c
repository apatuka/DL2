// FUN_004a5dda @ 004a5dda size=56 sig=undefined FUN_004a5dda() cc=unknown
// callers: FUN_004a4025
// callees: 

void FUN_004a5dda(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (param_1 == (&DAT_0069f04c)[iVar1 * 4]) {
      (&DAT_0069f04c)[iVar1 * 4] = 0;
      (&DAT_0069f058)[iVar1 * 4] = 0;
      return;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 10);
  return;
}

