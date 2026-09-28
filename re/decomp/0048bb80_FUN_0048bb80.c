// FUN_0048bb80 @ 0048bb80 size=59 sig=undefined FUN_0048bb80() cc=unknown
// callers: FUN_00494449,FUN_0048bf93,CYGame_InitDirectDraw,FUN_0048be9b,FUN_0048bc0d
// callees: 

void FUN_0048bb80(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (param_1 != 0) {
    if (param_2 == (undefined4 *)0x0) {
      *(undefined4 *)(param_1 + 0x30) = 0;
      *(undefined4 *)(param_1 + 0x2c) = 0;
      *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 4);
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 8);
    }
    else {
      puVar2 = (undefined4 *)(param_1 + 0x2c);
      for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar2 = *param_2;
        param_2 = param_2 + 1;
        puVar2 = puVar2 + 1;
      }
    }
  }
  return;
}

