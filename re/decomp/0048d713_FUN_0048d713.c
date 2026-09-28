// FUN_0048d713 @ 0048d713 size=45 sig=undefined FUN_0048d713() cc=unknown
// callers: FUN_00491898,FUN_0048d76a
// callees: 

void FUN_0048d713(int param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  if ((param_1 != 0) && (param_2 == 0)) {
    for (iVar2 = 0; iVar2 < *(short *)(param_1 + 2); iVar2 = iVar2 + 1) {
      uVar1 = (undefined1)iVar2;
      *(undefined1 *)(param_1 + 8 + iVar2 * 4) = uVar1;
      *(undefined1 *)(param_1 + 9 + iVar2 * 4) = uVar1;
      *(undefined1 *)(param_1 + 10 + iVar2 * 4) = uVar1;
    }
  }
  return;
}

