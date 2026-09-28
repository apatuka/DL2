// CheckSubUnit @ 00435ac4 size=850 sig=undefined CheckSubUnit() cc=unknown
// callers: FUN_00435e34
// callees: FUN_00434f28,FUN_00476d48,FUN_0049eb44,FUN_00412d38,FUN_00412f10,FUN_00432ad0,FUN_0048db5d,FUN_0043210c,FUN_00426594,FUN_00430b04,FUN_00431128,FUN_004a4025,FUN_004323d0,FUN_00432cf4,FUN_0042836c,DebugMessage,FUN_004a2cb5,FUN_00432e0c,FUN_00431734
// strings: \"gpSkirUnit NULL in CheckSubUnit()\"|\"Unfortunately, you cannot afford our price for that unit.\\nPlease return when your treasury is more substantial.\"|\"Insufficient Funds\"|\"Your chosen unit cannot operate on the selected territory's terrain.\\n If you want to buy this unit, please change your active territory and try again.\"|\"No Valid Targets\"

/* auto-named from string evidence: CheckSubUnit */

longlong CheckSubUnit(void)

{
  int iVar1;
  int iVar2;
  uint local_8;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  if (DAT_004c42e0 == 0) {
    DebugMessage(s_gpSkirUnit_NULL_in_CheckSubUnit__004c4636);
    return (ulonglong)local_8 << 0x20;
  }
  if ((((DAT_004c42e4 != 0) && (DAT_004c42f0 == 0)) && (*(char *)(DAT_004c42e4 + 0x3c) == '\0')) &&
     (DAT_004c42ec == 0)) {
    DAT_004c5b78 = 0;
    DAT_004c5b70 = 0;
    DAT_004c5b7c = 0;
    DAT_004c5b74 = 0;
    FUN_00412f10(DAT_004c42e4);
    FUN_00412d38(DAT_004c42e4,*(undefined4 *)(DAT_004c42e0 + 0x3c));
    DAT_004c42f0 = 1;
  }
  iVar1 = FUN_004a2cb5(DAT_004c42e0,&local_8);
  if (((iVar1 == 0) && (local_8 != 0)) && (*(int *)(DAT_004c42e0 + 100) == 0)) {
    switch(local_8) {
    case 5:
      FUN_00426594(&DAT_004d47e8);
      break;
    case 6:
      FUN_00431128();
      FUN_00432e0c();
      DAT_004d59a4 = 0;
      return CONCAT44(local_8,1);
    case 7:
      if (-1 < DAT_004c4508) {
        iVar1 = *(int *)(&DAT_004c42f8 + (&DAT_00558cd4)[DAT_004c4508 * 2] * 0xe);
        iVar2 = FUN_00430b04((&DAT_00558cd4)[DAT_004c4508 * 2]);
        if ((int)(&DAT_0059f16c)[DAT_0058f1f4 * 0xb6] < iVar2) {
          FUN_0042836c(PTR_s_Insufficient_Funds_005092b4,
                       PTR_s_Unfortunately__you_cannot_afford_0050943c,4,0,9);
        }
        else if ((((&DAT_004faf8d)[iVar1 * 0x24] == '\x02') &&
                 ((&DAT_005a43f1)[DAT_004c5b50 * 0xadc] != '\0')) ||
                (((&DAT_004faf8d)[iVar1 * 0x24] == '\x01' &&
                 ((&DAT_005a43f1)[DAT_004c5b50 * 0xadc] == '\0')))) {
          FUN_0042836c(PTR_s_No_Valid_Targets_005092bc,
                       PTR_s_Your_chosen_unit_cannot_operate_o_00509458,4,0,9);
        }
        else {
          FUN_00476d48(PTR_DAT_004d5988,(&DAT_00558cd4)[DAT_004c4508 * 2],
                       (int)(short)(&DAT_005a43ea)[DAT_004c5b50 * 0x56e]);
          FUN_004323d0(DAT_004c4508);
          if (DAT_00558e64 < 1) {
            FUN_004a4025(DAT_004c42e0);
            DAT_004c42e0 = 0;
            FUN_00434f28();
            FUN_00432cf4();
            DAT_004d59a4 = 0;
          }
          else {
            DAT_004c4508 = 0;
            FUN_0049eb44(DAT_004c42e0,0xe,1,0x1b,0,0);
            FUN_0049eb44(DAT_004c42e0,0xe,1,8,1,0);
            FUN_00431734(DAT_004c4508);
            FUN_00432cf4();
          }
        }
      }
      break;
    case 9:
      FUN_004a4025(DAT_004c42e0);
      DAT_004c42e0 = 0;
      FUN_00434f28();
      FUN_00432cf4();
      DAT_004d59a4 = 0;
      break;
    case 10:
      FUN_004a4025(DAT_004c42e0);
      DAT_004c42e0 = 0;
      FUN_00432ad0();
      FUN_00432cf4();
      DAT_004d59a4 = 0;
      break;
    case 0xb:
      FUN_004a4025(DAT_004c42e0);
      DAT_004c42e0 = 0;
      FUN_0043210c();
      FUN_00432cf4();
      DAT_004d59a4 = 0;
    }
    FUN_00432cf4();
    DAT_004d59a4 = 0;
    return (ulonglong)local_8 << 0x20;
  }
  FUN_00432cf4();
  DAT_004d59a4 = 0;
  return (ulonglong)local_8 << 0x20;
}

