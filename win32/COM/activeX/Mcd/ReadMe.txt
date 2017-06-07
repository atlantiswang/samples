========================================================================
		ActiveX Control DLL : MCD
========================================================================

ControlWizard has created this project for your MCD ActiveX Control
DLL, which contains 1 control.

This skeleton project not only demonstrates the basics of writing an
ActiveX Control, but is also a starting point for writing the specific
features of your control.

This file contains a summary of what you will find in each of the files
that make up your MCD ActiveX Control DLL.

Mcd.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.

Mcd.h
	This is the main include file for the ActiveX Control DLL.  It
	includes other project-specific includes such as resource.h.

Mcd.cpp
	This is the main source file that contains code for DLL initialization,
	termination and other bookkeeping.

Mcd.rc
	This is a listing of the Microsoft Windows resources that the project
	uses.  This file can be directly edited with the Visual C++ resource
	editor.

Mcd.def
	This file contains information about the ActiveX Control DLL that
	must be provided to run with Microsoft Windows.

Mcd.clw
	This file contains information used by ClassWizard to edit existing
	classes or add new classes.  ClassWizard also uses this file to store
	information needed to generate and edit message maps and dialog data
	maps and to generate prototype member functions.

Mcd.odl
	This file contains the Object Description Language source code for the
	type library of your control.

/////////////////////////////////////////////////////////////////////////////
Mcd control:

McdCtl.h
	This file contains the declaration of the CMcdCtrl C++ class.

McdCtl.cpp
	This file contains the implementation of the CMcdCtrl C++ class.

McdPpg.h
	This file contains the declaration of the CMcdPropPage C++ class.

McdPpg.cpp
	This file contains the implementation of the CMcdPropPage C++ class.

McdCtl.bmp
	This file contains a bitmap that a container will use to represent the
	CMcdCtrl control when it appears on a tool palette.  This bitmap
	is included by the main resource file Mcd.rc.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

stdafx.h, stdafx.cpp
	These files are used to build a precompiled header (PCH) file
	named stdafx.pch and a precompiled types (PCT) file named stdafx.obj.

resource.h
	This is the standard header file, which defines new resource IDs.
	The Visual C++ resource editor reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

ControlWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
