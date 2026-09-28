// FUN_00442978 @ 00442978 size=716 sig=undefined FUN_00442978() cc=unknown
// callers: FUN_004437c4
// callees: FUN_0046c3fc,FUN_00442900,FUN_00447190,FUN_0044d230,FUN_00446b3c

void FUN_00442978(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined1 local_c [4];
  int local_8;
  
  for (puVar8 = (undefined4 *)&DAT_00645370; puVar8 < &DAT_00651cb0; puVar8 = puVar8 + 0x17) {
    puVar2 = (undefined4 *)FUN_00442900(puVar8,param_1);
    if (puVar2 != (undefined4 *)0x0) {
      cVar1 = *(char *)((int)puVar8 + 6);
      if ((&DAT_004faf87)[cVar1 * 0x24] != '\t') {
        *(int *)(&DAT_0055f9a0 + *(char *)(puVar8 + 2) * 4 + *(short *)((int)puVar2 + 0x1a) * 0x1c)
             = *(int *)(&DAT_0055f9a0 +
                       *(char *)(puVar8 + 2) * 4 + *(short *)((int)puVar2 + 0x1a) * 0x1c) + 1;
      }
      if (cVar1 == '\x0f') {
        *(uint *)(&DAT_0055ef20 + *(short *)((int)puVar2 + 0x1a) * 4) =
             *(uint *)(&DAT_0055ef20 + *(short *)((int)puVar2 + 0x1a) * 4) |
             1 << (*(byte *)(puVar8 + 2) & 0x1f);
      }
      else if (cVar1 == '\x1a') {
        *(uint *)(&DAT_0055eba0 + *(short *)((int)puVar2 + 0x1a) * 4) =
             *(uint *)(&DAT_0055eba0 + *(short *)((int)puVar2 + 0x1a) * 4) |
             1 << (*(byte *)(puVar8 + 2) & 0x1f);
      }
      else if (cVar1 == '\x1c') {
        *(uint *)(&DAT_0055f2a0 + *(short *)((int)puVar2 + 0x1a) * 4) =
             *(uint *)(&DAT_0055f2a0 + *(short *)((int)puVar2 + 0x1a) * 4) |
             1 << (*(byte *)(puVar8 + 2) & 0x1f);
      }
      else if (cVar1 == '!') {
        *(uint *)(&DAT_0055f620 + *(short *)((int)puVar2 + 0x1a) * 4) =
             *(uint *)(&DAT_0055f620 + *(short *)((int)puVar2 + 0x1a) * 4) |
             1 << (*(byte *)(puVar8 + 2) & 0x1f);
      }
      iVar7 = 0x2000 << (*(byte *)(puVar8 + 2) & 0x1f);
      iVar3 = (int)*(char *)(puVar8 + 2);
      iVar4 = (int)(char)(&DAT_004faf8d)[*(char *)((int)puVar8 + 6) * 0x24];
      cVar1 = FUN_00447190(puVar8);
      FUN_00446b3c(puVar8[0xe],(int)cVar1,iVar4,iVar3,iVar7);
      for (puVar5 = &DAT_005a4eac; puVar5 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
          puVar5 = puVar5 + 0x2b7) {
        if (((0x2000 << (*(byte *)(puVar8 + 2) & 0x1f) & puVar5[7]) != 0) && (puVar2 != puVar5)) {
          *(int *)(&DAT_005605e0 +
                  (char)*(byte *)(puVar8 + 2) * 4 + *(short *)((int)puVar5 + 0x1a) * 0x1c) =
               *(int *)(&DAT_005605e0 +
                       (char)*(byte *)(puVar8 + 2) * 4 + *(short *)((int)puVar5 + 0x1a) * 0x1c) + 1;
          cVar1 = *(char *)((int)puVar8 + 6);
          if (cVar1 == '\x0f') {
            *(uint *)(&DAT_0055f0e0 + *(short *)((int)puVar5 + 0x1a) * 4) =
                 *(uint *)(&DAT_0055f0e0 + *(short *)((int)puVar5 + 0x1a) * 4) |
                 1 << (*(byte *)(puVar8 + 2) & 0x1f);
          }
          else if (cVar1 == '\x1a') {
            *(uint *)(&DAT_0055ed60 + *(short *)((int)puVar5 + 0x1a) * 4) =
                 *(uint *)(&DAT_0055ed60 + *(short *)((int)puVar5 + 0x1a) * 4) |
                 1 << (*(byte *)(puVar8 + 2) & 0x1f);
          }
          else if (cVar1 == '\x1c') {
            *(uint *)(&DAT_0055f460 + *(short *)((int)puVar5 + 0x1a) * 4) =
                 *(uint *)(&DAT_0055f460 + *(short *)((int)puVar5 + 0x1a) * 4) |
                 1 << (*(byte *)(puVar8 + 2) & 0x1f);
          }
          else if (cVar1 == '!') {
            *(uint *)(&DAT_0055f7e0 + *(short *)((int)puVar5 + 0x1a) * 4) =
                 *(uint *)(&DAT_0055f7e0 + *(short *)((int)puVar5 + 0x1a) * 4) |
                 1 << (*(byte *)(puVar8 + 2) & 0x1f);
          }
        }
      }
    }
  }
  for (puVar8 = &DAT_005a4eac; puVar8 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar8 = puVar8 + 0x2b7) {
    if (*(char *)((int)puVar8 + 0x7e) != '\0') {
      if (*(short *)(puVar8 + 0xc) != 0) {
        iVar7 = 0;
        piVar6 = puVar8 + 0x55;
        do {
          if ((*piVar6 != 0) && (*(char *)(*piVar6 + 5) == '\x12')) {
            *(int *)(&DAT_0055f9a0 +
                    *(char *)(puVar8 + 8) * 4 + *(short *)((int)puVar8 + 0x1a) * 0x1c) =
                 *(int *)(&DAT_0055f9a0 +
                         *(char *)(puVar8 + 8) * 4 + *(short *)((int)puVar8 + 0x1a) * 0x1c) + 1;
          }
          iVar7 = iVar7 + 1;
          piVar6 = piVar6 + 0xd;
        } while (iVar7 < 0x24);
      }
      if ((1 << ((byte)param_1 & 0x1f) & puVar8[0x22a]) != 0) {
        *(int *)(&DAT_0055f9a0 + *(short *)((int)puVar8 + 0x1a) * 0x1c + param_1 * 4) =
             *(int *)(&DAT_0055f9a0 + *(short *)((int)puVar8 + 0x1a) * 0x1c + param_1 * 4) + 6;
      }
      if ((((*(char *)((int)puVar8 + 0x21) != '\0') && (*(char *)(puVar8 + 8) != -1)) &&
          (*(short *)(puVar8 + 0xc) != 0)) && (iVar7 = FUN_0044d230(puVar8,0x13,0), iVar7 == -1)) {
        FUN_0046c3fc(puVar8,&local_8,local_c);
        *(int *)(&DAT_0055f9a0 + *(char *)(puVar8 + 8) * 4 + *(short *)((int)puVar8 + 0x1a) * 0x1c)
             = *(int *)(&DAT_0055f9a0 +
                       *(char *)(puVar8 + 8) * 4 + *(short *)((int)puVar8 + 0x1a) * 0x1c) + local_8;
      }
    }
  }
  return;
}

