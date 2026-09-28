// FUN_0048df75 @ 0048df75 size=50 sig=undefined FUN_0048df75() cc=unknown
// callers: FUN_004a2ac6,FUN_004a32d7
// callees: FUN_0048de8e

uint FUN_0048df75(void)

{
  char cVar1;
  
  cVar1 = FUN_0048de8e();
  if (cVar1 != '\0') {
    return (int)*(short *)(&DAT_0065e7b4 + DAT_0065e7b0 * 4) |
           (int)*(short *)(&DAT_0065e7b6 + DAT_0065e7b0 * 4) << 0x10;
  }
  return 0;
}

