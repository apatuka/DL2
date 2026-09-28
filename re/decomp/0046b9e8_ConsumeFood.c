// ConsumeFood @ 0046b9e8 size=573 sig=undefined ConsumeFood() cc=unknown
// callers: FUN_0046c7d4
// callees: FUN_0046b958,FUN_00446bf0,FUN_00472844,DebugMessage,FUN_00423690,FUN_004237d0,FUN_00472974
// strings: \"NULL territory in ConsumeFood()\"

/* auto-named from string evidence: ConsumeFood */

void ConsumeFood(void)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  uint *puVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  int iVar8;
  int local_44;
  int local_40 [3];
  int local_34;
  undefined1 local_30 [4];
  uint local_2c [7];
  
  for (puVar6 = &DAT_005a43d0; puVar6 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar6 = puVar6 + 0xadc) {
    local_44 = FUN_0046b958(puVar6);
    piVar3 = (int *)(puVar6 + 0x3e);
    if (local_44 <= *(int *)(puVar6 + 0x3e)) {
      piVar3 = &local_44;
    }
    iVar8 = *piVar3;
    iVar7 = (int)(short)iVar8;
    *(int *)(puVar6 + 0x3e) = *(int *)(puVar6 + 0x3e) - iVar7;
    *(int *)(puVar6 + 0xa82) = *(int *)(puVar6 + 0xa82) - iVar7;
    if (iVar8 < local_44) {
      local_40[0] = (char)puVar6[0x29] + 1;
      local_40[1] = 7;
      if ((char)puVar6[0x29] + 1 < 8) {
        piVar3 = local_40;
      }
      else {
        piVar3 = local_40 + 1;
      }
      iVar8 = *piVar3;
      puVar6[0x29] = (char)iVar8;
      if ((char)iVar8 == '\x01') {
        FUN_004237d0((int)(char)puVar6[0x20],0x32,puVar6,0,0,0,(int)*(short *)(puVar6 + 0x1a),0);
      }
    }
    else {
      local_40[2] = (char)puVar6[0x29] + -1;
      local_34 = 0;
      if ((char)puVar6[0x29] + -1 < 0) {
        piVar3 = &local_34;
      }
      else {
        piVar3 = local_40 + 2;
      }
      puVar6[0x29] = (char)*piVar3;
    }
  }
  puVar4 = local_2c;
  iVar8 = 0;
  do {
    iVar7 = iVar8 + 1;
    *puVar4 = (int)(char)(&DAT_0059f169)[iVar8 * 0x2d8] & 2;
    puVar4 = puVar4 + 1;
    (&DAT_0059f169)[iVar8 * 0x2d8] = (&DAT_0059f169)[iVar8 * 0x2d8] & 0xfd;
    iVar8 = iVar7;
  } while (iVar7 < 7);
  iVar8 = 0;
  do {
    iVar7 = iVar8 * 0x5c;
    if ((&DAT_00645370 + iVar8 * 0x2e != (undefined2 *)0x0) && ((&DAT_00645376)[iVar7] != '\0')) {
      cVar1 = (&DAT_00645378)[iVar7];
      iVar2 = (&DAT_006453ac)[iVar8 * 0x17];
      if (iVar2 == 0) {
        DebugMessage(s_NULL_territory_in_ConsumeFood___004d5896);
      }
      else if ((*(char *)(iVar2 + 0x20) == (&DAT_00645378)[iVar7]) && (0 < *(int *)(iVar2 + 0x3e)))
      {
        *(int *)(iVar2 + 0x3e) = *(int *)(iVar2 + 0x3e) + -1;
      }
      else {
        iVar5 = FUN_00446bf0(&DAT_00645370 + iVar8 * 0x2e);
        if ((iVar5 != 0) || ((&DAT_004faf8d)[(char)(&DAT_00645376)[iVar7] * 0x24] == '\x03')) {
          iVar5 = FUN_00472844(iVar2,(int)(char)(&DAT_00645378)[iVar7],1,3);
          if (iVar5 != 0) {
            piVar3 = (int *)(*(int *)(iVar2 + 0xad6) + 0x3e);
            *piVar3 = *piVar3 + -1;
            *(undefined4 *)(iVar2 + 0xad6) = 0;
            goto LAB_0046bbc9;
          }
        }
        iVar7 = FUN_00472974((&DAT_006453ac)[iVar8 * 0x17],(int)(char)(&DAT_00645378)[iVar7],1,1,1,
                             local_30,local_30);
        if (iVar7 == -1) {
          (&DAT_0059f169)[cVar1 * 0x2d8] = (&DAT_0059f169)[cVar1 * 0x2d8] | 2;
        }
        else {
          *(int *)(iVar2 + 0x3e) = *(int *)(iVar2 + 0x3e) + -1;
        }
      }
    }
LAB_0046bbc9:
    iVar8 = iVar8 + 1;
    if (0x22f < iVar8) {
      iVar8 = 0;
      puVar4 = local_2c;
      do {
        if (((&DAT_0059f169)[iVar8 * 0x2d8] & 2) != 0) {
          if (*puVar4 == 0) {
            FUN_00423690(iVar8,2,0,0,0,0);
          }
          else {
            (&DAT_0059f169)[iVar8 * 0x2d8] = (&DAT_0059f169)[iVar8 * 0x2d8] | 4;
          }
        }
        iVar8 = iVar8 + 1;
        puVar4 = puVar4 + 1;
      } while (iVar8 < 7);
      return;
    }
  } while( true );
}

