// FUN_0043cc5c @ 0043cc5c size=314 sig=undefined FUN_0043cc5c() cc=unknown
// callers: CheckTechTree
// callees: FUN_00483f20,FUN_004838d4,FUN_004838fc,FUN_0048394c,FUN_00483b84,FUN_00483a30,FUN_0043c540,FUN_0042836c,FUN_00450150,FUN_00483d58
// strings: \"Due to a mishap with your colony supply ship, Metallurgy technology can not be researched. It must be obtained through alternate means.\"|\"Oolan's Advice\"

void FUN_0043cc5c(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = &DAT_004fbbf6;
  iVar2 = 1;
  do {
    if (param_1 == *piVar3) {
      if (DAT_004d5aa0 == '\0') {
        iVar1 = FUN_004838d4(DAT_00559da8,iVar2);
        if (iVar1 == 0) {
          iVar1 = FUN_00483a30(DAT_0058f1f4,DAT_00559da8,iVar2);
          if (iVar1 == 0) {
            iVar1 = FUN_00450150((int)(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8],iVar2);
            if (iVar1 == 0) {
              FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,
                           PTR_s_Due_to_a_mishap_with_your_colony_00509db8,4,0,0x14);
            }
          }
          else {
            FUN_004838fc(&DAT_00559da8,iVar2);
          }
        }
        else {
          FUN_0048394c(&DAT_00559da8,&DAT_004fbbac + iVar2 * 0x19);
          FUN_00483b84(DAT_0058f1f4,&DAT_00559da8);
        }
      }
      else if ((1 << ((byte)DAT_0058f1f4 & 0x1f) & (int)(short)piVar3[-6]) == 0) {
        FUN_00483d58(DAT_0058f1f4,&DAT_004fbbac + iVar2 * 0x19);
      }
      else {
        FUN_00483f20(DAT_0058f1f4,&DAT_004fbbac + iVar2 * 0x19);
      }
    }
    iVar2 = iVar2 + 1;
    piVar3 = (int *)((int)piVar3 + 0x32);
  } while (iVar2 < 0x30);
  FUN_0043c540();
  return;
}

