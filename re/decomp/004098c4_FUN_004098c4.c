// FUN_004098c4 @ 004098c4 size=73 sig=undefined FUN_004098c4() cc=unknown
// callers: FUN_00409914
// callees: FUN_00405760,FUN_00409870

void FUN_004098c4(int param_1)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = (int *)(&DAT_00522294)[param_1 * 0x11]; piVar1 != (int *)0x0;
      piVar1 = (int *)piVar1[5]) {
    if (((piVar1[1] == 0) && (*piVar1 == 2)) &&
       (iVar2 = FUN_00409870(param_1,piVar1[7]), iVar2 != 0)) {
      FUN_00405760(piVar1);
    }
  }
  return;
}

