// FUN_0049551a @ 0049551a size=42 sig=undefined FUN_0049551a() cc=unknown
// callers: FUN_0049eb44,FUN_004a322d,FUN_0049f83e,FUN_004a3329,FUN_004a2cb5,FUN_004a4025,FUN_004a0f18,FUN_004a2078
// callees: 

int FUN_0049551a(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  for (iVar1 = *param_1; (iVar1 != 0 && (param_2 != iVar1)); iVar1 = *(int *)(iVar1 + 4)) {
    iVar2 = iVar2 + 1;
  }
  if (iVar1 == 0) {
    iVar2 = -1;
  }
  return iVar2;
}

