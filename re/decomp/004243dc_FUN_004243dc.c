// FUN_004243dc @ 004243dc size=149 sig=undefined FUN_004243dc() cc=unknown
// callers: FUN_00424590
// callees: FUN_00482f6c,FUN_004a5e12,FUN_00482f3c,FUN_00482940

void FUN_004243dc(void)

{
  DAT_004d5ac8 = DAT_00557510;
  FUN_004a5e12(DAT_00557510);
  if (DAT_004d5ab0 == 0) {
    FUN_00482f6c(0xffffd8f0);
  }
  else {
    FUN_00482f6c((DAT_004d5adc * 3000) / 100 + -3000);
  }
  if (DAT_004d5aac == 0) {
    FUN_00482f3c(0xffffd8f0);
  }
  else {
    FUN_00482f3c((DAT_004d5ad8 * 3000) / 100 + -3000);
  }
  FUN_00482940(DAT_004d5ab0);
  return;
}

