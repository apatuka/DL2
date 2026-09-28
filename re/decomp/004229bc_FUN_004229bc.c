// FUN_004229bc @ 004229bc size=56 sig=undefined FUN_004229bc() cc=unknown
// callers: FUN_00423b20,RunAITurns,FUN_00423960,FUN_004229f4,FUN_004226a0
// callees: FUN_0042278c

undefined4 FUN_004229bc(void)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar3 = 0;
  puVar2 = &DAT_00651cb4;
  while( true ) {
    if (DAT_0065209c <= iVar3) {
      return 0;
    }
    iVar1 = FUN_0042278c(*puVar2);
    if (*(int *)(&DAT_004fc90e + iVar1 * 0x12) == 1) break;
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 5;
  }
  return *puVar2;
}

