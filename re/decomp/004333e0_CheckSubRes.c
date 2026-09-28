// CheckSubRes @ 004333e0 size=666 sig=undefined CheckSubRes() cc=unknown
// callers: FUN_00435e34
// callees: FUN_0048de8e,FUN_0049eb44,FUN_00412d38,FUN_0048e1d5,FUN_0048df30,FUN_00412f10,FUN_0048db5d,FUN_004ae26c,sprintf,FUN_00430bd0,FUN_0048e169,FUN_00432cf4,DebugMessage,FUN_004a2cb5,FUN_00412e94
// strings: \"gpSkirRes NULL in CheckSubRes()\"|\"%d Cr.\"

/* auto-named from string evidence: CheckSubRes */

undefined4 CheckSubRes(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int local_41c;
  undefined1 local_418 [4];
  undefined1 local_414 [4];
  undefined1 local_410 [4];
  undefined1 local_40c [1024];
  
  if (DAT_004c42d4 == 0) {
    DebugMessage(s_gpSkirRes_NULL_in_CheckSubRes___004c45d0);
  }
  else {
    if ((((DAT_004c42e4 != 0) && (DAT_004c42f0 == 0)) && (*(char *)(DAT_004c42e4 + 0x3c) == '\0'))
       && (DAT_004c42ec == 0)) {
      DAT_004c5b78 = 0;
      DAT_004c5b70 = 0;
      DAT_004c5b7c = 0;
      DAT_004c5b74 = 0;
      FUN_00412f10(DAT_004c42e4);
      FUN_00412d38(DAT_004c42e4,*(undefined4 *)(DAT_004c42d4 + 0x3c));
      DAT_004c42f0 = 1;
      FUN_00430bd0();
    }
    DAT_004d59a4 = 1;
    DAT_0051b824 = 1;
    FUN_0048db5d(0);
    if ((DAT_004c42e4 != 0) && (DAT_004c42f0 == 0)) {
      iVar2 = FUN_0048e1d5(1,local_418,local_414,local_410);
      if (iVar2 != 0) {
        FUN_0048e169(1,local_418,local_414,local_410);
        DAT_004c5b78 = 0;
        DAT_004c5b70 = 0;
        DAT_004c5b7c = 0;
        DAT_004c5b74 = 0;
        FUN_00412e94(DAT_004c42e4);
        FUN_00412d38(DAT_004c42e4,*(undefined4 *)(DAT_004c42d4 + 0x3c));
        DAT_004c42f0 = 1;
        FUN_00430bd0();
      }
    }
    if ((DAT_004c42e4 != 0) && (DAT_004c42f0 == 0)) {
      cVar1 = FUN_0048de8e();
      if (cVar1 != '\0') {
        FUN_0048df30();
        DAT_004c5b78 = 0;
        DAT_004c5b70 = 0;
        DAT_004c5b7c = 0;
        DAT_004c5b74 = 0;
        FUN_00412e94(DAT_004c42e4);
        FUN_00412d38(DAT_004c42e4,*(undefined4 *)(DAT_004c42d4 + 0x3c));
        DAT_004c42f0 = 1;
        FUN_00430bd0();
      }
    }
    FUN_0049eb44(DAT_004c42d4,0x73,1,0xe,0x3ff,local_40c);
    iVar2 = FUN_004ae26c(local_40c);
    FUN_0049eb44(DAT_004c42d4,0x77,1,0xe,0x3ff,local_40c);
    iVar3 = FUN_004ae26c(local_40c);
    sprintf(local_40c,s__d_Cr__004c4599,iVar2 * iVar3);
    FUN_0049eb44(DAT_004c42d4,0x7b,1,0xf,0,local_40c);
    iVar2 = FUN_004a2cb5(DAT_004c42d4,&local_41c);
    if (((iVar2 == 0) && (local_41c != 0)) && (*(int *)(DAT_004c42d4 + 100) == 0)) {
      if (local_41c - 5U < 0x6d) {
                    /* WARNING: Could not emulate address calculation at 0x00433644 */
                    /* WARNING: Treating indirect jump as call */
        uVar4 = (**(code **)(&DAT_004336be +
                            CONCAT31((int3)(local_41c - 5U >> 8),
                                     *(undefined1 *)(local_41c + 0x43364c)) * 4))();
        return uVar4;
      }
      FUN_00432cf4();
      DAT_004d59a4 = 0;
    }
    else {
      FUN_00432cf4();
      DAT_004d59a4 = 0;
    }
  }
  return 0;
}

