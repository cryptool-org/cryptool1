/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

#ifndef _TEXTSCROLLER_H_
#define _TEXTSCROLLER_H_

#include "afxwin.h"
#include <list>

/*
Instances of this class can be linked to static MFC GUI elements in order to 
display scrolling lines of text (from bottom to top). See "DlgAuthors.cpp" for details.
*/
class CTextScroller : public CStatic
{
public:
	// construction and destruction
	CTextScroller();
	virtual ~CTextScroller();

	// initialize text scroller from the outside
	void initialize(const int timer);
	// add line from the outside
	void addLine(const CString line);
	// pause the scrolling (this function toggles the scrolling)
	void pause();

protected:
	// the font size
	int mFontSize;
	// the font
	CFont mFont;
	// the text color
	COLORREF mColorText;
	// the background color
	COLORREF mColorBackground;

	// draw the background on the passed DC
	void drawBackground(CDC *pDC);
	// draw the text
	void drawText();

	// the number of lines that can be displayed with the given font size
	int numberOfVisibleLines;
	// this variable keeps track of the scroll process
	int progress;
	// this variable is used to pause the scroll process
	bool paused;
	// this variable holds the timer interval in milliseconds
	int timerInMilliseconds;
	// this list of lines to be displayed
	std::list<CString> listLines;

protected:
	// overridden methods
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()
};

#endif