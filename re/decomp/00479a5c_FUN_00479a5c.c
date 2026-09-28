// FUN_00479a5c @ 00479a5c size=41 sig=undefined FUN_00479a5c() cc=unknown
// callers: FUN_0046ce10,FUN_00479b38,FUN_00479f90
// callees: FUN_00427ee8,fclose

void FUN_00479a5c(void)

{
  if (DAT_004dc310 != 0) {
    fclose(DAT_004dc310);
    DAT_004dc310 = 0;
  }
  if (DAT_004d59b4 == 0x24) {
    FUN_00427ee8();
  }
  return;
}

