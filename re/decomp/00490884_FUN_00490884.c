// FUN_00490884 @ 00490884 size=186 sig=undefined FUN_00490884() cc=unknown
// callers: 
// callees: FUN_00498aab

int FUN_00490884(int param_1,int param_2)

{
  int iVar1;
  short *psVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  if ((param_1 != 0) && (DAT_0051daf8 != (short *)0x0)) {
    psVar2 = DAT_0051daf8 + 2;
    for (iVar5 = (int)*DAT_0051daf8; 0 < iVar5; iVar5 = iVar5 + -1) {
      iVar1 = *(int *)(psVar2 + 1);
      if (iVar1 != 0) {
        iVar5 = FUN_00498aab(iVar1,1);
        piVar3 = (int *)(*(int *)(iVar5 + 0xc) * 8 + iVar5 + 0x14);
        for (iVar5 = *(int *)(iVar5 + 0xc); 0 < iVar5; iVar5 = iVar5 + -1) {
          iVar4 = *piVar3;
          piVar3 = piVar3 + 2;
          for (; 0 < iVar4; iVar4 = iVar4 + -1) {
            if (param_1 == piVar3[7]) {
              piVar3[8] = piVar3[8] + param_2;
              iVar5 = piVar3[8];
              FUN_00498aab(iVar1,0);
              return iVar5;
            }
            piVar3 = piVar3 + 10;
          }
        }
      }
      FUN_00498aab(iVar1,0);
      psVar2 = psVar2 + 0x85;
    }
  }
  return 0;
}

