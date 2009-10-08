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

#include "TextScroller.h"

CTextScroller::CTextScroller()
{
	paused = false;
}

CTextScroller::~CTextScroller()
{

}

void CTextScroller::initialize(const int timer)
{
	timerInMilliseconds = timer;

	mFontSize = 14;

	// create the font
	mFont.CreateFontA(mFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, "Arial");
	// set text color
	mColorText = RGB(0,0,0);
	// set background color
	//mColorBackground = RGB(255,255,255);
	mColorBackground = GetSysColor(COLOR_3DFACE);

	// determine how many lines we can display
	CRect rect;
	GetClientRect(&rect);
	numberOfVisibleLines = (rect.bottom - rect.top) / mFontSize;

	// set the progress to zero
	progress = 0;

	// initialize the timer
	SetTimer(0, timerInMilliseconds, NULL);
}

BEGIN_MESSAGE_MAP(CTextScroller, CStatic)
    //{{AFX_MSG_MAP(CTextScroller)
    ON_WM_PAINT()
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CTextScroller::OnPaint()
{
	// kill the timer, draw the background and restart the timer
	KillTimer(0);
	CPaintDC dc(this);
	drawBackground(&dc);
	SetTimer(0, timerInMilliseconds, NULL);
}

void CTextScroller::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 0) {
		drawText();
		progress++;
	}

	CStatic::OnTimer(nIDEvent);
}

void CTextScroller::drawBackground(CDC *pDC)
{
	CRect rect;
	GetClientRect(rect);

	pDC->FillSolidRect(&rect, mColorBackground);
}

void CTextScroller::drawText()
{
	CDC *pDC = GetDC();

	// draw the background
	drawBackground(pDC);

	CRect rectTemp;
	GetClientRect(rectTemp);
	const CRect rect = rectTemp;

	// choose font
	pDC->SelectObject(&mFont);

	int i=0;
	for(std::list<CString>::iterator iter=listLines.begin(); iter!=listLines.end(); iter++, i++) {

		// determine top position of current string
		int position = progress - i * mFontSize;

		// display string only if it's BELOW the top boundary and ABOVE the bottom boundary
		if(position - mFontSize > 0 && position + mFontSize < numberOfVisibleLines * mFontSize) {
			// determine rect for current string
			rectTemp = rect;
			rectTemp.top = rectTemp.bottom - position;
			rectTemp.bottom = rectTemp.top + mFontSize;	
			// draw the current string
			pDC->DrawText((*iter), (*iter).GetLength(), rectTemp, DT_CENTER);
		}
		// make sure we put all strings back to the bottom if they exceeded the top
		if(position > numberOfVisibleLines * mFontSize + (int)listLines.size() * mFontSize)
			progress = 0;
	}
	ReleaseDC(pDC);
}

void CTextScroller::addLine(const CString line)
{
	listLines.push_back(line);
}

void CTextScroller::pause()
{
	// either restart the timer...
	if(paused) SetTimer(0, timerInMilliseconds, NULL);
	// ...or stop it
	else KillTimer(0);
	// remember current state
	paused = !paused;
}