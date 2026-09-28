// FUN_004681ac @ 004681ac size=101 sig=undefined FUN_004681ac() cc=unknown
// callers: 
// callees: DialogBoxParamA

undefined4 FUN_004681ac(void)

{
  INT_PTR IVar1;
  
  DAT_004d5a50 = 0;
  DAT_004d5a4c = 0;
  DAT_004d5a58 = 0;
  IVar1 = DialogBoxParamA(DAT_0058f19c,&DAT_000022f6,DAT_0058f1a4,_GameStyleDialog_qqspvuiuil,0);
  if (IVar1 == 2) {
    return 0x35;
  }
  if (IVar1 == 10) {
    return 0x3c;
  }
  if (IVar1 == 0xb) {
    return 0x37;
  }
  if (IVar1 != 0xc) {
    return 0x35;
  }
  return 0x39;
}

