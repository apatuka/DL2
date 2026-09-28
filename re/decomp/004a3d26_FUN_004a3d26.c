// FUN_004a3d26 @ 004a3d26 size=192 sig=undefined FUN_004a3d26() cc=unknown
// callers: FUN_004a5c60,FUN_004a3de6
// callees: FUN_004a3533,FUN_00495544,FUN_004a5d60,FUN_004a3b3c,FUN_00495162,FUN_004a39f7,FUN_00491159
// strings: \"Created SMenu %c%c%c%c, chain count = %d\\r\\n\"

int FUN_004a3d26(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_004a3b3c(0,0,0,0,0,0,0);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    if ((DAT_0051e388 & 1) != 0) {
      uVar2 = FUN_00495544(DAT_0051e384);
      FUN_00495162(s_Created_SMenu__c_c_c_c__chain_co_0051e47d,(int)(char)param_3,
                   (int)(char)((uint)param_3 >> 8),(int)(char)((uint)param_3 >> 0x10),
                   (int)(char)((uint)param_3 >> 0x18),uVar2);
    }
    if (param_3 != -1) {
      uVar2 = FUN_00491159(param_2,param_3);
      *(undefined4 *)(iVar1 + 0x54) = uVar2;
    }
    FUN_004a39f7(iVar1,param_1);
    FUN_004a3533(iVar1,0,param_1);
    if ((*(int *)(iVar1 + 0x28) == 0) && ((*(byte *)(iVar1 + 0x1c) & 4) != 0)) {
      uVar2 = FUN_004a5d60(FUN_004a24f1,iVar1,0);
      *(undefined4 *)(iVar1 + 0x28) = uVar2;
    }
  }
  return iVar1;
}

