/***************************************************************************
 *   Copyright (C) 2007 by Pino Toscano <pino@kde.org>                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "findbar.h"

// qt/kde includes
#include <qlabel.h>
#include <qlayout.h>
#include <qmenu.h>
#include <qtoolbutton.h>
#include <kicon.h>
#include <klocale.h>
#include <kpushbutton.h>

// local includes
#include "searchlineedit.h"
#include "core/document.h"

FindBar::FindBar( Okular::Document * document, QWidget * parent )
  : QWidget( parent )
{
    QHBoxLayout * lay = new QHBoxLayout( this );
    lay->setMargin( 2 );

    QToolButton * closeBtn = new QToolButton( this );
    closeBtn->setIcon( KIcon( "dialog-close" ) );
    closeBtn->setIconSize( QSize( 24, 24 ) );
    closeBtn->setToolTip( i18n( "Close" ) );
    closeBtn->setAutoRaise( true );
    lay->addWidget( closeBtn );

    QLabel * label = new QLabel( i18nc( "Find text", "F&ind:" ), this );
    lay->addWidget( label );

    m_search = new SearchLineWidget( this, document );
    m_search->lineEdit()->setSearchCaseSensitivity( Qt::CaseInsensitive );
    m_search->lineEdit()->setSearchMinimumLength( 0 );
    m_search->lineEdit()->setSearchType( Okular::Document::NextMatch );
    m_search->lineEdit()->setSearchId( PART_SEARCH_ID );
    m_search->lineEdit()->setSearchColor( qRgb( 255, 255, 64 ) );
    m_search->lineEdit()->setSearchMoveViewport( true );
    m_search->lineEdit()->setToolTip( i18n( "Text to search for" ) );
    label->setBuddy( m_search );
    lay->addWidget( m_search );

    QPushButton * findNextBtn = new QPushButton( KIcon( "go-down-search" ), i18nc( "Find and go to the next search match", "Next" ), this );
    findNextBtn->setToolTip( i18n( "Jump to next match" ) );
    lay->addWidget( findNextBtn );

    QPushButton * findPrevBtn = new QPushButton( KIcon( "go-up-search" ), i18nc( "Find and go to the previous search match", "Previous" ), this );
    findPrevBtn->setToolTip( i18n( "Jump to previous match" ) );
    lay->addWidget( findPrevBtn );

    QPushButton * optionsBtn = new QPushButton( this );
    optionsBtn->setText( i18n( "Options" ) );
    optionsBtn->setToolTip( i18n( "Modify search behavior" ) );
    QMenu * optionsMenu = new QMenu( optionsBtn );
    m_caseSensitiveAct = optionsMenu->addAction( i18n( "Case sensitive" ) );
    m_caseSensitiveAct->setCheckable( true );
    m_fromCurrentPageAct = optionsMenu->addAction( i18n( "From current page" ) );
    m_fromCurrentPageAct->setCheckable( true );
    optionsBtn->setMenu( optionsMenu );
    lay->addWidget( optionsBtn );

    connect( closeBtn, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( findNextBtn, SIGNAL( clicked() ), this, SLOT( findNext() ) );
    connect( findPrevBtn, SIGNAL( clicked() ), this, SLOT( findPrev() ) );
    connect( m_caseSensitiveAct, SIGNAL( toggled( bool ) ), this, SLOT( caseSensitivityChanged() ) );
    connect( m_fromCurrentPageAct, SIGNAL( toggled( bool ) ), this, SLOT( fromCurrentPageChanged() ) );

    hide();
}

FindBar::~FindBar()
{
}

QString FindBar::text() const
{
    return m_search->lineEdit()->text();
}

Qt::CaseSensitivity FindBar::caseSensitivity() const
{
    return m_caseSensitiveAct->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
}

void FindBar::focusAndSetCursor()
{
    setFocus();
    m_search->lineEdit()->selectAll();
    m_search->lineEdit()->setFocus();
}

void FindBar::findNext()
{
    m_search->lineEdit()->setSearchType( Okular::Document::NextMatch );
    m_search->lineEdit()->findNext();
}

void FindBar::findPrev()
{
    m_search->lineEdit()->setSearchType( Okular::Document::PreviousMatch );
    m_search->lineEdit()->findPrev();
}

void FindBar::caseSensitivityChanged()
{
    m_search->lineEdit()->setSearchCaseSensitivity( m_caseSensitiveAct->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive );
    m_search->lineEdit()->restartSearch();
}

void FindBar::fromCurrentPageChanged()
{
    m_search->lineEdit()->setSearchFromStart( !m_fromCurrentPageAct->isChecked() );
}

#include "findbar.moc"