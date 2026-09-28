// FUN_004217a0 @ 004217a0 size=84 sig=undefined FUN_004217a0() cc=unknown
// callers: FUN_0044ab00,FUN_0044aa64
// callees: FUN_0041ff24,FUN_0041ff18,GetKeyState,FUN_00421340,FUN_0041b908

void FUN_004217a0(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  ushort uVar2;
  
  uVar1 = GetKeyState(0x10);
  uVar2 = GetKeyState(0x11);
  if (((uVar1 & 0x8000) == 0) && ((uVar2 & 0x8000) == 0)) {
    FUN_0041b908();
    FUN_00421340(param_1,param_2);
    FUN_0041ff24();
    FUN_0041ff18();
  }
  return;
}

