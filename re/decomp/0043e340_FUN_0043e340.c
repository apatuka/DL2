// FUN_0043e340 @ 0043e340 size=60 sig=undefined FUN_0043e340() cc=unknown
// callers: FUN_00448dfc
// callees: FUN_00414ea4

void FUN_0043e340(void)

{
  int local_10;
  int local_c;
  int local_8;
  int local_4;
  
  if (DAT_004c4950 != 0) {
    local_10 = *(int *)(DAT_004c4950 + 8);
    local_c = *(int *)(DAT_004c4950 + 0xc);
    local_8 = *(int *)(DAT_004c4950 + 0x14) + local_10;
    local_4 = *(int *)(DAT_004c4950 + 0x10) + local_c;
    FUN_00414ea4(&local_10);
  }
  return;
}

