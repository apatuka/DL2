// FUN_004749f8 @ 004749f8 size=525 sig=undefined FUN_004749f8() cc=unknown
// callers: FUN_0043bdf4,FUN_00474c08
// callees: sprintf,FUN_0044a000,FUN_00441128,FUN_004a6b48
// strings: \"%s Landing\"|\"%s %s #%d\"

undefined4 FUN_004749f8(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  char *pcVar4;
  undefined4 uVar5;
  int *piVar6;
  int iVar7;
  ushort *puVar8;
  undefined1 local_114 [256];
  short *local_14;
  undefined **local_10;
  short *local_c;
  undefined4 *local_8;
  
  if ((-1 < param_3) && (param_3 < 5)) {
    (&DAT_005a0548)[param_1] = (char)param_3;
  }
  bVar3 = false;
  iVar7 = 0;
  pcVar4 = &DAT_0059f161;
  do {
    if ((*pcVar4 != '\0') && (pcVar4[1] == param_2)) {
      bVar3 = true;
    }
    iVar7 = iVar7 + 1;
    pcVar4 = pcVar4 + 0x2d8;
  } while (iVar7 < 7);
  if (bVar3) {
    uVar5 = 4;
  }
  else {
    sprintf(&DAT_0059f413 + param_1 * 0x2d8,(&PTR_s_Sting_00509938)[param_2]);
    local_10 = &PTR_s_ChCh_t_00509038 + param_2;
    local_c = &DAT_0059f166 + param_1 * 0x16c;
    for (local_8 = &DAT_005a4eac; local_8 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
        local_8 = local_8 + 0x2b7) {
      if (*(char *)(local_8 + 8) == param_1) {
        if (*(short *)((int)local_8 + 0x1a) == *local_c) {
          sprintf(local_8,PTR_s__s_Landing_00509888,*local_10);
        }
        iVar7 = 0;
        local_14 = local_c + -2;
        piVar6 = local_8 + 0x55;
        do {
          iVar2 = *piVar6;
          if (((iVar2 != 0) && ((char)*local_14 == *(char *)(iVar2 + 6))) &&
             (((cVar1 = *(char *)(iVar2 + 4), cVar1 == '\x01' ||
               (((cVar1 == '\x02' || (cVar1 == '\x03')) || (cVar1 == '\'')))) ||
              ((cVar1 == '%' || (cVar1 == '\x17')))))) {
            *(undefined1 *)(*piVar6 + 6) = (undefined1)param_2;
          }
          iVar7 = iVar7 + 1;
          piVar6 = piVar6 + 0xd;
        } while (iVar7 < 0x24);
      }
    }
    for (puVar8 = &DAT_00645370; puVar8 < &DAT_00651cb0; puVar8 = puVar8 + 0x2e) {
      if ((char)puVar8[4] == param_1) {
        sprintf(local_114,s__s__s___d_004d6477,(&PTR_s_ChCh_t_00509038)[param_2],
                (&PTR_s_No_Unit_005095e4)[(char)puVar8[3]],*puVar8 & 0x3ff);
        FUN_004a6b48((int)puVar8 + 0xb,local_114,0x18);
      }
    }
    (&DAT_0059f162)[param_1 * 0x2d8] = (undefined1)param_2;
    FUN_00441128();
    FUN_0044a000();
    uVar5 = 0;
  }
  return uVar5;
}

