// FUN_004482cc @ 004482cc size=72 sig=undefined FUN_004482cc() cc=unknown
// callers: FUN_00447c2c,FUN_0045539c,FUN_004556b0,FUN_00447da4,FUN_00454928,BirthCombatSprites,FUN_00447f44,LoadCombatSprites,FUN_00447c08,FUN_004480a8,FUN_00448118,FUN_00453bf4,FUN_00455c88,DestroyAnim
// callees: 

int FUN_004482cc(int param_1)

{
  int iVar1;
  
  if ((*(char *)(param_1 + 9) == '\x02') &&
     ((&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24] == '\x01')) {
    iVar1 = (int)*(short *)(&DAT_00559fdc +
                           (char)(&DAT_0059f162)[(uint)*(byte *)(param_1 + 0x1e) * 0x2d8] * 2);
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

