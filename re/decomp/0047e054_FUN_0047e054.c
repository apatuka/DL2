// FUN_0047e054 @ 0047e054 size=31 sig=undefined FUN_0047e054() cc=unknown
// callers: FUN_0047eed8,FUN_00440b68
// callees: 

void FUN_0047e054(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = &DAT_006552cc;
  iVar2 = 0;
  do {
    *puVar1 = param_1;
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 1;
  } while (iVar2 < 0x500);
  return;
}

