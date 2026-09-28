// FUN_00448284 @ 00448284 size=72 sig=undefined FUN_00448284() cc=unknown
// callers: FUN_00447c2c,FUN_00447da4,BirthCombatSprites,LoadCombatSprites,FUN_00447be4,SetRetreat,FUN_0043d990
// callees: 

int FUN_00448284(int param_1)

{
  int iVar1;
  
  if ((*(char *)(param_1 + 9) == '\x01') &&
     ((&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24] == '\x01')) {
    iVar1 = (int)*(short *)(&DAT_00559fce +
                           (char)(&DAT_0059f162)[(uint)*(byte *)(param_1 + 0x1e) * 0x2d8] * 2);
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

