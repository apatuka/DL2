// FUN_0044fcd4 @ 0044fcd4 size=64 sig=undefined FUN_0044fcd4() cc=unknown
// callers: FUN_0046c7d4
// callees: FUN_0044f3f0

void FUN_0044fcd4(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = &DAT_005a4eac;
  for (iVar2 = 1; iVar2 <= DAT_004d5b18; iVar2 = iVar2 + 1) {
    if (*(char *)(puVar1 + 8) != -1) {
      FUN_0044f3f0(puVar1,param_2,param_1);
    }
    puVar1 = puVar1 + 0x2b7;
  }
  return;
}

