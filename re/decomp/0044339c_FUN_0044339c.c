// FUN_0044339c @ 0044339c size=269 sig=undefined FUN_0044339c() cc=unknown
// callers: FUN_004437c4
// callees: FUN_004412d4,FUN_004012dc,FUN_0046c3fc,FUN_0044d230

void FUN_0044339c(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined1 local_c [4];
  int local_8;
  
  puVar2 = &DAT_005a4eac;
  do {
    if (&DAT_005a43d0 + DAT_004d5b18 * 0xadc < puVar2) {
      return;
    }
    if (((*(char *)((int)puVar2 + 0x21) != '\0') && (*(char *)(puVar2 + 8) != -1)) &&
       (*(short *)(puVar2 + 0xc) != 0)) {
      iVar1 = FUN_0044d230(puVar2,0x13,0);
      if (iVar1 == -1) {
        FUN_0046c3fc(puVar2,&local_8,local_c);
        iVar3 = (int)*(char *)(puVar2 + 8);
        iVar4 = (int)*(short *)((int)puVar2 + 0x1a);
        iVar1 = FUN_004012dc(iVar3,0x17,*(uint *)(&DAT_0055eba0 + iVar4 * 4) & (uint)(1 < iVar3),
                             *(uint *)(&DAT_0055ef20 + iVar4 * 4) & (uint)(1 < iVar3),0,0);
        iVar1 = iVar1 * *(int *)(&DAT_0055f9a0 + iVar3 * 4 + iVar4 * 0x1c) * local_8;
        (&DAT_0055a804)[*(char *)(puVar2 + 8)] = (&DAT_0055a804)[*(char *)(puVar2 + 8)] + iVar1;
        if (*(char *)(puVar2 + 8) != param_1) {
          iVar3 = FUN_004412d4(param_1,(int)*(char *)(puVar2 + 8),2);
          if (iVar3 == 0) {
            puVar2[0x294] = puVar2[0x294] + iVar1;
            puVar2[0x296] = puVar2[0x296] + iVar1;
            goto LAB_0044347f;
          }
        }
        *(int *)((int)puVar2 + 0xa0a) = *(int *)((int)puVar2 + 0xa0a) + iVar1;
        *(int *)((int)puVar2 + 0xa12) = *(int *)((int)puVar2 + 0xa12) + iVar1;
      }
    }
LAB_0044347f:
    puVar2 = puVar2 + 0x2b7;
  } while( true );
}

