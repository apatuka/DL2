// FUN_0042836c @ 0042836c size=154 sig=undefined FUN_0042836c() cc=unknown
// callers: FUN_0043210c,FUN_00429464,FUN_00461e9c,FUN_00467e58,FUN_0045e6d0,FUN_0045e554,FUN_00419f50,FUN_00420d34,FUN_00413784,FUN_00468a28,FUN_00468c94,FUN_00426868,FUN_00446084,FUN_004618e8,CheckSubTech,FUN_00471d34,FUN_004634a0,CheckSubUnit,GetNetGameOptions,FUN_0045c384,FUN_00474920,FUN_00439e98,OpenDataFiles,FUN_0045d984,FUN_0045eadc,FUN_00468214,FUN_0045b094,FUN_00420e34,FUN_0043cc5c,FUN_00467884,FUN_00437718,ResetNetGame,FUN_0045e4f4,FUN_0041db10,FUN_00479b6c,WinMain,FUN_0043baf4,FUN_0045b8e8,FUN_0043bd5c,FUN_0045c560,FUN_0043be98,FUN_0045ca3c,TestMemory,InitCYGame,FUN_004748dc,FUN_0046a844,FUN_0045b304,FUN_004751d0,FUN_0041d710,FUN_00419924,FUN_0045ef64,FUN_0045ad98,FUN_00473924,FUN_0043242c,FUN_00479700,FUN_0046f5d4,FUN_0045c704,ChCht,FUN_00461d80,FUN_00458508,FUN_0045b448,FUN_00420aac,FUN_00468da0,NetBreakPact,FUN_00421178,FUN_00401ac0,FUN_0046e39c,FUN_00423904,FUN_004848cc,FUN_00466ddc,FUN_004752fc,FUN_00472da4,FUN_0041d414,FUN_00461c68,FUN_00415624,WaitSync,FUN_0045ae78,CheckSubInfo,FUN_004393e8,FUN_0042ebb8
// callees: FUN_00427ee8,FUN_00427f04,FUN_00427e6c,FUN_00427e80

undefined4
FUN_0042836c(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5
            )

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = 0x28a0;
  if (param_3 == 0x37333044) {
    iVar3 = 0x37333044;
  }
  else if (param_3 == 4) {
    iVar3 = 0x28a2;
  }
  else if ((param_3 == 6) || (param_3 == 0x18)) {
    iVar3 = 0x28a1;
  }
  iVar1 = FUN_00427e80(iVar3,param_1,param_2,param_4,param_5);
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    FUN_00427f04();
    if (iVar3 == 0x37333044) {
      uVar2 = 1;
    }
    else {
      iVar3 = 0;
      while ((iVar3 != 3 && (iVar3 != 4))) {
        iVar3 = FUN_00427e6c();
      }
      FUN_00427ee8();
      if (iVar3 == 3) {
        uVar2 = 1;
      }
      else {
        uVar2 = 2;
      }
    }
  }
  return uVar2;
}

