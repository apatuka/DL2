// FUN_0047fc84 @ 0047fc84 size=257 sig=undefined FUN_0047fc84() cc=unknown
// callers: FUN_00480150
// callees: sprintf,FUN_0046b074,FUN_00459c48,FUN_004847c8,FUN_0046b0e4
// strings: \"Population %d/%d\"

void FUN_0047fc84(int param_1)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined1 local_10c [256];
  int local_c;
  int local_8;
  
  iVar2 = DAT_004c545c;
  iVar4 = DAT_004c5458 + 0x10;
  iVar5 = DAT_004c545c + 0x10;
  local_8 = DAT_004c5460 - DAT_004c5b60;
  sprintf(local_10c,&DAT_004dce01,param_1);
  FUN_004847c8(iVar4,iVar5,local_8 + -0x20,local_10c,0xff,1);
  if ((DAT_004cf850 == 0) && ('\x02' < *(char *)(param_1 + 0x66 + DAT_0058f1f4))) {
    iVar5 = FUN_0046b074(param_1);
    if (0 < iVar5) {
      if ((DAT_004d5aa0 == '\0') && (*(char *)(param_1 + 0x66 + DAT_0058f1f4) != '\x04')) {
        sVar1 = *(short *)(param_1 + 0x38);
      }
      else {
        sVar1 = *(short *)(param_1 + 0x30);
      }
      local_c = (int)sVar1;
      uVar3 = FUN_0046b0e4(param_1);
      sprintf(local_10c,PTR_s_Population__d__d_00509978,local_c,uVar3);
      FUN_004847c8(iVar4,iVar2 + 0x1e,local_8 + -0x20,local_10c,0xff,1);
    }
    FUN_00459c48(param_1);
  }
  return;
}

