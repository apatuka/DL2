// FUN_0049b268 @ 0049b268 size=209 sig=undefined FUN_0049b268() cc=unknown
// callers: FUN_0049ae0c,FUN_00440b68,FUN_00491d38,FUN_0049aa95,FUN_00411808,FUN_0048c662,BlitSprite8
// callees: 

void FUN_0049b268(int param_1,int param_2)

{
  ushort *puVar1;
  int iVar2;
  ushort *puVar3;
  
  if ((*(byte *)(param_1 + 6) & 0xf) == 0) {
    puVar1 = (ushort *)(param_1 + 8);
    if (param_2 == 1) {
      puVar3 = puVar1;
      for (iVar2 = 0; iVar2 < *(short *)(param_1 + 2); iVar2 = iVar2 + 1) {
        *puVar3 = ((byte)*puVar1 & 0xf8) << 7 | (*(byte *)((int)puVar1 + 1) & 0xf8) << 2 |
                  (ushort)((int)(uint)(byte)puVar1[1] >> 3);
        puVar3 = puVar3 + 1;
        puVar1 = puVar1 + 2;
      }
      *(ushort *)(param_1 + 6) = *(ushort *)(param_1 + 6) & 0xfff0 | 1;
    }
    else if (param_2 == 2) {
      puVar3 = puVar1;
      for (iVar2 = 0; iVar2 < *(short *)(param_1 + 2); iVar2 = iVar2 + 1) {
        *puVar3 = ((byte)*puVar1 & 0xf8) << 8 | (*(byte *)((int)puVar1 + 1) & 0xfc) << 3 |
                  (ushort)((int)(uint)(byte)puVar1[1] >> 3);
        puVar3 = puVar3 + 1;
        puVar1 = puVar1 + 2;
      }
      *(ushort *)(param_1 + 6) = *(ushort *)(param_1 + 6) & 0xfff0 | 2;
    }
  }
  return;
}

