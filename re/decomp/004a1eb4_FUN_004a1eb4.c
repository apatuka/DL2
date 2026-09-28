// FUN_004a1eb4 @ 004a1eb4 size=272 sig=undefined FUN_004a1eb4() cc=unknown
// callers: FUN_004a1fc4
// callees: FUN_00498aab,FUN_00496c61,FUN_004a118a

undefined4 FUN_004a1eb4(int param_1,int param_2)

{
  undefined4 uVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  if ((*(uint *)(param_2 + 0x24) & 0x1f) == 2) {
    if ((*(int *)(param_2 + 0x38) != 0) &&
       ((*(int *)(param_2 + 0x14) == -1 || (*(int *)(param_2 + 0x18) == -1)))) {
      uVar1 = FUN_00498aab(*(undefined4 *)(param_2 + 0x38),1);
      piVar2 = (int *)FUN_00496c61(uVar1,*(undefined4 *)(param_2 + 0x54),0,0,0,0,0,0);
      if (piVar2 != (int *)0x0) {
        if (*(int *)(param_2 + 0x14) == -1) {
          *(int *)(param_2 + 0x14) = (int)*(short *)(*piVar2 + 2);
        }
        if (*(int *)(param_2 + 0x18) == -1) {
          *(int *)(param_2 + 0x18) = (int)*(short *)(*piVar2 + 4);
        }
      }
      FUN_00498aab(*(undefined4 *)(param_2 + 0x38),0);
    }
  }
  else if (((*(uint *)(param_2 + 0x24) & 0x1f) == 4) && (*(int *)(param_2 + 0x38) != 0)) {
    if (*(int *)(param_2 + 0x14) == -1) {
      *(undefined4 *)(param_2 + 0x14) = *(undefined4 *)(*(int *)(param_2 + 0x38) + 8);
    }
    if (*(int *)(param_2 + 0x18) == -1) {
      *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(*(int *)(param_2 + 0x38) + 4);
    }
  }
  if (*(int *)(param_2 + 0xc) == -1) {
    uVar3 = *(int *)(param_1 + 0x14) - *(int *)(param_2 + 0x18);
    iVar4 = (int)uVar3 >> 1;
    if (iVar4 < 0) {
      iVar4 = iVar4 + (uint)((uVar3 & 1) != 0);
    }
    *(int *)(param_2 + 0xc) = iVar4;
  }
  if (*(int *)(param_2 + 0x10) == -1) {
    uVar3 = *(int *)(param_1 + 0x10) - *(int *)(param_2 + 0x14);
    iVar4 = (int)uVar3 >> 1;
    if (iVar4 < 0) {
      iVar4 = iVar4 + (uint)((uVar3 & 1) != 0);
    }
    *(int *)(param_2 + 0x10) = iVar4;
  }
  FUN_004a118a(param_2,*(undefined4 *)(param_2 + 0xc),*(undefined4 *)(param_2 + 0x10),1);
  if (*(int *)(param_2 + 0x40) != 0) {
    (**(code **)(param_2 + 0x40))(param_2,6,0,0);
  }
  return 1;
}

