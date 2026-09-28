// FUN_00484270 @ 00484270 size=116 sig=undefined FUN_00484270() cc=unknown
// callers: FUN_00474718
// callees: FUN_00450150

void FUN_00484270(int param_1)

{
  int iVar1;
  ushort *puVar2;
  int iVar3;
  
  puVar2 = &DAT_004fbbac;
  iVar3 = 0;
  do {
    if (puVar2[0x10] == 1) {
      iVar1 = FUN_00450150((int)(char)(&DAT_0059f162)[param_1 * 0x2d8],iVar3);
      if (iVar1 != 0) {
        puVar2[1] = puVar2[1] | 1 << ((byte)param_1 & 0x1f);
      }
    }
    *puVar2 = *puVar2 & ~(1 << ((byte)param_1 & 0x1f));
    iVar3 = iVar3 + 1;
    puVar2[param_1 + 3] = 0;
    puVar2 = puVar2 + 0x19;
  } while (iVar3 < 0x30);
  return;
}

