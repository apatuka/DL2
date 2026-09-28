// FUN_004383a4 @ 004383a4 size=774 sig=undefined FUN_004383a4() cc=unknown
// callers: FUN_004386ac,FUN_00438830
// callees: FUN_0049eb44,WriteUnitData,FUN_004382d0,FUN_0044ddf4,FUN_00471e58,FUN_00437a18,sprintf,FUN_0044ff28
// strings: \"Scout\"

void FUN_004383a4(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  char *pcVar7;
  int local_134;
  int *local_12c;
  int *local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined1 local_10c [200];
  undefined1 local_44 [52];
  
  local_134 = 0;
  iVar4 = 0;
  bVar1 = false;
  local_124 = 0;
  local_120 = *(undefined4 *)(DAT_004c46b4 + 0x34);
  local_11c = 0;
  local_118 = 0;
  local_114 = 0;
  if ((DAT_004d5aa0 == '\0') || (DAT_00559338 != 0)) {
    iVar5 = 0;
    local_128 = &DAT_0055940c;
    pcVar7 = &DAT_004f9dd9 + *(char *)(DAT_00559338 + 4) * 0x32;
    do {
      iVar3 = (int)*pcVar7;
      if (iVar3 != 0) {
        FUN_0044ddf4(PTR_DAT_004d5988,iVar3,local_44);
        iVar2 = FUN_00471e58(PTR_DAT_004d5988,DAT_0055933c,local_44);
        if (((DAT_00559340 != '\0') || (iVar2 == 0)) && (iVar2 = FUN_0044ff28(iVar3), iVar2 == 0)) {
          sprintf(local_10c,s__d__s_004c473c + 3,(&PTR_s_No_Unit_004faf7c)[iVar3 * 9]);
          iVar4 = FUN_0049eb44(DAT_004c46b4,5,1,0x26,0xffffffff,local_10c);
          if (iVar4 != 0) {
            *local_128 = iVar3;
            local_128 = local_128 + 1;
            FUN_004382d0(&local_124,(int)(char)*PTR_DAT_004d5988,iVar3);
            FUN_0049eb44(DAT_004c46b4,5,1,0x23,iVar4 + -1,local_10c);
            FUN_0049eb44(DAT_004c46b4,5,1,0x24,iVar4 + -1,&local_124);
            if (iVar3 == DAT_004c4738) {
              bVar1 = true;
              local_134 = iVar4 + -1;
            }
          }
        }
      }
      iVar5 = iVar5 + 1;
      pcVar7 = pcVar7 + 1;
    } while (iVar5 < 10);
  }
  else {
    iVar5 = 0;
    local_12c = &DAT_0055940c;
    piVar6 = &DAT_004c46b8;
    do {
      iVar3 = *piVar6;
      iVar2 = FUN_0044ff28(iVar3);
      if (iVar2 == 0) {
        *local_12c = iVar3;
        local_12c = local_12c + 1;
        sprintf(local_10c,s__d__s_004c473c + 3,(&PTR_s_No_Unit_004faf7c)[iVar3 * 9]);
        iVar4 = FUN_0049eb44(DAT_004c46b4,5,1,0x26,0xffffffff,local_10c);
        if (iVar4 != 0) {
          FUN_004382d0(&local_124,(int)(char)*PTR_DAT_004d5988,iVar3);
          FUN_0049eb44(DAT_004c46b4,5,1,0x23,iVar4 + -1,local_10c);
          FUN_0049eb44(DAT_004c46b4,5,1,0x24,iVar4 + -1,&local_124);
          if (iVar3 == DAT_004c4738) {
            bVar1 = true;
            local_134 = iVar4 + -1;
          }
        }
      }
      iVar5 = iVar5 + 1;
      piVar6 = piVar6 + 1;
    } while (iVar5 < 0x20);
  }
  FUN_0049eb44(DAT_004c46b4,6,1,0x31,5,1);
  if (bVar1) {
    FUN_0049eb44(DAT_004c46b4,5,1,0x1b,local_134,0);
    FUN_0049eb44(DAT_004c46b4,5,1,0x21,local_134,1);
    FUN_00437a18();
  }
  else if (iVar4 < 1) {
    DAT_004c4738 = 0;
  }
  else {
    FUN_0049eb44(DAT_004c46b4,5,1,0x1b,0,0);
    FUN_0049eb44(DAT_004c46b4,5,1,0x21,0,1);
    FUN_00437a18();
  }
  WriteUnitData();
  return;
}

