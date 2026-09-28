// FUN_0046fae4 @ 0046fae4 size=394 sig=undefined FUN_0046fae4() cc=unknown
// callers: WinMain
// callees: FUN_0049539b,FUN_004a6b00
// strings: \"-debug\"|\"-nosound\"|\"Unknown parameter %s\\n\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0046fae4(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar3 = 1;
  puVar2 = (undefined4 *)(param_2 + 4);
  if (1 < param_1) {
    do {
      iVar1 = FUN_004a6b00(*puVar2,&DAT_004d5d29);
      if (iVar1 == 0) {
        DAT_004d1f58 = 0;
      }
      else {
        iVar1 = FUN_004a6b00(*puVar2,&DAT_004d5d2c);
        if (iVar1 == 0) {
          iVar3 = iVar3 + 1;
          puVar2 = puVar2 + 1;
          DAT_004d5a80 = 0;
        }
        else {
          iVar1 = FUN_004a6b00(*puVar2,&DAT_004d5d2f);
          if (iVar1 == 0) {
            iVar3 = iVar3 + 1;
            puVar2 = puVar2 + 1;
            DAT_004d5a8c = 0x10;
          }
          else {
            iVar1 = FUN_004a6b00(*puVar2,&DAT_004d5d33);
            if (iVar1 == 0) {
              iVar3 = iVar3 + 1;
              puVar2 = puVar2 + 1;
              DAT_004d5a8c = 8;
            }
            else {
              iVar1 = FUN_004a6b00(*puVar2,s__debug_004d5d36);
              if (iVar1 == 0) {
                iVar3 = iVar3 + 1;
                puVar2 = puVar2 + 1;
                DAT_0051c3a0 = 1;
              }
              else {
                iVar1 = FUN_004a6b00(*puVar2,&DAT_004d5d3d);
                if (iVar1 == 0) {
                  iVar3 = iVar3 + 1;
                  puVar2 = puVar2 + 1;
                  _DAT_004d5a84 = 1;
                }
                else {
                  iVar1 = FUN_004a6b00(*puVar2,&DAT_004d5d41);
                  if (iVar1 == 0) {
                    iVar3 = iVar3 + 1;
                    puVar2 = puVar2 + 1;
                    DAT_004d599c = 0;
                  }
                  else {
                    iVar1 = FUN_004a6b00(*puVar2,&DAT_004d5d45);
                    if (iVar1 == 0) {
                      iVar3 = iVar3 + 1;
                      puVar2 = puVar2 + 1;
                      DAT_004d59a8 = 1;
                    }
                    else {
                      iVar1 = FUN_004a6b00(*puVar2,s__nosound_004d5d49);
                      if (iVar1 != 0) {
                        FUN_0049539b(s_Unknown_parameter__s_004d5d52,
                                     *(undefined4 *)(param_2 + iVar3 * 4));
                        return 0;
                      }
                      iVar3 = iVar3 + 1;
                      puVar2 = puVar2 + 1;
                      DAT_004d5b40 = 1;
                    }
                  }
                }
              }
            }
          }
        }
      }
    } while (iVar3 < param_1);
  }
  return 1;
}

