// FUN_0040e384 @ 0040e384 size=187 sig=undefined FUN_0040e384() cc=unknown
// callers: FUN_0040e6e4
// callees: FUN_00401670,FUN_0040e348,FUN_0040c4d4,FUN_0040bbf4,FUN_004412d4,FUN_0040bfb4,FUN_0040beb4

void FUN_0040e384(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int local_8;
  
  iVar3 = *(int *)(param_1 + 0x10);
  if ((iVar3 != 0) &&
     (((*(char *)(iVar3 + 0x20) == -1 ||
       (iVar1 = FUN_004412d4((int)*(short *)(param_1 + 10),(int)*(char *)(iVar3 + 0x20),2),
       iVar1 != 0)) ||
      (((int)*(char *)(iVar3 + 0x20) == (int)*(short *)(param_1 + 10) &&
       ((*(short *)(iVar3 + 0x30) == 0 ||
        (iVar1 = FUN_00401670(iVar3,(int)*(short *)(param_1 + 10)), iVar1 != 0)))))))) {
    uVar2 = FUN_0040c4d4(iVar3);
    *(undefined4 *)(param_1 + 0x14) = uVar2;
    if ((*(short *)(iVar3 + 0x30) == 0) ||
       (iVar3 = FUN_0040e348((int)*(short *)(param_1 + 10),iVar3), iVar3 != 0)) {
      piVar4 = (int *)(param_1 + 0x14);
      local_8 = 1;
      if (*piVar4 < 2) {
        piVar4 = &local_8;
      }
      *(int *)(param_1 + 0x14) = *piVar4;
    }
    FUN_0040bfb4(param_1,10);
    FUN_0040bfb4(param_1,0x11);
    FUN_0040bfb4(param_1,0xc);
    FUN_0040bbf4(param_1,0,0);
    return;
  }
  FUN_0040beb4(param_1);
  return;
}

