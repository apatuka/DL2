// FUN_0048e4c1 @ 0048e4c1 size=48 sig=undefined FUN_0048e4c1() cc=unknown
// callers: FUN_004a5b30
// callees: FUN_0048dc0d,GetKeyState

byte FUN_0048e4c1(void)

{
  ushort uVar1;
  byte bVar2;
  
  FUN_0048dc0d();
  uVar1 = GetKeyState(1);
  bVar2 = (uVar1 & 0x8000) != 0;
  uVar1 = GetKeyState(2);
  if ((uVar1 & 0x8000) != 0) {
    bVar2 = bVar2 | 2;
  }
  return bVar2;
}

