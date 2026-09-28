// FUN_0041d414 @ 0041d414 size=620 sig=undefined FUN_0041d414() cc=unknown
// callers: CheckBuilding
// callees: FUN_004761b0,FUN_0041c378,FUN_004762a8,FUN_00438aa4,FUN_00482f94,FUN_0041d2bc,FUN_0042836c,FUN_0044ddf4,FUN_00471d34,FUN_0041d680,FUN_0041c418,FUN_0041d710,FUN_0041c3dc,FUN_0041d2b4,FUN_00475f80
// strings: \"You may not queue units in a building which is either shut down or under construction.\"|\"Oolan's Advice\"

void FUN_0041d414(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  char local_58 [4];
  int local_54;
  undefined4 local_50 [5];
  undefined1 local_3c [52];
  
  if (((*(short *)(DAT_0053b850 + 0x14) == 0) && ((*(byte *)(DAT_0053b850 + 2) & 2) != 0)) &&
     (DAT_0053b33c != 0)) {
    local_58[0] = '\x01';
    local_54 = 0;
    iVar1 = FUN_00438aa4(DAT_0053b850,local_58,&local_54);
    do {
      if (local_54 == 8) {
        FUN_0041d2b4();
        local_58[0] = '\0';
        DAT_004d59a4 = 0;
      }
      else if (local_54 == 0xb) {
        FUN_0041d710();
        if (*(char *)(DAT_0053b850 + 0x30) != '\0') {
          FUN_0041c3dc();
          FUN_0041c418();
        }
        FUN_00482f94(PTR_DAT_004d5988);
        FUN_0041c378();
        iVar1 = FUN_00438aa4(DAT_0053b850,local_58,&local_54);
      }
      else if (local_54 == 10) {
        FUN_0041d680();
        if (*(char *)(DAT_0053b850 + 0x30) != '\0') {
          FUN_0041c3dc();
          FUN_0041c418();
        }
        FUN_00482f94(PTR_DAT_004d5988);
        FUN_0041c378();
        iVar1 = FUN_00438aa4(DAT_0053b850,local_58,&local_54);
      }
      else if (local_54 == 9) {
        FUN_0041d2bc();
        local_58[0] = '\0';
      }
      else if ((local_54 == 3) && (iVar1 < 0x27)) {
        if (iVar1 < 1) {
          local_58[0] = '\0';
        }
        else {
          iVar2 = FUN_00475f80(DAT_0053b84c,PTR_DAT_004d5988,iVar1);
          if (iVar2 == 0) {
            if (*(char *)(DAT_0053b850 + 0x30) != '\0') {
              FUN_0041c3dc();
              FUN_0041c418();
            }
            FUN_00482f94(PTR_DAT_004d5988);
            FUN_0041c378();
          }
          else {
            FUN_0044ddf4(&DAT_0059f160 + DAT_0058f1f4 * 0x2d8,iVar1,local_3c);
            FUN_00471d34((&PTR_s_No_Unit_004faf7c)[iVar1 * 9],iVar2,local_3c);
            local_58[0] = '\0';
          }
          iVar1 = FUN_00438aa4(DAT_0053b850,local_58,&local_54);
        }
      }
      else if (local_54 != 4) {
        FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_may_not_queue_units_in_a_bui_00509224,4
                     ,0,0xd);
        local_58[0] = '\0';
      }
    } while (local_58[0] != '\0');
    iVar1 = 0;
    puVar3 = (undefined4 *)(DAT_0053b850 + 0x18);
    puVar4 = local_50;
    do {
      *puVar4 = *puVar3;
      iVar1 = iVar1 + 1;
      puVar4 = puVar4 + 1;
      puVar3 = puVar3 + 1;
    } while (iVar1 < 5);
    FUN_004761b0(DAT_0053b84c,DAT_0053b850,local_50,
                 CONCAT31((int3)((uint)puVar4 >> 8),*(undefined1 *)(DAT_0053b84c + 0x9ae)));
    FUN_004762a8(DAT_0053b84c,DAT_0053b850);
  }
  return;
}

