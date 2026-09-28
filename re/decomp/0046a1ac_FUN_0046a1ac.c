// FUN_0046a1ac @ 0046a1ac size=471 sig=undefined FUN_0046a1ac() cc=unknown
// callers: FUN_0046a844
// callees: FUN_004ae5d8

void FUN_0046a1ac(void)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int local_24;
  int local_18;
  
  for (local_24 = 0; local_24 <= DAT_004d5b18; local_24 = local_24 + 1) {
    piVar7 = &DAT_005a4450 + local_24 * 0x2b7;
    for (iVar6 = 0; iVar6 < (char)(&DAT_005a444e)[local_24 * 0xadc]; iVar6 = iVar6 + 1) {
      iVar9 = *piVar7;
      if ((*(char *)(iVar9 + 5) == '\0') != true) {
        switch((&DAT_005a43f1)[local_24 * 0xadc]) {
        case 0:
          *(undefined1 *)(iVar9 + 5) = 0;
          break;
        case 1:
          uVar4 = FUN_004ae5d8();
          uVar4 = uVar4 & 0x8000000f;
          if ((int)uVar4 < 0) {
            uVar4 = (uVar4 - 1 | 0xfffffff0) + 1;
          }
          if (uVar4 == 0) {
            *(undefined1 *)(iVar9 + 5) = 4;
          }
          else {
            *(undefined1 *)(iVar9 + 5) = 3;
          }
          break;
        case 2:
          uVar4 = FUN_004ae5d8();
          uVar4 = uVar4 & 0x80000007;
          if ((int)uVar4 < 0) {
            uVar4 = (uVar4 - 1 | 0xfffffff8) + 1;
          }
          if (uVar4 == 0) {
            *(undefined1 *)(iVar9 + 5) = 4;
          }
          else {
            *(undefined1 *)(iVar9 + 5) = 2;
          }
          break;
        case 3:
          *(undefined1 *)(iVar9 + 5) = 1;
          break;
        case 4:
          *(undefined1 *)(iVar9 + 5) = 5;
          break;
        case 5:
          *(undefined1 *)(iVar9 + 5) = 6;
        }
      }
      piVar7 = piVar7 + 1;
    }
  }
  for (local_24 = 0; local_24 <= DAT_004d5b18; local_24 = local_24 + 1) {
    iVar6 = local_24 * 0xadc;
    if (((&DAT_005a43f1)[iVar6] != '\0') && ((&DAT_005a4444)[iVar6] != -1)) {
      pcVar3 = (char *)(&DAT_005a4450)[local_24 * 0x2b7 + (int)(char)(&DAT_005a4444)[iVar6]];
      cVar1 = *pcVar3;
      cVar2 = pcVar3[1];
      local_18 = -1;
      do {
        iVar9 = cVar2 + local_18;
        iVar6 = -1;
        do {
          iVar8 = cVar1 + iVar6;
          if ((((-1 < iVar8) && (-1 < iVar9)) && (iVar8 < DAT_004d5b1a)) &&
             (((iVar9 < DAT_004d5b1b &&
               (iVar5 = FUN_004ae5d8(),
               iVar5 % 100 < *(int *)(&DAT_004d52a8 + (iVar6 * 3 + local_18) * 4))) &&
              ((&DAT_005a0555)[iVar8 * 10 + iVar9 * 400] == '\x05')))) {
            (&DAT_005a0555)[iVar8 * 10 + iVar9 * 400] = 4;
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < 2);
        local_18 = local_18 + 1;
      } while (local_18 < 2);
      pcVar3[5] = '\x03';
    }
  }
  return;
}

