// FUN_00410164 @ 00410164 size=109 sig=undefined FUN_00410164() cc=unknown
// callers: FUN_004059bc
// callees: FUN_0040febc,FUN_0040c3b8,FUN_0040b994

void FUN_00410164(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = param_1 * 0x2648 + *(int *)(param_2 + 0x1c) * 0xc4;
  piVar3 = (int *)(&DAT_00522584 + iVar2);
  if ((*piVar3 == 0) || (*piVar3 == 1)) {
    *(undefined4 *)(param_2 + 0x10) = 1;
  }
  else {
    FUN_0040b994(piVar3);
    FUN_0040febc(param_1,param_2);
    iVar1 = FUN_0040c3b8(piVar3);
    if (iVar1 < *(int *)(&DAT_00522598 + iVar2)) {
      *(undefined4 *)(param_2 + 0xc) = 1;
    }
    else {
      *(undefined4 *)(param_2 + 0x10) = 1;
    }
  }
  return;
}

