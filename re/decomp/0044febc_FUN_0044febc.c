// FUN_0044febc @ 0044febc size=45 sig=undefined FUN_0044febc() cc=unknown
// callers: FUN_00450094,FUN_00415924,FUN_00450058,FUN_00450320
// callees: FUN_0044fdf0

undefined4 FUN_0044febc(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0044fdf0(param_1);
  return *(undefined4 *)(&DAT_004c61e0 + iVar1 * 0x44 + DAT_004d5a94 * 0xd8);
}

