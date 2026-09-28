// FUN_00495162 @ 00495162 size=208 sig=undefined FUN_00495162() cc=unknown
// callers: FUN_00490d98,FUN_0048fee9,FUN_0049eb9f,FUN_00490bca,FUN_0048badd,FUN_00488aae,FUN_0048de1d,FUN_00488d30,FUN_00490ce4,FUN_0048ddb8,FUN_00489ef5,FUN_00488c95,FUN_00488e9d,FUN_004a4025,FUN_00489c98,FUN_004a1715,FUN_00498d22,FUN_00496358,FUN_00495086,FUN_00495241,FUN_004962e7,FUN_00488ce9,FUN_004888ec,FUN_0048e5f8,FUN_00488ba3,FUN_004a3d26,FUN_0049539b,FUN_0048dd95,FUN_0048c2c5,FUN_0048de49,FUN_00488d7e,FUN_004a0f18,FUN_0048e0d7,FUN_00488998,FUN_0048baa6,FUN_00488b0f,FUN_00488e1b,FUN_00488f20,FUN_00488c1c,CYGame_InitDirectDraw,FUN_004953e8,FUN_00488a67,FUN_0048e0b7,FUN_00488a09,FUN_00488dd3,FUN_00488b59
// callees: FUN_004888ec,FUN_00488c95,FUN_004ab474,FUN_00488c1c,FUN_00488a09,FUN_0049512a,FUN_00488998
// strings: \"err.log\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00495162(int param_1)

{
  int iVar1;
  int iVar2;
  undefined1 local_508 [1024];
  undefined1 local_108 [260];
  
  if (((_DAT_0051dcc4 & 0x80000000) != 0) && (param_1 != 0)) {
    iVar1 = FUN_004ab474(local_508,param_1,&stack0x00000008);
    if (((_DAT_0051dcc4 & 0x1000) != 0) && (DAT_0051dda0 != (code *)0x0)) {
      (*DAT_0051dda0)(local_508);
    }
    _DAT_0051dcc4 = _DAT_0051dcc4 & 0x7fffffff;
    if (0 < iVar1) {
      FUN_0049512a(local_108,s_err_log_0051e031);
      iVar2 = FUN_004888ec(local_108,2);
      if ((iVar2 == -1) && (iVar2 = FUN_00488998(local_108,0), iVar2 == -1)) {
        return;
      }
      FUN_00488c95(iVar2,0,2);
      FUN_00488c1c(iVar2,local_508,iVar1);
      FUN_00488a09(iVar2);
    }
    _DAT_0051dcc4 = _DAT_0051dcc4 | 0x80000000;
  }
  return;
}

