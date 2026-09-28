// FUN_0048ae5a @ 0048ae5a size=86 sig=undefined FUN_0048ae5a() cc=unknown
// callers: FUN_0048aeb0
// callees: 

void FUN_0048ae5a(int param_1)

{
  ushort *puVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  
  puVar3 = (ushort *)(param_1 + 0x1a);
  for (iVar4 = (int)*(short *)(param_1 + 2); iVar4 != 0; iVar4 = iVar4 + -1) {
    puVar1 = puVar3;
    for (iVar2 = (int)*(short *)(param_1 + 4); iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar1 = (&DAT_0067ee30)[*puVar1];
      puVar1 = puVar1 + 1;
    }
    puVar3 = (ushort *)((int)puVar3 + (int)*(short *)(param_1 + 6));
  }
  *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) & 0xfff3 | 8;
  return;
}

