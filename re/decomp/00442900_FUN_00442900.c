// FUN_00442900 @ 00442900 size=117 sig=undefined FUN_00442900() cc=unknown
// callers: FUN_00442c44,FUN_004180b0,FUN_00442978,FUN_00403f14
// callees: 

undefined4 FUN_00442900(int param_1,int param_2)

{
  if (*(char *)(param_1 + 6) != '\0') {
    if (param_2 == *(char *)(param_1 + 8)) {
      return *(undefined4 *)(param_1 + 0x3c);
    }
    if (('\x01' < *(char *)(*(int *)(param_1 + 0x38) + 0x66 + param_2)) &&
       (((*(byte *)(param_1 + 2) & 1) == 0 || ((param_2 == DAT_0058f1f4 && (DAT_00583c20 != 0))))))
    {
      return *(undefined4 *)(param_1 + 0x38);
    }
    if (('\x02' < (char)(&DAT_0059f161)[param_2 * 0x2d8]) && ((*(byte *)(param_1 + 2) & 1) == 0)) {
      return *(undefined4 *)(param_1 + 0x38);
    }
  }
  return 0;
}

