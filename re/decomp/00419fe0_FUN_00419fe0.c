// FUN_00419fe0 @ 00419fe0 size=363 sig=undefined FUN_00419fe0() cc=unknown
// callers: FUN_0041a204,FUN_0041a470,FUN_0041a518
// callees: FUN_00419c88,FUN_00418d18

undefined4 FUN_00419fe0(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  uVar1 = FUN_00419c88(param_1,param_2,&local_8,&local_c);
  if ((char)uVar1 != '\0') {
    DAT_004b76c0 = local_8 + DAT_005332bc;
    DAT_004b76c4 = local_c;
    if (((param_3 == 0) ||
        (*(int *)((int)&DAT_005332d8 + local_c * 0x20 + (local_8 + DAT_005332bc) * 0x146) == 0)) ||
       ((DAT_004d5aa0 == '\0' &&
        (*(char *)(*(int *)((int)&DAT_005332dc + local_c * 0x20 + (local_8 + DAT_005332bc) * 0x146)
                  + 8) != DAT_0058f1f4)))) {
      uVar1 = 0;
    }
    else {
      if (param_3 == 2) {
        iVar3 = local_8 + DAT_005332bc;
        iVar2 = local_c * 0x20;
        if (*(int *)((int)&DAT_005332d8 + iVar2 + iVar3 * 0x146) == 1) {
          *(undefined4 *)((int)&DAT_005332d8 + iVar2 + iVar3 * 0x146) = 2;
        }
        else if (*(int *)((int)&DAT_005332d8 + iVar2 + iVar3 * 0x146) == 2) {
          *(undefined4 *)((int)&DAT_005332d8 + iVar2 + iVar3 * 0x146) = 1;
        }
      }
      else if (param_3 == 1) {
        *(undefined4 *)((int)&DAT_005332d8 + local_c * 0x20 + (local_8 + DAT_005332bc) * 0x146) = 1;
      }
      FUN_00418d18();
    }
  }
  return uVar1;
}

