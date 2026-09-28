// FUN_00490ce4 @ 00490ce4 size=140 sig=undefined FUN_00490ce4() cc=unknown
// callers: FUN_00490e39
// callees: FUN_004901ed,FUN_0048f7f1,FUN_00495162,FUN_004989de,FUN_004989c0,FUN_00490603,FUN_004906b5,FUN_00498aab
// strings: \"Library closed: %s\\r\\n\"

undefined4 FUN_00490ce4(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00490603(param_1);
  if (iVar1 != 0) {
    if ((DAT_0051dcc4 & 0x10) != 0) {
      FUN_00495162(s_Library_closed___s_0051dbb2,iVar1 + 10);
    }
    FUN_004906b5(param_1);
    FUN_004901ed(param_1);
    if (DAT_0051dafc != 0) {
      FUN_00498aab(param_1,0);
    }
    FUN_004989de(param_1);
    iVar2 = FUN_004989c0(DAT_0051daf8);
    iVar2 = (int)DAT_0051daf8 + (iVar2 - (iVar1 + 0x10a));
    if (0 < iVar2) {
      FUN_0048f7f1(iVar1 + 0x10a,iVar1,iVar2);
    }
    *DAT_0051daf8 = *DAT_0051daf8 + -1;
  }
  return 0;
}

