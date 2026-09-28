// FUN_0044ad14 @ 0044ad14 size=252 sig=undefined FUN_0044ad14() cc=unknown
// callers: @BackWndProc$qqspvuiuil
// callees: FUN_0044a9b8,FUN_0044abe8,FUN_0044ab7c,FUN_0044ab00,FUN_00449cc4,FUN_004590d4,FUN_0044930c,FUN_004590a8,FUN_0044a7c8,FUN_0044aa64

void FUN_0044ad14(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 local_c;
  undefined4 local_8;
  
  uVar2 = param_2 & 0xffff;
  param_2 = param_2 >> 0x10;
  iVar1 = FUN_0044930c();
  if (iVar1 == 0) {
    iVar1 = FUN_004590d4();
    if (iVar1 == 0) {
      iVar1 = FUN_00449cc4(uVar2,param_2,&local_8,&local_c);
      if (iVar1 != -1) {
        if (iVar1 < 8) {
          if (iVar1 == 0) {
            FUN_0044a7c8(local_8,local_c);
          }
          else if (iVar1 == 1) {
            FUN_0044a9b8(local_8,local_c);
          }
          else if (iVar1 - 2U < 6) {
            FUN_0044ab7c(uVar2,param_2,local_8,local_c,param_1,iVar1);
          }
        }
        else if (iVar1 - 8U < 4) {
          FUN_0044aa64(uVar2,param_2,local_8,local_c,param_1,iVar1);
        }
        else if (iVar1 - 0xdU < 3) {
          FUN_0044abe8(uVar2,param_2);
        }
        else if (iVar1 - 0x10U < 0x18) {
          FUN_0044ab00(uVar2,param_2,local_8,local_c,param_1,iVar1);
        }
      }
    }
    else if (DAT_004d1c7c == '\0') {
      FUN_004590a8(uVar2,param_2);
    }
  }
  return;
}

