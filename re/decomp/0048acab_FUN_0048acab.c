// FUN_0048acab @ 0048acab size=106 sig=undefined FUN_0048acab() cc=unknown
// callers: FUN_0048aeb0
// callees: 

void FUN_0048acab(int param_1)

{
  int iVar1;
  ushort *puVar2;
  int iVar3;
  ushort *puVar4;
  
  puVar4 = (ushort *)(param_1 + 0x1a);
  for (iVar1 = (int)*(short *)(param_1 + 2); iVar1 != 0; iVar1 = iVar1 + -1) {
    puVar2 = puVar4;
    for (iVar3 = (int)*(short *)(param_1 + 4); iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar2 = *puVar2 * 2 & 0xffc0 | *puVar2 & 0x1f;
      puVar2 = puVar2 + 1;
    }
    puVar4 = (ushort *)((int)puVar4 + (int)*(short *)(param_1 + 6));
  }
  *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) & 0xfff3 | 4;
  return;
}

