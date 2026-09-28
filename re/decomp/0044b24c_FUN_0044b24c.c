// FUN_0044b24c @ 0044b24c size=130 sig=undefined FUN_0044b24c() cc=unknown
// callers: @BackWndProc$qqspvuiuil
// callees: FUN_0044b224,FUN_00449cc4,FUN_0044a92c,FUN_0044930c,FUN_0044b1fc

void FUN_0044b24c(undefined4 param_1,uint param_2)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar1 = FUN_0044930c();
  if ((iVar1 == 0) &&
     (iVar1 = FUN_00449cc4(param_2 & 0xffff,param_2 >> 0x10,&local_8,&local_c), iVar1 != -1)) {
    if (iVar1 == 0) {
      FUN_0044a92c(local_8,local_c,param_1);
    }
    else if (iVar1 == 1) {
      FUN_0044b1fc(local_8,local_c);
    }
    else if (iVar1 - 0xdU < 3) {
      FUN_0044b224(local_8,local_c);
    }
  }
  return;
}

