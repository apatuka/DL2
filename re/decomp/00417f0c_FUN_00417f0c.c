// FUN_00417f0c @ 00417f0c size=166 sig=undefined FUN_00417f0c() cc=unknown
// callers: FUN_0041800c,FUN_004180b0,FUN_00417fb4
// callees: FUN_004382d0

void FUN_00417f0c(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *param_2;
  iVar2 = *param_3 * 0x20;
  *(undefined4 *)((int)&DAT_005332d8 + iVar2 + iVar1 * 0x146) = 2;
  *(int *)((int)&DAT_005332dc + iVar2 + iVar1 * 0x146) = param_1;
  *(undefined4 *)(&DAT_005332d0 + iVar2 + iVar1 * 0x146) = 0;
  *(undefined4 *)(&DAT_005332c0 + iVar2 + iVar1 * 0x146) = 0;
  *(undefined4 *)(&DAT_005332c4 + iVar2 + iVar1 * 0x146) = 0x31304c55;
  FUN_004382d0(&DAT_005332c0 + *param_2 * 0x146 + iVar2,(int)*(char *)(param_1 + 8),
               (int)*(char *)(param_1 + 6));
  *param_3 = *param_3 + 1;
  if (9 < *param_3) {
    *param_2 = *param_2 + 1;
    *param_3 = 0;
  }
  return;
}

