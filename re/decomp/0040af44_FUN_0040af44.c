// FUN_0040af44 @ 0040af44 size=95 sig=undefined FUN_0040af44() cc=unknown
// callers: 
// callees: 

undefined4 FUN_0040af44(int param_1,undefined *param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 1;
  piVar1 = (int *)(param_1 + 0x88);
  while (((*piVar1 == 0 ||
          (iVar3 = *(short *)(param_1 + 10) * 0x2648 + *piVar1 * 0xc4, iVar3 == -0x5224c0)) ||
         (&DAT_005224c0 + iVar3 != param_2))) {
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
    if (0xf < iVar2) {
      return 0;
    }
  }
  return 1;
}

