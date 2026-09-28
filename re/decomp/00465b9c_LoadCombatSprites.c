// LoadCombatSprites @ 00465b9c size=601 sig=undefined LoadCombatSprites() cc=unknown
// callers: FUN_00465df8
// callees: FUN_00448284,FUN_004482cc,DebugMessage,LoadPhaseSprites,memset
// strings: \"LoadCombatSprites: Missile from ?\"|\"Could not load Combat Phase sprites.\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Loads combat phase sprites */

void LoadCombatSprites(void)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  int local_10;
  
  local_10 = 0;
  if (DAT_00559dbc != 0) {
    memset(&DAT_0058df4c,0,0x6ac);
    memset(&DAT_0058e5f8,0,0x6ac);
    iVar3 = 0;
    piVar5 = &DAT_004d4e14;
    do {
      iVar7 = *piVar5;
      piVar5 = piVar5 + 1;
      iVar3 = iVar3 + 1;
      (&DAT_0058df4c)[iVar7] = 1;
    } while (iVar3 < 0xe);
    iVar3 = 0;
    piVar5 = &DAT_004d4e4c;
    do {
      iVar7 = *piVar5;
      piVar5 = piVar5 + 1;
      iVar3 = iVar3 + 1;
      (&DAT_0058df4c)[iVar7] = 1;
    } while (iVar3 < 6);
    for (iVar3 = *(int *)(DAT_00559dbc + 0x7c); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x16)) {
      (&DAT_0058df4c)
      [(int)(short)(&DAT_004f9dc0)[*(short *)(iVar3 + 4) * 0x19] + (uint)*(byte *)(iVar3 + 0x12)] =
           1;
    }
    for (iVar3 = *(int *)(DAT_00559dbc + 0x74); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x44)) {
      iVar7 = (int)*(short *)(&DAT_004faf80 + *(int *)(iVar3 + 4) * 0x24);
      if (iVar7 != 0) {
        cVar1 = (&DAT_004faf87)[*(int *)(iVar3 + 4) * 0x24];
        if ((cVar1 == '\f') && (*(char *)(*(int *)(DAT_00559dbc + 4) + 0x21) == '\0')) {
          iVar7 = iVar7 + 7;
        }
        if (cVar1 == '\t') {
          cVar2 = *(char *)(iVar3 + 0x14);
          if (cVar2 == '\x01') {
            iVar7 = iVar7 + 3;
          }
          else if (cVar2 == '\x02') {
            iVar7 = iVar7 + 1;
          }
          else if (cVar2 == '\x04') {
            iVar7 = iVar7 + 2;
          }
          else if (cVar2 != '\b') {
            DebugMessage(s_LoadCombatSprites__Missile_from___004d4eb3);
          }
        }
        if ((cVar1 != '\n') && (cVar1 != '\t')) {
          iVar7 = iVar7 + (char)(&DAT_0059f162)[(uint)*(byte *)(iVar3 + 0x1e) * 0x2d8];
        }
        iVar4 = FUN_004482cc(iVar3);
        if (iVar4 == 0) {
          iVar4 = FUN_00448284(iVar3);
          if (iVar4 != 0) {
            iVar7 = *(int *)(iVar3 + 4) + 0x18b;
          }
        }
        else {
          iVar7 = *(int *)(iVar3 + 4) + 399;
        }
        (&DAT_0058df4c)[iVar7] = 1;
      }
      iVar7 = *(int *)(iVar3 + 4);
      if (*(short *)(&DAT_004faf82 + iVar7 * 0x24) != 0) {
        (&DAT_0058df4c)[*(short *)(&DAT_004faf82 + iVar7 * 0x24)] = 1;
      }
      if (iVar7 == 0xf) {
        if (*(short *)(&DAT_00559fb2 + (char)(&DAT_0059f162)[(uint)*(byte *)(iVar3 + 8) * 0x2d8] * 2
                      ) != 0) {
          _DAT_0058e5a0 = 1;
          _DAT_0058e59c = 1;
        }
        if (*(short *)(&DAT_00559fc0 + (char)(&DAT_0059f162)[(uint)*(byte *)(iVar3 + 8) * 0x2d8] * 2
                      ) != 0) {
          _DAT_0058e5a8 = 1;
          _DAT_0058e5a4 = 1;
        }
      }
    }
    iVar3 = 0;
    piVar5 = &DAT_0058e5f8;
    piVar6 = &DAT_0058df4c;
    do {
      if (*piVar6 != 0) {
        *piVar5 = iVar3;
        local_10 = local_10 + 1;
        piVar5 = piVar5 + 1;
      }
      iVar3 = iVar3 + 1;
      piVar6 = piVar6 + 1;
    } while (iVar3 < 0x1ab);
    iVar3 = LoadPhaseSprites(&DAT_0058e5f8,local_10);
    if (iVar3 == 0) {
      DebugMessage(s_Could_not_load_Combat_Phase_spri_004d4ed5);
    }
  }
  return;
}

