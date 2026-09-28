// WaitSync @ 0046e9f4 size=877 sig=undefined WaitSync() cc=unknown
// callers: SyncBeginTurn,RunAITurns,SyncCreateBuilding,ResetNetGame,SyncCreateUnit,FUN_0046eda8,CreateRandomEvents,SyncDisbandUnit,WinMain
// callees: sprintf,FUN_00423d84,FUN_004779c0,FUN_0046e9d0,FUN_00477394,FUN_0046e96c,FUN_0042836c,FUN_0046c9cc,FUN_00477e4c,DebugMessage,FUN_00475344,FUN_00427e6c,ChCht,FUN_0046e980,FUN_004780e4,FUN_00477f9c
// strings: \"WaitSync in %s\"|\"WaitSync\"|\"Are you sure you want to exit Deadlock 2?\"|\"Exit Game\"|\"Reseed\"

/* Network synchronization barrier (tag string logged as "WaitSync in %s") */

void WaitSync(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined1 local_104 [256];
  
  sprintf(local_104,s_WaitSync_in__s_004d5c87,param_1);
  DebugMessage(local_104);
  FUN_0046e96c();
  if (DAT_004d5a50 != 0) {
    if (DAT_004d5a58 != DAT_0058f1f4) {
LAB_0046ebd0:
      iVar1 = DAT_004d5a58;
      DAT_0058f208 = 0;
      uVar3 = FUN_0046c9cc(s_WaitSync_004d5c96);
      FUN_004779c0(DAT_0058f1f4,0x33,DAT_0059f154,uVar3 & 0xffff,(int)uVar3 >> 0x10 & 0xffff,0,0);
      FUN_00477e4c();
      DAT_004d59a4 = DAT_004d59a4 | 1;
LAB_0046ed08:
      do {
        if ((((DAT_004d5a50 == 0) || (DAT_0058f208 != 0)) || (DAT_0058f1ec != 0)) ||
           (DAT_004d8264 != 0)) {
          DAT_004d59a4 = DAT_004d59a4 & 0xfffffffe;
          DAT_0058f208 = 0;
          goto LAB_0046ed42;
        }
        if (iVar1 != DAT_004d5a58) goto code_r0x0046ec2b;
        FUN_00477f9c();
        FUN_0046e980();
        if (DAT_004d59b4 == 0x24) {
          iVar4 = FUN_00427e6c();
        }
        else {
          iVar4 = 0;
        }
        if (iVar4 == 4) {
          if ((DAT_0058f1fc != 0) && (DAT_0059f154 == 0)) {
            FUN_00475344();
            DAT_0058f1ec = 1;
            PTR_DAT_004d5988[1] = 0;
            FUN_0046e9d0();
            return;
          }
          if ((code *)PTR_FUN_004d02b8 == FUN_00457ac0) {
            iVar4 = FUN_00423d84();
            if ((iVar4 == 2) || ((iVar4 == 1 && (iVar4 = ChCht(0,1,0), iVar4 == 0))))
            goto LAB_0046ed08;
          }
          else {
            iVar4 = FUN_0042836c(PTR_s_Exit_Game_00509894,
                                 PTR_s_Are_you_sure_you_want_to_exit_De_00509898,0x18,0,4);
            if (iVar4 == 2) goto LAB_0046ed08;
          }
          FUN_004780e4(DAT_0058f1f4,1);
          DAT_0058f1ec = 1;
          PTR_DAT_004d5988[1] = 0;
          FUN_0046e9d0();
        }
      } while( true );
    }
LAB_0046ea48:
    DAT_004d59a4 = DAT_004d59a4 | 1;
    DAT_0059f0f4 = FUN_0046c9cc(s_WaitSync_004d5c96);
    DAT_0059f0f8 = 0;
LAB_0046eb50:
    do {
      if ((((DAT_004d5a50 == 0) || (DAT_0058f200 + -1 <= DAT_0058f208)) || (DAT_0058f1ec != 0)) ||
         (DAT_004d8264 != 0)) goto LAB_0046eb81;
      FUN_00477f9c();
      FUN_0046e980();
      if (DAT_004d59b4 == 0x24) {
        iVar1 = FUN_00427e6c();
      }
      else {
        iVar1 = 0;
      }
    } while (iVar1 != 4);
    if ((DAT_0058f1fc != 0) && (DAT_0059f154 == 0)) {
      FUN_00475344();
      DAT_0058f1ec = 1;
      PTR_DAT_004d5988[1] = 0;
      FUN_0046e9d0();
      return;
    }
    if ((code *)PTR_FUN_004d02b8 == FUN_00457ac0) {
      iVar1 = FUN_00423d84();
      if ((iVar1 == 2) || ((iVar1 == 1 && (iVar1 = ChCht(0,1,0), iVar1 == 0)))) goto LAB_0046eb50;
    }
    else {
      iVar1 = FUN_0042836c(PTR_s_Exit_Game_00509894,PTR_s_Are_you_sure_you_want_to_exit_De_00509898,
                           0x18,0,4);
      if (iVar1 == 2) goto LAB_0046eb50;
    }
    FUN_004780e4(DAT_0058f1f4,1);
    DAT_0058f1ec = 1;
    PTR_DAT_004d5988[1] = 0;
    if ((DAT_0058f1fc != 0) && (DAT_0059f154 == 0)) {
      FUN_00475344();
    }
    FUN_0046e9d0();
    goto LAB_0046eb50;
  }
LAB_0046ed42:
  if (DAT_004d8264 != 0) {
    DAT_0058f1ec = 1;
  }
  FUN_0046e9d0();
  return;
code_r0x0046ec2b:
  if (DAT_004d5a58 == DAT_0058f1f4) goto LAB_0046ea48;
  goto LAB_0046ebd0;
LAB_0046eb81:
  DAT_004d59a4 = DAT_004d59a4 & 0xfffffffe;
  DAT_0058f208 = 0;
  if (DAT_0059f0f8 != 0) {
    uVar2 = FUN_0046c9cc(s_Reseed_004d5c9f);
    FUN_00477394(uVar2);
  }
  FUN_004779c0(DAT_0058f1f4,0x34,DAT_0059f154,0,0,0,0);
  FUN_00477e4c();
  goto LAB_0046ed42;
}

