// FUN_0048dfdf @ 0048dfdf size=28 sig=undefined FUN_0048dfdf() cc=unknown
// callers: 
// callees: FUN_0048dc0d,GetKeyState

undefined4 FUN_0048dfdf(void)

{
  ushort uVar1;
  undefined2 extraout_var;
  undefined4 uVar2;
  
  FUN_0048dc0d();
  uVar1 = GetKeyState(0x11);
  if ((uVar1 & 0x8000) == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = CONCAT31((int3)(CONCAT22(extraout_var,uVar1) >> 8),1);
  }
  return uVar2;
}

