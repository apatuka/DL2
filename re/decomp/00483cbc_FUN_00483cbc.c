// FUN_00483cbc @ 00483cbc size=155 sig=undefined FUN_00483cbc() cc=unknown
// callers: FUN_0040a3c0,@CheatTechDialog$qqspvuiuil,FUN_00422638,FUN_0045e4f4,FUN_0043cbf8,FUN_0047323c,FUN_0046f804
// callees: FUN_00457ac0,FUN_00450150

int FUN_00483cbc(byte *param_1)

{
  uint uVar1;
  int iVar2;
  short *psVar3;
  int iVar4;
  
  uVar1 = 1 << (*param_1 & 0x1f);
  iVar4 = 1;
  psVar3 = &DAT_004fbbe0;
  do {
    if (((int)*psVar3 & uVar1) != 0) {
      if ('\x02' < (char)param_1[1]) {
        return iVar4;
      }
      iVar2 = (*(code *)PTR_FUN_004d02b8)(3);
      if (psVar3[0xf] < iVar2) {
        return iVar4;
      }
    }
    iVar4 = iVar4 + 1;
    psVar3 = psVar3 + 0x19;
    if (0x2f < iVar4) {
      iVar4 = (*(code *)PTR_FUN_004d02b8)(3);
      if (((iVar4 == 10) && (((int)DAT_004fc4da & uVar1) == 0)) &&
         (iVar4 = FUN_00450150((int)(char)param_1[2],0x2f), iVar4 != 0)) {
        iVar4 = 0x2f;
      }
      else {
        iVar4 = 0;
      }
      return iVar4;
    }
  } while( true );
}

