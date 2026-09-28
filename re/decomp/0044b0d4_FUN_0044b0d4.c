// FUN_0044b0d4 @ 0044b0d4 size=145 sig=undefined FUN_0044b0d4() cc=unknown
// callers: @BackWndProc$qqspvuiuil
// callees: FUN_0044b058,FUN_0044a838,FUN_00449cc4,FUN_0044930c,FUN_0044b078

void FUN_0044b0d4(undefined4 param_1,uint param_2)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar1 = FUN_0044930c();
  if (iVar1 == 0) {
    DAT_004c5bc9 = 0;
    iVar1 = FUN_00449cc4(param_2 & 0xffff,param_2 >> 0x10,&local_8,&local_c);
    if (iVar1 != -1) {
      if (iVar1 < 8) {
        if (iVar1 == 0) {
          FUN_0044a838(local_8,local_c);
        }
        else if (iVar1 == 1) {
          FUN_0044b058(local_8,local_c);
        }
      }
      else if ((3 < iVar1 - 8U) && (iVar1 - 0xdU < 3)) {
        FUN_0044b078(param_2 & 0xffff,param_2 >> 0x10);
      }
    }
  }
  return;
}

