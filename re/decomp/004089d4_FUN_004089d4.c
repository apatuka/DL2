// FUN_004089d4 @ 004089d4 size=179 sig=undefined FUN_004089d4() cc=unknown
// callers: FUN_0040e2f4
// callees: FUN_004412d4,FUN_0046ca40

uint FUN_004089d4(uint param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int local_10;
  int local_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  local_c = 0;
  local_10 = 8;
  uVar1 = FUN_0046ca40();
  uVar1 = uVar1 % DAT_004d5aec;
  uVar3 = uVar1;
  do {
    if (((local_c <= (int)(&DAT_0052254c)[uVar3]) &&
        (*(int *)(&DAT_005220a4 + uVar3 * 4 + param_1 * 0x1c) <= local_10)) && (uVar3 != param_1)) {
      iVar2 = FUN_004412d4(param_1,uVar3,0x10);
      if ((iVar2 == 0) && ((DAT_004d5b00 != '\x02' || ((&DAT_0065e3e8)[uVar3] != 0)))) {
        local_c = (&DAT_0052254c)[uVar3];
        local_10 = *(int *)(&DAT_005220a4 + uVar3 * 4 + param_1 * 0x1c);
        local_8 = uVar3;
      }
    }
    uVar3 = uVar3 + 1;
    if ((int)DAT_004d5aec <= (int)uVar3) {
      uVar3 = 0;
    }
  } while (uVar3 != uVar1);
  return local_8;
}

