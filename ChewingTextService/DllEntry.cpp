#include "ChewingImeModule.h"
#include "resource.h"

Chewing::ImeModule* g_imeModule = NULL;

// GUID of our language profile
// {CE45F71D-CE79-41D1-967D-640B65A380E3}
static const GUID g_profileGuid = {
	0xce45f71d, 0xce79, 0x41d1, { 0x96, 0x7d, 0x64, 0xb, 0x65, 0xa3, 0x80, 0xe3 }
};

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		::DisableThreadLibraryCalls(hModule); // disable DllMain calls due to new thread creation
		g_imeModule = new Chewing::ImeModule(hModule);
		break;
	case DLL_PROCESS_DETACH:
		if(g_imeModule) {
			g_imeModule->Release();
			g_imeModule = NULL;
		}
		break;
	}
	return TRUE;
}

STDAPI DllCanUnloadNow(void) {
	return g_imeModule->canUnloadNow();
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppvObj) {
	return g_imeModule->getClassObject(rclsid, riid, ppvObj);
}

STDAPI DllUnregisterServer(void) {
	return g_imeModule->unregisterServer(g_profileGuid);
}

STDAPI DllRegisterServer(void) {
	wchar_t name[32];
	::LoadStringW(g_imeModule->hInstance(), IDS_CHEWING, name, 32);
	return g_imeModule->registerServer(
		name,
		g_profileGuid,
		MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL));
}
