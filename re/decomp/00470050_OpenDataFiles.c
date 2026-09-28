// OpenDataFiles @ 00470050 size=1281 sig=undefined OpenDataFiles() cc=unknown
// callers: WinMain
// callees: FUN_00411dac,FUN_0042836c,sprintf,FUN_00411dd4,FUN_00412154,FUN_004116f4,FUN_004b02a8,HdxArchive_Open,FUN_00411b34,FUN_00411ab0
// strings: \"Could not open dictionary\"|\"script\"|\"sound\"|\"CYHMRTUOSchat\"|\"%c%dN\"

/* Opens the HDX/HDD archives and dictionary (CYHMRTUOSchat) */

undefined4 OpenDataFiles(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  char *pcVar5;
  undefined1 local_21c [12];
  undefined1 local_210 [512];
  
  iVar1 = FUN_004b02a8(0x1c);
  if (iVar1 == 0) {
    DAT_004d5a5c = 0;
  }
  else {
    DAT_004d5a5c = FUN_00411dac(iVar1);
  }
  if (DAT_004d5a5c == 0) {
    FUN_0042836c(&DAT_004d5dec,PTR_s_Could_not_open_dictionary_005098ec,4,0,0);
    return 0;
  }
  iVar1 = HdxArchive_Open(DAT_004d5a5c,s_CYHMRTUOSchat_004d5920 + 9,1);
  if (iVar1 == 0) {
    if (DAT_004d59ac == 0) {
      return 0;
    }
    sprintf(local_210,&DAT_004d5d9f,&DAT_0058f20c,s_CYHMRTUOSchat_004d5920 + 9);
    iVar1 = HdxArchive_Open(DAT_004d5a5c,local_210,1);
    if (iVar1 == 0) {
      FUN_0042836c(&DAT_004d5dec,PTR_s_Could_not_open_dictionary_005098ec,4,0,0);
      return 0;
    }
  }
  if (DAT_004d59ac == 0) {
    uVar2 = 1;
  }
  else {
    iVar1 = FUN_004b02a8(0x1c);
    if (iVar1 == 0) {
      DAT_004d5a60 = 0;
    }
    else {
      DAT_004d5a60 = FUN_00411dac(iVar1);
    }
    if (DAT_004d5a60 == 0) {
      FUN_0042836c(&DAT_004d5dec,PTR_s_Could_not_open_dictionary_005098ec,4,0,0);
      uVar2 = 0;
    }
    else {
      iVar1 = HdxArchive_Open(DAT_004d5a60,&DAT_004d592e,1);
      if (iVar1 == 0) {
        sprintf(local_210,&DAT_004d5d9f,&DAT_0058f20c,&DAT_004d592e);
        iVar1 = HdxArchive_Open(DAT_004d5a60,local_210,1);
        if (iVar1 == 0) {
          FUN_00411dd4(DAT_004d5a60,3);
          DAT_004d5a60 = 0;
        }
      }
      if (DAT_004d5a60 == 0) {
        DAT_004d5a64 = 0;
      }
      else {
        iVar1 = FUN_004b02a8(0x1c);
        if (iVar1 == 0) {
          DAT_004d5a64 = 0;
        }
        else {
          DAT_004d5a64 = FUN_00411dac(iVar1);
        }
        if (DAT_004d5a64 == 0) {
          FUN_0042836c(&DAT_004d5dec,PTR_s_Could_not_open_dictionary_005098ec,4,0,0);
          return 0;
        }
        iVar1 = HdxArchive_Open(DAT_004d5a64,&DAT_004d5933,1);
        if (iVar1 == 0) {
          sprintf(local_210,&DAT_004d5d9f,&DAT_0058f20c,&DAT_004d5933);
          iVar1 = HdxArchive_Open(DAT_004d5a64,local_210,1);
          if (iVar1 == 0) {
            FUN_00412154(DAT_004d5a60);
            FUN_00411dd4(DAT_004d5a60,3);
            FUN_00411dd4(DAT_004d5a64,3);
            DAT_004d5a64 = 0;
            DAT_004d5a60 = 0;
          }
        }
      }
      if (DAT_004d5a60 == 0) {
        DAT_004d5a68 = 0;
      }
      else {
        iVar1 = FUN_004b02a8(0x1c);
        if (iVar1 == 0) {
          DAT_004d5a68 = 0;
        }
        else {
          DAT_004d5a68 = FUN_00411dac(iVar1);
        }
        if (DAT_004d5a68 == 0) {
          FUN_0042836c(&DAT_004d5dec,PTR_s_Could_not_open_dictionary_005098ec,4,0,0);
          return 0;
        }
        iVar1 = HdxArchive_Open(DAT_004d5a68,s_script_004d5938,1);
        if (iVar1 == 0) {
          sprintf(local_210,&DAT_004d5d9f,&DAT_0058f20c,s_script_004d5938);
          iVar1 = HdxArchive_Open(DAT_004d5a68,local_210,1);
          if (iVar1 == 0) {
            FUN_00412154(DAT_004d5a60);
            FUN_00412154(DAT_004d5a64);
            FUN_00411dd4(DAT_004d5a60,3);
            FUN_00411dd4(DAT_004d5a64,3);
            FUN_00411dd4(DAT_004d5a68,3);
            DAT_004d5a68 = 0;
            DAT_004d5a64 = 0;
            DAT_004d5a60 = 0;
          }
        }
      }
      if (DAT_004d5a60 == 0) {
        DAT_004d5a6c = 0;
      }
      else {
        iVar1 = FUN_004b02a8(0x1c);
        if (iVar1 == 0) {
          DAT_004d5a6c = 0;
        }
        else {
          DAT_004d5a6c = FUN_00411dac(iVar1);
        }
        if (DAT_004d5a6c == 0) {
          FUN_0042836c(&DAT_004d5dec,PTR_s_Could_not_open_dictionary_005098ec,4,0,0);
          return 0;
        }
        iVar1 = HdxArchive_Open(DAT_004d5a6c,s_sound_004d593f,1);
        if (iVar1 == 0) {
          sprintf(local_210,&DAT_004d5d9f,&DAT_0058f20c,s_sound_004d593f);
          iVar1 = HdxArchive_Open(DAT_004d5a6c,local_210,1);
          if (iVar1 == 0) {
            FUN_00412154(DAT_004d5a60);
            FUN_00412154(DAT_004d5a64);
            FUN_00412154(DAT_004d5a68);
            FUN_00411dd4(DAT_004d5a60,3);
            FUN_00411dd4(DAT_004d5a64,3);
            FUN_00411dd4(DAT_004d5a68,3);
            FUN_00411dd4(DAT_004d5a6c,3);
            DAT_004d5a6c = 0;
            DAT_004d5a68 = 0;
            DAT_004d5a64 = 0;
            DAT_004d5a60 = 0;
          }
        }
      }
      puVar3 = (undefined4 *)FUN_004b02a8(0x18);
      if (puVar3 != (undefined4 *)0x0) {
        FUN_004116f4(puVar3);
        *puVar3 = &PTR_FUN_004b700c;
      }
      DAT_004d5a70 = puVar3;
      puVar3[5] = DAT_004d5a60;
      iVar1 = FUN_004b02a8(0x1c);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = FUN_00411b34(iVar1,DAT_004d5a70);
      }
      iVar4 = 0;
      pcVar5 = s_CYHMRTUOSchat_004d5920;
      DAT_004d5a74 = iVar1;
      *(int *)(iVar1 + 0x14) = DAT_004d5a64;
      *(undefined4 *)(iVar1 + 0xc) = 100;
      do {
        iVar1 = 0;
        do {
          sprintf(local_21c,s__c_dN_004d5dee,(int)*pcVar5,iVar1);
          (**(code **)*DAT_004d5a70)(DAT_004d5a70,local_21c);
          iVar1 = iVar1 + 1;
        } while (iVar1 < 9);
        iVar4 = iVar4 + 1;
        pcVar5 = pcVar5 + 1;
      } while (iVar4 < 9);
      uVar2 = 1;
    }
  }
  return uVar2;
}

