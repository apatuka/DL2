// FUN_00482320 @ 00482320 size=420 sig=undefined FUN_00482320() cc=unknown
// callers: FUN_00449f5c,FUN_00443830,FUN_00427198,FUN_0043ae78,FUN_00414b10
// callees: FUN_00481da0,BlitSprite8,FUN_0049a93f,FUN_0049aa64,InvalidateRect,FUN_00463d00,FUN_0049a8ed

void FUN_00482320(void)

{
  int iVar1;
  int iVar2;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  if (DAT_004d59b4 == 0x4a) {
    iVar1 = DAT_004b7d54 - DAT_004b7d4c;
    iVar2 = DAT_004b7d50 - DAT_004b7d48;
    FUN_0049a8ed();
    FUN_00463d00(DAT_004b7d4c,DAT_004b7d48,iVar1,iVar2);
    if (DAT_0058f1e0 != 0) {
      BlitSprite8(DAT_0058f1e0,DAT_004b7d4c,DAT_004b7d48,iVar1,iVar2,iVar1,1);
    }
    FUN_00481da0(DAT_004b7d4c,DAT_004b7d48,DAT_00657dec,DAT_00657df0,3,DAT_0058f1e0 == 0);
    FUN_0049a93f();
  }
  else if (DAT_004d5acc == 0) {
    local_14 = DAT_004c547c;
    local_18 = DAT_004c5478;
    local_10 = DAT_004c5478 + DAT_004c5480;
    local_c = DAT_004c547c + DAT_004c5484;
    FUN_0049a8ed();
    iVar1 = FUN_0049aa64(&local_18);
    if (iVar1 != 0) {
      FUN_00463d00(DAT_0065e580,DAT_0065e584,DAT_0065e588 - DAT_0065e580,DAT_0065e58c - DAT_0065e584
                  );
      if (DAT_0058f1e0 != 0) {
        BlitSprite8(DAT_0058f1e0,local_18,local_14,local_10 - local_18,local_c - local_14,
                    local_10 - local_18,1);
      }
      FUN_00481da0(DAT_004c5478,DAT_004c547c,DAT_00657dec,DAT_00657df0,DAT_004dce1c,
                   DAT_0058f1e0 == 0);
      if (DAT_004d5974 != (HWND)0x0) {
        InvalidateRect(DAT_004d5974,(RECT *)&DAT_0065e580,0);
      }
    }
    FUN_0049a93f();
  }
  return;
}

