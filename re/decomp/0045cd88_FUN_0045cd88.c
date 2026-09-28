// FUN_0045cd88 @ 0045cd88 size=595 sig=undefined FUN_0045cd88() cc=unknown
// callers: FUN_0044ae10
// callees: FUN_00459230,FUN_0045b970,FUN_0047ee9c,FUN_0045aed4,FUN_0044ba18,FUN_004590f0,FUN_00449cc4

void FUN_0045cd88(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  undefined4 unaff_EDI;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if ((DAT_004d5aa0 != '\0') || (*(char *)(DAT_00657de0 + 0x66 + DAT_0058f1f4) == '\x04')) {
    FUN_0047ee9c(param_3,param_4,&local_8,&local_c);
    if ((local_8 < 0) || (((5 < local_8 || (local_c < 0)) || (5 < local_c)))) {
      DAT_004c5450 = 0;
      iVar2 = FUN_00449cc4(param_1,param_2,local_18,local_1c);
      DAT_004c5450 = 1;
      if ((((0x27 < iVar2) && (iVar2 < 0x2d)) &&
          (iVar2 = FUN_0045b970(param_1,param_2,0), 999 < iVar2)) && (iVar2 < 9000)) {
        switch(iVar2) {
        case 1000:
          unaff_EDI = 1;
          DAT_00583d7c = 0;
          break;
        case 0x3e9:
          if (*(char *)(DAT_00657de0 + 0x21) == '\0') {
            unaff_EDI = 6;
          }
          else {
            unaff_EDI = 0;
          }
          DAT_00583d7c = 1;
          break;
        case 0x3ea:
          unaff_EDI = 2;
          DAT_00583d7c = 2;
          break;
        case 0x3eb:
          if (*(char *)(DAT_00657de0 + 0x21) == '\0') {
            unaff_EDI = 3;
          }
          else {
            unaff_EDI = 4;
          }
          DAT_00583d7c = 3;
          break;
        case 0x3ec:
          unaff_EDI = 5;
          DAT_00583d7c = 4;
          break;
        case 0x3ed:
          unaff_EDI = 7;
          DAT_00583d7c = 1;
        }
        DAT_00583d80 = (int)*(short *)(DAT_00657de0 + 0x1a);
        FUN_00459230(DAT_004d5974,0x31304955,(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] + 1000,
                     unaff_EDI,param_1,param_2,0x10,0x10,0,FUN_0045ccf8);
      }
    }
    else {
      local_10 = local_c * 6 + local_8;
      iVar2 = FUN_0045aed4(local_10);
      if (iVar2 != 0) {
        local_14 = &DAT_005a43d0 + *(short *)(iVar2 + 8) * 0xadc;
        iVar3 = FUN_0044ba18(iVar2);
        if (iVar3 != 0) {
          puVar1 = (&PTR_DAT_004d078c)[(char)(&DAT_0059f162)[(char)local_14[0x20] * 0x2d8] * 3];
          DAT_00583d6c = iVar2;
          FUN_004590f0(DAT_004d5974,*(undefined4 *)(puVar1 + 8),param_1,param_2,
                       (int)*(short *)(puVar1 + 4),(int)*(short *)(puVar1 + 6),0,FUN_0045b448);
        }
      }
    }
  }
  return;
}

