// CheckMoveStuff @ 0042864c size=469 sig=undefined CheckMoveStuff() cc=unknown
// callers: FUN_00428824
// callees: FUN_0048db5d,DebugMessage,sprintf,FUN_004a2cb5,FUN_00498ba9,FUN_00428408,FUN_004ae26c,FUN_0049eb44
// strings: \"pColorList NULL in CheckMoveStuff()\"

/* auto-named from string evidence: CheckMoveStuff */

int CheckMoveStuff(void)

{
  undefined4 *puVar1;
  int iVar2;
  int local_18;
  undefined1 local_14 [12];
  
  puVar1 = (undefined4 *)FUN_00498ba9(0x10);
  if (puVar1 == (undefined4 *)0x0) {
    DebugMessage(s_pColorList_NULL_in_CheckMoveStuf_004b7de5);
    return -1;
  }
  *puVar1 = 3;
  FUN_0049eb44(DAT_004b7dcc,0xb,1,0x12,2,puVar1);
  FUN_0049eb44(DAT_004b7dcc,7,1,0xe,9,local_14);
  iVar2 = FUN_004ae26c(local_14);
  iVar2 = iVar2 * DAT_00557ba8;
  sprintf(local_14,&DAT_004b7de0,iVar2);
  FUN_0049eb44(DAT_004b7dcc,0xb,1,0xf,0,local_14);
  if (iVar2 - (&DAT_0059f16c)[DAT_0058f1f4 * 0xb6] == 0 ||
      iVar2 < (int)(&DAT_0059f16c)[DAT_0058f1f4 * 0xb6]) {
    puVar1[1] = 0x30;
    FUN_0049eb44(DAT_004b7dcc,8,1,10,0,0);
  }
  else {
    puVar1[1] = 0x60;
    FUN_0049eb44(DAT_004b7dcc,8,1,10,1,0);
  }
  FUN_0049eb44(DAT_004b7dcc,0xb,1,0x13,2,puVar1);
  FUN_00428408();
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  iVar2 = FUN_004a2cb5(DAT_004b7dcc,&local_18);
  if (((iVar2 == 0) && (local_18 != 0)) && (*(int *)(DAT_004b7dcc + 100) == 0)) {
    if (local_18 == 8) {
      FUN_0049eb44(DAT_004b7dcc,7,1,0xe,9,local_14);
      DAT_00557ba0 = FUN_004ae26c(local_14);
      DAT_004d59a4 = 0;
      return local_18;
    }
    if (local_18 == 9) {
      DAT_004d59a4 = 0;
      DAT_00557ba0 = 0;
      return 9;
    }
    if (local_18 == 0xc) {
      DAT_004d59a4 = 0;
      DAT_00557ba0 = 0xffffffff;
      return 0xc;
    }
  }
  DAT_004d59a4 = 0;
  return 0;
}

