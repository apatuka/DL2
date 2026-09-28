// FUN_0041e440 @ 0041e440 size=84 sig=undefined FUN_0041e440() cc=unknown
// callers: FUN_0044aa64,FUN_0044ab7c
// callees: FUN_0041c378,FUN_0041e0a8,GetKeyState,FUN_0041b908,FUN_0041c36c

void FUN_0041e440(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  ushort uVar2;
  
  uVar1 = GetKeyState(0x10);
  uVar2 = GetKeyState(0x11);
  if (((uVar1 & 0x8000) == 0) && ((uVar2 & 0x8000) == 0)) {
    FUN_0041b908();
    FUN_0041e0a8(param_1,param_2);
    FUN_0041c378();
    FUN_0041c36c();
  }
  return;
}

