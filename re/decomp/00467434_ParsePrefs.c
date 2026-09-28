// ParsePrefs @ 00467434 size=671 sig=undefined ParsePrefs() cc=unknown
// callers: LoadPrefs
// callees: FUN_004a5e12,FUN_00482940
// strings: \"New Player\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Copies DL2.PRF fields into globals */

undefined4 ParsePrefs(short *param_1)

{
  short sVar1;
  undefined4 uVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  undefined1 *puVar6;
  short *psVar7;
  int iVar8;
  short *psVar9;
  char *pcVar10;
  
  if (*param_1 == DAT_004d5ae8) {
    uVar4 = 0xffffffff;
    psVar7 = param_1 + 9;
    do {
      psVar9 = psVar7;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      psVar9 = (short *)((int)psVar7 + 1);
      sVar1 = *psVar7;
      psVar7 = psVar9;
    } while ((char)sVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar3 = (char *)((int)psVar9 - uVar4);
    pcVar10 = s_New_Player_00509804;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar10 = pcVar10 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar10 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar10 = pcVar10 + 1;
    }
    DAT_004d5b1a = (char)param_1[0x25];
    if ((DAT_004d5b1a < '\x14') || ('(' < DAT_004d5b1a)) {
      uVar2 = 0;
    }
    else {
      DAT_004d5b1b = *(char *)((int)param_1 + 0x4b);
      if ((DAT_004d5b1b < '\x14') || ('(' < DAT_004d5b1b)) {
        uVar2 = 0;
      }
      else {
        DAT_004d5aec = (int)(char)param_1[0x34];
        if ((DAT_004d5aec < 2) || (7 < DAT_004d5aec)) {
          uVar2 = 0;
        }
        else {
          DAT_004d5af0 = (int)*(char *)((int)param_1 + 0x69);
          if ((DAT_004d5af0 < 2) || (10 < DAT_004d5af0)) {
            uVar2 = 0;
          }
          else {
            DAT_004d5b04 = (int)(char)param_1[0x35];
            DAT_004d5b08 = (int)*(char *)((int)param_1 + 0x6b);
            DAT_004d5b0c = (int)(char)param_1[0x36];
            if ((DAT_004d5b0c < 0) || (4 < DAT_004d5b0c)) {
              uVar2 = 0;
            }
            else {
              iVar8 = 0;
              puVar6 = &DAT_005a0548;
              do {
                iVar8 = iVar8 + 1;
                *puVar6 = (undefined1)DAT_004d5b0c;
                puVar6 = puVar6 + 1;
              } while (iVar8 < 7);
              DAT_004d5b2c = (int)*(char *)((int)param_1 + 0x6d);
              DAT_004d5b30 = (int)param_1[0x37];
              DAT_004d5b34 = (int)(char)param_1[0x38];
              DAT_004d5b38 = (int)param_1[0x39];
              DAT_004d5b3c = (int)(char)param_1[0x3a];
              DAT_004d5aa8 = (int)*(char *)((int)param_1 + 5);
              DAT_004d5aac = (int)(char)param_1[3];
              DAT_004d5ab0 = (int)*(char *)((int)param_1 + 7);
              DAT_004d5ab4 = (int)(char)param_1[4];
              _DAT_004d5aa4 = (int)(char)param_1[2];
              _DAT_004d5abc = (int)(char)param_1[1];
              _DAT_004d5ac0 = (int)*(char *)((int)param_1 + 9);
              DAT_004d5ac4 = (int)(char)param_1[5];
              DAT_004d5ac8 = (int)*(char *)((int)param_1 + 0xb);
              FUN_004a5e12(DAT_004d5ac8);
              DAT_004d5acc = (int)(char)param_1[6] & 1;
              DAT_004d5ad0 = (int)*(char *)((int)param_1 + 0xd);
              DAT_004d5ad8 = (int)param_1[7];
              DAT_004d5adc = (int)param_1[8];
              FUN_00482940(DAT_004d5ab0);
              DAT_004d5ae0 = *(undefined4 *)(param_1 + 0x26);
              DAT_004d5a90 = *(undefined4 *)(param_1 + 0x28);
              DAT_004d5af4 = *(undefined4 *)(param_1 + 0x2a);
              DAT_004d5af8 = *(int *)(param_1 + 0x2c);
              if ((DAT_004d5af8 < 1) || (5 < DAT_004d5af8)) {
                uVar2 = 0;
              }
              else {
                DAT_004d5afc = *(int *)(param_1 + 0x2e);
                if ((DAT_004d5afc < 3) || (8 < DAT_004d5afc)) {
                  uVar2 = 0;
                }
                else {
                  DAT_004d5b00 = (char)param_1[0x30];
                  if ((DAT_004d5b00 < '\0') || ('\x02' < DAT_004d5b00)) {
                    uVar2 = 0;
                  }
                  else {
                    DAT_004d5b1c = *(char *)((int)param_1 + 0x61);
                    if ((DAT_004d5b1c < '\0') || ('\x06' < DAT_004d5b1c)) {
                      uVar2 = 0;
                    }
                    else {
                      iVar8 = 0;
                      pcVar3 = &DAT_004d5b1d;
                      psVar7 = param_1 + 0x31;
                      do {
                        *pcVar3 = (char)*psVar7;
                        if ((*pcVar3 < '\0') || ('d' < *pcVar3)) {
                          return 0;
                        }
                        iVar8 = iVar8 + 1;
                        pcVar3 = pcVar3 + 1;
                        psVar7 = (short *)((int)psVar7 + 1);
                      } while (iVar8 < 6);
                      DAT_004d5ae4 = *(undefined1 *)((int)param_1 + 0x75);
                      uVar2 = 1;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

