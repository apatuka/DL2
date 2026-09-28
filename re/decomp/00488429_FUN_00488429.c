// FUN_00488429 @ 00488429 size=155 sig=undefined FUN_00488429() cc=unknown
// callers: FUN_0043febc,FUN_0043ee90,FUN_0043f858,FUN_0047e0e8
// callees: 

void FUN_00488429(int param_1,int param_2,uint param_3,undefined1 param_4)

{
  int iVar1;
  uint uVar2;
  undefined1 *puVar3;
  
  if ((DAT_00559de8 <= param_1) && (param_1 < DAT_00559df0)) {
    iVar1 = (&DAT_006552cc)[param_1];
    if (iVar1 <= param_2) {
      param_3 = ((param_3 - param_2) + iVar1) - 1;
      if ((int)param_3 < 0) {
        return;
      }
      param_2 = iVar1 + -1;
    }
    param_2 = param_2 - param_3;
    if (param_2 < DAT_00559dec) {
      param_3 = (param_3 - DAT_00559dec) + param_2;
      param_2 = DAT_00559dec;
    }
    if (-1 < (int)param_3) {
      (&DAT_006552cc)[param_1] = param_2;
      iVar1 = DAT_00583e14;
      puVar3 = (undefined1 *)(*(int *)(DAT_00583e08 + param_2 * 4) + param_1 + DAT_00583e04);
      uVar2 = param_3 >> 1;
      if ((param_3 & 1) == 0) {
        *puVar3 = param_4;
        if (uVar2 == 0) {
          return;
        }
        puVar3 = puVar3 + iVar1;
      }
      do {
        *puVar3 = param_4;
        puVar3[iVar1] = param_4;
        puVar3 = puVar3 + iVar1 * 2;
        uVar2 = uVar2 - 1;
      } while (-1 < (int)uVar2);
    }
  }
  return;
}

