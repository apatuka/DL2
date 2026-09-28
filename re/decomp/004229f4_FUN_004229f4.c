// FUN_004229f4 @ 004229f4 size=423 sig=undefined FUN_004229f4() cc=unknown
// callers: FUN_00423104,CheckEventLog
// callees: FUN_004229bc,FUN_0049eb44

undefined8 FUN_004229f4(void)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  undefined4 unaff_EDI;
  undefined4 local_14;
  
  iVar2 = 0;
  local_14 = 0;
  FUN_0049eb44(DAT_004b7b50,0x15,1,10,1,0);
  FUN_0049eb44(DAT_004b7b50,0x14,1,10,1,0);
  FUN_0049eb44(DAT_004b7b50,0x11,1,10,1,0);
  FUN_0049eb44(DAT_004b7b50,0x16,1,10,1,0);
  FUN_0049eb44(DAT_004b7b50,0x13,1,10,1,0);
  FUN_0049eb44(DAT_004b7b50,0x12,1,10,1,0);
  iVar1 = FUN_004229bc();
  if (iVar1 == 0) {
    iVar1 = 0;
    pcVar3 = &DAT_00540ce0;
    do {
      if (*pcVar3 != '\0') {
        switch(iVar1) {
        case 0:
          unaff_EDI = 0x11;
          break;
        case 1:
          unaff_EDI = 0x12;
          break;
        case 2:
          unaff_EDI = 0x13;
          break;
        case 3:
          unaff_EDI = 0x14;
          break;
        case 4:
          unaff_EDI = 0x15;
          break;
        case 5:
          unaff_EDI = 0x16;
        }
        FUN_0049eb44(DAT_004b7b50,unaff_EDI,1,10,0,0);
        if ((char)local_14 == '\0') {
          local_14 = 1;
          DAT_004b7b44 = iVar1;
          FUN_0049eb44(DAT_004b7b50,unaff_EDI,1,0xb,1,0);
        }
        iVar2 = iVar2 + 1;
      }
      iVar1 = iVar1 + 1;
      pcVar3 = pcVar3 + 0x4802;
    } while (iVar1 < 6);
  }
  else {
    iVar2 = 1;
    FUN_0049eb44(DAT_004b7b50,0x12,1,10,0,0);
    if (DAT_00540ce0 == '\0') {
      FUN_0049eb44(DAT_004b7b50,0x11,1,10,1,0);
    }
    else {
      iVar2 = 2;
      FUN_0049eb44(DAT_004b7b50,0x11,1,10,0,0);
    }
    DAT_004b7b44 = 1;
    FUN_0049eb44(DAT_004b7b50,0x12,1,0xb,1,0);
  }
  return CONCAT44(local_14,iVar2);
}

