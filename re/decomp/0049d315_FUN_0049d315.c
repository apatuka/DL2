// FUN_0049d315 @ 0049d315 size=346 sig=undefined FUN_0049d315() cc=unknown
// callers: FUN_004a3533
// callees: FUN_0049117e,strlen,FUN_00498ba9,FUN_0049d105,FUN_0048f774,FUN_0049d1dd,FUN_004989cf,FUN_004a6964

int * FUN_0049d315(int param_1,undefined4 param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  undefined1 local_28 [4];
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_10;
  int local_c;
  int local_8;
  
  iVar2 = 0;
  local_8 = 0;
  FUN_0048f774(local_28,0x18,0);
  while (piVar1 = param_3, *piVar1 != 0x18) {
    param_3 = piVar1 + 1;
    switch(*piVar1) {
    case 1:
      if (iVar2 != 0) {
        FUN_004989cf(iVar2);
      }
      iVar2 = strlen(local_c);
      iVar2 = FUN_00498ba9(iVar2 + 1);
      if (iVar2 != 0) {
        FUN_004a6964(iVar2,*param_3);
      }
      param_3 = piVar1 + 2;
      break;
    case 7:
      if (iVar2 != 0) {
        FUN_004989cf(iVar2);
      }
      iVar2 = 0;
      if ((*(int *)(param_1 + 0x54) != 0) &&
         (local_c = FUN_0049117e(*(undefined4 *)(param_1 + 0x54),0,*param_3), local_c != 0)) {
        iVar2 = strlen(local_c);
        iVar2 = FUN_00498ba9(iVar2 + 1);
        if (iVar2 != 0) {
          FUN_004a6964(iVar2,local_c);
        }
      }
      param_3 = piVar1 + 2;
      break;
    case 0xc:
      local_24 = *param_3;
      param_3 = piVar1 + 2;
      break;
    case 0xd:
      local_20 = *param_3;
      param_3 = piVar1 + 2;
      break;
    case 0x11:
      local_8 = *param_3;
      param_3 = piVar1 + 2;
      break;
    case 0x19:
      local_1c = *param_3;
      param_3 = piVar1 + 2;
      break;
    case 0x1a:
      local_18 = *param_3;
      param_3 = piVar1 + 2;
    }
  }
  local_10 = FUN_0049d105(param_1,param_2,0xffffffff);
  if (local_10 != 0) {
    FUN_0049d1dd(param_1,param_2,local_10 + -1,0,iVar2);
    FUN_0049d1dd(param_1,param_2,local_10 + -1,1,local_28);
    FUN_0049d1dd(param_1,param_2,local_10 + -1,2,local_8);
  }
  if (iVar2 != 0) {
    FUN_004989cf(iVar2);
  }
  return piVar1 + 1;
}

