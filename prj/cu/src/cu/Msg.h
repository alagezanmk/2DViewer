#ifndef ___MSG__PH___
#define ___MSG__PH___

///////////////////////////////////////////////////////////////////////////////////////////////////
#define WIN_MSG_START_				(WM_APP)
#define WIN_MSG_START				(WIN_MSG_START_)
#define WIN_MSG						(WIN_MSG_START)

#define WIN_MSG_END					(WIN_MSG_START + 99)
#define WIN_MSG_END_				(WIN_MSG_END)

///////////////////////////////////////////////////////////////////////////////////////////////////
//// WMC  Win Message Code
#define WMC_CALL						1
#define WMC_CALLEX						2
#define WMC_CMD							3
#define WMC_CMDEX						4
#define WMC_CMDROUTE					5
#define WMC_MSG							6

///////////////////////////////////////////////////////////////////////////////////////////////////
//// CM  Common Message
#define CM_AFS_MAINFRM_START			1

#define CM_MF_CREATE_PROGRESS_CTRL		1
#define CM_MF_GET_PROGRESS_CTRL			2
#define CM_MF_CLOSE_PROGRESS_CTRL		3

#define CM_MF_VIEW_ADD					4
#define CM_MF_VIEW_CLOSE				5
#define CM_MF_VIEW_ACTIVATE				6
#define CM_MF_GET_ACTIVE_VIEW			7
		
#define CM_MF_GET_FULLSCREEN			8

#define CM_AFS_MAINFRM_END				50

///////////////////////////////////////////////////////////////////////////////////////////////////
#define CM_AFS_SCRLVIEW_START			1

#define CM_SV_VIEW_ACTIVATE				1

#define CM_AFS_SCRLVIEW_END				50

///////////////////////////////////////////////////////////////////////////////////////////////////
#define CM_AFS_CHILDFRM_START			1

#define CM_CF_GET_SBAR					1

#define CM_AFS_CHILDFRM_END				50

///////////////////////////////////////////////////////////////////////////////////////////////////
#define CM_WIN_MSG_						0x400000
#define CM_UPDATE_CURSOR				0x400001
#define CM_UPDATE_CURSOR_POS			0x400002

#define CM_INIT_MAIN_MENU				0x400003

#define CM_KEY_DOWN						0x400004
#define CM_KEY_UP						0x400005

#define CM_SYS_KEY_DOWN					0x400006
#define CM_SYS_KEY_UP					0x400007

#define CM_ADD_OPTION_PAGE				0x400008

///////////////////////////////////////////////////////////////////////////////////////////////////
#define ONC_CALL(id, memberFxn) \
	{ WIN_MSG, WMC_CALL, id, id, AfxSig_vv, \
		(AFX_PMSG)&memberFxn },

#define ONC_CALL_EX(id, memberFxn) \
	{ WIN_MSG, WMC_CALLEX, id, id, AfxSig_bv, \
		(AFX_PMSG)(BOOL (AFX_MSG_CALL CCmdTarget::*)())&memberFxn },

#define ONC_CALL_ROUTE(id, memberFxn) \
	{ WIN_MSG, WMC_ROUTE, id, id, AfxSig_bv, \
		(AFX_PMSG)(BOOL (AFX_MSG_CALL CCmdTarget::*)())&memberFxn },

///////////////////////////////////////////////////////////////////////////////////////////////////
#define ONC_CALL_RANGE(id, idLast, memberFxn) \
	{ WIN_MSG, WMC_CALL, id, idLast, AfxSig_vw, \
		(AFX_PMSG)(void (AFX_MSG_CALL CCmdTarget::*)(UINT))&memberFxn },

#define ONC_CALL_EX_RANGE(id, idLast, memberFxn) \
	{ WIN_MSG, WMC_CALLEX, id, idLast, AfxSig_vw, \
		(AFX_PMSG)(void (AFX_MSG_CALL CCmdTarget::*)(UINT))&memberFxn },

