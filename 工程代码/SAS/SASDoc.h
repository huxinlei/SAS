// SASDoc.h : interface of the CSASDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SASDOC_H__9474A64A_E6CE_4955_993B_AF91FF25F1E5__INCLUDED_)
#define AFX_SASDOC_H__9474A64A_E6CE_4955_993B_AF91FF25F1E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSASDoc : public CDocument
{
protected: // create from serialization only
	CSASDoc();
	DECLARE_DYNCREATE(CSASDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSASDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSASDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSASDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SASDOC_H__9474A64A_E6CE_4955_993B_AF91FF25F1E5__INCLUDED_)
