// FUN_00402df4 @ 00402df4 size=498 sig=undefined FUN_00402df4() cc=unknown
// callers: 
// callees: FUN_0044d440,FUN_00402548,FUN_0044de9c,FindConstructionSite,FUN_0044d3f4,FUN_0044d1a4,FUN_0044d1e4,FUN_0044d2f8,FUN_00401d6c

undefined4
FUN_00402df4(undefined4 param_1,undefined4 param_2,int param_3,int param_4,undefined4 param_5,
            int *param_6,int *param_7,undefined4 *param_8,int *param_9,undefined4 param_10)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int local_30;
  int local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  int local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  local_10 = 0;
  local_14 = 0;
  local_18 = 0xffffffff;
  local_20 = -1000000;
  local_24 = (int)(char)(&DAT_004f9dc3)[param_4 * 0x32];
  local_30 = 0;
  piVar4 = param_6;
  do {
    iVar1 = *piVar4;
    iVar2 = FUN_0044d1a4(iVar1,0x11,0);
    if ((iVar2 != -1) && ((param_3 == 0 || (iVar1 == param_3)))) {
      FUN_0044de9c(param_1,param_4,(int)*(char *)(iVar1 + 0x21),param_10);
      iVar2 = FUN_00401d6c(param_1,param_2,iVar1,param_10,(int)(char)(&DAT_004f9dc8)[param_4 * 0x32]
                          );
      if (iVar2 == 0) {
        local_8 = 1;
        if (*(char *)(iVar1 + 0x21) == '\0') {
LAB_00402eb4:
          iVar2 = FUN_0044d1e4(iVar1,0x14,0);
          if (iVar2 != -1) {
            iVar2 = FUN_0044d3f4(param_4);
            if (iVar2 != 0) goto LAB_00402ed3;
          }
        }
        else {
          iVar2 = FUN_0044d440(param_4);
          if (iVar2 != 0) goto LAB_00402eb4;
LAB_00402ed3:
          if (local_24 == 7) {
            iVar2 = FUN_0044d2f8(iVar1,0);
            if (iVar2 == 0) goto LAB_00402f66;
          }
          if (local_24 == 9) {
            iVar2 = FUN_0044d1a4(iVar1,9,0);
            if (iVar2 != -1) goto LAB_00402f66;
          }
          local_1c = FUN_00402548(iVar1,param_4,param_5,&local_28,&local_2c);
          if (local_10 == 0) {
            iVar2 = FindConstructionSite(iVar1,param_4);
            if ((iVar2 != -1) && (local_10 = 1, local_14 == 0)) {
              local_18 = local_28;
              local_30 = local_2c;
              local_14 = iVar1;
            }
          }
          if (local_20 < local_1c) {
            local_30 = local_2c;
            local_20 = local_1c;
            local_18 = local_28;
            local_c = 1;
            local_14 = iVar1;
          }
        }
      }
    }
LAB_00402f66:
    piVar4 = (int *)piVar4[1];
    if (piVar4 == param_6) {
      *param_7 = local_14;
      *param_8 = local_18;
      *param_9 = local_30;
      if (local_10 == 0) {
        if (local_8 == 0) {
          uVar3 = 1;
        }
        else {
          uVar3 = 0;
        }
      }
      else if (local_c == 0) {
        uVar3 = 2;
      }
      else if ((((local_24 == 1) || (local_24 == 2)) || (local_24 == 3)) && (local_30 < 0x14)) {
        uVar3 = 2;
      }
      else {
        uVar3 = 3;
      }
      return uVar3;
    }
  } while( true );
}

