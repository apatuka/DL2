// FUN_0044930c @ 0044930c size=166 sig=undefined FUN_0044930c() cc=unknown
// callers: FUN_0044ae10,FUN_0044b0d4,FUN_0044b168,FUN_0044ac18,FUN_0044a48c,FUN_0044ad14,@BackWndProc$qqspvuiuil,FUN_0044b24c,FUN_0044a5e8,@IntroWndProc$qqspvuiuil
// callees: CheckBuilding,FUN_0043baf4,CheckViewCombat,FUN_00435e34,FUN_0043be98,FUN_00414870,CheckEventLog,CheckTechTree,FUN_00427e6c,FUN_0042f5d8,FUN_00436ef4,FUN_00413eb4,CheckColonyAssistant,CheckArmy

undefined4 FUN_0044930c(void)

{
  undefined4 uVar1;
  
  if (DAT_004d59b4 < 0xc) {
    if (DAT_004d59b4 == 0xb) {
      uVar1 = FUN_00436ef4();
      return uVar1;
    }
    switch(DAT_004d59b4) {
    case 0:
    case 1:
      if (DAT_004d5aa0 != '\0') {
        uVar1 = FUN_0043be98();
        return uVar1;
      }
      uVar1 = FUN_0043baf4();
      return uVar1;
    case 2:
      uVar1 = CheckViewCombat();
      return uVar1;
    case 3:
      uVar1 = CheckTechTree();
      return uVar1;
    case 5:
      uVar1 = CheckBuilding();
      return uVar1;
    case 6:
      uVar1 = FUN_0042f5d8();
      return uVar1;
    case 7:
      uVar1 = CheckColonyAssistant();
      return uVar1;
    case 9:
      uVar1 = CheckEventLog();
      return uVar1;
    }
  }
  else if (DAT_004d59b4 < 0x33) {
    if (DAT_004d59b4 == 0x32) {
      return 0;
    }
    if (DAT_004d59b4 == 0xe) {
      uVar1 = FUN_00435e34();
      return uVar1;
    }
    if (DAT_004d59b4 == 0x22) {
      uVar1 = CheckArmy();
      return uVar1;
    }
    if (DAT_004d59b4 == 0x24) {
      uVar1 = FUN_00427e6c();
      return uVar1;
    }
  }
  else {
    if (DAT_004d59b4 == 0x58) {
      uVar1 = FUN_00414870();
      return uVar1;
    }
    if (DAT_004d59b4 == 0x59) {
      uVar1 = FUN_00413eb4();
      return uVar1;
    }
  }
  return 0;
}

