// FUN_0043acd4 @ 0043acd4 size=264 sig=undefined FUN_0043acd4() cc=unknown
// callers: FUN_0045e554
// callees: FUN_00449760,FUN_00414ea4,FUN_00493784,FUN_0048d32c,FUN_0049eb44,FUN_00495c51,FUN_0049a9e7,FUN_0049a8ed,FUN_004a3fcd,FUN_0049a93f,FUN_0048d2e7,FUN_004a2078,FUN_00495bf0

void FUN_0043acd4(void)

{
  int iVar1;
  char *pcVar2;
  bool bVar3;
  undefined1 local_28 [16];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  FUN_00449760();
  local_10 = 0;
  local_18 = 0;
  local_c = 0;
  local_14 = 0;
  pcVar2 = &DAT_0059f161;
  for (iVar1 = 0; iVar1 < DAT_004d5aec; iVar1 = iVar1 + 1) {
    if (*pcVar2 != '\0') {
      FUN_0049eb44(DAT_004c48a0,iVar1 + 0x26,1,1,0,local_28);
      FUN_00495bf0(local_28,&local_18);
    }
    pcVar2 = pcVar2 + 0x2d8;
  }
  FUN_00495c51(&local_18,*(undefined4 *)(DAT_004c48a0 + 8),*(undefined4 *)(DAT_004c48a0 + 0xc));
  FUN_0049a8ed();
  FUN_0049a9e7(&local_18);
  bVar3 = (*(byte *)(DAT_004c48a0 + 0x1c) & 0x80) != 0;
  FUN_004a3fcd(DAT_004c48a0,0);
  FUN_004a2078(DAT_004c48a0);
  if (bVar3) {
    FUN_0048d2e7(DAT_004d5c28);
    FUN_00493784(local_18,local_14,local_10,local_c,2,0,1);
    FUN_0048d32c();
  }
  FUN_004a3fcd(DAT_004c48a0,bVar3);
  FUN_00414ea4(&local_18);
  FUN_0049a93f();
  return;
}

