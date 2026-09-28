// FUN_00486b74 @ 00486b74 size=442 sig=undefined FUN_00486b74() cc=unknown
// callers: FUN_00486d30,FUN_00474920,FUN_00486e34
// callees: FUN_004780e4,FUN_0044fe58,_DemolishBuilding,FUN_0044a000,FUN_0044fe1c,FUN_0045add0,FUN_00450000,DeleteUnit,FUN_0046e374

void FUN_00486b74(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  
  if ((&DAT_0059f161)[param_1 * 0x2d8] != '\0') {
    iVar1 = FUN_0044fe1c(0xb);
    if (iVar1 != 0) {
      iVar1 = FUN_00450000(0xb,(int)(char)(&DAT_0059f162)[param_1 * 0x2d8]);
      if (iVar1 != 0) {
        FUN_0044fe58(0xb);
      }
    }
    for (puVar2 = (undefined4 *)&DAT_00645370; puVar2 < &DAT_00651cb0; puVar2 = puVar2 + 0x17) {
      if ((*(char *)((int)puVar2 + 6) != '\0') && (*(char *)(puVar2 + 2) == param_1)) {
        DeleteUnit(puVar2);
      }
    }
    for (puVar2 = &DAT_005a4eac; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
        puVar2 = puVar2 + 0x2b7) {
      if (*(char *)(puVar2 + 8) == param_1) {
        *(undefined2 *)(puVar2 + 0xc) = 0;
        *(undefined1 *)(puVar2 + 8) = 0xff;
        iVar1 = 0;
        piVar3 = puVar2 + 0x55;
        do {
          if ((*piVar3 != 0) && ((&DAT_004f9dc3)[*(char *)(*piVar3 + 4) * 0x32] != '\v')) {
            _DemolishBuilding(&DAT_0059f160 + param_1 * 0x2d8,puVar2,iVar1,0);
          }
          iVar1 = iVar1 + 1;
          piVar3 = piVar3 + 0xd;
        } while (iVar1 < 0x24);
      }
    }
    if ((DAT_004d5a50 != 0) && ((char)(&DAT_0059f161)[param_1 * 0x2d8] < '\x03')) {
      FUN_004780e4(param_1,0);
    }
    (&DAT_0059f161)[param_1 * 0x2d8] = 0;
    if ((param_1 != DAT_0058f1f4) && (DAT_004d5a50 != 0)) {
      iVar1 = FUN_0045add0();
      if ((iVar1 == 1) && (DAT_0065e3ac == 0)) {
        DAT_0058f1fc = 0;
        DAT_004d5a50 = 0;
        DAT_004d5a58 = DAT_0058f1f4;
        FUN_0046e374();
      }
    }
  }
  FUN_0044a000();
  return;
}

