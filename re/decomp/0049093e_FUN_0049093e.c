// FUN_0049093e @ 0049093e size=187 sig=undefined FUN_0049093e() cc=unknown
// callers: 
// callees: FUN_00498bba,FUN_0048fe90,FUN_00498aab

int FUN_0049093e(int param_1)

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
              if (piVar3[8] == 0) {
                FUN_0048fe90(piVar3);
              }
              else {
                param_1 = FUN_00498bba(param_1);
              }
              FUN_00498aab(iVar1,0);
              return param_1;
            }
            piVar3 = piVar3 + 10;
          }
        }
      }
      FUN_00498aab(iVar1,0);
      psVar2 = psVar2 + 0x85;
    }
  }
  return param_1;
}

