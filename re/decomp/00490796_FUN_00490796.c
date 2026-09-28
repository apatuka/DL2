// FUN_00490796 @ 00490796 size=238 sig=undefined FUN_00490796() cc=unknown
// callers: FUN_0049d7f4,FUN_004a588c,FUN_004a3cc8,FUN_0047e0a0,FUN_0041beac,FUN_004a3de6,DrawCAGuyPool,FUN_004a17f6,FUN_004a3ea0,FUN_0043e198,FUN_00491bd5,FUN_00459068,FUN_0043b50c,FUN_00480150,FUN_004a3e49,FUN_00495fc5,FUN_0049116d,FUN_0043b2c4,FUN_0048d13d,FUN_004878a8,FUN_0041ba74,FUN_00418704
// callees: FUN_004901c6,FUN_004989de,FUN_00498aab

void FUN_00490796(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  short *psVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  
  if (param_1 != 0) {
    if (DAT_0051daf8 != (short *)0x0) {
      psVar4 = DAT_0051daf8 + 2;
      for (iVar5 = (int)*DAT_0051daf8; 0 < iVar5; iVar5 = iVar5 + -1) {
        iVar1 = *(int *)(psVar4 + 1);
        if (iVar1 != 0) {
          iVar2 = FUN_00498aab(iVar1,1);
          piVar3 = (int *)(*(int *)(iVar2 + 0xc) * 8 + iVar2 + 0x14);
          puVar7 = (undefined4 *)(iVar2 + 0x14);
          for (iVar2 = *(int *)(iVar2 + 0xc); 0 < iVar2; iVar2 = iVar2 + -1) {
            iVar6 = *piVar3;
            piVar3 = piVar3 + 2;
            for (; 0 < iVar6; iVar6 = iVar6 + -1) {
              if (param_1 == piVar3[7]) {
                if ((piVar3[8] == 0) ||
                   ((param_2 != 0 && (piVar3[8] = piVar3[8] + -1, piVar3[8] < 1)))) {
                  FUN_004901c6(iVar1,*puVar7,*piVar3,piVar3,2,0,0);
                }
                FUN_00498aab(iVar1,0);
                return;
              }
              piVar3 = piVar3 + 10;
            }
            puVar7 = puVar7 + 2;
          }
        }
        FUN_00498aab(iVar1,0);
        psVar4 = psVar4 + 0x85;
      }
    }
    FUN_004989de(param_1);
  }
  return;
}

