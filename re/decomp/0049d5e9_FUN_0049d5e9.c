// FUN_0049d5e9 @ 0049d5e9 size=483 sig=undefined FUN_0049d5e9() cc=unknown
// callers: FUN_0049edb2
// callees: FUN_0049eb44,FUN_0049f7f8

undefined4 FUN_0049d5e9(undefined4 param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (*(int *)(param_2 + 0x94) != 0) {
    iVar3 = 0;
    for (iVar1 = **(int **)(param_2 + 0x94); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      if (param_5 == 3) {
        if ((*(byte *)(iVar1 + 0xc) & 1) != 0) {
          iVar2 = FUN_0049eb44(param_1,param_2,2,0x3a,iVar3,0);
          if (iVar2 != 0) {
            *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffffffe;
            FUN_0049eb44(param_1,param_2,2,0x3b,iVar3,0);
          }
          FUN_0049f7f8(param_2,iVar3);
        }
      }
      else if (param_5 == 4) {
        if ((*(byte *)(iVar1 + 0xc) & 1) == 0) {
          iVar2 = FUN_0049eb44(param_1,param_2,2,0x3a,iVar3,0);
          if (iVar2 != 0) {
            *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 1;
            FUN_0049eb44(param_1,param_2,2,0x3b,iVar3,1);
          }
          FUN_0049f7f8(param_2,iVar3);
        }
      }
      else if ((iVar3 < param_3) || (param_4 < iVar3)) {
        if ((param_5 == 5) && ((*(byte *)(iVar1 + 0xc) & 1) != 0)) {
          iVar2 = FUN_0049eb44(param_1,param_2,2,0x3a,iVar3,0);
          if (iVar2 != 0) {
            *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffffffe;
            FUN_0049eb44(param_1,param_2,2,0x3b,iVar3,0);
          }
          FUN_0049f7f8(param_2,iVar3);
        }
      }
      else if (param_5 == 0) {
LAB_0049d6c6:
        if ((*(byte *)(iVar1 + 0xc) & 1) == 0) {
          iVar2 = FUN_0049eb44(param_1,param_2,2,0x3a,iVar3,0);
          if (iVar2 != 0) {
            *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 1;
            FUN_0049eb44(param_1,param_2,2,0x3b,iVar3,1);
          }
          FUN_0049f7f8(param_2,iVar3);
        }
      }
      else if (param_5 == 1) {
        if ((*(byte *)(iVar1 + 0xc) & 1) != 0) {
          iVar2 = FUN_0049eb44(param_1,param_2,2,0x3a,iVar3,0);
          if (iVar2 != 0) {
            *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffffffe;
            FUN_0049eb44(param_1,param_2,2,0x3b,iVar3,0);
          }
          FUN_0049f7f8(param_2,iVar3);
        }
      }
      else if (param_5 == 2) {
        iVar2 = FUN_0049eb44(param_1,param_2,2,0x3a,iVar3,0);
        if (iVar2 != 0) {
          *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) ^ 1;
          FUN_0049eb44(param_1,param_2,2,0x3b,iVar3,(*(byte *)(iVar1 + 0xc) & 1) != 0);
        }
        FUN_0049f7f8(param_2,iVar3);
      }
      else if (param_5 == 5) goto LAB_0049d6c6;
      iVar3 = iVar3 + 1;
    }
  }
  return 1;
}

