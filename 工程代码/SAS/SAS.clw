; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=SCaseDisplay
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SAS.h"
LastPage=0

ClassCount=13
Class1=CSASApp
Class2=CSASDoc
Class3=CSASView
Class4=CMainFrame

ResourceCount=12
Resource1=IDD_SAS_FORM
Resource2=IDD_SCASEDISPLAY_DIALOG
Class5=CAboutDlg
Resource3=IDR_MAINFRAME
Class6=SCaseDisplay
Resource4=IDR_MENUPOP
Class7=SCaseNew
Resource5=IDD_SCASENEW
Class8=SCaseShow
Class9=SetColor
Resource6=IDD_SHOWRESULT
Resource7=IDD_RESULT
Resource8=IDD_CONFIGSET
Class10=SetConfig
Resource9=IDD_COLORSET
Class11=SEventList
Resource10=IDD_EVENTDIALOG
Class12=ResultDialog
Resource11=IDD_ABOUTBOX
Class13=SResultDialog
Resource12=IDR_TOOLBAR1

[CLS:CSASApp]
Type=0
HeaderFile=SAS.h
ImplementationFile=SAS.cpp
Filter=N

[CLS:CSASDoc]
Type=0
HeaderFile=SASDoc.h
ImplementationFile=SASDoc.cpp
Filter=N

[CLS:CSASView]
Type=0
HeaderFile=SASView.h
ImplementationFile=SASView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=IDC_PAD


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=SAS.cpp
ImplementationFile=SAS.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_NEWSCASE
Command3=ID_COLORSET
Command4=ID_WORDANDSPEED
Command5=ID_APP_ABOUT
CommandCount=5

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[DLG:IDD_SAS_FORM]
Type=1
Class=CSASView
ControlCount=43
Control1=IDC_STATIC,button,1342177287
Control2=IDC_PLIST,SysListView32,1350631429
Control3=IDC_OPEN,button,1342242816
Control4=IDC_DELETE,button,1342242816
Control5=IDC_SAVE,button,1342242816
Control6=IDC_CANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_COMMENT,edit,1350631556
Control23=IDC_SID,edit,1484849280
Control24=IDC_SNAME1,edit,1350631552
Control25=IDC_SNAME2,edit,1350631552
Control26=IDC_SSEX,combobox,1344471299
Control27=IDC_SBIRTHDAY,SysDateTimePick32,1342242848
Control28=IDC_SAGE,edit,1484849280
Control29=IDC_SHIGH,edit,1350631552
Control30=IDC_SWEIGHT,edit,1350631552
Control31=IDC_DIAGNOSIS,edit,1350631552
Control32=IDC_RECORD,edit,1350631552
Control33=IDC_STATIC,static,1342308352
Control34=IDC_TOTALTIME,edit,1484849280
Control35=IDC_STARTDATE1,SysDateTimePick32,1342242848
Control36=IDC_STARTDATE2,SysDateTimePick32,1342242857
Control37=IDC_SENDDATE1,SysDateTimePick32,1476460576
Control38=IDC_SENDDATE2,SysDateTimePick32,1476460585
Control39=IDC_Picture,static,1342177294
Control40=IDC_PAD,edit,1353781444
Control41=IDC_PADW,button,1342242816
Control42=IDC_PADR,button,1342242816
Control43=IDC_CONSULT,button,1342242816

[DLG:IDD_SCASEDISPLAY_DIALOG]
Type=1
Class=SCaseDisplay
ControlCount=0

[CLS:SCaseDisplay]
Type=0
HeaderFile=SCaseDisplay.h
ImplementationFile=SCaseDisplay.cpp
BaseClass=CDialog
Filter=W
VirtualFilter=dWC
LastObject=DELETE_E

[DLG:IDD_SCASENEW]
Type=1
Class=SCaseNew
ControlCount=31
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_COMMENT,edit,1350631556
Control17=IDC_SID,edit,1484849280
Control18=IDC_SNAME1,edit,1350631552
Control19=IDC_SNAME2,edit,1350631552
Control20=IDC_SSEX,combobox,1344471299
Control21=IDC_SBIRTHDAY,SysDateTimePick32,1342242848
Control22=IDC_SAGE,edit,1484849280
Control23=IDC_SHIGH,edit,1350631552
Control24=IDC_SWEIGHT,edit,1350631552
Control25=IDC_DIAGNOSIS,edit,1350631552
Control26=IDC_RECORD,edit,1350631552
Control27=IDC_STATIC,static,1342308352
Control28=IDC_FILEPATH,edit,1350631552
Control29=IDC_FILESCAN,button,1342242816
Control30=IDC_SSTARTDATE1,SysDateTimePick32,1342242848
Control31=IDC_SSTARTDATE2,SysDateTimePick32,1342242857

