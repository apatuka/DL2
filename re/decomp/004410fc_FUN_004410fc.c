// FUN_004410fc @ 004410fc size=44 sig=undefined FUN_004410fc() cc=unknown
// callers: FUN_00441128
// callees: 

void FUN_004410fc(int param_1,short param_2)

{
  short *psVar1;
  int iVar2;
  
  iVar2 = 0;
  psVar1 = &DAT_00559e00 + param_1;
  do {
    *psVar1 = *psVar1 + param_2;
    iVar2 = iVar2 + 1;
    psVar1 = psVar1 + 7;
  } while (iVar2 < 0x16);
  *(short *)(&DAT_00559f6c + param_1 * 2) = *(short *)(&DAT_00559f6c + param_1 * 2) + param_2;
  return;
}

