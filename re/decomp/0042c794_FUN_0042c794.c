// FUN_0042c794 @ 0042c794 size=416 sig=undefined FUN_0042c794() cc=unknown
// callers: FUN_0042d0ac
// callees: FUN_0049eb44

void FUN_0042c794(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  char *pcVar4;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_1c = 0x4c;
  local_20 = 7;
  local_14 = 0x87;
  local_18 = 0x44;
  FUN_0049eb44(DAT_004bf8fc,
               *(undefined4 *)(&DAT_004bf9fc + (char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] * 4),1,
               0xd,0,&local_20);
  iVar3 = 0;
  piVar2 = &DAT_00557c18;
  pcVar4 = &DAT_0059f161;
  for (iVar1 = 0; iVar1 < DAT_004d5aec; iVar1 = iVar1 + 1) {
    if (iVar1 != DAT_0058f1f4) {
      if (iVar3 == 0) {
        local_24 = iVar1;
      }
      if (*pcVar4 < '\x01') {
        FUN_0049eb44(DAT_004bf8fc,*(undefined4 *)(&DAT_004bf9e0 + pcVar4[1] * 4),1,0xd,0,
                     &DAT_004bf914 + iVar3 * 0x10);
      }
      else {
        FUN_0049eb44(DAT_004bf8fc,*(undefined4 *)(&DAT_004bf9c4 + pcVar4[1] * 4),1,0xd,0,
                     &DAT_004bf914 + iVar3 * 0x10);
      }
      *piVar2 = iVar1;
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    }
    pcVar4 = pcVar4 + 0x2d8;
  }
  pcVar4 = &DAT_0059f161;
  iVar3 = DAT_004d5aec + -3;
  piVar2 = &DAT_00557c30 + iVar3;
  for (iVar1 = 0; iVar1 < DAT_004d5aec; iVar1 = iVar1 + 1) {
    if ((iVar1 != DAT_0058f1f4) && (iVar1 != local_24)) {
      if (*pcVar4 < '\x01') {
        FUN_0049eb44(DAT_004bf8fc,*(undefined4 *)(&DAT_004bfa18 + pcVar4[1] * 4),1,0xd,0,
                     &DAT_004bf974 + iVar3 * 0x10);
      }
      else {
        FUN_0049eb44(DAT_004bf8fc,*(undefined4 *)(&DAT_004bf9fc + pcVar4[1] * 4),1,0xd,0,
                     &DAT_004bf974 + iVar3 * 0x10);
      }
      *piVar2 = iVar1;
      iVar3 = iVar3 + -1;
      piVar2 = piVar2 + -1;
    }
    pcVar4 = pcVar4 + 0x2d8;
  }
  return;
}

