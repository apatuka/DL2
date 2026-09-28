// AnyKnown @ 004851a8 size=67 sig=undefined AnyKnown() cc=unknown
// callers: 
// callees: FUN_0046c9d8
// strings: \"AnyKnown\"

/* auto-named from string evidence: AnyKnown */

int AnyKnown(byte param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0046c9d8(0x30,s_AnyKnown_005123d3);
  iVar2 = iVar1;
  do {
    if (((int)(short)(&DAT_004fbbac)[iVar2 * 0x19] & 1 << (param_1 & 0x1f)) != 0) {
      return iVar2;
    }
    iVar2 = iVar2 + 1;
    if (0x2f < iVar2) {
      iVar2 = 0;
    }
  } while (iVar1 != iVar2);
  return 0;
}

