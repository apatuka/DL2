// FUN_0043e058 @ 0043e058 size=95 sig=undefined FUN_0043e058() cc=unknown
// callers: FUN_0044a3b0
// callees: FUN_00445270,InvalidateRect,FUN_00463da8,FUN_004570e0,FUN_00480150,FUN_004450e0,FUN_004879fc,FUN_00457048,FUN_004451cc

void FUN_0043e058(void)

{
  int iVar1;
  
  iVar1 = FUN_00457048();
  if (iVar1 == 0) {
    FUN_004450e0();
    FUN_00463da8(1);
    FUN_004451cc();
    DAT_00559dd0 = DAT_00559dd0 + 1;
    if (DAT_004c4954 <= DAT_00559dd0) {
      FUN_004570e0();
      DAT_00559dd0 = 0;
    }
    FUN_00445270(1);
    FUN_00480150();
    InvalidateRect(DAT_004d5974,(RECT *)&DAT_00561a20,0);
    FUN_004879fc();
  }
  return;
}

