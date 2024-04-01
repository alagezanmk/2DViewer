#ifndef ___TEST_BLD_DOC__PH___
#define ___TEST_BLD_DOC__PH___

class CGINode;
class CTestBldDoc : public CDocument
{
	DECLARE_DYNCREATE( CTestBldDoc )
protected:
	CTestBldDoc();
	virtual ~CTestBldDoc();

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

public:
	CGINode* GetFileNode();
	void SetFileNode( CGINode* pNode );

protected:
	CGINode* m_pFileNode;
};

inline CGINode* CTestBldDoc::GetFileNode() {
	return m_pFileNode; }

//{{AFX_INSERT_LOCATION}}
#endif //!___TEST_BLD_DOC__PH___
