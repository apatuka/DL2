// CheckBuildingList @ 0041b018 size=400 sig=undefined CheckBuildingList() cc=unknown
// callers: FUN_0041b280
// callees: FUN_0048db5d,FUN_00471d34,FUN_0041ac8c,FUN_0044de9c,FUN_00426594,FUN_0041ac34,FUN_0041a610,FUN_004a2cb5,FUN_00471f5c,FUN_0041ac40,FUN_0041afec,DebugMessage
// strings: \"No pointer to SMenu in CheckBuildingList()\"

/* auto-named from string evidence: CheckBuildingList */

int CheckBuildingList(void)

{
  int iVar1;
  int local_3c;
  undefined1 local_38 [52];
  
  if (DAT_004b76f8 == 0) {
    DebugMessage(s_No_pointer_to_SMenu_in_CheckBuil_004b772b);
    return 0;
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  iVar1 = FUN_004a2cb5(DAT_004b76f8,&local_3c);
  if (((iVar1 != 0) || (local_3c == 0)) || (*(int *)(DAT_004b76f8 + 100) != 0))
  goto switchD_0041b08d_caseD_0;
  switch(local_3c) {
  case 2:
    FUN_0041afec();
    break;
  case 3:
    iVar1 = FUN_0041a610();
    if ((DAT_004b76f0 == 0) || (DAT_004b76f0 <= iVar1)) {
      DAT_004b76fc = 0;
    }
    else {
      iVar1 = FUN_00471f5c(DAT_004b76fc,DAT_0053b334);
      if (iVar1 != 0) {
        FUN_0044de9c(&DAT_0059f160 + *(char *)(DAT_0053b334 + 0x20) * 0x2d8,DAT_004b76fc,
                     (int)*(char *)(DAT_0053b334 + 0x21),local_38);
        FUN_00471d34(*(undefined4 *)(&DAT_004f9dbc + DAT_004b76fc * 0x32),iVar1,local_38);
        DAT_004b76fc = 0;
        FUN_0041ac40();
        return 0;
      }
    }
    FUN_0041ac8c();
    break;
  case 4:
    FUN_0041ac8c();
    break;
  case 5:
    FUN_00426594(&DAT_004d345c + DAT_004b76fc * 0x24);
  default:
switchD_0041b08d_caseD_0:
    FUN_0041ac34();
    local_3c = 0;
    break;
  case 6:
    FUN_0041a610();
  }
  DAT_004d59a4 = 0;
  return local_3c;
}

