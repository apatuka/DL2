// FUN_00435f5c @ 00435f5c size=163 sig=undefined FUN_00435f5c() cc=unknown
// callers: FUN_00476e40,FUN_00476e0c
// callees: FUN_0047d3d8

void FUN_00435f5c(char *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if (99 < *(int *)(param_1 + 0xc)) {
    (&DAT_005a4436)[(int)*param_1 + param_2 * 0xadc] = 3;
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + -100;
    if (*(short *)(param_1 + 6) == -1) {
      for (iVar2 = 1; iVar2 <= DAT_004d5b18; iVar2 = iVar2 + 1) {
        iVar1 = iVar2 * 0xadc;
        if ((((&DAT_005a444e)[iVar1] != '\0') &&
            ((*(byte *)((int)&DAT_005a43ec + iVar1 + 1) & 1) == 0)) &&
           (*param_1 == (&DAT_005a43f0)[iVar1])) {
          FUN_0047d3d8((int)*param_1,(int)(short)(&DAT_005a43ea)[iVar2 * 0x56e],0,0);
          return;
        }
      }
    }
    else {
      FUN_0047d3d8((int)*param_1,(int)*(short *)(param_1 + 6),0,0);
    }
  }
  return;
}

