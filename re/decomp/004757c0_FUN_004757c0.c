// FUN_004757c0 @ 004757c0 size=87 sig=undefined FUN_004757c0() cc=unknown
// callers: FUN_00401ac0
// callees: FUN_00446084,FUN_004779c0,FUN_00474d90

void FUN_004757c0(undefined2 *param_1,int param_2,int param_3)

{
  int iVar1;
  
  if (DAT_0058f1fc == 0) {
    FUN_00446084(param_1,param_2,param_3);
  }
  else {
    if (param_3 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = (int)*(short *)(param_3 + 0x1a);
    }
    FUN_004779c0((int)*(char *)(param_1 + 4),0x13,*param_1,(int)*(short *)(param_2 + 0x1a),iVar1,0,0
                );
    FUN_00474d90(0x13,(int)*(char *)(param_1 + 4));
  }
  return;
}

