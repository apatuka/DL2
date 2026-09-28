// FUN_00421340 @ 00421340 size=187 sig=undefined FUN_00421340() cc=unknown
// callers: FUN_004213fc,FUN_004217a0
// callees: FUN_0041ff24,FUN_0041b934,FUN_0041ff18

void FUN_00421340(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  cVar1 = FUN_0041b934(param_1,param_2,&local_8,&local_c);
  if (cVar1 != '\0') {
    DAT_004b7a18 = local_8;
    DAT_004b7a1c = local_c;
    if ((&DAT_004b7760)[local_8 * 0xd + local_c] == 1) {
      (&DAT_004b7760)[local_8 * 0xd + local_c] = 2;
    }
    else if ((&DAT_004b7760)[local_8 * 0xd + local_c] == 2) {
      (&DAT_004b7760)[local_8 * 0xd + local_c] = 1;
    }
    FUN_0041ff24(0x66,0x144,0x192,0x196);
    FUN_0041ff18();
  }
  return;
}

