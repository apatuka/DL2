// FUN_00456618 @ 00456618 size=170 sig=undefined FUN_00456618() cc=unknown
// callers: FUN_0046fa54,FUN_004566c4,FUN_004568c8
// callees: 

void FUN_00456618(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  do {
    iVar2 = iVar3 * 0x34 + param_1;
    *(undefined1 *)(iVar2 + 0x158) = 0;
    iVar1 = *(int *)(iVar2 + 0x154);
    if (iVar1 == 0) {
      if ((((int)(short)*(ushort *)(iVar2 + 0x142) & 0xf000U) == 0x4000) &&
         ((*(ushort *)(iVar2 + 0x142) & 0x100) == 0)) {
        *(undefined1 *)(iVar2 + 0x158) = *(undefined1 *)(*(int *)(iVar2 + 600) + 4);
        *(undefined1 *)(iVar2 + 0x159) = *(undefined1 *)(*(int *)(iVar2 + 600) + 6);
      }
      else if (((int)*(short *)(iVar2 + 0x142) & 0xf000U) == 0x6000) {
        *(undefined1 *)(iVar2 + 0x158) = *(undefined1 *)(*(int *)(iVar2 + 0x634) + 4);
        *(undefined1 *)(iVar2 + 0x159) = *(undefined1 *)(*(int *)(iVar2 + 0x634) + 6);
      }
    }
    else if ((&DAT_004f9dc5)[*(char *)(iVar1 + 4) * 0x32] == '\x01') {
      *(undefined1 *)(iVar2 + 0x158) = *(undefined1 *)(iVar1 + 4);
      *(undefined1 *)(iVar2 + 0x159) = *(undefined1 *)(iVar1 + 6);
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x24);
  return;
}

