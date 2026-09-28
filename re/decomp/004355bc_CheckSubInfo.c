// CheckSubInfo @ 004355bc size=552 sig=undefined CheckSubInfo() cc=unknown
// callers: FUN_00435e34
// callees: FUN_00434f28,FUN_0043242c,FUN_00412d38,FUN_00412f10,FUN_00476e40,FUN_00432d30,FUN_0048db5d,FUN_0043210c,FUN_00426594,FUN_00431128,FUN_004326b0,FUN_004a4025,FUN_00432cf4,FUN_0042836c,FUN_00432dd0,DebugMessage,FUN_004a2cb5,FUN_00432e0c,FUN_00432660,FUN_0045dfb0
// strings: \"gpSkirInfo NULL in CheckSubInfo()\"|\"Unfortunately, you cannot afford our price for that unit.\\nPlease return when your treasury is more substantial.\"|\"Insufficient Funds\"

/* auto-named from string evidence: CheckSubInfo */

longlong CheckSubInfo(void)

{
  int iVar1;
  uint local_4;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  if (DAT_004c42d8 == 0) {
    DebugMessage(s_gpSkirInfo_NULL_in_CheckSubInfo__004c45f2);
    return (ulonglong)local_4 << 0x20;
  }
  if ((((DAT_004c42e4 != 0) && (DAT_004c42f0 == 0)) && (*(char *)(DAT_004c42e4 + 0x3c) == '\0')) &&
     (DAT_004c42ec == 0)) {
    DAT_004c5b78 = 0;
    DAT_004c5b70 = 0;
    DAT_004c5b7c = 0;
    DAT_004c5b74 = 0;
    FUN_00412f10(DAT_004c42e4);
    FUN_00412d38(DAT_004c42e4,*(undefined4 *)(DAT_004c42d8 + 0x3c));
    DAT_004c42f0 = 1;
  }
  iVar1 = FUN_004a2cb5(DAT_004c42d8,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004c42d8 + 100) == 0)) {
    switch(local_4) {
    case 5:
      FUN_00426594(&DAT_004d47c4);
      break;
    case 6:
      FUN_00431128();
      FUN_00432e0c();
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,1);
    case 7:
      if (DAT_00558cc0 != -1) {
        if ((int)(&DAT_0059f16c)[DAT_0058f1f4 * 0xb6] < 100) {
          FUN_0042836c(PTR_s_Insufficient_Funds_005092b4,
                       PTR_s_Unfortunately__you_cannot_afford_0050943c,4,0,9);
        }
        else {
          FUN_00476e40(PTR_DAT_004d5988,DAT_00558cc0);
          (&DAT_005a43ec)[DAT_00558cc0 * 0x2b7] = (&DAT_005a43ec)[DAT_00558cc0 * 0x2b7] | 4;
          FUN_0045dfb0(2);
          FUN_00432660();
          FUN_004326b0();
          FUN_00432d30();
          FUN_00432cf4();
        }
      }
      break;
    case 9:
      FUN_004a4025(DAT_004c42d8);
      DAT_004c42d8 = 0;
      FUN_00434f28();
      FUN_00432cf4();
      DAT_004d59a4 = 0;
      break;
    case 0xb:
      FUN_00432dd0();
      FUN_0043210c();
      FUN_00432cf4();
      DAT_004d59a4 = 0;
      break;
    case 0xc:
      FUN_004a4025(DAT_004c42d8);
      DAT_004c42d8 = 0;
      FUN_0043242c();
      FUN_00432cf4();
      DAT_004d59a4 = 0;
    }
    FUN_00432cf4();
    DAT_004d59a4 = 0;
    return (ulonglong)local_4 << 0x20;
  }
  DAT_004d59a4 = 0;
  FUN_00432cf4();
  return (ulonglong)local_4 << 0x20;
}

