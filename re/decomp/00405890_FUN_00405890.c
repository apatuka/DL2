// FUN_00405890 @ 00405890 size=78 sig=undefined FUN_00405890() cc=unknown
// callers: FUN_004058e0
// callees: 

undefined4 FUN_00405890(int *param_1,int *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (((*param_2 == *param_1) || (*param_1 == -1)) || (*param_2 == -1)) {
    iVar2 = 0;
    param_2 = param_2 + 7;
    param_1 = param_1 + 7;
    do {
      if (((*param_2 != *param_1) && (*param_1 != -1)) && (*param_2 != -1)) {
        return 0;
      }
      iVar2 = iVar2 + 1;
      param_2 = param_2 + 1;
      param_1 = param_1 + 1;
    } while (iVar2 < 10);
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

