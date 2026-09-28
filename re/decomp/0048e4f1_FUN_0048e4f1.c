// FUN_0048e4f1 @ 0048e4f1 size=43 sig=undefined FUN_0048e4f1() cc=unknown
// callers: 
// callees: FUN_0048dc0d,GetKeyState

undefined4 FUN_0048e4f1(void)

{
  ushort uVar1;
  
  FUN_0048dc0d();
  uVar1 = GetKeyState(1);
  if (((uVar1 & 0x8000) == 0) && (uVar1 = GetKeyState(2), (uVar1 & 0x8000) == 0)) {
    return 0;
  }
  return 1;
}

