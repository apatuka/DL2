// FUN_004a1715 @ 004a1715 size=130 sig=undefined FUN_004a1715() cc=unknown
// callers: FUN_004a3533,FUN_004a19b4,FUN_004a43da
// callees: FUN_00490ab3,FUN_004a16fc,FUN_00495162
// strings: \"Unable to SMenu item font, %c%c%c%c\\r\\n\"

undefined4 FUN_004a1715(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  FUN_004a16fc(param_1);
  if ((param_2 == 0) || (param_2 == -1)) {
    uVar1 = 1;
  }
  else {
    iVar2 = FUN_00490ab3(0,0x544e4f46,param_2,0,0x80000000);
    *(int *)(param_1 + 0x3c) = iVar2;
    if (iVar2 == 0) {
      FUN_00495162(s_Unable_to_SMenu_item_font___c_c__0051e3de,(int)(char)param_2,
                   (int)(char)((uint)param_2 >> 8),(int)(char)((uint)param_2 >> 0x10),
                   (int)(char)((uint)param_2 >> 0x18));
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}

