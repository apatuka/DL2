// FUN_0045fae4 @ 0045fae4 size=542 sig=undefined FUN_0045fae4() cc=unknown
// callers: FUN_004618e8
// callees: FUN_004b0b44,sprintf,memcpy,FUN_004b0a30,ReadFile
// strings: \"New Player\"

undefined4 FUN_0045fae4(HANDLE param_1)

{
  int *piVar1;
  LPVOID lpBuffer;
  BOOL BVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  char *pcVar7;
  DWORD local_10;
  int local_c;
  DWORD local_8;
  
  if (DAT_00583da4 < 3) {
    lpBuffer = (LPVOID)FUN_004b0b44(DAT_004d5aec * 0x13e8);
    BVar2 = ReadFile(param_1,lpBuffer,DAT_004d5aec * 0x13e8,&local_8,(LPOVERLAPPED)0x0);
    if (BVar2 == 0) {
      return 0;
    }
    memcpy(&DAT_0059f160,lpBuffer,0x13e8);
    FUN_004b0a30(lpBuffer);
  }
  else {
    BVar2 = ReadFile(param_1,&DAT_0059f160,0x13e8,&local_8,(LPOVERLAPPED)0x0);
    if (BVar2 == 0) {
      return 0;
    }
    if ((DAT_00583da4 < 4) || ((DAT_004d5a94 != 0 && (DAT_0059f154 == 1)))) {
      pcVar7 = &DAT_0059f161;
      for (iVar6 = 0; iVar6 < DAT_004d5aec; iVar6 = iVar6 + 1) {
        if ('\0' < *pcVar7) {
          DAT_0059f0fc = DAT_0059f0fc | '\x01' << ((byte)iVar6 & 0x1f);
          pcVar7[0x2d3] = '\0';
          pcVar7[0x2d4] = '\0';
          pcVar7[0x2d5] = '\0';
          pcVar7[0x2d6] = '\0';
        }
        pcVar7 = pcVar7 + 0x2d8;
      }
    }
  }
  puVar3 = &DAT_0059f19a;
  for (iVar6 = 0; iVar6 < DAT_004d5aec; iVar6 = iVar6 + 1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 0xb6;
  }
  if (DAT_00583da8 < 7) {
LAB_0045fc80:
    iVar6 = 0;
    pcVar7 = &DAT_0059f161;
    do {
      if (iVar6 == DAT_0058f1f4) {
        sprintf(&DAT_0059f413 + iVar6 * 0x2d8,s_New_Player_00509804);
      }
      else if ('\x02' < *pcVar7) {
        sprintf(&DAT_0059f413 + iVar6 * 0x2d8,(&PTR_s_Sting_00509938)[pcVar7[1]]);
      }
      iVar6 = iVar6 + 1;
      pcVar7 = pcVar7 + 0x2d8;
    } while (iVar6 < 7);
    uVar4 = 1;
  }
  else {
    BVar2 = ReadFile(param_1,&local_c,4,&local_10,(LPOVERLAPPED)0x0);
    piVar1 = (int *)0x0;
    if (BVar2 == 0) {
      uVar4 = 0;
    }
    else {
      do {
        if (local_c == -1) goto LAB_0045fc80;
        piVar5 = (int *)FUN_004b0b44(8);
        *piVar5 = local_c;
        piVar5[1] = 0;
        if (piVar1 == (int *)0x0) {
          (&DAT_0059f19a)[DAT_0058f1f4 * 0xb6] = piVar5;
        }
        else {
          piVar1[1] = (int)piVar5;
        }
        BVar2 = ReadFile(param_1,&local_c,4,&local_10,(LPOVERLAPPED)0x0);
        piVar1 = piVar5;
      } while (BVar2 != 0);
      uVar4 = 0;
    }
  }
  return uVar4;
}

