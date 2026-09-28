// FUN_004aff64 @ 004aff64 size=32 sig=undefined FUN_004aff64() cc=unknown
// callers: FUN_004ae26c,FUN_004ab1a0
// callees: 

ushort FUN_004aff64(uint param_1)

{
  if (0xff < param_1) {
    return 0;
  }
  return *(ushort *)(&DAT_005209ce + param_1 * 2) & 8;
}

