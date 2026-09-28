// FUN_0043baa4 @ 0043baa4 size=80 sig=undefined FUN_0043baa4() cc=unknown
// callers: FUN_00448dfc
// callees: FUN_0043b7e4,FUN_00414ea4,FUN_0043afb0,FUN_0043b754,FUN_0043b008

void FUN_0043baa4(void)

{
  int local_10;
  int local_c;
  int local_8;
  int local_4;
  
  if (DAT_004c48a0 != 0) {
    local_10 = *(int *)(DAT_004c48a0 + 8);
    local_c = *(int *)(DAT_004c48a0 + 0xc);
    local_8 = *(int *)(DAT_004c48a0 + 0x14) + local_10;
    local_4 = *(int *)(DAT_004c48a0 + 0x10) + local_c;
    FUN_00414ea4(&local_10);
    FUN_0043b7e4();
    FUN_0043b754();
    FUN_0043b008();
    FUN_0043afb0();
  }
  return;
}

