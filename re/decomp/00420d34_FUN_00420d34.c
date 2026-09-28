// FUN_00420d34 @ 00420d34 size=253 sig=undefined FUN_00420d34() cc=unknown
// callers: CheckColonyAssistant,FUN_00420e34
// callees: sprintf,FUN_0041ff24,FUN_004760d0,FUN_00484ebc,FUN_0041ff98,FUN_0042836c,FUN_0044b5bc,FUN_00484ea4,FUN_0049eb44,FUN_0041ffd4,FUN_00484ee0
// strings: \"You must have a unit in the build queue selected before you can delete one.\"|\"Oolan's Advice\"|\"Do you want to remove this %s from the build queue?\"|\"You must select a unit before you may delete it.\"

void FUN_00420d34(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 local_110 [256];
  
  iVar2 = FUN_0049eb44(DAT_004b7a14,0xb,1,0x18,0,0);
  iVar3 = FUN_0049eb44(DAT_004b7a14,0xb,1,0x22,0,0);
  if (iVar3 == iVar2) {
    FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_must_have_a_unit_in_the_buil_00509228,4,0,
                 0xd);
  }
  else {
    iVar5 = DAT_0053b8ac + -0x16;
    uVar4 = FUN_0044b5bc(DAT_0053b8b8,iVar5);
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
      sprintf(local_110,PTR_s_Do_you_want_to_remove_this__s_fr_0050922c,
              (&PTR_s_No_Unit_004faf7c)[cVar1 * 9]);
      FUN_004760d0(DAT_0053b8b8,PTR_DAT_004d5988,iVar5,iVar3);
      FUN_0041ff98();
      FUN_0041ffd4();
      FUN_0041ff24();
    }
  }
  return;
}

