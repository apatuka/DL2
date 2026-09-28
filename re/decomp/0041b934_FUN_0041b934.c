// FUN_0041b934 @ 0041b934 size=208 sig=undefined FUN_0041b934() cc=unknown
// callers: FUN_00421340,FUN_0041e26c,FUN_0041e0a8,FUN_004213fc
// callees: 

undefined4 FUN_0041b934(int param_1,int param_2,undefined4 *param_3,int *param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  if ((((param_2 < 0x144) || (0x198 < param_2)) || (param_1 < 0x66)) || (299 < param_1)) {
    uVar2 = 0;
  }
  else {
    if (param_2 < 0x15a) {
      iVar3 = 0xc;
      *param_3 = 0;
    }
    else if (param_2 < 0x16f) {
      *param_3 = 1;
      iVar3 = 0xd;
    }
    else if (param_2 < 0x184) {
      *param_3 = 2;
      iVar3 = 0xd;
    }
    else {
      if (0x198 < param_2) {
        return 0;
      }
      *param_3 = 3;
      iVar3 = 0xc;
    }
    *param_4 = -1;
    iVar1 = 0;
    if (iVar3 != 0) {
      do {
        if ((iVar1 * 0x17 + 0x66 <= param_1) && (param_1 <= iVar1 * 0x17 + 0x7d)) {
          *param_4 = iVar1;
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < iVar3);
    }
    if (*param_4 + 1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = CONCAT31((int3)((uint)(*param_4 + 1) >> 8),1);
    }
  }
  return uVar2;
}

