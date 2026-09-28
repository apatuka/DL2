// FUN_004431bc @ 004431bc size=278 sig=undefined FUN_004431bc() cc=unknown
// callers: FUN_004437c4
// callees: FUN_004012dc

void FUN_004431bc(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar3 = puVar3 + 0x2b7) {
    if (((*(char *)((int)puVar3 + 0x7e) != '\0') && ('\0' < *(char *)((int)puVar3 + param_1 + 0x66))
        ) && (uVar1 = (uint)*(char *)((int)puVar3 + 0x22), uVar1 < 0x20)) {
      if (param_1 == *(char *)(puVar3 + 8)) {
        (&DAT_0055a832)[uVar1 * 0xd1] = (&DAT_0055a832)[uVar1 * 0xd1] + 1;
      }
      else if (*(char *)(puVar3 + 8) == -1) {
        (&DAT_0055a834)[uVar1 * 0xd1] = (&DAT_0055a834)[uVar1 * 0xd1] + 1;
      }
      else {
        (&DAT_0055a830)[uVar1 * 0xd1] = (&DAT_0055a830)[uVar1 * 0xd1] + 1;
      }
    }
    if ((1 << ((byte)param_1 & 0x1f) & puVar3[0x22a]) != 0) {
      if (*(char *)((int)puVar3 + 0x21) == '\0') {
        iVar2 = FUN_004012dc(param_1,0x26,0,0,0,0);
        iVar2 = iVar2 * *(int *)(&DAT_0055f9a0 + *(short *)((int)puVar3 + 0x1a) * 0x1c + param_1 * 4
                                );
      }
      else {
        iVar2 = FUN_004012dc(param_1,0x25,0,0,0,0);
        iVar2 = iVar2 * *(int *)(&DAT_0055f9a0 + *(short *)((int)puVar3 + 0x1a) * 0x1c + param_1 * 4
                                );
      }
      iVar2 = iVar2 * 6;
      (&DAT_0055a804)[param_1] = (&DAT_0055a804)[param_1] + iVar2;
      *(int *)((int)puVar3 + 0xa0a) = *(int *)((int)puVar3 + 0xa0a) + iVar2;
      *(int *)((int)puVar3 + 0xa12) = *(int *)((int)puVar3 + 0xa12) + iVar2;
    }
  }
  return;
}

