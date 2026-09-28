// FUN_0045727c @ 0045727c size=933 sig=undefined FUN_0045727c() cc=unknown
// callers: FUN_00457624
// callees: FUN_004412d4,FUN_00401108,FUN_00423690,FUN_0045723c,memset,FUN_00446084

void FUN_0045727c(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined *puVar6;
  undefined4 *local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  undefined4 *local_24;
  undefined4 *local_20;
  undefined *local_14;
  
  memset(&DAT_0057f254,0,0x4600);
  puVar5 = &DAT_005a4eac;
  do {
    if (&DAT_005a43d0 + DAT_004d5b18 * 0xadc < puVar5) {
      for (local_38 = &DAT_005a4eac; local_38 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
          local_38 = local_38 + 0x2b7) {
        if (*(char *)((int)local_38 + 0x7e) != '\0') {
          for (puVar5 = &DAT_005a4eac; puVar5 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
              puVar5 = puVar5 + 0x2b7) {
            if (*(char *)((int)puVar5 + 0x7e) != '\0') {
              local_34 = 0;
              local_14 = &DAT_0057f254;
              do {
                local_30 = 0;
                puVar6 = &DAT_0057f254;
                do {
                  if ((((*(int *)(local_14 + *(short *)((int)local_38 + 0x1a) * 0xa0 + 4) !=
                         *(int *)(puVar6 + *(short *)((int)puVar5 + 0x1a) * 0xa0 + 4)) &&
                       (iVar2 = FUN_004412d4(*(int *)(local_14 +
                                                     *(short *)((int)local_38 + 0x1a) * 0xa0 + 4),
                                             *(undefined4 *)
                                              (puVar6 + *(short *)((int)puVar5 + 0x1a) * 0xa0 + 4),2
                                            ), iVar2 == 0)) &&
                      (*(int *)(local_14 + *(short *)((int)local_38 + 0x1a) * 0xa0) ==
                       (int)*(short *)((int)puVar5 + 0x1a))) &&
                     ((*(int *)(puVar6 + *(short *)((int)puVar5 + 0x1a) * 0xa0) ==
                       (int)*(short *)((int)local_38 + 0x1a) &&
                      (*(short *)((int)local_38 + 0x1a) < *(short *)((int)puVar5 + 0x1a))))) {
                    iVar4 = (int)*(short *)((int)local_38 + 0x1a);
                    iVar2 = (int)*(short *)((int)puVar5 + 0x1a);
                    if (*(int *)(puVar6 + iVar2 * 0xa0 + 0xc) * *(int *)(puVar6 + iVar2 * 0xa0 + 8)
                        - *(int *)(local_14 + iVar4 * 0xa0 + 0xc) *
                          *(int *)(local_14 + iVar4 * 0xa0 + 8) == 0 ||
                        *(int *)(puVar6 + iVar2 * 0xa0 + 0xc) * *(int *)(puVar6 + iVar2 * 0xa0 + 8)
                        < *(int *)(local_14 + iVar4 * 0xa0 + 0xc) *
                          *(int *)(local_14 + iVar4 * 0xa0 + 8)) {
                      local_2c = *(int *)(puVar6 + iVar2 * 0xa0 + 4);
                      local_28 = *(int *)(local_14 + iVar4 * 0xa0 + 4);
                      local_24 = local_38;
                      local_20 = puVar5;
                    }
                    else {
                      local_2c = *(int *)(local_14 + iVar4 * 0xa0 + 4);
                      local_28 = *(int *)(puVar6 + iVar2 * 0xa0 + 4);
                      local_20 = local_38;
                      local_24 = puVar5;
                    }
                    iVar2 = *(int *)((int)local_20 + 0x7a);
                    while (iVar4 = iVar2, iVar4 != 0) {
                      iVar2 = *(int *)(iVar4 + 0x54);
                      if (((*(char *)(iVar4 + 8) == local_2c) &&
                          (*(undefined4 **)(iVar4 + 0x38) == local_24)) &&
                         (iVar3 = FUN_0045723c(iVar4), iVar3 != 0)) {
                        FUN_00446084(iVar4,*(undefined4 *)(iVar4 + 0x38),0);
                      }
                    }
                    FUN_00423690(local_2c,0x98,local_20,
                                 (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[local_28 * 0x2d8]],
                                 local_24,0);
                  }
                  local_30 = local_30 + 1;
                  puVar6 = puVar6 + 0x10;
                } while (local_30 < 10);
                local_34 = local_34 + 1;
                local_14 = local_14 + 0x10;
              } while (local_34 < 10);
            }
          }
        }
      }
      return;
    }
    if (*(char *)((int)puVar5 + 0x7e) != '\0') {
      for (iVar2 = *(int *)((int)puVar5 + 0x7a); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x54)) {
        iVar4 = FUN_0045723c(iVar2);
        if (iVar4 != 0) {
          iVar4 = 0;
          puVar6 = &DAT_0057f254;
          do {
            iVar3 = iVar4;
            if ((*(int *)(puVar6 + *(short *)((int)puVar5 + 0x1a) * 0xa0 + 0xc) == 0) ||
               ((*(int *)(puVar6 + *(short *)((int)puVar5 + 0x1a) * 0xa0) ==
                 (int)*(short *)(*(int *)(iVar2 + 0x38) + 0x1a) &&
                (*(int *)(puVar6 + *(short *)((int)puVar5 + 0x1a) * 0xa0 + 4) ==
                 (int)*(char *)(iVar2 + 8))))) break;
            iVar4 = iVar4 + 1;
            puVar6 = puVar6 + 0x10;
            iVar3 = -1;
          } while (iVar4 < 10);
          if (iVar3 != -1) {
            iVar3 = iVar3 * 0x10;
            sVar1 = *(short *)((int)puVar5 + 0x1a);
            *(int *)(&DAT_0057f254 + iVar3 + sVar1 * 0xa0) =
                 (int)*(short *)(*(int *)(iVar2 + 0x38) + 0x1a);
            *(int *)(&DAT_0057f258 + iVar3 + sVar1 * 0xa0) = (int)*(char *)(iVar2 + 8);
            iVar4 = FUN_00401108(iVar2,0,0,0,0);
            *(int *)(&DAT_0057f25c + iVar3 + *(short *)((int)puVar5 + 0x1a) * 0xa0) =
                 *(int *)(&DAT_0057f25c + iVar3 + *(short *)((int)puVar5 + 0x1a) * 0xa0) + iVar4;
            *(int *)(&DAT_0057f260 + iVar3 + *(short *)((int)puVar5 + 0x1a) * 0xa0) =
                 *(int *)(&DAT_0057f260 + iVar3 + *(short *)((int)puVar5 + 0x1a) * 0xa0) + 1;
          }
        }
      }
    }
    puVar5 = puVar5 + 0x2b7;
  } while( true );
}

