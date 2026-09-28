// FUN_00496330 @ 00496330 size=38 sig=undefined FUN_00496330() cc=unknown
// callers: 
// callees: 

void FUN_00496330(int param_1)

{
  if ((DAT_0051e090 & 1) != 0) {
    if (param_1 == 2) {
      DAT_0051e090 = DAT_0051e090 | 2;
    }
    else {
      DAT_0051e090 = DAT_0051e090 & 0xfffffffd;
    }
  }
  return;
}

