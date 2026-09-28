// FUN_00490bca @ 00490bca size=282 sig=undefined FUN_00490bca() cc=unknown
// callers: FUN_0046fc70
// callees: FUN_004a6b00,FUN_0048f7f1,FUN_004a6964,FUN_00495162,FUN_0049028e,FUN_004888ec
// strings: \"Library added: %s\\r\\n\"

int FUN_00490bca(undefined4 param_1)

{
  int iVar1;
  short *psVar2;
  short *psVar3;
  int iVar4;
  
  if (DAT_0051daf8 == (short *)0x0) {
    iVar1 = 0;
  }
  else {
    psVar2 = DAT_0051daf8 + 2;
    for (iVar4 = (int)*DAT_0051daf8; 0 < iVar4; iVar4 = iVar4 + -1) {
      iVar1 = FUN_004a6b00(param_1,psVar2 + 5);
      if (iVar1 == 0) {
        return *(int *)(psVar2 + 1);
      }
      psVar2 = psVar2 + 0x85;
    }
    if (((*DAT_0051daf8 < DAT_0051daf8[1]) && (iVar4 = FUN_004888ec(param_1,0), iVar4 != -1)) &&
       (iVar1 = FUN_0049028e(iVar4), iVar1 != 0)) {
      if (*DAT_0051daf8 != 0) {
        FUN_0048f7f1(DAT_0051daf8 + 2,DAT_0051daf8 + 0x87,*DAT_0051daf8 * 0x10a);
      }
      *DAT_0051daf8 = *DAT_0051daf8 + 1;
      psVar2 = DAT_0051daf8;
      psVar3 = DAT_0051daf8 + 2;
      FUN_004a6964(DAT_0051daf8 + 7,param_1);
      *(int *)(psVar2 + 3) = iVar1;
      *psVar3 = 0;
      *(int *)(psVar2 + 5) = iVar4;
      if ((DAT_0051dcc4 & 0x10) != 0) {
        FUN_00495162(s_Library_added___s_0051db9e,param_1);
      }
    }
    else {
      iVar1 = 0;
    }
  }
  return iVar1;
}

