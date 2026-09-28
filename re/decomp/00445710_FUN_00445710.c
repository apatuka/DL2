// FUN_00445710 @ 00445710 size=106 sig=undefined FUN_00445710() cc=unknown
// callers: FUN_0046147c,WinMain,FUN_0047c03c
// callees: FUN_004455fc

void FUN_00445710(void)

{
  char *pcVar1;
  int iVar2;
  
  DAT_004c515c = (undefined2 *)0x0;
  iVar2 = 0;
  pcVar1 = &DAT_00645376;
  do {
    if (*pcVar1 == '\0') {
      *(undefined2 **)(pcVar1 + 0x4e) = DAT_004c515c;
      DAT_004c515c = &DAT_00645370 + iVar2 * 0x2e;
      pcVar1[0x52] = '\0';
      pcVar1[0x53] = '\0';
      pcVar1[0x54] = '\0';
      pcVar1[0x55] = '\0';
      if (*(int *)(pcVar1 + 0x4e) != 0) {
        *(undefined2 **)(*(int *)(pcVar1 + 0x4e) + 0x58) = &DAT_00645370 + iVar2 * 0x2e;
      }
    }
    iVar2 = iVar2 + 1;
    pcVar1 = pcVar1 + 0x5c;
  } while (iVar2 < 0x230);
  FUN_004455fc(1);
  return;
}

