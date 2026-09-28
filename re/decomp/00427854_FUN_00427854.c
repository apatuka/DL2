// FUN_00427854 @ 00427854 size=438 sig=undefined FUN_00427854() cc=unknown
// callers: FUN_00426f20
// callees: FUN_0044d2f8,FUN_00441bf4,FUN_00441c90,FUN_00441c28

int FUN_00427854(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  ushort *local_18;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = 0;
  local_10 = -1;
  FUN_00441c90();
  for (local_8 = 1; local_8 <= DAT_004d5b18; local_8 = local_8 + 1) {
    iVar5 = local_8 * 0xadc;
    puVar6 = &DAT_005a43d0 + iVar5;
    bVar1 = false;
    if (param_3 == 0) {
      iVar3 = 0;
      local_18 = &DAT_005a4c60 + local_8 * 0x56e;
      while( true ) {
        iVar2 = DAT_004d5b18 + 0xf;
        if (iVar2 < 0) {
          iVar2 = DAT_004d5b18 + 0x1e;
        }
        if (iVar2 >> 4 <= iVar3) break;
        iVar2 = 0;
        uVar4 = *local_18;
        do {
          if ((((uVar4 & 1) != 0) &&
              (iVar7 = (iVar3 * 0x10 + iVar2) * 0xadc, (&DAT_005a43f0)[iVar7] != -1)) &&
             ((char)(&DAT_005a43f0)[iVar7] != param_1)) {
            bVar1 = true;
          }
          iVar2 = iVar2 + 1;
          uVar4 = (short)uVar4 >> 1;
        } while (iVar2 < 0x10);
        iVar3 = iVar3 + 1;
        local_18 = local_18 + 1;
      }
    }
    if (((((!bVar1) && ((&DAT_005a444e)[iVar5] != '\0')) &&
         (((&DAT_005a4444)[iVar5] != -1 &&
          (((&DAT_005a4445)[iVar5] != -1 && ((&DAT_005a43f1)[iVar5] != '\0')))))) &&
        ((&DAT_005a43f1)[iVar5] != '\x05')) &&
       (((char)(&DAT_005a43f0)[iVar5] == param_1 ||
        (((&DAT_005a43f0)[iVar5] == -1 && (param_2 != 0)))))) {
      iVar3 = *(int *)(&DAT_004b7d5c + (char)(&DAT_005a43f1)[iVar5] * 4);
      if ((char)(&DAT_005a43f2)[iVar5] < 0x20) {
        iVar3 = iVar3 + (short)(&DAT_0055a836)[(char)(&DAT_005a43f2)[iVar5] * 0xd1];
      }
      iVar5 = FUN_00441bf4(puVar6);
      iVar2 = FUN_00441c28(puVar6);
      iVar2 = iVar3 + iVar5 + iVar2;
      iVar5 = FUN_0044d2f8(puVar6,0);
      if (iVar5 != 0) {
        iVar2 = iVar2 + 10;
      }
      iVar5 = FUN_0044d2f8(puVar6,4);
      if (iVar5 != 0) {
        iVar2 = iVar2 + 5;
      }
      iVar5 = FUN_0044d2f8(puVar6,3);
      if (iVar5 != 0) {
        iVar2 = iVar2 + 4;
      }
      iVar5 = FUN_0044d2f8(puVar6,2);
      if (iVar5 != 0) {
        iVar2 = iVar2 + 3;
      }
      if (local_c < iVar2) {
        local_10 = local_8;
        local_c = iVar2;
      }
    }
  }
  return local_10;
}

