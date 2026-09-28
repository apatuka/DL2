// FUN_00406538 @ 00406538 size=339 sig=undefined FUN_00406538() cc=unknown
// callers: FUN_004067d0
// callees: FUN_0044eeb4,FUN_00476448,FUN_0044c8ac,FUN_004023dc,FUN_0044ba40,FUN_004063c0,FUN_0044ba18

int FUN_00406538(int param_1,undefined4 param_2,int param_3,int *param_4,int *param_5)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  int local_14;
  
  iVar6 = *(short *)(param_1 + 8) * 0xadc;
  puVar7 = &DAT_005a43d0 + iVar6;
  cVar1 = (&DAT_005a43f0)[iVar6];
  iVar3 = FUN_004023dc(param_1,param_2);
  iVar8 = 0;
  if ((((param_1 != 0) && (*(char *)(param_1 + 4) != '\0')) && (iVar3 != -1)) && (cVar1 != -1)) {
    cVar2 = (&DAT_005a43f0)[iVar6];
    local_14 = *(int *)(param_1 + 0x18 + iVar3 * 4);
    iVar6 = FUN_0044eeb4(&DAT_0059f160 + cVar2 * 0x2d8,puVar7,(int)*(char *)(param_1 + 7),iVar3,
                         local_14);
    while( true ) {
      while( true ) {
        if (*param_4 == 0) {
          return iVar8;
        }
        if (param_3 <= iVar8) {
          return iVar8;
        }
        iVar4 = FUN_0044c8ac(puVar7,param_1,iVar3);
        if (iVar4 == 0) break;
        *param_4 = *param_4 + -1;
        local_14 = local_14 + 1;
        iVar8 = FUN_0044eeb4(&DAT_0059f160 + cVar2 * 0x2d8,puVar7,(int)*(char *)(param_1 + 7),iVar3,
                             local_14);
        iVar8 = iVar8 - iVar6;
      }
      if (*param_5 < 0x19) break;
      iVar4 = FUN_0044ba18(param_1);
      iVar5 = FUN_0044ba40(param_1);
      if (iVar5 <= iVar4) {
        return iVar8;
      }
      if (DAT_00522018 < 0x19) {
        return iVar8;
      }
      iVar4 = FUN_004063c0((int)cVar1,puVar7,&DAT_00521bb4);
      if (iVar4 == 0) {
        return iVar8;
      }
      iVar4 = FUN_00476448(iVar4,puVar7,100,0,0xffffffff,0xffffffff);
      if (iVar4 == 0) {
        return iVar8;
      }
      *param_5 = *param_5 + -0x19;
    }
  }
  return iVar8;
}

