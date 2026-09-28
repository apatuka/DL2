// FUN_0045b094 @ 0045b094 size=538 sig=undefined FUN_0045b094() cc=unknown
// callers: 
// callees: FUN_0044d1a4,FUN_00482f94,FUN_00475a60,FUN_0046f0e0,sprintf,FUN_0047ee9c,FUN_0046e6b8,FUN_0045aed4,FUN_00449f5c,FUN_0042836c,FUN_00449cc4,FUN_00449dec
// strings: \"Demolishing a sea platform will also destroy every building on it!\\n\\nAre you sure you want to demolish your sea platform?\"|\"Demolishing this %s will give you back half the resources you used to build it.  However, this building will be gone.\\n\\nAre you sure you want to demolish your %s?\"|\"Demolish Building\"

undefined4 FUN_0045b094(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  char local_218 [512];
  int local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar2 = FUN_00449cc4(param_1,param_2,&local_8,&local_c);
  if (((((iVar2 == 0) && (DAT_004d59b4 == 1)) &&
       (FUN_0047ee9c(local_8,local_c,&local_10,&local_14), -1 < local_10)) &&
      ((local_10 < 6 && (-1 < local_14)))) && (local_14 < 6)) {
    iVar6 = local_14 * 6 + local_10;
    iVar2 = FUN_0045aed4(iVar6);
    if (iVar2 != 0) {
      if ((*(char *)(iVar2 + 4) == '&') || (*(char *)(iVar2 + 4) == '\'')) {
        uVar4 = 0xffffffff;
        pcVar7 = PTR_s_Demolishing_a_sea_platform_will_a_00509760;
        do {
          pcVar8 = pcVar7;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar8 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar8;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        pcVar7 = pcVar8 + -uVar4;
        pcVar8 = local_218;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar8 = pcVar8 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar8 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar8 = pcVar8 + 1;
        }
        iVar6 = FUN_0044d1a4(&DAT_005a43d0 + *(short *)(iVar2 + 8) * 0xadc,0x14,0);
        local_18 = iVar2;
        if (*(char *)(iVar2 + 4) == '\'') {
          iVar2 = (&DAT_005a4524)[*(short *)(iVar2 + 8) * 0x2b7 + iVar6 * 0xd];
          local_18 = iVar2;
        }
      }
      else {
        sprintf(local_218,PTR_s_Demolishing_this__s_will_give_yo_00509694,
                *(undefined4 *)(&DAT_004f9dbc + *(char *)(iVar2 + 4) * 0x32),
                *(undefined4 *)(&DAT_004f9dbc + *(char *)(iVar2 + 4) * 0x32));
      }
      if (DAT_004d5aa0 == '\0') {
        iVar3 = FUN_0042836c(PTR_s_Demolish_Building_00509690,local_218,6,0,0xc);
      }
      else {
        iVar3 = 1;
      }
      if (iVar3 == 1) {
        iVar3 = iVar2;
        if (*(char *)(iVar2 + 4) == '&') {
          iVar9 = 0;
          do {
            switch(iVar9) {
            case 0:
              iVar2 = FUN_0045aed4(iVar6 + -0x16);
              break;
            case 1:
              iVar2 = FUN_0045aed4(iVar6 + -8);
              break;
            case 2:
              iVar2 = FUN_0045aed4(iVar6 + -0xc);
              break;
            case 3:
              iVar2 = FUN_0045aed4(iVar6 + 2);
              break;
            case 4:
              iVar2 = FUN_0045aed4(iVar6 + -10);
            }
            if ((iVar2 != 0) && (*(char *)(iVar2 + 4) != '&')) {
              FUN_00475a60(DAT_00657de0,(int)*(char *)(iVar2 + 7),0);
            }
            iVar9 = iVar9 + 1;
            iVar3 = local_18;
          } while (iVar9 < 5);
        }
        FUN_00475a60(DAT_00657de0,(int)*(char *)(iVar3 + 7),0);
        FUN_0046f0e0(0);
        FUN_00482f94(PTR_DAT_004d5988);
        if (DAT_004d5aa0 != '\0') {
          FUN_0046e6b8(DAT_00657de0);
        }
        FUN_00449dec();
        FUN_00449f5c();
      }
    }
  }
  return 1;
}

