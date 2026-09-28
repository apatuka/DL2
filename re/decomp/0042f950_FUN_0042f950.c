// FUN_0042f950 @ 0042f950 size=530 sig=undefined FUN_0042f950() cc=unknown
// callers: FUN_0042fb64,FUN_0043044c
// callees: FUN_0049eb44
// strings: \"Win by finding and holding shrines for long enough to complete your research, as below:\"|\"Win by totally eliminating your opponents.\"|\"Win either by owning the below number of cities, or totally eliminating your opponents.\"

void FUN_0042f950(void)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 local_14;
  
  puVar1 = PTR_s_Win_either_by_owning_the_below_n_00509514;
  if (((DAT_004d5b00 != '\0') &&
      (puVar1 = PTR_s_Win_by_totally_eliminating_your_o_00509518, DAT_004d5b00 != '\x01')) &&
     (puVar1 = PTR_s_Win_by_finding_and_holding_shrin_0050951c, DAT_004d5b00 != '\x02')) {
    puVar1 = (undefined *)0x0;
  }
  FUN_0049eb44(DAT_004c4294,0x35,1,0xf,0,puVar1);
  FUN_0049eb44(DAT_004c4294,0xc,1,0x3c,0,1);
  FUN_0049eb44(DAT_004c4294,0xd,1,0x3c,0,1);
  FUN_0049eb44(DAT_004c4294,0xe,1,0x3c,0,1);
  FUN_0049eb44(DAT_004c4294,0xf,1,0x3c,0,1);
  FUN_0049eb44(DAT_004c4294,0x10,1,0x3c,0,1);
  FUN_0049eb44(DAT_004c4294,0x11,1,0x3c,0,1);
  FUN_0049eb44(DAT_004c4294,0x12,1,0x3c,0,1);
  FUN_0049eb44(DAT_004c4294,0x13,1,0x3c,0,1);
  FUN_0049eb44(DAT_004c4294,0x14,1,0x3c,0,1);
  FUN_0049eb44(DAT_004c4294,0x15,1,0x3c,0,1);
  FUN_0049eb44(DAT_004c4294,0x16,1,0x3c,0,1);
  if (DAT_004d5b00 == '\0') {
    uVar2 = 0x12;
    uVar5 = 0x13;
    uVar6 = 0x14;
    uVar4 = 0x15;
    local_14 = 0x16;
    iVar3 = 0;
  }
  else {
    if (DAT_004d5b00 == '\x01') {
      return;
    }
    if (DAT_004d5b00 != '\x02') {
      return;
    }
    uVar2 = 0xc;
    uVar5 = 0xd;
    uVar6 = 0xe;
    uVar4 = 0xf;
    local_14 = 0x10;
    iVar3 = 0x11;
  }
  FUN_0049eb44(DAT_004c4294,uVar2,1,0x3c,1,1);
  FUN_0049eb44(DAT_004c4294,uVar5,1,0x3c,1,1);
  FUN_0049eb44(DAT_004c4294,uVar6,1,0x3c,1,1);
  FUN_0049eb44(DAT_004c4294,uVar4,1,0x3c,1,1);
  FUN_0049eb44(DAT_004c4294,local_14,1,0x3c,1,1);
  if (iVar3 != 0) {
    FUN_0049eb44(DAT_004c4294,iVar3,1,0x3c,1,1);
  }
  return;
}

