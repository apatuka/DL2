// FindConstructionSite @ 0044d464 size=324 sig=undefined FindConstructionSite() cc=unknown
// callers: FUN_004096a8,FUN_0044d0e4,FUN_0040fb14,FUN_0040ecec,FUN_0044dcc8,FUN_00402df4,FUN_0044d5a8,FUN_0044dcf4,FUN_00402cc0,FUN_0040b5cc
// callees: FUN_0044d3f4,FUN_0044d2f8,FUN_0044d36c,FUN_0046c9d8,FUN_0044d1a4,FUN_0044d600,FUN_0044d440
// strings: \"FindConstructionSite\"

/* auto-named from string evidence: FindConstructionSite */

undefined4 FindConstructionSite(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 local_c;
  int local_8;
  
  cVar1 = (&DAT_004f9dc3)[param_2 * 0x32];
  if (*(char *)(param_1 + 0x21) == '\0') {
    if (param_2 == 0x2f) {
      iVar2 = FUN_0044d1a4(param_1,0xb,0);
      if (iVar2 != -1) {
        return 0xffffffff;
      }
      iVar2 = FUN_0046c9d8(4,s_FindConstructionSite_004c60ff);
      if (iVar2 == 0) {
        return 0;
      }
      if (iVar2 == 1) {
        return 5;
      }
      if (iVar2 == 2) {
        return 0x1e;
      }
      if (iVar2 == 3) {
        return 0x23;
      }
    }
    else {
      iVar2 = FUN_0044d1a4(param_1,0x14,0);
      if (iVar2 == -1) {
        if ((param_2 != 0x2f) && (param_2 != 0x26)) {
          return 0xffffffff;
        }
      }
      else {
        iVar2 = FUN_0044d3f4(param_2);
        if ((iVar2 == 0) && (param_2 != 0x2f)) {
          return 0xffffffff;
        }
      }
    }
  }
  else {
    iVar2 = FUN_0044d440(param_2);
    if (iVar2 != 0) {
      return 0xffffffff;
    }
  }
  if ((cVar1 == '\a') && (iVar2 = FUN_0044d2f8(param_1,0), iVar2 == 0)) {
    local_c = 0xffffffff;
  }
  else if ((cVar1 == '\t') && (iVar2 = FUN_0044d1a4(param_1,9,0), iVar2 != -1)) {
    local_c = 0xffffffff;
  }
  else {
    local_c = 0xffffffff;
    puVar3 = &DAT_004c5e58;
    local_8 = 0;
    do {
      iVar2 = FUN_0044d600(param_1,param_2,*puVar3);
      if (iVar2 == 0) {
        iVar2 = FUN_0044d36c(param_1,param_2,*puVar3);
        if (iVar2 == 0) {
          return *puVar3;
        }
        local_c = *puVar3;
      }
      local_8 = local_8 + 1;
      puVar3 = puVar3 + 1;
    } while (local_8 < 0x24);
  }
  return local_c;
}

