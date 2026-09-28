// BirthCombatSprites @ 0043ddcc size=257 sig=undefined BirthCombatSprites() cc=unknown
// callers: FUN_0048149c
// callees: DebugMessage,FUN_0043d184,FUN_004482cc,FUN_00444f20,FUN_00448284
// strings: \"BirthCombatSprites: Missile from ?\"

/* auto-named from string evidence: BirthCombatSprites */

void BirthCombatSprites(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (DAT_00559dbc != 0) {
    for (iVar2 = *(int *)(DAT_00559dbc + 0x74); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x44)) {
      iVar3 = *(int *)(iVar2 + 4) * 0x24;
      iVar4 = (int)*(short *)(&DAT_004faf80 + iVar3);
      if (iVar4 != 0) {
        if (((&DAT_004faf87)[iVar3] != '\n') && ((&DAT_004faf87)[iVar3] != '\t')) {
          iVar4 = iVar4 + (char)(&DAT_0059f162)[(uint)*(byte *)(iVar2 + 0x1e) * 0x2d8];
        }
        if (((&DAT_004faf87)[iVar3] == '\f') &&
           (*(char *)(*(int *)(DAT_00559dbc + 4) + 0x21) == '\0')) {
          iVar4 = iVar4 + 7;
        }
        if ((&DAT_004faf87)[iVar3] == '\t') {
          cVar1 = *(char *)(iVar2 + 0x14);
          if (cVar1 == '\x01') {
            iVar4 = iVar4 + 3;
          }
          else if (cVar1 == '\x02') {
            iVar4 = iVar4 + 1;
          }
          else if (cVar1 == '\x04') {
            iVar4 = iVar4 + 2;
          }
          else if (cVar1 != '\b') {
            DebugMessage(s_BirthCombatSprites__Missile_from_004c4a0d);
          }
        }
        iVar3 = FUN_004482cc(iVar2);
        if (iVar3 == 0) {
          iVar3 = FUN_00448284(iVar2);
          if (iVar3 != 0) {
            iVar4 = *(int *)(iVar2 + 4) + 0x18b;
          }
        }
        else {
          iVar4 = *(int *)(iVar2 + 4) + 399;
        }
        iVar3 = FUN_00444f20(iVar4,0,0,0);
        if (iVar3 != 0) {
          *(int *)(iVar2 + 0x38) = iVar3;
          FUN_0043d184(iVar2,0);
        }
      }
    }
  }
  return;
}

