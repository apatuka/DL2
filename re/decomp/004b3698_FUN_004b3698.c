// FUN_004b3698 @ 004b3698 size=150 sig=undefined FUN_004b3698() cc=unknown
// callers: FUN_004b366c
// callees: memset,FUN_004b38a0,FUN_004b3890,FUN_004b0a30,FUN_004b0b44

undefined4 * FUN_004b3698(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  FUN_004b3890(DAT_0069f890);
  if (DAT_0069f88c == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)FUN_004b0b44(0x54);
    if (puVar2 != (undefined4 *)0x0) {
      memset(puVar2,0,0x54);
    }
  }
  else {
    puVar2 = DAT_0069f88c;
    DAT_0069f88c = (undefined4 *)*DAT_0069f88c;
  }
  if (puVar2 != (undefined4 *)0x0) {
    puVar2[0x11] = 1;
    puVar2[0x12] = 0;
    if (puVar2[0x13] == 0) {
      iVar1 = FUN_004b0b44(DAT_0051f100);
      puVar2[0x13] = iVar1;
      if (iVar1 == 0) {
        FUN_004b0a30(puVar2);
        puVar2 = (undefined4 *)0x0;
        goto LAB_004b371d;
      }
    }
    memset(puVar2[0x13],0,DAT_0051f100);
  }
LAB_004b371d:
  FUN_004b38a0(DAT_0069f890);
  return puVar2;
}

