// GlobalLock @ 004b3ef1 size=6 sig=LPVOID GlobalLock(HGLOBAL hMem) cc=__stdcall
// callers: FUN_004a52db,FUN_004a54e5,FUN_0048d8a1,FUN_00491200,FUN_0049b6a0,FUN_00498bba,FUN_00498a30,FUN_0048fc05,FUN_004a3de6,FUN_0048d82a,FUN_0048d76a,FUN_00498a5c,FUN_00411808,FUN_004995ab,FUN_00498196,FUN_00499748,FUN_00498a7f,FUN_004989ed,FUN_0048fee9,FUN_00498aab,FUN_0049859f,FUN_004a5655,FUN_004a5699,FUN_004a08c5,FUN_0049028e,FUN_0049979f,FUN_0048d391,FUN_004916e9,FUN_00498c3e,FUN_0048d5c4,FUN_00499227,FUN_004916c2,FUN_00498c06,FUN_004a2078,FUN_0049002d
// callees: 

LPVOID GlobalLock(HGLOBAL hMem)

{
  LPVOID pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3ef1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = GlobalLock(hMem);
  return pvVar1;
}

