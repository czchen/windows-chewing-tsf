#ifndef IME_TEXT_SERVICE_H
#define IME_TEXT_SERVICE_H

#include "libIME.h"
#include <msctf.h>
#include "EditSession.h"
#include "KeyEvent.h"
#include "ComPtr.h"

#include <vector>

namespace Ime {

class ImeModule;
class CandidateWindow;
class LangBarButton;

class TextService:
	// TSF interfaces
	public ITfTextInputProcessor,
	public ITfDisplayAttributeProvider,
	// event sinks
	public ITfThreadMgrEventSink,
	public ITfTextEditSink,
	public ITfKeyEventSink,
	public ITfCompositionSink {
public:

	TextService(ImeModule* module);
	virtual ~TextService(void);

	// public methods
	ImeModule* module() const;

	ITfThreadMgr* threadMgr() const;

	TfClientId clientId() const;

	ITfContext* currentContext();

	bool isActivated() const {
		return (threadMgr() != NULL);
	}

	DWORD activateFlags() const {
		return activateFlags_;
	}

	// running in Windows 8 app mode
	bool isImmersive() const {
		return (activateFlags_ & TF_TMF_IMMERSIVEMODE) != 0;
	}

	// language bar buttons
	void addButton(LangBarButton* button);
	void removeButton(LangBarButton* button);

	// preserved keys
	void addPreservedKey(UINT keyCode, UINT modifiers, const GUID& guid);
	void removePreservedKey(const GUID& guid);

	// text composition handling
	bool isComposing();
	bool isInsertionAllowed(EditSession* session);
	void startComposition(ITfContext* context);
	void endComposition(ITfContext* context);
	bool compositionRect(EditSession* session, RECT* rect);
	bool selectionRect(EditSession* session, RECT* rect);
	HWND compositionWindow(EditSession* session);

	void setCompositionString(EditSession* session, const wchar_t* str, int len);
	void setCompositionCursor(EditSession* session, int pos);

	// virtual functions that IME implementors may need to override
	virtual void onActivate();
	virtual void onDeactivate();

	virtual void onFocus();

	virtual bool filterKeyDown(KeyEvent& keyEvent);
	virtual bool onKeyDown(KeyEvent& keyEvent, EditSession* session);
	
	virtual bool filterKeyUp(KeyEvent& keyEvent);
	virtual bool onKeyUp(KeyEvent& keyEvent, EditSession* session);

	virtual bool onPreservedKey(const GUID& guid);

	// called when a language button or menu item is clicked
	virtual bool onCommand(UINT id);

	// COM related stuff
public:
    // IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, void **ppvObj);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

    // ITfTextInputProcessor
    STDMETHODIMP Activate(ITfThreadMgr *pThreadMgr, TfClientId tfClientId);
    STDMETHODIMP Deactivate();

    // ITfThreadMgrEventSink
    STDMETHODIMP OnInitDocumentMgr(ITfDocumentMgr *pDocMgr);
    STDMETHODIMP OnUninitDocumentMgr(ITfDocumentMgr *pDocMgr);
    STDMETHODIMP OnSetFocus(ITfDocumentMgr *pDocMgrFocus, ITfDocumentMgr *pDocMgrPrevFocus);
    STDMETHODIMP OnPushContext(ITfContext *pContext);
    STDMETHODIMP OnPopContext(ITfContext *pContext);

    // ITfTextEditSink
    STDMETHODIMP OnEndEdit(ITfContext *pContext, TfEditCookie ecReadOnly, ITfEditRecord *pEditRecord);

    // ITfKeyEventSink
    STDMETHODIMP OnSetFocus(BOOL fForeground);
    STDMETHODIMP OnTestKeyDown(ITfContext *pContext, WPARAM wParam, LPARAM lParam, BOOL *pfEaten);
    STDMETHODIMP OnKeyDown(ITfContext *pContext, WPARAM wParam, LPARAM lParam, BOOL *pfEaten);
    STDMETHODIMP OnTestKeyUp(ITfContext *pContext, WPARAM wParam, LPARAM lParam, BOOL *pfEaten);
    STDMETHODIMP OnKeyUp(ITfContext *pContext, WPARAM wParam, LPARAM lParam, BOOL *pfEaten);
    STDMETHODIMP OnPreservedKey(ITfContext *pContext, REFGUID rguid, BOOL *pfEaten);

    // ITfCompositionSink
    STDMETHODIMP OnCompositionTerminated(TfEditCookie ecWrite, ITfComposition *pComposition);

    // ITfDisplayAttributeProvider
    STDMETHODIMP EnumDisplayAttributeInfo(IEnumTfDisplayAttributeInfo **ppEnum);
    STDMETHODIMP GetDisplayAttributeInfo(REFGUID guidInfo, ITfDisplayAttributeInfo **ppInfo);

protected:
	// edit session classes, used with TSF
	class KeyEditSession: public EditSession {
	public:
		KeyEditSession(TextService* service, ITfContext* context, KeyEvent& keyEvent):
			EditSession(service, context),
			keyEvent_(keyEvent),
			result_(false) {
		}
		STDMETHODIMP DoEditSession(TfEditCookie ec);

		KeyEvent keyEvent_;
		bool result_;
	};

	class StartCompositionEditSession: public EditSession {
	public:
		StartCompositionEditSession(TextService* service, ITfContext* context):
			EditSession(service, context){
		}
		STDMETHODIMP DoEditSession(TfEditCookie ec);
	};

	class EndCompositionEditSession: public EditSession {
	public:
		EndCompositionEditSession(TextService* service, ITfContext* context):
			EditSession(service, context){
		}
		STDMETHODIMP DoEditSession(TfEditCookie ec);
	};

	HRESULT doKeyEditSession(TfEditCookie cookie, KeyEditSession* session);
	HRESULT doStartCompositionEditSession(TfEditCookie cookie, StartCompositionEditSession* session);
	HRESULT doEndCompositionEditSession(TfEditCookie cookie, EndCompositionEditSession* session);

	struct PreservedKey : public TF_PRESERVEDKEY {
		GUID guid;
	};

private:
	ImeModule* module_;
	ComPtr<ITfThreadMgr> threadMgr_;
	TfClientId clientId_;
	DWORD activateFlags_;

	// event sink cookies
	DWORD threadMgrEventSinkCookie_;
	DWORD textEditSinkCookie_;
	DWORD compositionSinkCookie_;

	ITfComposition* composition_; // acquired when starting composition, released when ending composition
	CandidateWindow* candidateWindow_;
	std::vector<LangBarButton*> langBarButtons_;
	std::vector<PreservedKey> preservedKeys_;

	long refCount_; // reference counting
};

}

#endif
