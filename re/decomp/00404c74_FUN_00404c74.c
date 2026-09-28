// FUN_00404c74 @ 00404c74 size=119 sig=undefined FUN_00404c74() cc=unknown
// callers: 
// callees: FUN_0046ca40

int FUN_00404c74(int param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  uVar1 = FUN_0046ca40();
  uVar1 = uVar1 % 100;
  if (*(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c) < -8) {
    iVar3 = 0;
  }
  else if (*(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c) < 9) {
    iVar3 = 1;
  }
  else {
    iVar3 = 2;
  }
  iVar2 = 0;
  piVar4 = (int *)(param_3 + iVar3 * 0x14);
  do {
    uVar1 = uVar1 - *piVar4;
    if ((int)uVar1 < 1) break;
    iVar2 = iVar2 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar2 < 4);
  return iVar2 + 0x1f;
}

