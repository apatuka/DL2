// FUN_0048ad15 @ 0048ad15 size=95 sig=undefined FUN_0048ad15() cc=unknown
// callers: FUN_0048aeb0
// callees: 

void FUN_0048ad15(int param_1)

{
  int iVar1;
  ushort *puVar2;
  int iVar3;
  ushort *puVar4;
  
  puVar4 = (ushort *)(param_1 + 0x1a);
  for (iVar1 = (int)*(short *)(param_1 + 2); iVar1 != 0; iVar1 = iVar1 + -1) {
    puVar2 = puVar4;
    for (iVar3 = (int)*(short *)(param_1 + 4); iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar2 = (ushort)((int)(uint)*puVar2 >> 1) & 0x7fe0 | *puVar2 & 0x1f;
      puVar2 = puVar2 + 1;
    }
    puVar4 = (ushort *)((int)puVar4 + (int)*(short *)(param_1 + 6));
  }
  *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) & 0xfff3;
  return;
}

