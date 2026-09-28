// FUN_00466508 @ 00466508 size=675 sig=undefined FUN_00466508() cc=unknown
// callers: RaceInit
// callees: FUN_004ae5d8,SyncCreateBuilding,FUN_0040d920,FUN_0046c9d8,FUN_0044d1e4
// strings: \"Place\"|\"Place3\"|\"Place4\"|\"Place5\"

undefined8 FUN_00466508(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  int local_18;
  int local_14;
  
  if (DAT_004d5b04 != 0) {
    for (iVar2 = 0; iVar2 <= DAT_004d5b18; iVar2 = iVar2 + 1) {
      iVar5 = iVar2 * 0xadc;
      puVar4 = &DAT_005a43d0 + iVar5;
      iVar3 = FUN_0046c9d8(8,s_Place_004d50f8);
      if ((((((iVar3 == 0) && ((&DAT_005a444e)[iVar5] != '\0')) && (DAT_0058f134 != 0)) &&
           (((*(byte *)((int)&DAT_005a43ec + iVar5 + 1) & 1) == 0 &&
            ((&DAT_005a43f1)[iVar5] != '\x05')))) &&
          (((&DAT_005a43f1)[iVar5] != '\0' || ((&DAT_005a4c7c)[iVar2 * 0x2b7] != 0)))) &&
         ((&DAT_005a43f0)[iVar5] == -1)) {
        (&DAT_005a43ec)[iVar2 * 0x2b7] = (&DAT_005a43ec)[iVar2 * 0x2b7] | 0x10;
        if ((&DAT_005a43f1)[iVar5] == '\0') {
          SyncCreateBuilding(puVar4,0x2f);
        }
        else {
          iVar3 = FUN_0046c9d8(4,s_Place3_004d50fe);
          if (iVar3 == 0) {
            SyncCreateBuilding(puVar4,0x2e);
          }
          else {
            SyncCreateBuilding(puVar4,0x2d);
          }
        }
        DAT_0058eca4 = DAT_0058eca4 + 1;
      }
    }
  }
  if (DAT_004d5b00 == '\x02') {
    local_18 = 0;
    for (iVar2 = 0; iVar2 <= DAT_004d5b18; iVar2 = iVar2 + 1) {
      iVar3 = iVar2 * 0xadc;
      puVar4 = &DAT_005a43d0 + iVar3;
      if (((((DAT_0058eca4 < DAT_004d5af8 * 2 + -1) && ((&DAT_005a444e)[iVar3] != '\0')) &&
           ((DAT_0058f134 != 0 && ((*(byte *)((int)&DAT_005a43ec + iVar3 + 1) & 1) == 0)))) &&
          ((((&DAT_005a43f1)[iVar3] != '\0' || ((&DAT_005a4c7c)[iVar2 * 0x2b7] != 0)) &&
           (((&DAT_005a43f1)[iVar3] != '\x05' || (local_18 == 2)))))) &&
         ((&DAT_005a43f0)[iVar3] == -1)) {
        if (DAT_004d5af8 <= DAT_0058eca4) {
          iVar5 = ((DAT_004d5af8 * 2 + DAT_004d5aec) - DAT_0058eca4) + -2;
          if (iVar5 == 0) {
            iVar1 = 0;
          }
          else {
            iVar1 = FUN_004ae5d8();
            iVar1 = iVar1 % iVar5;
          }
          if (iVar1 == 0) break;
        }
        local_14 = 0;
        for (iVar5 = 0; iVar5 <= DAT_004d5b18; iVar5 = iVar5 + 1) {
          iVar1 = FUN_0040d920(puVar4,&DAT_005a43d0 + iVar5 * 0xadc);
          if (iVar1 != 0) {
            iVar1 = FUN_0044d1e4(&DAT_005a43d0 + iVar5 * 0xadc,0xb,0);
            if (iVar1 != -1) {
              local_14 = 1;
              break;
            }
          }
        }
        if ((local_18 != 0) || (local_14 == 0)) {
          iVar5 = FUN_0044d1e4(puVar4,0xb,0);
          if (iVar5 == -1) {
            if ((&DAT_005a43f1)[iVar3] == '\0') {
              iVar3 = SyncCreateBuilding(puVar4,0x2f);
            }
            else {
              if ((local_18 == 2) && ((&DAT_005a43f1)[iVar3] == '\x05')) {
LAB_0046673b:
                iVar3 = SyncCreateBuilding(puVar4,0x2e);
              }
              else {
                if ((&DAT_005a43f1)[iVar3] != '\x05') {
                  iVar3 = FUN_0046c9d8(4,s_Place4_004d5105);
                  if (iVar3 == 0) goto LAB_0046673b;
                }
                iVar3 = SyncCreateBuilding(puVar4,0x2d);
              }
              iVar5 = FUN_0046c9d8(2,s_Place5_004d510c);
              if (iVar5 == 0) {
                (&DAT_005a43ec)[iVar2 * 0x2b7] = (&DAT_005a43ec)[iVar2 * 0x2b7] | 0x10;
              }
            }
            if (iVar3 != 0) {
              DAT_0058eca4 = DAT_0058eca4 + 1;
            }
            goto LAB_0046676f;
          }
        }
      }
      else {
LAB_0046676f:
        if ((iVar2 == DAT_004d5b18) && (DAT_0058eca4 < DAT_004d5af8)) {
          iVar2 = 0;
          local_18 = local_18 + 1;
        }
      }
    }
  }
  return CONCAT44(local_14,1);
}

