// FUN_0045328c @ 0045328c size=193 sig=undefined FUN_0045328c() cc=unknown
// callers: FUN_0045539c,FUN_00453350
// callees: 

void FUN_0045328c(int param_1)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_1 + 4);
  if ((((iVar1 == 0xf) || (iVar1 == 0x1c)) || (iVar1 == 0x21)) || (iVar1 == 0x1a)) {
    bVar2 = false;
    uVar3 = (uint)*(byte *)(param_1 + 0x1e);
    for (iVar1 = *(int *)(DAT_0057cdf8 + 0x74); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x44)) {
      if ((((uVar3 == *(byte *)(iVar1 + 0x1e)) && (param_1 != iVar1)) &&
          ((*(char *)(iVar1 + 0x1d) != '\0' &&
           ((*(int *)(iVar1 + 4) == *(int *)(param_1 + 4) && (*(int *)(param_1 + 0x20) != 0x7f))))))
         && (*(int *)(param_1 + 0x24) != 0x7f)) {
        bVar2 = true;
        break;
      }
    }
    if (!bVar2) {
      iVar1 = *(int *)(param_1 + 4);
      if (iVar1 == 0xf) {
        *(undefined1 *)(DAT_0057cdf8 + 0xe + uVar3) = 0;
      }
      else if (iVar1 == 0x1a) {
        *(undefined1 *)(DAT_0057cdf8 + 0x23 + uVar3) = 0;
      }
      else if (iVar1 == 0x1c) {
        *(undefined1 *)(DAT_0057cdf8 + 0x1c + uVar3) = 0;
      }
      else if (iVar1 == 0x21) {
        *(undefined1 *)(DAT_0057cdf8 + 0x15 + uVar3) = 0;
      }
    }
  }
  return;
}

