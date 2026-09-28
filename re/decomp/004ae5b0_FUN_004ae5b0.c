// FUN_004ae5b0 @ 004ae5b0 size=40 sig=undefined FUN_004ae5b0() cc=unknown
// callers: RaceInit,FUN_004634a0,FUN_0046c9cc,ResetVariables
// callees: FUN_004b366c

uint FUN_004ae5b0(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_004b366c();
  iVar1 = *(int *)(iVar1 + 0x44);
  iVar2 = FUN_004b366c();
  *(int *)(iVar2 + 0x44) = iVar1 * 0x15a4e35 + 1;
  iVar1 = FUN_004b366c();
  return *(uint *)(iVar1 + 0x44) >> 0x10 & 0x7fff;
}

