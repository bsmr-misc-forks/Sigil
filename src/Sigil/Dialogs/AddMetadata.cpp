/************************************************************************
**
**  Copyright (C) 2009  Strahinja Markovic
**
**  This file is part of Sigil.
**
**  Sigil is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  Sigil is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Sigil.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#include <stdafx.h>
#include "AddMetadata.h"
#include "../BookManipulation/Metadata.h"


// Constructor
AddMetadata::AddMetadata( const QMap< QString, Metadata::MetaInfo > &metadata, QWidget *parent )
    : QDialog( parent ), m_Metadata( metadata )
{
    ui.setupUi( this );

    connect(	ui.lwProperties,	SIGNAL( currentItemChanged( QListWidgetItem*, QListWidgetItem* ) ),
                this,				SLOT( UpdateDescription( QListWidgetItem* ) )		);

    connect( this, SIGNAL( accepted() ), this, SLOT( EmitSelection() ) );

    // Filling the dialog with metadata names
    foreach( QString name, m_Metadata.keys() )
    {
        ui.lwProperties->addItem( name );
    }
}


// Updates the description of the currently selected item
// whenever the user selects a new item
void AddMetadata::UpdateDescription( QListWidgetItem *current )
{
    QString text = m_Metadata.value( current->text() ).description;

    if ( text.isNull() != true )
    
        ui.lbDescription->setText( text );
}


// Emits the name of the metadata that
// should be added to the metadata table;
// should be called on accept signal
void AddMetadata::EmitSelection()
{
    emit MetadataToAdd( ui.lwProperties->currentItem()->text() );
}
