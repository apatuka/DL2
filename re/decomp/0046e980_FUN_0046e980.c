// FUN_0046e980 @ 0046e980 size=79 sig=undefined FUN_0046e980() cc=unknown
// callers: WaitSync
// callees: FUN_00427f04,FUN_00427eb4,timeGetTime
// strings: \"All players are now being synchronized.  This may take some time.  Please wait...\"|\"Re-synching Machines\"

void FUN_0046e980(void)

{
  DWORD DVar1;
  
  if ((DAT_004d5a78 == 0) && (DAT_004d5c24 == 0)) {
    DVar1 = timeGetTime();
    if (0x2ee < (int)(DVar1 - DAT_006520a4)) {
      FUN_00427eb4(1,PTR_s_Re_synching_Machines_00509844,
                   PTR_s_All_players_are_now_being_synchr_00509848,0,2);
      FUN_00427f04();
      DAT_004d5c24 = 1;
    }
  }
  return;
}

