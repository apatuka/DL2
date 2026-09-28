// FUN_00410c18 @ 00410c18 size=90 sig=undefined FUN_00410c18() cc=unknown
// callers: FUN_00410d24
// callees: FUN_004ac634,FUN_004aa948,FUN_004b185c
// strings: \"ERROR: Premature EOF in input!\\n\"

byte FUN_00410c18(undefined4 param_1)

{
  byte bVar1;
  int iVar2;
  
  if (DAT_00533198 == 0) {
    DAT_00533198 = 8;
    iVar2 = FUN_004ac634(param_1);
    if (iVar2 == -1) {
      FUN_004aa948(s_ERROR__Premature_EOF_in_input__004b6f92);
      FUN_004b185c(0xffffffff);
    }
    DAT_0053319c = (byte)iVar2;
  }
  bVar1 = DAT_0053319c;
  DAT_0053319c = DAT_0053319c >> 1;
  DAT_00533198 = DAT_00533198 + -1;
  return bVar1 & 1;
}

