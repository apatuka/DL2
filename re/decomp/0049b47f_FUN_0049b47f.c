// FUN_0049b47f @ 0049b47f size=243 sig=undefined FUN_0049b47f() cc=unknown
// callers: FUN_0049b5b7
// callees: 

undefined4 FUN_0049b47f(int param_1,int param_2,int param_3,uint *param_4)

{
  ushort uVar1;
  ushort uVar2;
  ushort *puVar3;
  
  puVar3 = (ushort *)(*(int *)(param_1 + 0x1a + param_3 * 4) + param_1 + 0x1a);
  if ((*(byte *)(param_1 + 8) & 3) == 0) {
    do {
      uVar1 = *puVar3;
      uVar2 = puVar3[1];
      if (param_2 < (int)((uint)uVar1 - (uVar2 & 0x7fff))) {
        return 0;
      }
      if (param_2 <= (int)(uint)uVar1) {
        if (param_4 != (uint *)0x0) {
          *param_4 = (uint)*(byte *)((int)puVar3 + (param_2 - (uint)uVar1) + 4);
        }
        return 1;
      }
      if ((uVar2 & 0x8000) != 0) {
        return 0;
      }
      puVar3 = (ushort *)((int)puVar3 + (uVar2 & 0x7fff) + 4);
    } while ((int)(uint)uVar1 < param_2);
  }
  else {
    do {
      uVar1 = *puVar3;
      uVar2 = puVar3[1];
      if (param_2 < (int)((uint)uVar1 - (uVar2 & 0x7fff))) {
        return 0;
      }
      if (param_2 <= (int)(uint)uVar1) {
        if (param_4 != (uint *)0x0) {
          *param_4 = (uint)puVar3[(param_2 - (uint)uVar1) + 2];
        }
        return 1;
      }
      if ((uVar2 & 0x8000) != 0) {
        return 0;
      }
      puVar3 = puVar3 + (uVar2 & 0x7fff) + 2;
    } while ((int)(uint)uVar1 < param_2);
  }
  return 0;
}

