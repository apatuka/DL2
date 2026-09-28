// MoveLaborToHousingNoNet @ 0044c368 size=121 sig=undefined MoveLaborToHousingNoNet() cc=unknown
// callers: FUN_0044c49c,FUN_0047d068,FUN_0044f3f0
// callees: FUN_0044ba40,FUN_004023dc,DebugMessage,FUN_0044c320,FUN_0044ba18
// strings: \"Invalid arguments in MoveLaborToHousingNoNet\"

/* auto-named from string evidence: MoveLaborToHousingNoNet */

undefined4 MoveLaborToHousingNoNet(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    DebugMessage(s_Invalid_arguments_in_MoveLaborTo_004c6008);
  }
  else {
    iVar6 = 0;
    piVar5 = (int *)(param_1 + 0x154);
    do {
      iVar1 = *piVar5;
      if (iVar1 != 0) {
        iVar2 = FUN_0044ba18(iVar1);
        iVar3 = FUN_0044ba40(iVar1);
        if ((iVar2 < iVar3) && (iVar2 = FUN_004023dc(iVar1,0x14), iVar2 != -1)) {
          uVar4 = FUN_0044c320(param_1,param_2,param_3,iVar1,iVar2);
          return uVar4;
        }
      }
      iVar6 = iVar6 + 1;
      piVar5 = piVar5 + 0xd;
    } while (iVar6 < 0x24);
  }
  return 0;
}

