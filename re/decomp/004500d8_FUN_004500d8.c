// FUN_004500d8 @ 004500d8 size=120 sig=undefined FUN_004500d8() cc=unknown
// callers: FUN_00415924,FUN_00486e34,FUN_00450380
// callees: FUN_0044fdf0,FUN_0044fe1c,FUN_0046ac44

undefined4 FUN_004500d8(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined1 local_80 [32];
  int aiStack_60 [22];
  
  iVar1 = FUN_0044fe1c(8);
  if (iVar1 != 0) {
    iVar1 = FUN_0044fdf0(8);
    iVar3 = iVar1 * 0x44 + DAT_004d5a94 * 0xd8;
    FUN_0046ac44(local_80,DAT_0058f1f4);
    piVar2 = (int *)(&DAT_004c61a8 + iVar3);
    for (iVar1 = 1; iVar1 <= *(int *)(&DAT_004c61a4 + iVar3); iVar1 = iVar1 + 1) {
      if (aiStack_60[*piVar2] < piVar2[1]) {
        return 0;
      }
      piVar2 = piVar2 + 2;
    }
  }
  return 1;
}

