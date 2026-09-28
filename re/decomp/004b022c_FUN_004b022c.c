// FUN_004b022c @ 004b022c size=28 sig=undefined FUN_004b022c() cc=unknown
// callers: FUN_004ac688
// callees: 

uint FUN_004b022c(uint param_1)

{
  if ((param_1 < 0x100) && (((&DAT_005209ce)[param_1 * 2] & 2) != 0)) {
    param_1 = param_1 - 0x20;
  }
  return param_1;
}

