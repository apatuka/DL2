// CoCreateInstance @ 004b4425 size=6 sig=HRESULT CoCreateInstance(IID * rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, IID * riid, LPVOID * ppv) cc=__stdcall
// callers: FUN_00489c98
// callees: 

HRESULT CoCreateInstance(IID *rclsid,LPUNKNOWN pUnkOuter,DWORD dwClsContext,IID *riid,LPVOID *ppv)

{
  HRESULT HVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4425. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  HVar1 = CoCreateInstance(rclsid,pUnkOuter,dwClsContext,riid,ppv);
  return HVar1;
}

