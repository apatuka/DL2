// FUN_004422bc @ 004422bc size=245 sig=undefined FUN_004422bc() cc=unknown
// callers: FUN_00466218
// callees: memset,FUN_00446b3c

int FUN_004422bc(void)

{
  undefined4 *puVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  int iVar4;
  
  iVar4 = 0;
  memset(&DAT_0055a820,0,0x3440);
  for (puVar2 = &DAT_005a43d0; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0xadc) {
    puVar2[0x22] = 0xff;
  }
  puVar3 = &DAT_005a4eac;
  do {
    if (&DAT_005a43d0 + DAT_004d5b18 * 0xadc < puVar3) {
      return iVar4;
    }
    if (((*(char *)((int)puVar3 + 0x7e) != '\0') && ((*(byte *)((int)puVar3 + 0x1d) & 1) == 0)) &&
       (*(char *)((int)puVar3 + 0x22) == -1)) {
      puVar1 = puVar3;
      if (*(char *)((int)puVar3 + 0x21) == '\0') {
        FUN_00446b3c(puVar3,500,2,0xffffffff,0x2000);
      }
      else {
        FUN_00446b3c(puVar3,500,1,0xffffffff,0x2000);
      }
      for (; puVar1 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc; puVar1 = puVar1 + 0x2b7) {
        if ((*(byte *)((int)puVar1 + 0x1d) & 0x20) != 0) {
          if (*(char *)((int)puVar1 + 0x22) == -1) {
            *(char *)((int)puVar1 + 0x22) = (char)iVar4;
          }
          else if ((*(byte *)((int)puVar1 + 0x1d) & 1) == 0) {
            return 0;
          }
        }
      }
      iVar4 = iVar4 + 1;
    }
    puVar3 = puVar3 + 0x2b7;
  } while( true );
}

