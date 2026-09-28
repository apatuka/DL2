// FUN_004b1b38 @ 004b1b38 size=176 sig=undefined FUN_004b1b38() cc=unknown
// callers: FUN_004b1be8
// callees: FUN_004b1660,strlen,FUN_004b0b44,FUN_004b1010
// strings: \"No space for command line argument vector\"|\"No space for command line argument\"

void FUN_004b1b38(char *param_1,int param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  if (DAT_0069f85c == DAT_0069f824) {
    DAT_0069f824 = DAT_0069f824 + 0x10;
    DAT_0069f820 = FUN_004b1010(DAT_0069f820,DAT_0069f824 * 4);
    if (DAT_0069f820 == 0) {
      FUN_004b1660(s_No_space_for_command_line_argume_00521322);
    }
  }
  pcVar3 = param_1;
  if (param_2 != 0) {
    iVar2 = strlen(param_1);
    pcVar3 = (char *)FUN_004b0b44(iVar2 + 1);
    if (pcVar3 == (char *)0x0) {
      FUN_004b1660(s_No_space_for_command_line_argume_0052134c);
    }
    uVar4 = 0xffffffff;
    do {
      pcVar6 = param_1;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar6 = param_1 + 1;
      cVar1 = *param_1;
      param_1 = pcVar6;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar6 = pcVar6 + -uVar4;
    pcVar7 = pcVar3;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar7 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    }
  }
  *(char **)(DAT_0069f820 + DAT_0069f85c * 4) = pcVar3;
  DAT_0069f85c = DAT_0069f85c + 1;
  return;
}

