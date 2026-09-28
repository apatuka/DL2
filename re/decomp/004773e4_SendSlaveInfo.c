// SendSlaveInfo @ 004773e4 size=482 sig=undefined SendSlaveInfo() cc=unknown
// callers: FUN_00468a28
// callees: FUN_0047526c,FUN_004a6b48,memcpy,FUN_00474cc4
// strings: \"SendSlaveInfo\"|\"New Player\"

/* auto-named from string evidence: SendSlaveInfo */

void SendSlaveInfo(void)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  char cVar4;
  undefined4 *puVar5;
  undefined1 local_6c;
  undefined1 local_6b;
  char local_6a;
  undefined1 local_64;
  undefined4 local_5e;
  undefined4 local_56;
  undefined2 local_50;
  undefined2 local_4e;
  undefined1 local_4c;
  char local_4b [7];
  char local_44 [7];
  undefined1 local_3d;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined1 local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2c [28];
  
  iVar3 = 0;
  local_6c = DAT_004d5a54;
  local_6b = 0xff;
  local_64 = 0xc;
  local_5e = 0x5c;
  pcVar1 = &DAT_0059f161;
  pcVar2 = local_44;
  do {
    cVar4 = *pcVar1;
    if (cVar4 == '\x02') {
      cVar4 = '\x01';
    }
    *pcVar2 = cVar4;
    pcVar2[-7] = pcVar1[1];
    iVar3 = iVar3 + 1;
    pcVar2 = pcVar2 + 1;
    pcVar1 = pcVar1 + 0x2d8;
  } while (iVar3 < 7);
  memcpy(local_2c,&DAT_004d5b10,0x14);
  local_56 = DAT_0059f158;
  local_50 = (undefined2)DAT_004d5b30;
  local_4e = (undefined2)DAT_004d5b38;
  local_3d = (undefined1)DAT_004d5aec;
  local_3c = (undefined1)DAT_004d5af0;
  local_32 = (undefined1)DAT_004d5af8;
  local_31 = (undefined1)DAT_004d5afc;
  local_3b = (undefined1)DAT_004d5b0c;
  local_3a = (undefined1)DAT_004d5b04;
  local_37 = (undefined1)DAT_004d5b2c;
  local_36 = (undefined1)DAT_004d5b34;
  local_39 = (undefined1)DAT_004d5b3c;
  local_35 = (code *)PTR_FUN_004d02b8 == FUN_00457ac0;
  local_38 = (undefined1)DAT_004d5b08;
  local_33 = DAT_004d5b00;
  local_2f = (undefined1)DAT_004d5a90;
  local_2e = (undefined1)DAT_004d5af4;
  if (DAT_004d5a88 == 0) {
    if (DAT_0058ed2e == '\0') {
      local_34 = 0;
    }
    else {
      local_34 = 1;
      local_30 = DAT_0058f12e;
    }
  }
  else {
    local_34 = 2;
  }
  cVar4 = '\0';
  puVar5 = &DAT_00653518;
  pcVar2 = &DAT_0059f161;
  for (iVar3 = 0; iVar3 < DAT_004d5aec; iVar3 = iVar3 + 1) {
    if (*pcVar2 == '\x02') {
      local_4c = (undefined1)iVar3;
      local_6a = cVar4;
      FUN_00474cc4(s_SendSlaveInfo_004dc1de,&local_6c,*puVar5);
      cVar4 = cVar4 + '\x01';
    }
    puVar5 = puVar5 + 1;
    pcVar2 = pcVar2 + 0x2d8;
  }
  DAT_0058f1fc = 1;
  FUN_0047526c(DAT_0058f1f4,s_New_Player_00509804);
  FUN_004a6b48(&DAT_0059f413 + DAT_0058f1f4 * 0x2d8,s_New_Player_00509804,0x1f);
  return;
}