#define ONC_CALL_ROUTE_RANGE(id, idLast, memberFxn) \
	{ WIN_MSG, WMC_ROUTE, id, idLast, AfxSig_bw, \
		(AFX_PMSG)(BOOL (AFX_MSG_CALL CCmdTarget::*)(UINT))&memberFxn },

///////////////////////////////////////////////////////////////////////////////////////////////////
#define ONC_CMD(id, memberFxn) \
	{ WIN_MSG, WMC_CMD, id, id, AfxSig_vw, \
		(AFX_PMSG)(void (AFX_MSG_CALL CCmdTarget::*)(UINT))&memberFxn },

#define ONC_CMD_EX(id, memberFxn) \
	{ WIN_MSG, WMC_CMDEX, id, id, AfxSig_bw, \
		(AFX_PMSG)(BOOL (AFX_MSG_CALL CCmdTarget::*)(UINT))&memberFxn },

#define ONC_CMD_ROUTE(id, memberFxn) \
	{ WIN_MSG, WMC_ROUTE, id, id, AfxSig_bw, \
		(AFX_PMSG)(BOOL (AFX_MSG_CALL CCmdTarget::*)(UINT))&memberFxn },

///////////////////////////////////////////////////////////////////////////////////////////////////
#define ONC_CMD_RANGE(id, idLast, memberFxn) \
	{ WIN_MSG, WMC_CMD, id, idLast, AfxSig_vww, \
		(AFX_PMSG)(void (AFX_MSG_CALL CCmdTarget::*)(UINT, UINT))&memberFxn },

#define ONC_CMD_EX_RANGE(id, idLast, memberFxn) \
	{ WIN_MSG, WMC_CMDEX, id, idLast, AfxSig_iww, \
		(AFX_PMSG)(BOOL (AFX_MSG_CALL CCmdTarget::*)(UINT, UINT))&memberFxn },

#define ONC_CMD_ROUTE_RANGE(id, idLast, memberFxn) \
	{ WIN_MSG, WMC_CMDEX, id, idLast, AfxSig_iww, \
		(AFX_PMSG)(BOOL (AFX_MSG_CALL CCmdTarget::*)(UINT, UINT))&memberFxn },

///////////////////////////////////////////////////////////////////////////////////////////////////
#define ONC_MSG(id, memberFxn) \
	{ WIN_MSG, WMC_MSG, id, id, AfxSig_lwl, \
		(AFX_PMSG)(AFX_PMSGW)(LRESULT (AFX_MSG_CALL CCmdTarget::*)(WPARAM, LPARAM))&memberFxn },

#define ONC_MSG_RANGE(id, idLast, memberFxn) \
	{ WIN_MSG, WMC_MSG, id, id, AfxSig_lwl, \
		(AFX_PMSG)(AFX_PMSGW)(LRESULT (AFX_MSG_CALL CCmdTarget::*)(UINT, LPARAM))&memberFxn },

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL AfsAddCtrlWnd( UINT nID, CWnd* pWnd );
CU_EXT_API void AfsSetCtrlWnd( UINT nID, CWnd* pWnd );
CU_EXT_API BOOL AfsRemoveCtrlWnd( UINT nID, CWnd* pWnd );
CU_EXT_API CWnd* AfsGetCtrlWnd( UINT nID );

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API LRESULT SendNotify( CWnd* pWnd, INT nCode, NMHDR* pnm = NULL );
inline CU_EXT_API void SendCommand( CWnd* pWnd, INT nID ) {
	pWnd->OnCmdMsg( nID, 0, NULL, NULL ); }

CU_EXT_API LRESULT AfsSend( UINT nCode, UINT nCtrlID, UINT id, WPARAM wParam = 0, LPARAM lParam = 0 );
CU_EXT_API LRESULT AfsSend( UINT nCode, HWND hWnd, UINT id, WPARAM wParam = 0, LPARAM lParam = 0 );
CU_EXT_API LRESULT AfsSend( UINT nCode, CWnd* pWnd, UINT id, WPARAM wParam = 0, LPARAM lParam = 0 );

