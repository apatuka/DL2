// FUN_0048558c @ 0048558c size=72 sig=undefined FUN_0048558c() cc=unknown
// callers: FUN_00485668
// callees: 

ushort * FUN_0048558c(int param_1)

{
  char cVar1;
  ushort *puVar2;
  ushort *puVar3;
  uint uVar4;
  
  puVar3 = (ushort *)0x0;
  uVar4 = 0x7fffffff;
  for (puVar2 = *(ushort **)(param_1 + 0x76); puVar2 != (ushort *)0x0;
      puVar2 = *(ushort **)(puVar2 + 0x2a)) {
    cVar1 = *(char *)((int)puVar2 + 7);
    if (((((byte)(cVar1 - 2U) < 2) || (cVar1 == '\t')) || ((byte)(cVar1 - 0xcU) < 2)) &&
       (*puVar2 < uVar4)) {
      puVar3 = puVar2;
      uVar4 = (uint)*puVar2;
    }
  }
  return puVar3;
}

