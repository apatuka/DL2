// FUN_004780e4 @ 004780e4 size=517 sig=undefined FUN_004780e4() cc=unknown
// callers: FUN_00468030,FUN_0046e39c,FUN_0046ce10,WaitSync,FUN_0043a1f8,FUN_00467fc0,FUN_00486b74,ResetNetGame
// callees: FUN_0046e374,FUN_0045860c,FUN_00478060,FUN_004152ec,DebugMessage,FUN_004152e0,FUN_0045add0,FUN_00458298,FUN_00477e4c,FUN_00475198,FUN_004585fc
// strings: \"Unable to connect to the new game master.\"

void FUN_004780e4(int param_1)

{
  int iVar1;
  int iVar2;
  ushort *puVar3;
  
  if ((DAT_004d8264 == 0) && (DAT_006535f0 == 0)) {
    DAT_006535f0 = 1;
    DAT_004d59a4 = DAT_004d59a4 | 2;
    if ((DAT_004d5a50 != 0) &&
       (((&DAT_0059f161)[param_1 * 0x2d8] != '\0' &&
        ((char)(&DAT_0059f161)[param_1 * 0x2d8] < '\x03')))) {
      FUN_004152e0();
      iVar1 = FUN_0045add0();
      if (param_1 == DAT_0058f1f4) {
        FUN_00475198(DAT_0058f1f4);
        FUN_00477e4c();
      }
      (&DAT_0059f161)[param_1 * 0x2d8] = 0;
      if ((param_1 == DAT_004d5a58) && (2 < iVar1)) {
        iVar2 = FUN_00478060();
        if (param_1 == DAT_0058f1f4) {
          FUN_00458298();
        }
        else if (iVar2 == DAT_0058f1f4) {
          iVar2 = 0;
          puVar3 = &DAT_005f0410;
          do {
            if ((int)DAT_004d825c < (int)(uint)*puVar3) {
              DAT_004d825c = (uint)*puVar3;
            }
            iVar2 = iVar2 + 1;
            puVar3 = puVar3 + 0x91;
          } while (iVar2 < 0x4b0);
          iVar2 = 0;
          puVar3 = &DAT_00645370;
          do {
            if ((int)DAT_004d825c < (int)(uint)*puVar3) {
              DAT_004d825c = (uint)*puVar3;
            }
            iVar2 = iVar2 + 1;
            puVar3 = puVar3 + 0x2e;
          } while (iVar2 < 0x230);
          DAT_004d825c = DAT_004d825c + 1;
          FUN_004585fc();
          DAT_004d5a58 = DAT_0058f1f4;
          DAT_0058f208 = 0;
          DAT_0058f200 = iVar1 + -1;
          FUN_0046e374();
        }
        else {
          iVar1 = FUN_0045860c(iVar2);
          DAT_004d5a58 = iVar2;
          if (iVar1 == 0) {
            DAT_004d5a58 = DAT_0058f1f4;
            DAT_004d5a50 = 0;
            DAT_0058f1fc = 0;
            DebugMessage(s_Unable_to_connect_to_the_new_gam_004dc296);
          }
        }
      }
      else if (DAT_0058f1f4 == DAT_004d5a58) {
        DAT_0058f200 = DAT_0058f200 + -1;
      }
      if (param_1 == DAT_0058f1f4) {
        DAT_004d5a50 = 0;
        DAT_0058f1fc = 0;
        FUN_00458298();
      }
      FUN_004152ec();
    }
    DAT_004d59a4 = DAT_004d59a4 & 0xfffffffd;
    DAT_006535f0 = 0;
  }
  return;
}

