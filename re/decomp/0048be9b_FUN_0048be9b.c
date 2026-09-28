// FUN_0048be9b @ 0048be9b size=248 sig=undefined FUN_0048be9b() cc=unknown
// callers: FUN_0048bf93
// callees: FUN_0048f774,FUN_0048bb80,FUN_00498ba9

undefined4 FUN_0048be9b(int *param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_4 == 0) {
    param_4 = DAT_0065e5a8;
  }
  FUN_0048f774(param_1,0xb0,0);
  param_1[1] = param_2;
  param_1[2] = param_3;
  param_1[3] = param_4;
  *(undefined2 *)((int)param_1 + 0x2a) = 2;
  FUN_0048bb80(param_1,0);
  if (param_4 == -1) {
    uVar1 = 1;
  }
  else {
    if (param_4 == 0x10) {
      if (DAT_0065e590 == 0x10) {
        if (((DAT_0065e594 == 0xf800) && (DAT_0065e598 == 0x7e0)) && (DAT_0065e59c == 0x1f)) {
          *(undefined2 *)((int)param_1 + 0x26) = 3;
        }
        else {
          *(undefined2 *)((int)param_1 + 0x26) = 2;
        }
      }
      else {
        *(undefined2 *)((int)param_1 + 0x26) = 2;
      }
    }
    else if (param_4 == 0x18) {
      *(undefined2 *)((int)param_1 + 0x26) = 4;
    }
    else if (param_4 == 0x20) {
      *(undefined2 *)((int)param_1 + 0x26) = 4;
    }
    else {
      *(undefined2 *)((int)param_1 + 0x26) = 1;
    }
    param_1[4] = (param_4 + 7 >> 3) * param_2;
    param_1[4] = param_1[4] + (4 - (param_1[4] & 3U) & 3);
    iVar2 = FUN_00498ba9(param_1[2] * param_1[4]);
    *param_1 = iVar2;
    if (iVar2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}

