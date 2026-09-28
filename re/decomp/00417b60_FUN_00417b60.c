// FUN_00417b60 @ 00417b60 size=158 sig=undefined FUN_00417b60() cc=unknown
// callers: CheckArmy
// callees: FUN_004171e0

void FUN_00417b60(void)

{
  char cVar1;
  int iVar2;
  char cVar3;
  int *piVar4;
  int iVar5;
  int local_18;
  int *local_14;
  
  if (DAT_004b76b8 == '\0') {
    *(undefined1 *)(DAT_004b76bc + 0x24) = (&DAT_0053b233)[DAT_0053b254];
  }
  else {
    local_18 = 0;
    local_14 = &DAT_005332d8;
    do {
      iVar5 = 0;
      piVar4 = local_14;
      do {
        if (*piVar4 == 1) {
          iVar2 = piVar4[1];
          cVar1 = (&DAT_0053b233)[DAT_0053b254];
          cVar3 = FUN_004171e0(iVar2,(int)cVar1,
                               (int)(char)(&DAT_0059f162)[*(char *)(iVar2 + 8) * 0x2d8]);
          if (cVar3 != '\0') {
            *(char *)(iVar2 + 0x24) = cVar1;
          }
        }
        iVar5 = iVar5 + 1;
        piVar4 = piVar4 + 8;
      } while (iVar5 < 10);
      local_18 = local_18 + 1;
      local_14 = (int *)((int)local_14 + 0x146);
    } while (local_18 < 100);
  }
  return;
}

