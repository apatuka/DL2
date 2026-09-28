// FUN_0043e0dc @ 0043e0dc size=83 sig=undefined FUN_0043e0dc() cc=unknown
// callers: CheckViewCombat
// callees: FUN_00445270,InvalidateRect,FUN_00463da8,FUN_004570e0,FUN_00480150,FUN_004450e0,FUN_004879fc,FUN_00457048,FUN_004451cc,FUN_0043da54

void FUN_0043e0dc(void)

{
  int iVar1;
  
  iVar1 = FUN_00457048();
  if (iVar1 == 0) {
    FUN_004450e0();
    FUN_00463da8(1);
    FUN_004451cc();
    while( true ) {
      iVar1 = FUN_00457048();
      if (iVar1 != 0) break;
      FUN_004570e0();
    }
    FUN_0043da54();
    FUN_00445270(1);
    FUN_00480150();
    InvalidateRect(DAT_004d5974,(RECT *)&DAT_00561a20,0);
    FUN_004879fc();
  }
  return;
}

