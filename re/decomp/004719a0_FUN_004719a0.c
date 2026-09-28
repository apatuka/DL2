// FUN_004719a0 @ 004719a0 size=246 sig=undefined FUN_004719a0() cc=unknown
// callers: FUN_00468800,GetNetGameOptions,FUN_00468d3c,FUN_00468214
// callees: FUN_00471028,FUN_00470fc0
// strings: \"Startup\"|\"master\"|\"Save File\"|\"Master Address\"|\"User Name\"|\"Players\"

undefined4
FUN_004719a0(undefined4 param_1,int param_2,uint *param_3,undefined4 param_4,undefined4 param_5,
            undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
            undefined4 param_10)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  char *pcVar6;
  bool bVar7;
  char local_18 [20];
  
  iVar2 = FUN_00470fc0(PTR_s_Startup_004d5f68,PTR_DAT_004d5fe0,local_18,0x14,param_1);
  if (iVar2 != 0) {
    pcVar3 = local_18;
    pcVar6 = PTR_s_master_004d6060;
    do {
      bVar7 = *pcVar3 == *pcVar6;
      if ((!bVar7) || (bVar7 = true, *pcVar3 == '\0')) break;
      pcVar1 = pcVar3 + 1;
      bVar7 = *pcVar1 == pcVar6[1];
      if (!bVar7) break;
      pcVar3 = pcVar3 + 2;
      pcVar6 = pcVar6 + 2;
      bVar7 = *pcVar1 == '\0';
    } while (!bVar7);
    *param_3 = (uint)bVar7;
  }
  if ((iVar2 != 0) && (param_2 != 0)) {
    iVar2 = FUN_00470fc0(PTR_s_Startup_004d5f68,PTR_s_Save_File_004d5fe4,param_5,param_6,param_1);
  }
  if ((iVar2 != 0) && (*param_3 == 0)) {
    iVar2 = FUN_00470fc0(PTR_s_Startup_004d5f68,PTR_s_Master_Address_004d5fe8,param_9,param_10,
                         param_1);
  }
  iVar4 = 0;
  if (iVar2 != 0) {
    iVar4 = FUN_00470fc0(PTR_s_Startup_004d5f68,PTR_s_User_Name_004d5ff0,param_7,param_8,param_1);
  }
  uVar5 = 0;
  if (iVar4 != 0) {
    uVar5 = FUN_00471028(PTR_s_Startup_004d5f68,PTR_s_Players_004d5fec,param_4,param_1);
  }
  return uVar5;
}

