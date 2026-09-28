// __assertfail @ 004b1210 size=94 sig=undefined __assertfail() cc=unknown
// callers: FUN_004a90cc,FUN_004a75c4,FUN_004a86dc,FUN_004a8c58,FUN_004a76d2,FUN_004a8bdc,FUN_004a7c1f,FUN_004a7d1c,Local_unwind,_ExceptionHandler,FUN_004a7c94,FUN_004a9564,FUN_004a881e,FUN_004a91de,FUN_004a95c1,FUN_004a9828,FUN_004a99f8,FUN_004a78a4,FUN_004a7826,FUN_004a7df4,FUN_004a9956,FUN_004a8ab8,FUN_004a9103
// callees: FUN_004b11c8,FUN_004ae488,strlen,FUN_004b1570,FUN_004b17d4
// strings: \", line \"|\", file \"|\"Assertion failed: \"

/* RTL: "Assertion failed: , file , line " */

void __assertfail(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  FUN_004b11c8(&DAT_0069f67c,0xf6,s_Assertion_failed__0052122c,param_1,s___file_0052123f,param_2,
               s___line_00521247,0);
  iVar1 = strlen(&DAT_0069f67c);
  FUN_004ae488(param_3,&DAT_0069f67c + iVar1);
  FUN_004b1570(&DAT_0069f67c);
  FUN_004b17d4();
  return;
}

