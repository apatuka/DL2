// FUN_004671d8 @ 004671d8 size=601 sig=undefined FUN_004671d8() cc=unknown
// callers: SavePrefs,LoadPrefs
// callees: 
// strings: \"New Player\"

undefined4 FUN_004671d8(undefined2 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  char *pcVar7;
  int iVar8;
  undefined4 local_8;
  
  *param_1 = (undefined2)DAT_004d5ae8;
  uVar4 = 0xffffffff;
  pcVar7 = s_New_Player_00509804;
  do {
    pcVar3 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar3 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar3;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar3 + -uVar4;
  pcVar3 = (char *)(param_1 + 9);
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar3 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar3 = pcVar3 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar3 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar3 = pcVar3 + 1;
  }
  if ((DAT_004d5b1a < '\x14') || ('(' < DAT_004d5b1a)) {
    uVar2 = 0;
  }
  else {
    *(char *)(param_1 + 0x25) = DAT_004d5b1a;
    if ((DAT_004d5b1b < '\x14') || ('(' < DAT_004d5b1b)) {
      uVar2 = 0;
    }
    else {
      *(char *)((int)param_1 + 0x4b) = DAT_004d5b1b;
      if ((DAT_004d5aec < 2) || (7 < DAT_004d5aec)) {
        uVar2 = 0;
      }
      else {
        local_8 = 2;
        if (DAT_004d5aec < 2) {
          puVar6 = &local_8;
        }
        else {
          puVar6 = &DAT_004d5aec;
        }
        *(undefined1 *)(param_1 + 0x34) = *(undefined1 *)puVar6;
        if ((DAT_004d5af0 < 2) || (10 < DAT_004d5af0)) {
          uVar2 = 0;
        }
        else {
          *(undefined1 *)((int)param_1 + 0x69) = (undefined1)DAT_004d5af0;
          *(undefined1 *)(param_1 + 0x35) = (undefined1)DAT_004d5b04;
          *(undefined1 *)((int)param_1 + 0x6b) = (undefined1)DAT_004d5b08;
          if ((DAT_004d5b0c < 0) || (4 < DAT_004d5b0c)) {
            uVar2 = 0;
          }
          else {
            *(undefined1 *)(param_1 + 0x36) = (undefined1)DAT_004d5b0c;
            *(undefined1 *)((int)param_1 + 0x6d) = (undefined1)DAT_004d5b2c;
            param_1[0x37] = (undefined2)DAT_004d5b30;
            *(undefined1 *)(param_1 + 0x38) = (undefined1)DAT_004d5b34;
            param_1[0x39] = (undefined2)DAT_004d5b38;
            *(undefined1 *)(param_1 + 0x3a) = (undefined1)DAT_004d5b3c;
            *(undefined1 *)((int)param_1 + 5) = (undefined1)DAT_004d5aa8;
            *(undefined1 *)(param_1 + 3) = (undefined1)DAT_004d5aac;
            *(undefined1 *)((int)param_1 + 7) = (undefined1)DAT_004d5ab0;
            *(undefined1 *)(param_1 + 4) = (undefined1)DAT_004d5ab4;
            *(undefined1 *)(param_1 + 2) = DAT_004d5aa4;
            *(undefined1 *)((int)param_1 + 3) = DAT_004d5ab8;
            *(undefined1 *)(param_1 + 1) = DAT_004d5abc;
            *(undefined1 *)((int)param_1 + 9) = DAT_004d5ac0;
            *(undefined1 *)(param_1 + 5) = (undefined1)DAT_004d5ac4;
            *(undefined1 *)((int)param_1 + 0xb) = (undefined1)DAT_004d5ac8;
            *(byte *)(param_1 + 6) = (byte)DAT_004d5acc & 1;
            *(undefined1 *)((int)param_1 + 0xd) = (undefined1)DAT_004d5ad0;
            param_1[7] = (undefined2)DAT_004d5ad8;
            param_1[8] = (undefined2)DAT_004d5adc;
            *(undefined4 *)(param_1 + 0x26) = DAT_004d5ae0;
            *(undefined4 *)(param_1 + 0x28) = DAT_004d5a90;
            *(undefined4 *)(param_1 + 0x2a) = DAT_004d5af4;
            if ((DAT_004d5af8 < 1) || (5 < DAT_004d5af8)) {
              uVar2 = 0;
            }
            else {
              *(int *)(param_1 + 0x2c) = DAT_004d5af8;
              if ((DAT_004d5afc < 3) || (8 < DAT_004d5afc)) {
                uVar2 = 0;
              }
              else {
                *(int *)(param_1 + 0x2e) = DAT_004d5afc;
                if ((DAT_004d5b00 < '\0') || ('\x02' < DAT_004d5b00)) {
                  uVar2 = 0;
                }
                else {
                  *(char *)(param_1 + 0x30) = DAT_004d5b00;
                  if ((DAT_004d5b1c < '\0') || ('\x06' < DAT_004d5b1c)) {
                    uVar2 = 0;
                  }
                  else {
                    *(char *)((int)param_1 + 0x61) = DAT_004d5b1c;
                    iVar8 = 0;
                    pcVar7 = (char *)(param_1 + 0x31);
                    pcVar3 = &DAT_004d5b1d;
                    do {
                      if ((*pcVar3 < '\0') || ('d' < *pcVar3)) {
                        return 0;
                      }
                      *pcVar7 = *pcVar3;
                      iVar8 = iVar8 + 1;
                      pcVar7 = pcVar7 + 1;
                      pcVar3 = pcVar3 + 1;
                    } while (iVar8 < 6);
                    uVar2 = 1;
                    *(undefined1 *)((int)param_1 + 0x75) = DAT_004d5ae4;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return uVar2;
}

