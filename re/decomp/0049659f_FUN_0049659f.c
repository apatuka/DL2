// FUN_0049659f @ 0049659f size=340 sig=undefined FUN_0049659f() cc=unknown
// callers: FUN_004966f3
// callees: FUN_00496c03,FUN_00498ba9,FUN_0048f774,FUN_00496945,FUN_00490ab3

bool FUN_0049659f(int param_1,undefined4 param_2)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  int local_8;
  
  piVar2 = (int *)FUN_00496945(param_1,param_2);
  if (piVar2 == (int *)0x0) {
    bVar8 = false;
  }
  else {
    for (local_8 = 0; local_8 < *piVar2; local_8 = local_8 + 1) {
      iVar1 = piVar2[local_8 + 0x10];
      for (iVar7 = 0; iVar7 < (int)(uint)*(ushort *)((int)piVar2 + iVar1 + 0x1e); iVar7 = iVar7 + 1)
      {
        for (iVar6 = 0; iVar6 < (int)(uint)*(ushort *)((int)piVar2 + iVar1 + 0x1c);
            iVar6 = iVar6 + 1) {
          uVar3 = FUN_00496c03(param_1,param_2,local_8,iVar6,iVar7,0,0);
          if ((uVar3 & 0x10000000) == 0x10000000) {
            iVar4 = FUN_00490ab3(*(undefined4 *)(param_1 + 0xc),0x44335943,uVar3 & 0xffffff,0,0);
            if (iVar4 != 0) {
              if (piVar2[2] == 0) {
                iVar5 = FUN_00498ba9(0x10);
                piVar2[2] = iVar5;
                FUN_0048f774(piVar2[2],0x10,0);
              }
              if (piVar2[2] != 0) {
                if (*(int *)(piVar2[2] + 8) < *(int *)(iVar4 + 0x3c)) {
                  *(undefined4 *)(piVar2[2] + 8) = *(undefined4 *)(iVar4 + 0x3c);
                }
                if (*(int *)(piVar2[2] + 0xc) < *(int *)(iVar4 + 0x40)) {
                  *(undefined4 *)(piVar2[2] + 0xc) = *(undefined4 *)(iVar4 + 0x40);
                }
                *(uint *)(piVar2[2] + 4) = *(uint *)(piVar2[2] + 4) | 1;
              }
            }
          }
        }
      }
    }
    bVar8 = piVar2[2] != 0;
  }
  return bVar8;
}

