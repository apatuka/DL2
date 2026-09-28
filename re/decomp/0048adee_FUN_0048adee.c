// FUN_0048adee @ 0048adee size=108 sig=undefined FUN_0048adee() cc=unknown
// callers: FUN_0048aeb0
// callees: 

void FUN_0048adee(int param_1)

{
  ushort uVar1;
  ushort *puVar2;
  int iVar3;
  uint uVar4;
  
  for (iVar3 = (int)*(short *)(param_1 + 2); iVar3 != 0; iVar3 = iVar3 + -1) {
    puVar2 = (ushort *)(*(int *)(param_1 + 0x1a + iVar3 * 4) + param_1 + 0x1a);
    do {
      uVar1 = puVar2[1];
      puVar2 = puVar2 + 2;
      uVar4 = uVar1 & 0x7fff;
      if ((uVar1 & 0x7fff) != 0) {
        do {
          *puVar2 = (ushort)((int)(uint)*puVar2 >> 1) & 0x7fe0 | *puVar2 & 0x1f;
          puVar2 = puVar2 + 1;
          uVar4 = uVar4 - 1;
        } while (uVar4 != 0);
      }
    } while ((uVar1 & 0x8000) == 0);
  }
  *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) & 0xfff3;
  return;
}

