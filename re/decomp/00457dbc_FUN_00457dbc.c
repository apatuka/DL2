// FUN_00457dbc @ 00457dbc size=88 sig=undefined FUN_00457dbc() cc=unknown
// callers: FUN_004581a8,FUN_00458138
// callees: CGNet_Initialize,CGNet_FindServices

undefined4 FUN_00457dbc(void)

{
  int iVar1;
  
  iVar1 = CGNet_Initialize(&DAT_004d1704,&DAT_004d171c);
  if (iVar1 < 0) {
    DAT_00583b70 = 0;
    return 0;
  }
  DAT_00583b70 = CGNet_FindServices(DAT_004d1704,&DAT_00583b6c);
  if (DAT_00583b70 < 0) {
    DAT_00583b70 = 0;
    return 0;
  }
  DAT_004d1718 = 1;
  return 1;
}

