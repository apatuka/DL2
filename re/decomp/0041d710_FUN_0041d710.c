// FUN_0041d710 @ 0041d710 size=289 sig=undefined FUN_0041d710() cc=unknown
// callers: CheckBuilding,FUN_0041d414
// callees: sprintf,FUN_004760d0,FUN_0041c378,FUN_0044b620,FUN_0041c418,FUN_0041c3dc,FUN_00484ebc,FUN_00482f94,FUN_0042836c,FUN_00484ea4,FUN_0049eb44,FUN_00484ee0
// strings: \"You must have a unit in the build queue selected before you can delete one.\"|\"Oolan's Advice\"|\"Do you want to remove this %s from the build queue?\"|\"You must select a unit before you may delete it.\"

void FUN_0041d710(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 local_10c [256];
  
  iVar2 = FUN_0049eb44(DAT_004b7758,0x1e,1,0x18,0,0);
  iVar3 = FUN_0049eb44(DAT_004b7758,0x1e,1,0x22,0,0);
  if (iVar3 == iVar2) {
    FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_must_have_a_unit_in_the_buil_00509228,4,0,
                 0xd);
  }
  else {
    uVar4 = FUN_0044b620(DAT_0053b850);
    FUN_00484ea4(uVar4);
    iVar2 = iVar3;
    while (iVar2 != 0) {
      FUN_00484ebc(uVar4);
      iVar2 = iVar2 + -1;
    }
    cVar1 = FUN_00484ee0(uVar4);
    if (cVar1 == '\0') {
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_must_select_a_unit_before_yo_00509234,4,0
                   ,0xd);
    }
    else {
      sprintf(local_10c,PTR_s_Do_you_want_to_remove_this__s_fr_0050922c,
              (&PTR_s_No_Unit_004faf7c)[cVar1 * 9]);
      FUN_004760d0(DAT_0053b84c,PTR_DAT_004d5988,
                   *(undefined4 *)(&DAT_004f9de6 + *(char *)(DAT_0053b850 + 4) * 0x32),iVar3);
      if (*(char *)(DAT_0053b850 + 0x30) != '\0') {
        FUN_0041c3dc();
        FUN_0041c418();
      }
      FUN_00482f94(PTR_DAT_004d5988);
      FUN_0041c378();
    }
  }
  return;
}

