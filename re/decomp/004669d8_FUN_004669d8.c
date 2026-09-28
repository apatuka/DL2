// FUN_004669d8 @ 004669d8 size=1027 sig=undefined FUN_004669d8() cc=unknown
// callers: FUN_004745b0,FUN_004634a0,FUN_0043044c,FUN_00413bc8,FUN_00413eb4
// callees: FUN_0044d284,FUN_00466464,FUN_004663b8,memset,FUN_0046686c

void FUN_004669d8(char param_1)

{
  int iVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_18;
  int local_14;
  int local_c;
  int local_8;
  
  DAT_0058eca4 = 0;
  local_8 = 0;
  do {
    iVar1 = local_8;
    iVar5 = local_8 * 0xadc;
    puVar6 = &DAT_005a43d0 + iVar5;
    if ((((DAT_004d5b18 < local_8) || ((&DAT_005a444e)[iVar5] == '\0')) || (DAT_0058f134 == 0)) ||
       ((*(byte *)((int)&DAT_005a43ec + iVar5 + 1) & 1) != 0)) {
      (&DAT_005a43ec)[local_8 * 0x2b7] = (&DAT_005a43ec)[local_8 * 0x2b7] | 0x100;
    }
    else {
      if (param_1 != '\0') {
        *(undefined2 *)(&DAT_005a4d82 + iVar5) = 0;
        iVar4 = FUN_0044d284(puVar6);
        if (iVar4 == 0) {
          (&DAT_005a4c7c)[iVar1 * 0x2b7] = 0;
        }
        else {
          (&DAT_005a4c7c)[iVar1 * 0x2b7] = 1;
        }
        if (((&DAT_005a43f1)[iVar5] != '\0') && (DAT_004d5a88 == 0)) {
          cVar2 = FUN_0046686c(puVar6);
          (&DAT_005a4c6f)[iVar5] = cVar2;
          if (cVar2 < '\b') {
            FUN_004663b8(puVar6);
          }
        }
        uVar3 = FUN_0046686c(puVar6);
        (&DAT_005a4c6f)[iVar5] = uVar3;
      }
      local_c = 0;
      do {
        iVar1 = local_c;
        memset(&local_30,0,0x24);
        FUN_00466464(puVar6,local_c % 6,local_c / 6,&local_30);
        iVar4 = (int)(char)(&DAT_005a43f1)[iVar5];
        if (*(short *)(puVar6 + iVar1 * 0x34 + 0x142) == 5) {
          *(undefined2 *)(puVar6 + iVar1 * 0x34 + 0x148) = 0;
          *(undefined2 *)(puVar6 + iVar1 * 0x34 + 0x14a) = 0;
          *(undefined2 *)(puVar6 + iVar1 * 0x34 + 0x146) = 0;
          *(undefined2 *)(puVar6 + iVar1 * 0x34 + 0x14c) = 0;
          *(undefined2 *)(puVar6 + iVar1 * 0x34 + 0x14e) = 0;
        }
        else if (iVar4 == 0) {
          *(undefined2 *)(puVar6 + iVar1 * 0x34 + 0x148) = 2000;
          *(undefined2 *)(puVar6 + iVar1 * 0x34 + 0x14a) = 0;
          *(undefined2 *)(puVar6 + iVar1 * 0x34 + 0x146) = 0xe10;
          *(undefined2 *)(puVar6 + iVar1 * 0x34 + 0x14c) = 0;
          *(undefined2 *)(puVar6 + iVar1 * 0x34 + 0x14e) = 0;
        }
        else {
          cVar2 = DAT_004d5b1c;
          if (DAT_004d5a90 == 0) {
            cVar2 = '\0';
          }
          *(short *)(puVar6 + iVar1 * 0x34 + 0x148) =
               (short)(((*(int *)(&DAT_004d4f1c + iVar4 * 0x14) + local_30 * 0xfa + local_28 * 0x96
                         + local_24 * 100 + local_2c * 0x32 + local_20 * 0x32 + local_18 * 300 +
                        local_14 * 0x96) * *(int *)(&DAT_004d4f94 + cVar2 * 0x14)) / 100);
          *(short *)(puVar6 + iVar1 * 0x34 + 0x14a) =
               (short)(((*(int *)(&DAT_004d4f20 + iVar4 * 0x14) + local_30 * 0x32 + local_28 * 0xfa
                         + local_24 * 300 + local_2c * 0x19 + local_20 * 0x19 + local_14 * 0x96) *
                       *(int *)(&DAT_004d4f98 + cVar2 * 0x14)) / 100);
          *(short *)(puVar6 + iVar1 * 0x34 + 0x146) =
               (short)(((*(int *)(&DAT_004d4f24 + iVar4 * 0x14) + local_30 * 0x4b + local_28 * 100 +
                         local_24 * 0x96 + local_2c * 300 + local_20 * 0x32 + local_18 * 0x19 +
                        local_14 * 0x4b) * *(int *)(&DAT_004d4f9c + cVar2 * 0x14)) / 100);
          *(short *)(puVar6 + iVar1 * 0x34 + 0x14c) =
               (short)(((*(int *)(&DAT_004d4f28 + iVar4 * 0x14) + local_30 * 0x32 + local_28 * 0x4b
                         + local_24 * 100 + local_2c * 100 + local_20 * 300 + local_14 * 0x96) *
                       *(int *)(&DAT_004d4fa0 + cVar2 * 0x14)) / 100);
          *(short *)(puVar6 + iVar1 * 0x34 + 0x14e) =
               (short)(((*(int *)(&DAT_004d4f2c + iVar4 * 0x14) + local_30 * 0x19 + local_28 * 0x4b
                         + local_24 * 0x7d + local_2c * 0x32 + local_20 * 100 + local_14 * 0x19) *
                       *(int *)(&DAT_004d4fa4 + cVar2 * 0x14)) / 100);
        }
        local_c = local_c + 1;
      } while (local_c < 0x24);
    }
    local_8 = local_8 + 1;
  } while (local_8 < 0x70);
  return;
}

