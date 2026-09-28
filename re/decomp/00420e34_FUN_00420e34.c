// FUN_00420e34 @ 00420e34 size=362 sig=undefined FUN_00420e34() cc=unknown
// callers: CheckColonyAssistant
// callees: FUN_0041ff24,FUN_00420d34,FUN_00438aa4,FUN_00482f94,FUN_00420d2c,FUN_0041ff98,FUN_0042836c,FUN_00420cb8,FUN_0044ddf4,FUN_0041ffd4,FUN_00475f80,FUN_00471d34
// strings: \"You may not queue units in a building which is either shut down or under construction.\"|\"Oolan's Advice\"

void FUN_00420e34(void)

{
  int iVar1;
  int iVar2;
  char local_44 [4];
  int local_40;
  undefined1 local_3c [52];
  
  local_44[0] = '\x01';
  do {
    iVar1 = FUN_00438aa4(*(undefined4 *)(&DAT_0056421c + DAT_0053b8ac * 0x18),local_44,&local_40);
    if (local_40 == 8) {
      FUN_00420d2c();
      local_44[0] = '\0';
      DAT_004d59a4 = 0;
    }
    else if (local_40 == 0xb) {
      FUN_00420d34();
      FUN_0041ff98();
      FUN_0041ffd4();
      FUN_00482f94(PTR_DAT_004d5988);
      FUN_0041ff24();
    }
    else if (local_40 == 10) {
      FUN_00420cb8();
      FUN_0041ff98();
      FUN_0041ffd4();
      FUN_00482f94(PTR_DAT_004d5988);
      FUN_0041ff24();
    }
    else if (((local_40 == 3) && (0 < iVar1)) && (iVar1 < 0x27)) {
      iVar2 = FUN_00475f80(DAT_0053b8b8,PTR_DAT_004d5988,iVar1);
      if (iVar2 == 0) {
        FUN_0041ff98();
        FUN_0041ffd4();
        FUN_00482f94(PTR_DAT_004d5988);
        FUN_0041ff24();
      }
      else {
        FUN_0044ddf4(&DAT_0059f160 + DAT_0058f1f4 * 0x2d8,iVar1,local_3c);
        FUN_00471d34((&PTR_s_No_Unit_004faf7c)[iVar1 * 9],iVar2,local_3c);
      }
    }
    else if (local_40 != 4) {
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_may_not_queue_units_in_a_bui_00509224,4,0
                   ,0xd);
      local_44[0] = '\0';
    }
  } while (local_44[0] != '\0');
  return;
}

