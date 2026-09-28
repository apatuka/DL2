// FUN_0048dfa7 @ 0048dfa7 size=28 sig=undefined FUN_0048dfa7() cc=unknown
// callers: FUN_0049e007
// callees: FUN_0048dc0d,GetKeyState

undefined4 FUN_0048dfa7(void)

{
  ushort uVar1;
  undefined2 extraout_var;
  undefined4 uVar2;
  
  FUN_0048dc0d();
  uVar1 = GetKeyState(0x10);
  if ((uVar1 & 0x8000) == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = CONCAT31((int3)(CONCAT22(extraout_var,uVar1) >> 8),1);
  }
  return uVar2;
}

