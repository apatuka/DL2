// FUN_00431f6c @ 00431f6c size=166 sig=undefined FUN_00431f6c() cc=unknown
// callers: FUN_00476d98,FUN_00476dcc
// callees: FUN_0047d3d8,FUN_00483d58

void FUN_00431f6c(char *param_1,int param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  sVar1 = *(short *)(&DAT_004fbbce + param_2 * 0x32);
  iVar2 = sVar1 * 5;
  if (iVar2 <= *(int *)(param_1 + 0xc)) {
    FUN_00483d58((int)*param_1,&DAT_004fbbac + param_2 * 0x19);
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + sVar1 * -5;
    if (*(short *)(param_1 + 6) == -1) {
      for (iVar4 = 1; iVar4 <= DAT_004d5b18; iVar4 = iVar4 + 1) {
        iVar3 = iVar4 * 0xadc;
        if ((((&DAT_005a444e)[iVar3] != '\0') &&
            ((*(byte *)((int)&DAT_005a43ec + iVar3 + 1) & 1) == 0)) &&
           (*param_1 == (&DAT_005a43f0)[iVar3])) {
          FUN_0047d3d8((int)*param_1,(int)(short)(&DAT_005a43ea)[iVar4 * 0x56e],2,iVar2);
          return;
        }
      }
    }
    else {
      FUN_0047d3d8((int)*param_1,(int)*(short *)(param_1 + 6),2,iVar2);
    }
  }
  return;
}

