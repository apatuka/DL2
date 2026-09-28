// FUN_004843ac @ 004843ac size=177 sig=undefined FUN_004843ac() cc=unknown
// callers: FUN_00474920,FUN_00466218
// callees: sprintf,FUN_004ae5d8,FUN_004a6b48
// strings: \"%s #%d\"

char * FUN_004843ac(char *param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  short *psVar7;
  char *pcVar8;
  char *pcVar9;
  char local_84 [128];
  
  iVar6 = (int)param_1[0x21];
  *(short *)(&DAT_00501b50 + iVar6 * 2) = *(short *)(&DAT_00501b50 + iVar6 * 2) + 1;
  sVar2 = (&DAT_00503e10)[iVar6 * 3];
  if (sVar2 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = FUN_004ae5d8();
    iVar3 = iVar3 % (int)sVar2;
  }
  psVar7 = (short *)(*(int *)((int)&PTR_DAT_00503e12 + iVar6 * 6) + iVar3 * 6);
  if (*psVar7 == 0) {
    param_1 = (char *)FUN_004a6b48(param_1,*(undefined4 *)(psVar7 + 1),0x18);
    *psVar7 = 1;
  }
  else {
    sprintf(local_84,s__s___d_00508f87,(&PTR_DAT_00509054)[iVar6],
            (int)*(short *)(&DAT_00501b50 + iVar6 * 2));
    uVar4 = 0xffffffff;
    pcVar8 = local_84;
    do {
      pcVar9 = pcVar8;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar8 = pcVar9 + -uVar4;
    pcVar9 = param_1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    }
  }
  return param_1;
}

