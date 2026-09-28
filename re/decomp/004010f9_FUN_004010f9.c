// FUN_004010f9 @ 004010f9 size=15 sig=undefined FUN_004010f9() cc=unknown
// callers: FUN_004a7d1c,FUN_004a72d6,FUN_004a7182,FUN_004a78a4,FUN_004a71aa,FUN_004a70a2,_ExceptionHandler,FUN_004a70ca,FUN_004a7b8d,Local_unwind,FUN_004a74d5,FUN_004a76d2,FUN_004a723b,FUN_004a748b
// callees: 

undefined4 FUN_004010f9(void)

{
  int *piVar1;
  undefined2 in_FS;
  
  piVar1 = (int *)segment(in_FS,0x2c);
  return *(undefined4 *)(*piVar1 + _tls_index * 4);
}

