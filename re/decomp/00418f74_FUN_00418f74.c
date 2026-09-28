// FUN_00418f74 @ 00418f74 size=249 sig=undefined FUN_00418f74() cc=unknown
// callers: FUN_00419710
// callees: FUN_00417d44,FUN_0049eb44

void FUN_00418f74(void)

{
  if (DAT_004b76b8 == '\0') {
    if (*(char *)(DAT_004b76bc + 0x26) == '\0') {
      FUN_0049eb44(DAT_004b76b4,8,1,0xb,1,0);
      FUN_00417d44(0);
      return;
    }
    if (('\0' < *(char *)(DAT_004b76bc + 0x26)) && (*(char *)(DAT_004b76bc + 0x26) < '2')) {
      FUN_0049eb44(DAT_004b76b4,9,1,0xb,1,0);
      FUN_00417d44(0x19);
      return;
    }
    if (('1' < *(char *)(DAT_004b76bc + 0x26)) && (*(char *)(DAT_004b76bc + 0x26) < 'K')) {
      FUN_0049eb44(DAT_004b76b4,10,1,0xb,1,0);
      FUN_00417d44(0x32);
      return;
    }
    if (('J' < *(char *)(DAT_004b76bc + 0x26)) && (*(char *)(DAT_004b76bc + 0x26) < 'd')) {
      FUN_0049eb44(DAT_004b76b4,0xb,1,0xb,1,0);
      FUN_00417d44(0x4b);
      return;
    }
    if (*(char *)(DAT_004b76bc + 0x26) == 'd') {
      FUN_0049eb44(DAT_004b76b4,0xc,1,0xb,1,0);
      FUN_00417d44(100);
    }
  }
  return;
}

