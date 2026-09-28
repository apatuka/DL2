// FUN_0045e554 @ 0045e554 size=243 sig=undefined FUN_0045e554() cc=unknown
// callers: FUN_0043baf4
// callees: FUN_00474ff0,FUN_00477f9c,FUN_0043acd4,FUN_0045ae00,FUN_00449718,FUN_00427e80,FUN_00427e6c,FUN_00427ee8,FUN_0042836c,FUN_0045f108,FUN_00476ffc,FUN_00427f04
// strings: \"Your turn has been logged. (You probably push elevator buttons a million times too, don't you)?\"|\"Relax, colony leader.\"|\"Your opponents are still not done with their turns.\\n\\nWhile you wait you can keep working on your colony.  This turn is not over until everyone either presses their End Turn button or the timer runs out.\"|\"Continue Turn\"

void FUN_0045e554(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((DAT_004d59b4 == 0) || (DAT_004d59b4 == 1)) {
    if ((&DAT_0059f168)[DAT_0058f1f4 * 0x2d8] != '\0') {
      FUN_0042836c(PTR_s_Relax__colony_leader__005096f4,
                   PTR_s_Your_turn_has_been_logged___You_p_005096f8,4,0,4);
    }
    FUN_00476ffc(DAT_0058f1f4);
    iVar1 = FUN_0045f108();
    iVar2 = FUN_0045ae00();
    if ((iVar1 < iVar2) && (DAT_004d59b4 != 0x24)) {
      FUN_00427e80(1,PTR_s_Continue_Turn_005092f0,PTR_s_Your_opponents_are_still_not_don_005092f4,0,
                   2);
      FUN_00427f04();
      iVar1 = 0;
      while (DAT_0058f1ec == 0) {
        iVar2 = FUN_0045f108();
        iVar3 = FUN_0045ae00();
        if (iVar3 <= iVar2) break;
        FUN_00477f9c();
        iVar2 = FUN_00449718();
        if (iVar1 != iVar2) {
          FUN_0043acd4();
          iVar1 = FUN_00449718();
        }
        iVar2 = FUN_00427e6c();
        if (iVar2 == 4) {
          iVar2 = FUN_00474ff0(DAT_0058f1f4);
          if (iVar2 != 0) {
            FUN_00427ee8();
            return;
          }
        }
      }
      FUN_00427ee8();
    }
  }
  return;
}

