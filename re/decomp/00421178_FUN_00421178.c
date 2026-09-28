// FUN_00421178 @ 00421178 size=454 sig=undefined FUN_00421178() cc=unknown
// callers: 
// callees: FUN_00449cc4,FUN_0041ff24,FUN_0045c704,GetKeyState,FUN_0041ff18,FUN_0042836c,FUN_0049eb44,FUN_00420734,FUN_0042111c,FUN_004483d0,FUN_00448844,FUN_00459068,FUN_0041b908,FUN_00421154
// strings: \"You may only drag colonists to Task Buttons, the Labor Pool, the Housing Pool, and the Satellite Map. Try again.\"|\"Oolan's Advice\"

undefined4 FUN_00421178(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  ushort uVar4;
  int iVar5;
  uint *puVar6;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  iVar5 = 0;
  puVar6 = &DAT_004b7a20;
  do {
    uVar1 = *puVar6;
    if (*(int *)(&DAT_00564220 + uVar1 * 0x18) != 0) {
      if ((int)uVar1 < 0xc) {
        if (((uVar1 != 0xb) && (1 < uVar1)) && (uVar1 - 2 < 9)) {
LAB_004211bf:
          FUN_0049eb44(DAT_004b7a14,iVar5 * 2 + 0xe,1,0x42,0,(char)PTR_DAT_004d5988[2] + 0x3ea);
        }
      }
      else {
        if (uVar1 - 0xc < 10) goto LAB_004211bf;
        if (uVar1 - 0x17 < 5) {
          FUN_0049eb44(DAT_004b7a14,iVar5 * 2 + 0xe,1,0x42,0,(char)PTR_DAT_004d5988[2] + 0x3f1);
        }
      }
    }
    iVar5 = iVar5 + 1;
    puVar6 = puVar6 + 1;
    if (0x17 < iVar5) {
      uVar4 = GetKeyState(0x12);
      iVar5 = FUN_00449cc4(param_1,param_2,local_8,local_c);
      if ((iVar5 < 0xc) && (7 < iVar5)) {
        iVar5 = FUN_00421154(DAT_0053b8ac);
        iVar5 = iVar5 + 0x10;
      }
      FUN_00459068();
      if (iVar5 != DAT_0053b8bc) {
        uVar2 = *(undefined4 *)(&DAT_004b79e0 + iVar5 * 4);
        iVar3 = *(int *)(&DAT_004b79e0 + DAT_0053b8bc * 4);
        if (iVar5 == 1) {
          DAT_00583d70 = (int)*(short *)(DAT_0053b8b8 + 0x1a);
          FUN_0045c704(param_1,param_2);
          FUN_004483d0(DAT_0053b8b8);
          FUN_0041b908();
          FUN_00420734();
          FUN_0041ff24();
          FUN_0041ff18();
        }
        else if (iVar5 - 0x10U < 0x18) {
          if ((uVar4 & 0x8000) == 0) {
            iVar5 = FUN_0042111c();
          }
          else {
            iVar5 = (&DAT_00564224)[iVar3 * 6];
          }
          if (iVar5 != 0) {
            FUN_00448844(&DAT_005a43d0 + DAT_004c5b50 * 0xadc,iVar3,uVar2,iVar5);
          }
          FUN_0041b908();
          FUN_00420734();
          FUN_0041ff24();
          FUN_0041ff18();
        }
        else {
          FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_may_only_drag_colonists_to_T_00509788
                       ,4,0,0xb);
        }
      }
      return 1;
    }
  } while( true );
}

