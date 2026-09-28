// FUN_00467e58 @ 00467e58 size=360 sig=undefined FUN_00467e58() cc=unknown
// callers: FUN_00467fc0,FUN_00468030
// callees: fclose,FUN_00411dac,FUN_0042836c,FUN_004aa518,FUN_004b02a8,HdxArchive_Open,FUN_0041244c,thunk_FUN_004ad1a4,sprintf,fopen,free
// strings: \"Could not open dictionary\"|\"levels\"|\"campaign\\\\\"|\"%sAUTOSAVE%s\"

void FUN_00467e58(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 local_810 [1028];
  undefined1 local_40c [1028];
  int local_8;
  
  iVar1 = FUN_004b02a8(0x1c);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_00411dac(iVar1);
  }
  if (iVar1 == 0) {
    FUN_0042836c(&DAT_004d5245,PTR_s_Could_not_open_dictionary_005098ec,4,0,0);
    return;
  }
  iVar2 = HdxArchive_Open(iVar1,s_levels_004d5247,1);
  if (iVar2 == 0) {
    if (DAT_004d59ac == 0) {
      return;
    }
    sprintf(local_40c,&DAT_004d524e,&DAT_0058f20c,s_levels_004d5247);
    iVar2 = HdxArchive_Open(iVar1,local_40c,1);
    if (iVar2 == 0) {
      FUN_0042836c(&DAT_004d5245,PTR_s_Could_not_open_dictionary_005098ec,4,0,0);
      return;
    }
  }
  sprintf(local_810,&DAT_004d5253,(&PTR_s_CHCHT_004d5188)[param_2],param_3);
  sprintf(param_1,s__sAUTOSAVE_s_004d5258,s_campaign__004d5265,&DAT_004d526f);
  iVar1 = FUN_0041244c(iVar1,local_810,&local_8);
  if (iVar1 != 0) {
    iVar2 = fopen(param_1,&DAT_004d5274);
    if (iVar2 == 0) {
      free(iVar1);
    }
    else {
      iVar3 = FUN_004aa518(iVar1,1,local_8,iVar2);
      if (iVar3 == local_8) {
        free(iVar1);
        fclose(iVar2);
      }
      else {
        free(iVar1);
        fclose(iVar2);
        thunk_FUN_004ad1a4(param_1);
      }
    }
  }
  return;
}

