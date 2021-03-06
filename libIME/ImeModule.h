#ifndef IME_MODULE_H
#define IME_MODULE_H

#include <Unknwn.h>
#include <Windows.h>

namespace Ime {

class TextService;

class ImeModule: public IClassFactory {
public:
	ImeModule(HMODULE module, const CLSID& textServiceClsid);
	virtual ~ImeModule(void);

	// public methods
	HINSTANCE hInstance() const {
		return hInstance_;
	}

	const CLSID& textServiceClsid() const {
		return textServiceClsid_;
	}

	// Dll entry points implementations
	HRESULT canUnloadNow();
	HRESULT getClassObject(REFCLSID rclsid, REFIID riid, void **ppvObj);
	HRESULT registerServer(wchar_t* name, const GUID& profileGuid, LANGID languageId);
	HRESULT unregisterServer(const GUID& profileGuid);

	virtual TextService* createTextService() = 0;

	// COM-related stuff

	// IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, void **ppvObj);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

protected:
    // IClassFactory
    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObj);
    STDMETHODIMP LockServer(BOOL fLock);

private:
	volatile unsigned long refCount_;
	HINSTANCE hInstance_;
	CLSID textServiceClsid_;
	wchar_t* tooltip_;
};

}

#endif
