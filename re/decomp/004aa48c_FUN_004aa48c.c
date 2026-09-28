// FUN_004aa48c @ 004aa48c size=140 sig=undefined FUN_004aa48c() cc=unknown
// callers: FUN_00412358,FUN_00479700,FUN_00479b6c
// callees: FUN_004aa3bc,FUN_004ab648,FUN_004ab710,FUN_004acf20

int FUN_004aa48c(int param_1)

{
  int iVar1;
  int iVar2;
  
  FUN_004ab648(param_1);
  iVar1 = FUN_004acf20((int)*(char *)(param_1 + 0x16),0,1);
  iVar2 = iVar1;
  if (iVar1 != -1) {
    if (*(int *)(param_1 + 8) < 0) {
      if ((*(byte *)((int)&DAT_00520198 + *(char *)(param_1 + 0x16) * 4 + 1) & 8) != 0) {
        iVar2 = FUN_004acf20((int)*(char *)(param_1 + 0x16),0,2);
        if (iVar2 == -1) goto LAB_004aa50a;
        iVar1 = FUN_004acf20((int)*(char *)(param_1 + 0x16),iVar1,0);
        if (iVar1 == -1) {
          iVar2 = -1;
          goto LAB_004aa50a;
        }
      }
      iVar1 = FUN_004aa3bc(param_1);
      iVar2 = iVar2 + iVar1;
    }
    else {
      iVar2 = FUN_004aa3bc(param_1);
      iVar2 = iVar1 - iVar2;
    }
  }
LAB_004aa50a:
  FUN_004ab710(param_1);
  return iVar2;
}

