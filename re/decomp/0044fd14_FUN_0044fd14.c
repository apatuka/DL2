// FUN_0044fd14 @ 0044fd14 size=220 sig=undefined FUN_0044fd14() cc=unknown
// callers: @CampaignNumDialog$qqspvuiuil,FUN_0045f828
// callees: FUN_0044fe38

undefined4 FUN_0044fd14(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (DAT_004d5a94 != 0) {
    DAT_004d5b00 = (&DAT_004c6194)[DAT_004d5a94 * 0xd8];
    if (DAT_004d5b00 == '\0') {
      DAT_004d5af0 = *(undefined4 *)(&DAT_004c6198 + DAT_004d5a94 * 0xd8);
    }
    else if (DAT_004d5b00 == '\x02') {
      DAT_004d5af8 = *(undefined4 *)(&DAT_004c6198 + DAT_004d5a94 * 0xd8);
      DAT_004d5afc = *(undefined4 *)(&DAT_004c619c + DAT_004d5a94 * 0xd8);
    }
    iVar3 = 0;
    DAT_0059f100 = 0;
    do {
      iVar4 = DAT_004d5a94 * 0xd8 + iVar3 * 0x44;
      iVar1 = *(int *)(&DAT_004c61a0 + iVar4);
      if (((iVar1 != 0) && (DAT_0059f100 = DAT_0059f100 | 1 << ((byte)iVar1 & 0x1f), param_1 != 0))
         && ((iVar2 = FUN_0044fe38(iVar1), iVar2 != 0 ||
             (((iVar1 == 0xd || (iVar1 == 0xc)) || (iVar1 == 2)))))) {
        *(undefined4 *)(&DAT_004c61e0 + iVar4) = 0;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 3);
  }
  return 1;
}

