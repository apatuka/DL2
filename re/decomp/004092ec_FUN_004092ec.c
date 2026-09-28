// FUN_004092ec @ 004092ec size=120 sig=undefined FUN_004092ec() cc=unknown
// callers: FUN_00409364
// callees: FUN_0044fe1c

bool FUN_004092ec(int param_1)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  
  iVar4 = FUN_0044fe1c(7);
  if (iVar4 == 0) {
    iVar6 = 0;
    iVar7 = 0;
    iVar4 = 0;
    piVar5 = (int *)(param_1 + 0x154);
    do {
      iVar2 = *piVar5;
      if (((iVar2 != 0) && (*(char *)(iVar2 + 4) != '\0')) &&
         ((&DAT_004f9dc3)[*(char *)(iVar2 + 4) * 0x32] == '\x12')) {
        cVar1 = *(char *)(iVar2 + 4);
        if ((cVar1 == '\x1d') || (cVar1 == '\x1f')) {
LAB_00409348:
          iVar6 = iVar6 + 1;
        }
        else if (cVar1 == ' ') {
          iVar7 = iVar7 + 1;
        }
        else if (cVar1 == '(') goto LAB_00409348;
      }
      iVar4 = iVar4 + 1;
      piVar5 = piVar5 + 0xd;
    } while (iVar4 < 0x24);
    bVar3 = iVar7 < iVar6;
  }
  else {
    bVar3 = false;
  }
  return bVar3;
}

