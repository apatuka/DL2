// FUN_00461078 @ 00461078 size=567 sig=undefined FUN_00461078() cc=unknown
// callers: FUN_004618e8
// callees: FUN_00460f68,ReadFile,FUN_00401830,FUN_004423b4,memset,FUN_0047510c

undefined4 FUN_00461078(HANDLE param_1,int param_2)

{
  BOOL BVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  int *local_18;
  int *local_14;
  int local_10;
  int local_c;
  DWORD local_8;
  
  if (DAT_00583da4 < 3) {
    BVar1 = ReadFile(param_1,&DAT_00522584,0xc40,&local_8,(LPOVERLAPPED)0x0);
    if (BVar1 == 0) {
      return 0;
    }
    memset(&DAT_00522584,0,0x10bf8);
  }
  else {
    BVar1 = ReadFile(param_1,&DAT_00522584,0x10bf8,&local_8,(LPOVERLAPPED)0x0);
    if (BVar1 == 0) {
      return 0;
    }
    if (DAT_00583da8 < 0x26) {
      memset(&DAT_00522584,0,0x10bf8);
    }
  }
  BVar1 = ReadFile(param_1,&DAT_0052222c,0x1c,&local_8,(LPOVERLAPPED)0x0);
  if (BVar1 == 0) {
    uVar2 = 0;
  }
  else {
    BVar1 = ReadFile(param_1,&DAT_005220a4,0xc4,&local_8,(LPOVERLAPPED)0x0);
    if (BVar1 == 0) {
      uVar2 = 0;
    }
    else {
      BVar1 = ReadFile(param_1,&DAT_00522168,0xc4,&local_8,(LPOVERLAPPED)0x0);
      if (BVar1 == 0) {
        uVar2 = 0;
      }
      else {
        BVar1 = ReadFile(param_1,&DAT_0055a820,0x3440,&local_8,(LPOVERLAPPED)0x0);
        if (BVar1 == 0) {
          uVar2 = 0;
        }
        else {
          FUN_004423b4();
          if (param_2 != 0) {
            pcVar4 = &DAT_0059f161;
            local_c = 0;
            do {
              if (local_c == DAT_0058f1f4) {
                *pcVar4 = '\x01';
                DAT_0058f1f4 = local_c;
                PTR_DAT_004d5988 = &DAT_0059f160 + local_c * 0x2d8;
                DAT_004d5a58 = local_c;
              }
              else if (((*pcVar4 == '\x01') || (*pcVar4 == '\x02')) && (DAT_0058f1fc == 0)) {
                if (DAT_004d5aa0 == '\0') {
                  *pcVar4 = '\x03';
                  FUN_00401830(local_c);
                }
                else {
                  *pcVar4 = '\x01';
                }
              }
              local_c = local_c + 1;
              pcVar4 = pcVar4 + 0x2d8;
            } while (local_c < 7);
          }
          local_c = 0;
          local_18 = &DAT_005225c8;
          do {
            local_10 = 0;
            local_14 = local_18;
            do {
              iVar7 = 0;
              piVar6 = local_14 + -8;
              piVar5 = local_14;
              do {
                if ((short)*piVar6 == 0) {
                  *piVar5 = 0;
                }
                else {
                  iVar3 = FUN_0047510c((short)*piVar6);
                  *piVar5 = iVar3;
                  if (*piVar5 != 0) {
                    *(short *)(*piVar5 + 0x36) = (short)local_10 + 1;
                  }
                }
                iVar7 = iVar7 + 1;
                piVar5 = piVar5 + 1;
                piVar6 = (int *)((int)piVar6 + 2);
              } while (iVar7 < 0x10);
              local_10 = local_10 + 1;
              local_14 = local_14 + 0x31;
            } while (local_10 < 0x32);
            local_c = local_c + 1;
            local_18 = local_18 + 0x992;
          } while (local_c < 7);
          FUN_00460f68();
          uVar2 = 1;
        }
      }
    }
  }
  return uVar2;
}

