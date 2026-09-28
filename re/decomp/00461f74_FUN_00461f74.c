// FUN_00461f74 @ 00461f74 size=128 sig=undefined FUN_00461f74() cc=unknown
// callers: FUN_0045f5e4
// callees: WriteFile,memset
// strings: \"Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\\nPre-release version XXXXXXXXXXX\"

void FUN_00461f74(HANDLE param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  char local_a4 [88];
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined1 local_3c [52];
  DWORD local_8;
  
  uVar2 = 0xffffffff;
  pcVar4 = s_Deadlock_2__c_1997_Accolade_Inc__004d1ea0;
  do {
    pcVar5 = pcVar4;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar5 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar5;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar5 + -uVar2;
  pcVar5 = local_a4;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar5 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  }
  local_4c = DAT_004d5ae8;
  local_48 = param_2;
  local_44 = 0;
  local_40 = 0xffffffff;
  memset(local_3c,0,0x14);
  WriteFile(param_1,local_a4,0x9c,&local_8,(LPOVERLAPPED)0x0);
  return;
}

