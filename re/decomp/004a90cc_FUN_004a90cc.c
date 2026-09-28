// FUN_004a90cc @ 004a90cc size=55 sig=undefined FUN_004a90cc() cc=unknown
// callers: FUN_004a76d2,FUN_004a9553,FUN_004a78a4
// callees: __assertfail
// strings: \"<notype>\"|\"XXTYPE.CPP\"|\"id->tpName\"

char * FUN_004a90cc(int param_1)

{
  if (param_1 == 0) {
    return s_<notype>_0051f9c4;
  }
  if (*(short *)(param_1 + 6) == 0) {
    __assertfail(s_id_>tpName_0051f9cd,s_XXTYPE_CPP_0051f9d8,0x21);
  }
  return (char *)((uint)*(ushort *)(param_1 + 6) + param_1);
}

