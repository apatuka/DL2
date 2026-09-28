// FUN_004a5d60 @ 004a5d60 size=122 sig=undefined FUN_004a5d60() cc=unknown
// callers: FUN_004a3d26
// callees: 

undefined4 FUN_004a5d60(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if ((&DAT_0069f04c)[iVar1 * 4] == 0) {
      (&DAT_0069f04c)[iVar1 * 4] = DAT_0069f03c;
      DAT_0069f03c = DAT_0069f03c + 1;
      (&DAT_0069f050)[iVar1 * 4] = param_2;
      (&DAT_0069f054)[iVar1 * 4] = param_3;
      (&DAT_0069f058)[iVar1 * 4] = param_1;
      if (DAT_0069f03c == 0) {
        DAT_0069f03c = 1;
      }
      return (&DAT_0069f04c)[iVar1 * 4];
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 10);
  return 0;
}

