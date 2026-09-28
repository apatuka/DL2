// FUN_004976dc @ 004976dc size=168 sig=undefined FUN_004976dc() cc=unknown
// callers: FUN_004977e9,FUN_004978f7,FUN_00497784,FUN_004977bb,FUN_00497956
// callees: strlen,FUN_004974ef,FUN_004971d4,FUN_004a6b00,FUN_0049716d

int FUN_004976dc(undefined4 param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  char local_104 [256];
  
  bVar1 = false;
  iVar2 = FUN_004971d4(param_1);
LAB_0049776d:
  do {
    while( true ) {
      if (((bVar1) || (iVar2 == 0)) || (param_2 == 0)) {
        return iVar2;
      }
      FUN_004974ef(iVar2,local_104);
      iVar3 = FUN_004a6b00(param_2,&DAT_0051e15c);
      if (iVar3 == 0) break;
      iVar3 = FUN_004a6b00(local_104,param_2);
      if (iVar3 == 0) {
        bVar1 = true;
      }
      else {
        iVar2 = FUN_0049716d(iVar2);
      }
    }
    if (local_104[0] == '[') {
      iVar3 = strlen(local_104);
      if (local_104[iVar3 + -1] == ']') {
        bVar1 = true;
        goto LAB_0049776d;
      }
    }
    iVar2 = FUN_0049716d(iVar2);
  } while( true );
}

