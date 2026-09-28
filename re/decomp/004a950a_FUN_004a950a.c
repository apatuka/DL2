// FUN_004a950a @ 004a950a size=73 sig=undefined FUN_004a950a() cc=unknown
// callers: 
// callees: FUN_004a6918

bool FUN_004a950a(int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  
  if (*(int *)(param_1 + 4) == 0) {
    bVar2 = false;
  }
  else if (*(int *)(param_2 + 4) == 0) {
    bVar2 = true;
  }
  else {
    iVar1 = FUN_004a6918((uint)*(ushort *)(*(int *)(param_1 + 4) + 6) + *(int *)(param_1 + 4),
                         (uint)*(ushort *)(*(int *)(param_2 + 4) + 6) + *(int *)(param_2 + 4));
    bVar2 = iVar1 < 0;
  }
  return bVar2;
}

