// FUN_0044c3fc @ 0044c3fc size=78 sig=undefined FUN_0044c3fc() cc=unknown
// callers: FUN_004761b0,NetBuildingTasks
// callees: 

void FUN_0044c3fc(int param_1,int *param_2,undefined1 param_3)

{
  int *piVar1;
  int iVar2;
  
  if (param_1 != 0) {
    iVar2 = 0;
    piVar1 = (int *)(param_1 + 0x18);
    do {
      if (-1 < *param_2) {
        *piVar1 = (int)(short)*param_2;
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 1;
      param_2 = param_2 + 1;
    } while (iVar2 < 5);
    (&DAT_005a4d7e)[*(short *)(param_1 + 8) * 0xadc] = param_3;
  }
  return;
}

