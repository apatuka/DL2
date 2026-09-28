// FUN_0049fa76 @ 0049fa76 size=499 sig=undefined FUN_0049fa76() cc=unknown
// callers: FUN_0049d7f4,FUN_0049fe03
// callees: 

void FUN_0049fa76(int *param_1,int *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar1 = param_2[2] - *param_2;
  iVar2 = param_2[3] - param_2[1];
  if (param_3 < 0x28001) {
    if (param_3 == 0x28000) {
      param_2[1] = param_1[3] - iVar2;
      param_2[3] = iVar2 + param_2[1];
      *param_2 = param_1[2] - iVar1;
      param_2[2] = iVar1 + *param_2;
    }
    else if (param_3 < 0x10001) {
      if (param_3 == 0x10000) {
        param_2[1] = param_1[1];
        param_2[3] = iVar2 + param_2[1];
        uVar3 = (param_1[2] - *param_1) - iVar1;
        iVar2 = (int)uVar3 >> 1;
        if (iVar2 < 0) {
          iVar2 = iVar2 + (uint)((uVar3 & 1) != 0);
        }
        *param_2 = iVar2 + *param_1;
        param_2[2] = iVar1 + *param_2;
      }
      else if (param_3 == 0) {
        for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
          *param_2 = *param_1;
          param_1 = param_1 + 1;
          param_2 = param_2 + 1;
        }
      }
      else if (param_3 == 0x8000) {
        param_2[1] = param_1[1];
        *param_2 = *param_1;
        param_2[2] = iVar1 + *param_2;
        param_2[3] = iVar2 + param_2[1];
      }
    }
    else if (param_3 == 0x18000) {
      param_2[1] = param_1[1];
      param_2[3] = iVar2 + param_2[1];
      *param_2 = param_1[2] - iVar1;
      param_2[2] = iVar1 + *param_2;
    }
    else if (param_3 == 0x20000) {
      uVar3 = (param_1[3] - param_1[1]) - iVar2;
      iVar4 = (int)uVar3 >> 1;
      if (iVar4 < 0) {
        iVar4 = iVar4 + (uint)((uVar3 & 1) != 0);
      }
      param_2[1] = iVar4 + param_1[1];
      param_2[3] = iVar2 + param_2[1];
      *param_2 = param_1[2] - iVar1;
      param_2[2] = iVar1 + *param_2;
    }
  }
  else if (param_3 == 0x30000) {
    param_2[1] = param_1[3] - iVar2;
    param_2[3] = iVar2 + param_2[1];
    uVar3 = (param_1[2] - *param_1) - iVar1;
    iVar2 = (int)uVar3 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar3 & 1) != 0);
    }
    *param_2 = iVar2 + *param_1;
    param_2[2] = iVar1 + *param_2;
  }
  else if (param_3 == 0x38000) {
    param_2[1] = param_1[3] - iVar2;
    param_2[3] = iVar2 + param_2[1];
    *param_2 = *param_1;
    param_2[2] = iVar1 + *param_2;
  }
  else if (param_3 == 0x400000) {
    uVar3 = (param_1[3] - param_1[1]) - iVar2;
    iVar4 = (int)uVar3 >> 1;
    if (iVar4 < 0) {
      iVar4 = iVar4 + (uint)((uVar3 & 1) != 0);
    }
    param_2[1] = iVar4 + param_1[1];
    param_2[3] = iVar2 + param_2[1];
    *param_2 = *param_1;
    param_2[2] = iVar1 + *param_2;
  }
  else if (param_3 == 0x408000) {
    uVar3 = (param_1[3] - param_1[1]) - iVar2;
    iVar4 = (int)uVar3 >> 1;
    if (iVar4 < 0) {
      iVar4 = iVar4 + (uint)((uVar3 & 1) != 0);
    }
    param_2[1] = iVar4 + param_1[1];
    param_2[3] = iVar2 + param_2[1];
    uVar3 = (param_1[2] - *param_1) - iVar1;
    iVar2 = (int)uVar3 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar3 & 1) != 0);
    }
    *param_2 = iVar2 + *param_1;
    param_2[2] = iVar1 + *param_2;
  }
  return;
}

