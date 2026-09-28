// FUN_00489a43 @ 00489a43 size=39 sig=undefined FUN_00489a43() cc=unknown
// callers: 
// callees: 

undefined4 FUN_00489a43(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = (**(code **)(param_1 + 0x48))(param_1);
  if ((iVar1 == 0) || (param_1 == 0)) {
    uVar2 = 0;
  }
  else {
    (**(code **)(param_1 + 0x58))(param_1,1);
    uVar2 = 1;
  }
  return uVar2;
}

