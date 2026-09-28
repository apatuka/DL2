// FUN_00490603 @ 00490603 size=56 sig=undefined FUN_00490603() cc=unknown
// callers: FUN_00490ce4,FUN_0049063b,FUN_00490d70,FUN_004906b5,FUN_00490680
// callees: 

short * FUN_00490603(int param_1)

{
  short *psVar1;
  int iVar2;
  
  if (DAT_0051daf8 != (short *)0x0) {
    psVar1 = DAT_0051daf8 + 2;
    for (iVar2 = (int)*DAT_0051daf8; 0 < iVar2; iVar2 = iVar2 + -1) {
      if (param_1 == *(int *)(psVar1 + 1)) {
        return psVar1;
      }
      psVar1 = psVar1 + 0x85;
    }
  }
  return (short *)0x0;
}

