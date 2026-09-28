// FUN_00418704 @ 00418704 size=1415 sig=undefined FUN_00418704() cc=unknown
// callers: FUN_00418c8c
// callees: FUN_00490ab3,FUN_0048c85e,FUN_0041860c,FUN_0049aa64,FUN_00490796,FUN_0049a8ed,FUN_0049f22b,FUN_00498aab,FUN_00447a40,FUN_0049a93f,FUN_00418660,FUN_00496e80,FUN_0048c434

void FUN_00418704(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined1 local_68 [16];
  undefined4 local_58 [7];
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  uVar1 = DAT_0051bddc;
  FUN_0048c434(*(undefined4 *)(DAT_004b76b0 + 0x3c));
  local_74 = 0;
  do {
    iVar4 = 0;
    if ((DAT_005332bc + local_74 < 100) &&
       ((&DAT_00533405)[(DAT_005332bc + local_74) * 0x146] == '\0')) {
      do {
        iVar5 = iVar4 * 0x20;
        if (*(int *)((int)&DAT_005332d8 + iVar5 + (DAT_005332bc + local_74) * 0x146) != 0) {
          FUN_0041860c(&local_70,&local_6c,iVar4,local_74);
          if (*(int *)((int)&DAT_005332d8 + iVar5 + (DAT_005332bc + local_74) * 0x146) == 1) {
            FUN_0049a8ed();
            FUN_0049f22b(DAT_004b76b0,local_68);
            FUN_0049aa64(local_68);
            iVar2 = FUN_00490ab3(0,0x47414d49,
                                 *(undefined4 *)
                                  (&DAT_005332c4 + iVar5 + (DAT_005332bc + local_74) * 0x146),0,0);
            if (iVar2 != 0) {
              uVar3 = FUN_00498aab(iVar2,1);
              FUN_00496e80(uVar3,*(undefined4 *)
                                  (&DAT_005332c8 + iVar5 + (DAT_005332bc + local_74) * 0x146),
                           *(undefined4 *)
                            (&DAT_005332cc + iVar5 + (DAT_005332bc + local_74) * 0x146),0,local_70,
                           local_6c,0xffffffff);
              FUN_00498aab(iVar2,0);
              FUN_00490796(iVar2,0);
            }
            puVar6 = (undefined4 *)(&DAT_005332c0 + iVar5 + (DAT_005332bc + local_74) * 0x146);
            puVar7 = local_58;
            for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
              *puVar7 = *puVar6;
              puVar6 = puVar6 + 1;
              puVar7 = puVar7 + 1;
            }
            FUN_00418660(local_58,(int)*(char *)(*(int *)((int)&DAT_005332dc +
                                                         iVar5 + (DAT_005332bc + local_74) * 0x146)
                                                + 6));
            local_58[1] = 0x31304c53;
            iVar2 = FUN_00490ab3(0,0x47414d49,0x31304c53,0,0);
            if (iVar2 != 0) {
              uVar3 = FUN_00498aab(iVar2,1);
              FUN_00496e80(uVar3,local_58[2],local_58[3],0,local_70,local_6c,0xffffffff);
              FUN_00498aab(iVar2,0);
              FUN_00490796(iVar2,0);
            }
            local_34 = 0;
            local_3c = 0x31305741;
            iVar5 = FUN_00447a40((int)*(short *)(*(int *)((int)&DAT_005332dc +
                                                         iVar5 + (DAT_005332bc + local_74) * 0x146)
                                                + 0x28));
            if (iVar5 != 0) {
              if (iVar5 == 1) {
                local_38 = 0x3eb;
                iVar5 = FUN_00490ab3(0,0x47414d49,local_3c,0,0);
                if (iVar5 != 0) {
                  uVar3 = FUN_00498aab(iVar5,1);
                  FUN_00496e80(uVar3,local_38,local_34,0,local_70,local_6c,0xffffffff);
                  FUN_00498aab(iVar5,0);
                  FUN_00490796(iVar5,0);
                }
              }
              else if (iVar5 == 2) {
                local_38 = 0x3ec;
                iVar5 = FUN_00490ab3(0,0x47414d49,local_3c,0,0);
                if (iVar5 != 0) {
                  uVar3 = FUN_00498aab(iVar5,1);
                  FUN_00496e80(uVar3,local_38,local_34,0,local_70,local_6c,0xffffffff);
                  FUN_00498aab(iVar5,0);
                  FUN_00490796(iVar5,0);
                }
              }
            }
            FUN_0049a93f();
          }
          else {
            iVar5 = iVar4 * 0x20;
            if (*(int *)((int)&DAT_005332d8 + iVar5 + (DAT_005332bc + local_74) * 0x146) == 2) {
              FUN_0049a8ed();
              FUN_0049f22b(DAT_004b76b0,local_68);
              FUN_0049aa64(local_68);
              iVar2 = FUN_00490ab3(0,0x47414d49,
                                   *(undefined4 *)
                                    (&DAT_005332c4 + iVar5 + (DAT_005332bc + local_74) * 0x146),0,0)
              ;
              if (iVar2 != 0) {
                uVar3 = FUN_00498aab(iVar2,1);
                FUN_00496e80(uVar3,*(undefined4 *)
                                    (&DAT_005332c8 + iVar5 + (DAT_005332bc + local_74) * 0x146),
                             *(undefined4 *)
                              (&DAT_005332cc + iVar5 + (DAT_005332bc + local_74) * 0x146),0,local_70
                             ,local_6c,0xffffffff);
                FUN_00498aab(iVar2,0);
                FUN_00490796(iVar2,0);
              }
              local_1c = 0;
              local_24 = 0x31305741;
              iVar5 = FUN_00447a40((int)*(short *)(*(int *)((int)&DAT_005332dc +
                                                           iVar5 + (DAT_005332bc + local_74) * 0x146
                                                           ) + 0x28));
              if (iVar5 != 0) {
                if (iVar5 == 1) {
                  local_20 = 0x3ec;
                  iVar5 = FUN_00490ab3(0,0x47414d49,local_24,0,0);
                  if (iVar5 != 0) {
                    uVar3 = FUN_00498aab(iVar5,1);
                    FUN_00496e80(uVar3,local_20,local_1c,0,local_70,local_6c,0xffffffff);
                    FUN_00498aab(iVar5,0);
                    FUN_00490796(iVar5,0);
                  }
                }
                else if (iVar5 == 2) {
                  local_20 = 0x3ed;
                  iVar5 = FUN_00490ab3(0,0x47414d49,local_24,0,0);
                  if (iVar5 != 0) {
                    uVar3 = FUN_00498aab(iVar5,1);
                    FUN_00496e80(uVar3,local_20,local_1c,0,local_70,local_6c,0xffffffff);
                    FUN_00498aab(iVar5,0);
                    FUN_00490796(iVar5,0);
                  }
                }
              }
              FUN_0049a93f();
            }
          }
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < 10);
    }
    local_74 = local_74 + 1;
  } while (local_74 < 3);
  if (((DAT_004b76b0 != 0) && (*(int *)(DAT_004b76b0 + 0x3c) != 0)) &&
     ((*(byte *)(DAT_004b76b0 + 0x1c) & 2) != 0)) {
    FUN_0048c85e(*(undefined4 *)(DAT_004b76b0 + 0x3c),&DAT_0065e644,local_68,local_68,0,
                 &DAT_0065e580,0);
  }
  FUN_0048c434(uVar1);
  return;
}

