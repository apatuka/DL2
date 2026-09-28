// CheckBuilding @ 0041d834 size=516 sig=undefined CheckBuilding() cc=unknown
// callers: FUN_0044930c
// callees: FUN_0042f680,FUN_0041b308,FUN_004762a8,FUN_0041d2bc,FUN_00476324,DebugMessage,FUN_0041d414,FUN_0041d680,FUN_0041c418,FUN_00426594,FUN_0041d710,FUN_0041c3dc,FUN_004a2cb5,FUN_0041c36c,FUN_0041bd60,FUN_0041d2b4
// strings: \"NULL gpBuilding in CheckBuilding()\"

/* auto-named from string evidence: CheckBuilding */

longlong CheckBuilding(void)

{
  int iVar1;
  uint local_8;
  
  if (DAT_004b7758 == 0) {
    DebugMessage(s_NULL_gpBuilding_in_CheckBuilding_004b7906);
    return (ulonglong)local_8 << 0x20;
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  if (DAT_0053b86c != '\0') {
    DAT_0053b86c = '\0';
    FUN_00476324(DAT_0053b84c,DAT_0053b870);
  }
  iVar1 = FUN_004a2cb5(DAT_004b7758,&local_8);
  if (((iVar1 == 0) && (local_8 != 0)) && (*(int *)(DAT_004b7758 + 100) == 0)) {
    switch(local_8) {
    case 3:
      FUN_00426594(&DAT_004d345c + *(char *)(DAT_0053b850 + 4) * 0x24);
      break;
    case 4:
      FUN_0041d2b4();
      DAT_004d59a4 = 0;
      return (ulonglong)local_8 << 0x20;
    case 5:
      FUN_0042f680();
      break;
    case 8:
      FUN_0041b308();
      break;
    case 9:
      FUN_0041bd60(1);
      break;
    case 0xb:
      *(ushort *)(DAT_0053b850 + 2) = *(ushort *)(DAT_0053b850 + 2) ^ 0x100;
      FUN_004762a8(DAT_0053b84c,DAT_0053b850);
      break;
    case 0xc:
      FUN_0041bd60(2);
      break;
    case 0xe:
      *(ushort *)(DAT_0053b850 + 2) = *(ushort *)(DAT_0053b850 + 2) ^ 0x200;
      FUN_004762a8(DAT_0053b84c,DAT_0053b850);
      break;
    case 0xf:
      FUN_0041bd60(3);
      break;
    case 0x11:
      *(ushort *)(DAT_0053b850 + 2) = *(ushort *)(DAT_0053b850 + 2) ^ 0x400;
      FUN_004762a8(DAT_0053b84c,DAT_0053b850);
      break;
    case 0x12:
      FUN_0041bd60(4);
      break;
    case 0x14:
      *(ushort *)(DAT_0053b850 + 2) = *(ushort *)(DAT_0053b850 + 2) ^ 0x800;
      FUN_004762a8(DAT_0053b84c,DAT_0053b850);
      break;
    case 0x15:
      FUN_0041bd60(5);
      break;
    case 0x17:
      *(ushort *)(DAT_0053b850 + 2) = *(ushort *)(DAT_0053b850 + 2) ^ 0x1000;
      FUN_004762a8(DAT_0053b84c,DAT_0053b850);
      break;
    case 0x18:
      FUN_0041bd60(6);
      break;
    case 0x1a:
      FUN_0041d2bc();
      break;
    case 0x1b:
      FUN_0041d680();
      if (*(char *)(DAT_0053b850 + 0x30) != '\0') {
        FUN_0041c3dc();
        FUN_0041c418();
      }
      break;
    case 0x1c:
      FUN_0041d414();
      break;
    case 0x1d:
      FUN_0041d710();
    }
  }
  DAT_004d59a4 = 0;
  FUN_0041c36c();
  return CONCAT44(local_8,iVar1);
}

