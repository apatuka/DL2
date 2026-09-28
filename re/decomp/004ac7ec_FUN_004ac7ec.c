// FUN_004ac7ec @ 004ac7ec size=323 sig=undefined FUN_004ac7ec() cc=unknown
// callers: FUN_004aa560,FUN_004b1c4c
// callees: strlen,GetLogicalDrives,GetCurrentDirectoryA,FUN_004b12c4,FUN_004b0b44,GetFullPathNameA

char * FUN_004ac7ec(int param_1,char *param_2,int param_3)

{
  code *pcVar1;
  DWORD DVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  char cVar7;
  char *pcVar8;
  char *pcVar9;
  bool bVar10;
  char local_110 [260];
  LPSTR local_c;
  char local_8 [4];
  
  if (param_1 == 0) {
    DVar2 = GetCurrentDirectoryA(0x103,local_110);
    if ((DVar2 == 0) || (param_3 < (int)DVar2)) {
      puVar3 = (undefined4 *)FUN_004b12c4();
      *puVar3 = 8;
      return (char *)0x0;
    }
  }
  else {
    cVar7 = (char)param_1;
    if (DAT_0069f79c == 1) {
      local_110[0] = cVar7 + '@';
      bVar10 = (char *)0xfffffffc < local_110;
      local_110[1] = 0x3a;
      local_110[2] = 0x5c;
      local_110[3] = 0;
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      if (bVar10) {
        return (char *)0x0;
      }
    }
    else {
      DVar2 = GetLogicalDrives();
      if ((1 << (cVar7 - 1U & 0x1f) & DVar2) == 0) {
        return (char *)0x0;
      }
      local_8[0] = cVar7 + '@';
      local_8[1] = 0x3a;
      local_8[2] = 0x2e;
      local_8[3] = 0;
      GetFullPathNameA(local_8,0x103,local_110,&local_c);
    }
  }
  iVar4 = strlen(local_110);
  if (iVar4 < param_3) {
    if ((param_2 == (char *)0x0) &&
       (param_2 = (char *)FUN_004b0b44(param_3), param_2 == (char *)0x0)) {
      puVar3 = (undefined4 *)FUN_004b12c4();
      *puVar3 = 8;
      param_2 = (char *)0x0;
    }
    else {
      uVar5 = 0xffffffff;
      pcVar8 = local_110;
      do {
        pcVar9 = pcVar8;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar9 = pcVar8 + 1;
        cVar7 = *pcVar8;
        pcVar8 = pcVar9;
      } while (cVar7 != '\0');
      uVar5 = ~uVar5;
      pcVar8 = pcVar9 + -uVar5;
      pcVar9 = param_2;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar9 = pcVar9 + 1;
      }
    }
  }
  else {
    puVar3 = (undefined4 *)FUN_004b12c4();
    *puVar3 = 0x22;
    param_2 = (char *)0x0;
  }
  return param_2;
}

