// FUN_0044b168 @ 0044b168 size=145 sig=undefined FUN_0044b168() cc=unknown
// callers: @BackWndProc$qqspvuiuil
// callees: FUN_0044a8bc,FUN_0044b0a4,FUN_00449cc4,FUN_0044930c,FUN_0044b034

void FUN_0044b168(undefined4 param_1,uint param_2)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar1 = FUN_0044930c();
  if ((iVar1 == 0) &&
     (iVar1 = FUN_00449cc4(param_2 & 0xffff,param_2 >> 0x10,&local_8,&local_c), iVar1 != -1)) {
    if (iVar1 < 8) {
      if (iVar1 == 0) {
        FUN_0044a8bc(local_8,local_c);
      }
      else if (iVar1 == 1) {
        FUN_0044b034(local_8,local_c);
      }
    }
    else if ((3 < iVar1 - 8U) && (iVar1 - 0xdU < 3)) {
      FUN_0044b0a4(param_2 & 0xffff,param_2 >> 0x10);
    }
  }
  DAT_004c5bc9 = 0;
  return;
}

