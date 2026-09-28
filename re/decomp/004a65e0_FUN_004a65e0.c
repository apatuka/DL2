// FUN_004a65e0 @ 004a65e0 size=451 sig=undefined FUN_004a65e0() cc=unknown
// callers: 
// callees: FUN_00498ba9,FUN_0048f8e8,FUN_004989cf,FUN_0048f992,FUN_0048f7f1,FUN_0048fade,FUN_0048fa92,FUN_0048fbbf

int FUN_004a65e0(undefined4 param_1,undefined4 param_2,int *param_3,undefined4 *param_4,int *param_5
                )

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  short local_20;
  ushort local_1e;
  undefined2 local_14;
  ushort local_12;
  ushort local_e;
  int local_c;
  int local_8;
  
  iVar5 = 0;
  *param_3 = 0;
  iVar1 = FUN_0048f8e8(param_1,param_2);
  if (iVar1 == 0) {
    return 0;
  }
  iVar2 = FUN_0048f992(iVar1,&local_c,8);
  if (iVar2 == 8) {
    if (local_c != 0x46464952) {
      return iVar1;
    }
    iVar2 = FUN_0048f992(iVar1,&local_c,4);
    if (iVar2 == 4) {
      if (local_c != 0x45564157) {
        return iVar1;
      }
      while (iVar2 = FUN_0048f992(iVar1,&local_c,8), iVar2 == 8) {
        if (local_c == 0x20746d66) {
          iVar2 = FUN_0048f992(iVar1,&local_20,0x10);
          if (iVar2 != 0x10) break;
          if (local_20 == 1) {
            local_e = 0;
            iVar2 = (uint)local_12 * (uint)local_1e;
            if (iVar2 < 0) {
              iVar2 = iVar2 + 7;
            }
            local_14 = (undefined2)(iVar2 >> 3);
          }
          else {
            iVar2 = FUN_0048f992(iVar1,&local_e,2);
            if (iVar2 != 2) break;
          }
          iVar2 = FUN_00498ba9(local_e + 0x12);
          *param_3 = iVar2;
          if (iVar2 == 0) break;
          FUN_0048f7f1(&local_20,*param_3,0x10);
          *(ushort *)(*param_3 + 0x10) = local_e;
          if (((local_e != 0) &&
              (uVar3 = FUN_0048f992(iVar1,*param_3 + 0x12,local_e), uVar3 != local_e)) ||
             ((local_8 != local_e + 0x10 &&
              (iVar2 = FUN_0048fade(iVar1,local_8 - (local_e + 0x10),1), iVar2 < 0)))) break;
          iVar5 = iVar5 + 1;
        }
        else if (local_c == 0x61746164) {
          uVar4 = FUN_0048fa92(iVar1);
          *param_4 = uVar4;
          *param_5 = local_8;
          iVar5 = iVar5 + 1;
        }
        else {
          iVar2 = FUN_0048fade(iVar1,local_8,1);
          if (iVar2 < 0) break;
        }
        if (1 < iVar5) {
          return iVar1;
        }
      }
    }
  }
  if (*param_3 != 0) {
    FUN_004989cf(*param_3);
  }
  *param_3 = 0;
  FUN_0048fbbf(iVar1,0);
  return 0;
}

