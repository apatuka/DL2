// FUN_0040afa4 @ 0040afa4 size=90 sig=undefined FUN_0040afa4() cc=unknown
// callers: FUN_0040beb4
// callees: 

void FUN_0040afa4(int param_1,undefined *param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 1;
  piVar1 = (int *)(param_1 + 0x88);
  do {
    if (((*piVar1 != 0) &&
        (iVar3 = *(short *)(param_1 + 10) * 0x2648 + *piVar1 * 0xc4, iVar3 != -0x5224c0)) &&
       (&DAT_005224c0 + iVar3 == param_2)) {
      *piVar1 = 0;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 0x10);
  return;
}

