// FUN_0042f0c4 @ 0042f0c4 size=173 sig=undefined FUN_0042f0c4() cc=unknown
// callers: FUN_004618e8,FUN_0043611c,FUN_00423960
// callees: FUN_0042ed64,FUN_0042ed70,FUN_0042ee18,GetTickCount,FUN_0042f04c,FUN_0042edc4,FUN_0042eff4,UpdateWindow

void FUN_0042f0c4(undefined4 param_1,char param_2)

{
  int iVar1;
  DWORD DVar2;
  DWORD unaff_ESI;
  
  DAT_004c3814 = param_2;
  iVar1 = FUN_0042ee18(param_1);
  if (iVar1 != 0) {
    FUN_0042ed70();
    FUN_0042ed64();
    UpdateWindow(DAT_004d5974);
    if (DAT_004c3814 != '\0') {
      DAT_004c3818 = 0;
      unaff_ESI = GetTickCount();
    }
    do {
      iVar1 = FUN_0042f04c();
      if ((DAT_004c3814 != '\0') && (DVar2 = GetTickCount(), 0x299 < (int)(DVar2 - unaff_ESI))) {
        DAT_004c3818 = DAT_004c3818 + 1;
        if (0x93 < DAT_004c3818) {
          DAT_004c3818 = 0;
        }
        DAT_00557cd0 = FUN_0042edc4();
        FUN_0042ed70();
        unaff_ESI = DVar2;
      }
    } while (iVar1 == 0);
    FUN_0042eff4();
  }
  return;
}

