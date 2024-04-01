#ifndef ___TEST_VIEW_DOC__PH___
#define ___TEST_VIEW_DOC__PH___

class CTestViewDoc : public CDocument
{
	DECLARE_DYNCREATE( CTestViewDoc )
protected:
	CTestViewDoc();
	virtual ~CTestViewDoc();

public:
	//{{AFX_VIRTUAL(CTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument( LPCTSTR lpszPathName );
	virtual BOOL OnOpenDocument( LPCTSTR lpszPathName );
	//}}AFX_VIRTUAL

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

protected:
	//{{AFX_MSG(CTestDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif //!___TEST_VIEW_DOC__PH___
