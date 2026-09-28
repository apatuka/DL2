// FUN_0045ca3c @ 0045ca3c size=537 sig=undefined FUN_0045ca3c() cc=unknown
// callers: 
// callees: FUN_0043edd8,FUN_00428824,FUN_00482f94,FUN_00481a5c,FUN_0042836c,FUN_004726cc,FUN_00437718,memset,FUN_004727dc,FUN_00459ea8,FUN_00476668,FUN_00449cc4,FUN_00449dec
// strings: \"You can only ship resources to territories that another colony owns.\"|\"Oolan's Advice\"|\"Sorry, you can't transfer materials to a blockaded territory without Transporter technology.\"

undefined4 FUN_0045ca3c(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int iVar4;
  undefined *puVar5;
  int local_40 [11];
  int local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar1 = FUN_00449cc4(param_1,param_2,&local_8,&local_c);
  if ((iVar1 == 0) || (iVar1 == 1)) {
    if (iVar1 == 0) {
      if (DAT_004d5ad0 == 0) {
        FUN_00459ea8(local_8,local_c,&local_10,&local_14);
      }
      else {
        FUN_0043edd8(local_8,local_c,&local_10,&local_14);
      }
    }
    else {
      FUN_00481a5c(local_8,local_c,&local_10,&local_14);
    }
    if ((((-1 < local_10) && (local_10 < DAT_004d5b1a)) && (-1 < local_14)) &&
       (local_14 < DAT_004d5b1b)) {
      iVar4 = DAT_00583d78 * 0xadc;
      puVar5 = &DAT_005a43d0 + iVar4;
      iVar1 = (short)(&DAT_005a0552)[local_14 * 200 + local_10 * 5] * 0xadc;
      puVar3 = &DAT_005a43d0 + iVar1;
      memset(local_40,0,0x2c);
      if (puVar3 != puVar5) {
        if (((&DAT_005a43f0)[iVar1] == -1) ||
           ((char)(&DAT_005a4436)[(char)(&DAT_005a43f0)[iVar4] + iVar1] < '\x01')) {
          FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_can_only_ship_resources_to_t_005096d8
                       ,4,0,0xe);
        }
        else if ((&DAT_005a43f0)[iVar4] == (&DAT_005a43f0)[iVar1]) {
          iVar1 = FUN_004726cc(puVar5,puVar3,DAT_0058f1f4);
          if ((iVar1 < 3) || ((1 << ((byte)DAT_0058f1f4 & 0x1f) & (int)DAT_004fc4a8) != 0)) {
            uVar2 = FUN_004727dc(puVar5,puVar3);
            iVar1 = FUN_00428824(DAT_00583d74,
                                 *(undefined4 *)(&DAT_005a440a + DAT_00583d74 * 4 + iVar4),uVar2);
            local_40[DAT_00583d74] = iVar1;
            if (iVar1 == -1) {
              local_40[DAT_00583d74] = *(int *)(&DAT_005a440a + DAT_00583d74 * 4 + iVar4);
            }
            FUN_00476668(puVar5,puVar3,local_40);
          }
          else {
            FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,
                         PTR_s_Sorry__you_can_t_transfer_materi_005097c0,4,0,0xe);
          }
        }
        else if (((&DAT_005a43f0)[iVar1] != -1) &&
                ('\0' < (char)(&DAT_005a4436)[(char)(&DAT_005a43f0)[iVar4] + iVar1])) {
          FUN_00437718(puVar5,puVar3,DAT_00583d74);
        }
        FUN_00482f94(PTR_DAT_004d5988);
        FUN_00449dec();
      }
    }
  }
  return 1;
}

