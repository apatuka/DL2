// FUN_00462724 @ 00462724 size=318 sig=undefined FUN_00462724() cc=unknown
// callers: FUN_004634a0
// callees: FUN_004ae5d8

void FUN_00462724(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_10;
  int local_c;
  
  local_c = 0;
LAB_00462732:
  iVar5 = local_c + 1;
  if (local_c < 0x79) {
    uVar1 = FUN_004ae5d8();
    uVar1 = uVar1 & 0x80000001;
    if ((int)uVar1 < 0) {
      uVar1 = (uVar1 - 1 | 0xfffffffe) + 1;
    }
    if (uVar1 == 0) {
      local_10 = 4;
    }
    else {
      local_10 = 3;
    }
    iVar6 = (int)DAT_004d5b1a;
    if (iVar6 + -3 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = FUN_004ae5d8();
      iVar2 = iVar2 % (iVar6 + -3);
    }
    iVar6 = (int)DAT_004d5b1b - (local_10 + -1);
    if (iVar6 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = FUN_004ae5d8();
      iVar3 = iVar3 % iVar6;
    }
    iVar6 = 0;
    if (local_10 != 0) {
      do {
        iVar4 = 0;
        do {
          local_c = iVar5;
          if ((&DAT_005a0552)[(iVar3 + iVar6) * 200 + (iVar4 + iVar2) * 5] != -1) goto LAB_00462732;
          iVar4 = iVar4 + 1;
        } while (iVar4 < 4);
        iVar6 = iVar6 + 1;
      } while (iVar6 < local_10);
    }
    iVar5 = 0;
    if (local_10 != 0) {
      do {
        iVar6 = 0;
        do {
          iVar4 = iVar6 + iVar2;
          iVar6 = iVar6 + 1;
          (&DAT_005a0552)[(iVar3 + iVar5) * 200 + iVar4 * 5] = (undefined2)param_1;
        } while (iVar6 < 4);
        iVar5 = iVar5 + 1;
      } while (iVar5 < local_10);
    }
    (&DAT_005a444e)[param_1 * 0xadc] = (char)local_10 * '\x04';
  }
  else {
    DAT_004d5b18 = DAT_004d5b18 + -1;
  }
  return;
}

