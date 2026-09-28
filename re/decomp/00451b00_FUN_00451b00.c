// FUN_00451b00 @ 00451b00 size=103 sig=undefined FUN_00451b00() cc=unknown
// callers: FUN_00451b68,FUN_00456e44
// callees: 

void FUN_00451b00(int param_1)

{
  if (*(int *)(param_1 + 4) == 0xf) {
    *(undefined1 *)(DAT_0057cdf8 + 0xe + (uint)*(byte *)(param_1 + 0x1e)) = 1;
  }
  if (*(int *)(param_1 + 4) == 0x21) {
    *(undefined1 *)(DAT_0057cdf8 + 0x15 + (uint)*(byte *)(param_1 + 0x1e)) = 1;
  }
  if (*(int *)(param_1 + 4) == 0x1c) {
    *(undefined1 *)(DAT_0057cdf8 + 0x1c + (uint)*(byte *)(param_1 + 0x1e)) = 1;
  }
  if (*(int *)(param_1 + 4) == 0x1a) {
    *(undefined1 *)(DAT_0057cdf8 + 0x23 + (uint)*(byte *)(param_1 + 0x1e)) = 1;
  }
  return;
}