///////////////////////////////////////////////////////////////////////////////////////////////////
inline LRESULT AfsSendCall( UINT nCtrlID, UINT id ) {
	return AfsSend( WMC_CALL, nCtrlID, id ); }

inline LRESULT AfsSendCall( HWND hWnd, UINT id ) {
	return AfsSend( WMC_CALL, hWnd, id ); }

inline LRESULT AfsSendCall( CWnd* pWnd, UINT id ) {
	return AfsSend( WMC_CALL, pWnd, id ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
inline LRESULT AfsSendCallEx( UINT nCtrlID, UINT id ) {
	return AfsSend( WMC_CALLEX, nCtrlID, id ); }

inline LRESULT AfsSendCallEx( HWND hWnd, UINT id ) {
	return AfsSend( WMC_CALLEX, hWnd, id ); }

inline LRESULT AfsSendCallEx( CWnd* pWnd, UINT id ) {
	return AfsSend( WMC_CALLEX, pWnd, id ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
inline LRESULT AfsSendCmd( UINT nCtrlID, UINT id, UINT nCmd ) {
	return AfsSend( WMC_CMD, nCtrlID, id, nCmd ); }

inline LRESULT AfsSendCmd( HWND hWnd, UINT id, UINT nCmd ) {
	return AfsSend( WMC_CMD, hWnd, id, nCmd ); }

inline LRESULT AfsSendCmd( CWnd* pWnd, UINT id, UINT nCmd ) {
	return AfsSend( WMC_CMD, pWnd, id, nCmd ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
inline LRESULT AfsSendCmdEx( UINT nCtrlID, UINT id, UINT nCmd ) {
	return AfsSend( WMC_CMDEX, nCtrlID, id, nCmd ); }

inline LRESULT AfsSendCmdEx( HWND hWnd, UINT id, UINT nCmd ) {
	return AfsSend( WMC_CMDEX, hWnd, id, nCmd ); }

inline LRESULT AfsSendCmdEx( CWnd* pWnd, UINT id, UINT nCmd ) {
	return AfsSend( WMC_CMDEX, pWnd, id, nCmd ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
inline LRESULT AfsSendCmdRoute( UINT nCtrlID, UINT id, UINT nCmd ) {
	return AfsSend( WMC_CMDROUTE, nCtrlID, id, nCmd ); }

inline LRESULT AfsSendCmdRoute( HWND hWnd, UINT id, UINT nCmd ) {
	return AfsSend( WMC_CMDROUTE, hWnd, id, nCmd ); }

inline LRESULT AfsSendCmdRoute( CWnd* pWnd, UINT id, UINT nCmd ) {
	return AfsSend( WMC_CMDROUTE, pWnd, id, nCmd ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
inline CU_EXT_API LRESULT AfsSendMsg( UINT nCtrlID, UINT id, WPARAM wParam, LPARAM lParam = 0 ) {
	return AfsSend( WMC_MSG, nCtrlID, id, wParam, lParam ); }

inline CU_EXT_API LRESULT AfsSendMsg( HWND hWnd, UINT id, WPARAM wParam, LPARAM lParam = 0 ) {
	return AfsSend( WMC_MSG, hWnd, id, wParam, lParam ); }

inline CU_EXT_API LRESULT AfsSendMsg( CWnd* pWnd, UINT id, WPARAM wParam, LPARAM lParam = 0 ) {
	return AfsSend( WMC_MSG, pWnd, id, wParam, lParam ); }

///////////////////////////////////////////////////////////////////////////////////////////////////
CU_EXT_API BOOL LoadWindowPlacement( LPCTSTR ptszRegKey, WINDOWPLACEMENT& wndPlace );
CU_EXT_API BOOL SaveWindowPlacement( LPCTSTR ptszRegKey, WINDOWPLACEMENT& wndPlace );

#endif //___MSG__PH___