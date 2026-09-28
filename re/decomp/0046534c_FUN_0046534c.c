// FUN_0046534c @ 0046534c size=298 sig=undefined FUN_0046534c() cc=unknown
// callers: FUN_004655b0,FUN_00465070,FUN_00457bec,FUN_00465540
// callees: thunk_FUN_0045792c,PatBlt,GetStockObject,SelectObject

void FUN_0046534c(HDC param_1,HGDIOBJ param_2,int *param_3,int param_4,int param_5)

{
  HGDIOBJ pvVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  HGDIOBJ local_8;
  
  if (DAT_004d1f58 == 0) {
    pvVar1 = GetStockObject(1);
    pvVar1 = SelectObject(param_1,pvVar1);
    PatBlt(param_1,*param_3,param_3[1],(param_3[2] - *param_3) + 1,(param_3[3] - param_3[1]) + 1,
           0xf00021);
    SelectObject(param_1,pvVar1);
  }
  else {
    local_8 = SelectObject(DAT_0058f1b0,param_2);
    for (iVar4 = param_3[1]; iVar4 < param_3[3]; iVar4 = iVar4 + local_14) {
      local_18 = iVar4 % param_5;
      local_14 = param_5 - iVar4 % param_5;
      local_1c = param_3[3] - iVar4;
      if (local_14 < param_3[3] - iVar4) {
        piVar2 = &local_14;
      }
      else {
        piVar2 = &local_1c;
      }
      local_c = *piVar2;
      for (iVar3 = *param_3; iVar3 < param_3[2]; iVar3 = iVar3 + local_10) {
        local_10 = param_4 - iVar3 % param_4;
        local_20 = param_3[2] - iVar3;
        if (local_10 < param_3[2] - iVar3) {
          piVar2 = &local_10;
        }
        else {
          piVar2 = &local_20;
        }
        thunk_FUN_0045792c(param_1,iVar3,iVar4,*piVar2,local_c,DAT_0058f1b0,iVar3 % param_4,local_18
                           ,0xcc0020);
      }
    }
    SelectObject(DAT_0058f1b0,local_8);
  }
  return;
}

