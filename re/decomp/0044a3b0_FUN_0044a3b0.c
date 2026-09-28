// FUN_0044a3b0 @ 0044a3b0 size=196 sig=undefined FUN_0044a3b0() cc=unknown
// callers: @BackWndProc$qqspvuiuil
// callees: FUN_0044a328,FUN_0045f028,FUN_0044a358,FUN_0043e058,FUN_0045f17c,FUN_004590d4,FUN_00418e00,FUN_0048796c,FUN_00472e04

void FUN_0044a3b0(void)

{
  char cVar1;
  int iVar2;
  
  FUN_00472e04();
  if (DAT_004c5b68 == 0) {
    iVar2 = FUN_0048796c();
    if (iVar2 == 0) {
      if (DAT_004d59b4 < 4) {
        if (DAT_004d59b4 != 3) {
          if (DAT_004d59b4 != 0) {
            if (DAT_004d59b4 != 1) {
              if (DAT_004d59b4 != 2) {
                return;
              }
              if (DAT_00559dc0 == 0) {
                FUN_0043e058();
              }
              FUN_0045f028();
              return;
            }
            if (DAT_005644d4 != 0) {
              FUN_0045f028();
              iVar2 = FUN_004590d4();
              if (iVar2 == 0) {
                FUN_0045f17c();
              }
            }
          }
          FUN_0045f028();
          FUN_0044a358();
          return;
        }
        FUN_0044a328();
      }
      else {
        if (DAT_004d59b4 == 7) {
          FUN_0045f028();
          return;
        }
        if (DAT_004d59b4 != 0x22) {
          return;
        }
        cVar1 = FUN_00418e00();
        if (cVar1 != '\0') {
          FUN_0044a358();
          return;
        }
        if ((DAT_005332b0 == '\0') && (DAT_005644d4 != 0)) {
          FUN_0045f028();
          iVar2 = FUN_004590d4();
          if (iVar2 == 0) {
            FUN_0045f17c();
            return;
          }
        }
      }
    }
  }
  return;
}

