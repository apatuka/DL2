// FUN_00419c88 @ 00419c88 size=268 sig=undefined FUN_00419c88() cc=unknown
// callers: FUN_0041a204,FUN_00419fe0,FUN_0041a470,FUN_0041a5dc,FUN_0041a14c,FUN_0041a518
// callees: 

undefined8 FUN_00419c88(int param_1,int param_2,int *param_3,int *param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((((0x16e < param_2) && (param_2 < 0x1df)) && (0x6a < param_1)) && (param_1 < 0x1d4)) {
    *param_3 = -1;
    iVar1 = 0;
    do {
      if ((iVar1 * 0x25 + 0x16f <= param_2) && (param_2 <= iVar1 * 0x25 + 0x194)) {
        *param_3 = iVar1;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 3);
    *param_4 = -1;
    iVar1 = 0;
    do {
      if ((iVar1 * 0x24 + 0x6b <= param_1) && (param_1 <= iVar1 * 0x24 + 0x8f)) {
        *param_4 = iVar1;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 10);
    param_1 = *param_4 + 1;
    if ((param_1 != 0) && (*param_3 != -1)) {
      param_1 = *param_3 + DAT_005332bc;
      iVar1 = *(int *)((int)&DAT_005332d8 + *param_4 * 0x20 + param_1 * 0x146);
      if ((iVar1 == 1) ||
         (param_1 = (int)&DAT_005332d8 + (*param_3 + DAT_005332bc) * 0x146, iVar1 == 2)) {
        uVar2 = CONCAT31((int3)((uint)iVar1 >> 8),1);
        goto LAB_00419d8d;
      }
    }
  }
  uVar2 = 0;
LAB_00419d8d:
  return CONCAT44(param_1,uVar2);
}