[CLS:SCaseNew]
Type=0
HeaderFile=SCaseNew.h
ImplementationFile=SCaseNew.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SSEX
VirtualFilter=dWC

[CLS:SCaseShow]
Type=0
HeaderFile=SCaseShow.h
ImplementationFile=SCaseShow.cpp
BaseClass=CFrameWnd
Filter=T

[CLS:SetColor]
Type=0
HeaderFile=SetColor.h
ImplementationFile=SetColor.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_NFLOW

[DLG:IDD_COLORSET]
Type=1
Class=SetColor
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_NFLOW,static,1342308608
Control10=IDC_NSPO2,static,1342308608
Control11=IDC_NPULSE,static,1342308608
Control12=IDC_NPLETH,static,1342308608
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_APNEAB,static,1342308608
Control17=IDC_HYPOPNEAB,static,1342308608
Control18=IDC_DESCENDB,static,1342308608
Control19=IDC_STATIC,static,1342308352
Control20=IDC_BACKC,static,1342308608

[MNU:IDR_MENUPOP]
Type=1
Class=?
Command1=ID_WSPEED002
Command2=ID_WSPEED02
Command3=ID_WSPEED1
Command4=ID_WSPEED2
Command5=ID_WSPEED1M
CommandCount=5

[TB:IDR_TOOLBAR1]
Type=1
Class=?
Command1=INSERT_A
Command2=INSERT_D
Command3=INSERT_H
Command4=DELETE_E
Command5=UPDATE_EE
Command6=RESULT_SHOW
Command7=EVENT_SHOW
CommandCount=7

[DLG:IDD_CONFIGSET]
Type=1
Class=SetConfig
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_TBWORD,msctls_trackbar32,1342242817
Control6=IDC_STATIC,static,1342308352
Control7=IDC_RLWORD,msctls_trackbar32,1342242817
Control8=IDC_MODESHOW,combobox,1344339971

[CLS:SetConfig]
Type=0
HeaderFile=SetConfig.h
ImplementationFile=SetConfig.cpp
BaseClass=CDialog
Filter=D
LastObject=DELETE_E
VirtualFilter=dWC

[DLG:IDD_EVENTDIALOG]
Type=1
Class=SEventList
ControlCount=2
Control1=IDC_EVENTTREE,SysTreeView32,1350631424
Control2=IDC_EVENTLIST,SysListView32,1350631429

[CLS:SEventList]
Type=0
HeaderFile=SEventList.h
ImplementationFile=SEventList.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EVENTLIST

[DLG:IDD_RESULT]
Type=1
Class=ResultDialog
ControlCount=9
Control1=IDC_APNEAC,edit,1484849280
Control2=IDC_APNEAI,edit,1484849280
Control3=IDC_HYPOPC,edit,1484849280
Control4=IDC_DESCENDC,edit,1484849280
Control5=IDC_DESCENDI,edit,1484849280
Control6=IDC_HYPOPI,edit,1484849280
Control7=IDC_MAXA,edit,1484849280
Control8=IDC_MAXH,edit,1484849280
Control9=IDC_SPO2SHOW,static,1342177298

[CLS:ResultDialog]
Type=0
HeaderFile=ResultDialog.h
ImplementationFile=ResultDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=DELETE_E

[DLG:IDD_SHOWRESULT]
Type=1
Class=SResultDialog
ControlCount=9
Control1=IDC_APNEAC,edit,1484849280
Control2=IDC_APNEAI,edit,1484849280
Control3=IDC_HYPOPC,edit,1484849280
Control4=IDC_DESCENDC,edit,1484849280
Control5=IDC_DESCENDI,edit,1484849280
Control6=IDC_HYPOPI,edit,1484849280
Control7=IDC_MAXA,edit,1484849280
Control8=IDC_MAXH,edit,1484849280
Control9=IDC_SPO2SHOW,static,1342177298

[CLS:SResultDialog]
Type=0
HeaderFile=SResultDialog.h
ImplementationFile=SResultDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=SResultDialog

