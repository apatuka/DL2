// FUN_00449d54 @ 00449d54 size=94 sig=undefined FUN_00449d54() cc=unknown
// callers: FUN_0045e99c,FUN_00419c08,FUN_0045d478,FUN_00437134,FUN_0045e8e8,FUN_0045d6a4
// callees: FUN_00449fe8,FUN_004812f4,FUN_0045dfd4,FUN_00449fd8

void FUN_00449d54(int param_1)

{
  if ('\x02' < (char)(&DAT_005a4436)[DAT_0058f1f4 + param_1 * 0xadc]) {
    FUN_004812f4(DAT_004d5acc,
                 (int)*(char *)(&DAT_005a4450)
                               [param_1 * 0x2b7 + (int)(char)(&DAT_005a4444)[param_1 * 0xadc]],
                 (int)((char *)(&DAT_005a4450)
                               [param_1 * 0x2b7 + (int)(char)(&DAT_005a4444)[param_1 * 0xadc]])[1]);
    FUN_0045dfd4(param_1,1);
    FUN_00449fe8();
    FUN_00449fd8();
  }
  return;
}

