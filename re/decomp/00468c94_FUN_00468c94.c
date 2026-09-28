// FUN_00468c94 @ 00468c94 size=165 sig=undefined FUN_00468c94() cc=unknown
// callers: 
// callees: FUN_00458434,FUN_0042836c,DestroyWindow,FUN_0046716c
// strings: \"Could not connect to the game.  Verify your network, serial, or modem settings and try again.\"|\"Network Error\"

undefined4 FUN_00468c94(void)

{
  int iVar1;
  
  if (DAT_004d5130 == -1) {
    return 0x38;
  }
  iVar1 = FUN_00458434(DAT_004d5130);
  if (iVar1 == 0) {
    FUN_0042836c(PTR_s_Network_Error_00509c94,PTR_s_Could_not_connect_to_the_game__V_00509c98,0x28a2
                 ,0,0);
    if (DAT_004d59a8 != '\0') {
      DAT_004d59a8 = 0;
      return 0x35;
    }
    return 0x38;
  }
  DestroyWindow(DAT_0058f1dc);
  DAT_0058f1dc = (HWND)0x0;
  FUN_0046716c();
  if ((DAT_0058f1f0 == 0) && (DAT_004d8264 == 0)) {
    return 0x43;
  }
  if (DAT_004d59a8 != '\0') {
    DAT_004d59a8 = 0;
    return 0x35;
  }
  return 0x38;
}

