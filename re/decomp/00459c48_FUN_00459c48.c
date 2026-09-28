// FUN_00459c48 @ 00459c48 size=588 sig=undefined FUN_00459c48() cc=unknown
// callers: FUN_0047fc84
// callees: sprintf,FUN_0047e074,FUN_0045973c,FUN_004847f8,FUN_00459864,FUN_00484818

void FUN_00459c48(int param_1)

{
  int iVar1;
  short *psVar2;
  int *piVar3;
  int *piVar4;
  int local_58 [5];
  int local_44 [7];
  short *local_28;
  int local_24;
  int local_20;
  undefined1 local_1c [12];
  undefined4 local_10;
  int local_c;
  int local_8;
  
  piVar3 = &DAT_004d1b10;
  piVar4 = local_44;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar4 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar4 = piVar4 + 1;
  }
  piVar3 = &DAT_004d1b2c;
  piVar4 = local_58;
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar4 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar4 = piVar4 + 1;
  }
  local_10 = 0;
  local_8 = FUN_0047e074();
  if (local_8 != 0) {
    FUN_0045973c(param_1,local_44,local_58,&local_c);
    iVar1 = 0;
    psVar2 = (short *)&DAT_004d1b40;
    local_28 = &DAT_004d1b54;
    piVar3 = local_58;
    do {
      if (*piVar3 != 0) {
        switch(iVar1) {
        case 0:
          local_10 = 1;
          break;
        case 1:
          if (*(char *)(param_1 + 0x21) == '\0') {
            local_10 = 7;
            if (local_c == 0) {
              local_10 = 6;
            }
          }
          else {
            local_10 = 0;
          }
          break;
        case 2:
          local_10 = 2;
          break;
        case 3:
          if (*(char *)(param_1 + 0x21) == '\0') {
            local_10 = 3;
          }
          else {
            local_10 = 4;
          }
          break;
        case 4:
          local_10 = 5;
        }
        if (*(char *)(param_1 + 0x21) == '\0') {
          FUN_00459864(local_8,(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] + 1000,local_10,
                       (int)*local_28,(int)local_28[1]);
          sprintf(local_1c,&DAT_004d1b84,*piVar3);
          FUN_004847f8(*local_28 + 0x10,local_28[1] + 0x10,local_1c,0xff);
        }
        else {
          FUN_00459864(local_8,(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] + 1000,local_10,
                       (int)*psVar2,(int)psVar2[1]);
          sprintf(local_1c,&DAT_004d1b84,*piVar3);
          FUN_004847f8(*psVar2 + 0x10,psVar2[1] + 0x10,local_1c,0xff);
        }
      }
      iVar1 = iVar1 + 1;
      psVar2 = psVar2 + 2;
      local_28 = local_28 + 2;
      piVar3 = piVar3 + 1;
    } while (iVar1 < 5);
    iVar1 = 0;
    psVar2 = &DAT_004d1b68;
    piVar3 = local_44;
    do {
      if (*piVar3 != 0) {
        local_20 = (int)*psVar2;
        local_24 = (int)psVar2[1];
        FUN_00459864(local_8,0x3ef,iVar1,local_20,local_24 + 0x10);
        sprintf(local_1c,&DAT_004d1b84,*piVar3);
        FUN_00484818(local_20,local_24 + 0xb,0x10,0xb,local_1c,0xd);
        psVar2 = psVar2 + 2;
      }
      iVar1 = iVar1 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar1 < 7);
  }
  return;
}

