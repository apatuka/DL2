// FUN_0047d460 @ 0047d460 size=60 sig=undefined FUN_0047d460() cc=unknown
// callers: FUN_0047d49c,FUN_00461418,ResetVariables
// callees: memset

void FUN_0047d460(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  
  memset(&DAT_00654ac0,0,0x578);
  iVar4 = 0;
  puVar2 = &DAT_00654ac0;
  do {
    iVar3 = 0;
    puVar1 = puVar2;
    do {
      *puVar1 = 0xffff;
      iVar3 = iVar3 + 1;
      puVar1 = puVar1 + 4;
    } while (iVar3 < 0x19);
    iVar4 = iVar4 + 1;
    puVar2 = puVar2 + 100;
  } while (iVar4 < 7);
  return;
}

