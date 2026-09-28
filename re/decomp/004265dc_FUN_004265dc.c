// FUN_004265dc @ 004265dc size=79 sig=undefined FUN_004265dc() cc=unknown
// callers: 
// callees: FUN_00426594

void FUN_004265dc(undefined4 param_1,int param_2,int param_3)

{
  if (param_2 == -1) {
    FUN_00426594(&DAT_004d4d64);
  }
  else if (param_3 == -1) {
    FUN_00426594(&DAT_004d4b24 + param_2 * 0x24);
  }
  else {
    FUN_00426594((&PTR_DAT_004d4b3a)[param_2 * 9] + param_3 * 0x24);
  }
  return;
}

