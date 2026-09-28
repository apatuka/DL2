// FUN_004884c4 @ 004884c4 size=161 sig=undefined FUN_004884c4() cc=unknown
// callers: FUN_0047e0e8
// callees: 

void FUN_004884c4(int param_1,int param_2,uint param_3,undefined2 param_4)

{
  int iVar1;
  uint uVar2;
  undefined2 *puVar3;
  
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
      puVar3 = (undefined2 *)(*(int *)(DAT_00583e08 + param_2 * 4) + param_1 * 2 + DAT_00583e04);
      uVar2 = param_3 >> 1;
      if ((param_3 & 1) == 0) {
        *puVar3 = param_4;
        if (uVar2 == 0) {
          return;
        }
        puVar3 = (undefined2 *)((int)puVar3 + iVar1);
      }
      do {
        *puVar3 = param_4;
        *(undefined2 *)((int)puVar3 + iVar1) = param_4;
        puVar3 = puVar3 + iVar1;
        uVar2 = uVar2 - 1;
      } while (-1 < (int)uVar2);
    }
  }
  return;
}

