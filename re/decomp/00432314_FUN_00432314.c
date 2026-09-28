// FUN_00432314 @ 00432314 size=134 sig=undefined FUN_00432314() cc=unknown
// callers: FUN_0043239c
// callees: FUN_0049eb44,FUN_00430b04

void FUN_00432314(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  DAT_00558e64 = 0;
  iVar2 = 0x18;
  uVar4 = 0x1000000;
  piVar3 = &DAT_004c4444;
  do {
    if (((*(uint *)(param_1 + 0x42) & uVar4) == 0) && (*piVar3 <= DAT_0059f154)) {
      (&DAT_00558cd4)[DAT_00558e64 * 2] = iVar2;
      uVar1 = FUN_00430b04(iVar2);
      (&DAT_00558cd8)[DAT_00558e64 * 2] = uVar1;
      DAT_00558e64 = DAT_00558e64 + 1;
      if (0xf < DAT_00558e64) break;
    }
    piVar3 = (int *)((int)piVar3 + -0xe);
    iVar2 = iVar2 + -1;
    uVar4 = (int)uVar4 >> 1;
  } while (-1 < iVar2);
  FUN_0049eb44(DAT_004c42e0,0x26,1,0x31,0xe,1);
  return;
}

