/*
    This file is part of QuickQanava library.

    Copyright (C) 2008-2017 Benoit AUTHEMAN

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//-----------------------------------------------------------------------------
// This file is a part of the QuickQanava software library.
//
// \file	qanGraphView.cpp
// \author	benoit@destrat.io
// \date	2016 08 15
//-----------------------------------------------------------------------------

// Qt headers
#include <QQuickItem>

// QuickQanava headers
#include "./qanNavigable.h"
#include "./qanGraphView.h"
#include "./qanGraph.h"

namespace qan { // ::qan

/* GraphView Object Management *///--------------------------------------------
GraphView::GraphView( QQuickItem* parent ) :
    qan::Navigable{ parent }
{
    setAntialiasing( true );
    setSmooth( true );
}

void    GraphView::setGraph( qan::Graph* graph )
{
    if ( graph == nullptr ) {
        qWarning() << "qan::GraphView::setGraph(): Error: Setting a nullptr graph in Qan.GraphView is not supported.";
        return;
    }
    if ( graph != _graph ) {
        if ( _graph != nullptr )
            disconnect(_graph, 0, this, 0 );
        _graph = graph;
        _graph->setContainerItem( getContainerItem() );
        connect( _graph, &qan::Graph::nodeClicked,
                 this,   &qan::GraphView::nodeClicked );

        connect( _graph, &qan::Graph::connectorChanged,
                 this,   &qan::GraphView::connectorChanged );
        connect( _graph, &qan::Graph::nodeRightClicked,
                 this,   &qan::GraphView::nodeRightClicked );
        connect( _graph, &qan::Graph::nodeDoubleClicked,
                 this,   &qan::GraphView::nodeDoubleClicked );
        connect( _graph, &qan::Graph::edgeClicked,
                 this,   &qan::GraphView::edgeClicked );
        connect( _graph, &qan::Graph::edgeRightClicked,
                 this,   &qan::GraphView::edgeRightClicked );
        connect( _graph, &qan::Graph::edgeDoubleClicked,
                 this,   &qan::GraphView::edgeDoubleClicked );
        connect( _graph, &qan::Graph::groupClicked,
                 this,   &qan::GraphView::groupClicked );
        connect( _graph, &qan::Graph::groupRightClicked,
                 this,   &qan::GraphView::groupRightClicked );
        connect( _graph, &qan::Graph::groupDoubleClicked,
                 this,   &qan::GraphView::groupDoubleClicked );
        emit graphChanged();
    }
}

void    GraphView::navigableClicked(QPointF pos)
{
    Q_UNUSED(pos);
    if ( _graph )
        _graph->clearSelection();
}
//-----------------------------------------------------------------------------

} // ::qan

