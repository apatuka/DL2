// FUN_004297e0 @ 004297e0 size=522 sig=undefined FUN_004297e0() cc=unknown
// callers: FUN_0042a36c
// callees: FUN_0049eb44

void FUN_004297e0(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  char *pcVar4;
  int local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_1c = 0x4c;
  local_20 = 7;
  local_14 = 0x87;
  local_18 = 0x44;
  FUN_0049eb44(DAT_004b9bf0,
               *(undefined4 *)(&DAT_004b9d44 + (char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] * 4),1,
               0xd,0,&local_20);
  iVar3 = 0;
  piVar2 = &DAT_00557bb4;
  pcVar4 = &DAT_0059f161;
  for (iVar1 = 0; iVar1 < DAT_004d5aec; iVar1 = iVar1 + 1) {
    if (iVar1 != DAT_0058f1f4) {
      if (iVar3 == 0) {
        local_28 = iVar1;
      }
      if (*pcVar4 < '\x01') {
        FUN_0049eb44(DAT_004b9bf0,*(undefined4 *)(&DAT_004b9d28 + pcVar4[1] * 4),1,0xd,0,
                     &DAT_004b9c5c + iVar3 * 0x10);
        switch(iVar3) {
        case 0:
          local_24 = 0xc;
          break;
        case 1:
          local_24 = 0xd;
          break;
        case 2:
          local_24 = 0xe;
          break;
        case 3:
          local_24 = 0xf;
          break;
        case 4:
          local_24 = 0x10;
          break;
        default:
          local_24 = 0x11;
        }
        FUN_0049eb44(DAT_004b9bf0,local_24,1,10,1,0);
      }
      else {
        FUN_0049eb44(DAT_004b9bf0,*(undefined4 *)(&DAT_004b9d0c + pcVar4[1] * 4),1,0xd,0,
                     &DAT_004b9c5c + iVar3 * 0x10);
      }
      *piVar2 = iVar1;
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    }
    pcVar4 = pcVar4 + 0x2d8;
  }
  pcVar4 = &DAT_0059f161;
  iVar3 = DAT_004d5aec + -3;
  piVar2 = &DAT_00557bcc + iVar3;
  for (iVar1 = 0; iVar1 < DAT_004d5aec; iVar1 = iVar1 + 1) {
    if ((iVar1 != DAT_0058f1f4) && (iVar1 != local_28)) {
      if (*pcVar4 < '\x01') {
        FUN_0049eb44(DAT_004b9bf0,*(undefined4 *)(&DAT_004b9d60 + pcVar4[1] * 4),1,0xd,0,
                     &DAT_004b9cbc + iVar3 * 0x10);
      }
      else {
        FUN_0049eb44(DAT_004b9bf0,*(undefined4 *)(&DAT_004b9d44 + pcVar4[1] * 4),1,0xd,0,
                     &DAT_004b9cbc + iVar3 * 0x10);
      }
      *piVar2 = iVar1;
      iVar3 = iVar3 + -1;
      piVar2 = piVar2 + -1;
    }
    pcVar4 = pcVar4 + 0x2d8;
  }
  return;
}

