#include "darkchessboardwidget.h"
#include <QGridLayout>
#include <QDrag>
#include <QMimeData>
#include <QPushButton>
#include "types.h"


const size_t rowCount=8;
const size_t colCount=8;

bool isCorrectTile(Tile tile){
    return tile.x>=1 && tile.x<=colCount && tile.y>=1 && tile.y<=rowCount;
}

QPixmap getPixmapForPiece(PieceType type,PlayerColor color){
    if(color==PlayerColor::White){
        switch(type){
        case PieceType::Pawn:
            return QPixmap(":/Images/pawn_white.svg");
        case PieceType::Rook:
            return QPixmap(":/Images/rook_white.svg");
        case PieceType::Knight:
            return QPixmap(":/Images/knight_white.svg");
        case PieceType::King:
            return QPixmap(":/Images/king_white.svg");
        case PieceType::Queen:
            return QPixmap(":/Images/queen_white.svg");
        case PieceType::Bishop:
            return QPixmap(":/Images/bishop_white.svg");
        }
    }else{
        switch(type){
        case PieceType::Pawn:
            return QPixmap(":/Images/pawn_black.svg");
        case PieceType::Rook:
            return QPixmap(":/Images/rook_black.svg");
        case PieceType::Knight:
            return QPixmap(":/Images/knight_black.svg");
        case PieceType::King:
            return QPixmap(":/Images/king_black.svg");
        case PieceType::Queen:
            return QPixmap(":/Images/queen_black.svg");
        case PieceType::Bishop:
            return QPixmap(":/Images/bishop_black.svg");
        }
    }
    return QPixmap();
}

void translateCoord(int x,int y,BoardDirection from,BoardDirection to,int &toX,int &toY){
    toX=x;
    toY=y;
    bool fromBool[2];
    bool toBool[2];
    fromBool[0]=from==BoardDirection::TopLeft || from==BoardDirection::TopRight;
    fromBool[1]=from==BoardDirection::TopRight || from==BoardDirection::BottomRight;
    toBool[0]=to==BoardDirection::TopLeft || to==BoardDirection::TopRight;
    toBool[1]=to==BoardDirection::TopRight || to==BoardDirection::BottomRight;
    if(fromBool[0]!=toBool[0])
        toY=rowCount-y-1;
    if(fromBool[1]!=toBool[1])
        toX=colCount-x-1;
}

DarkChessBoardWidget::DarkChessBoardWidget(QWidget *parent) : QWidget(parent),_direction(BoardDirection::TopRight)
{
    QSizePolicy p(sizePolicy());
    p.setHeightForWidth(true);
    setSizePolicy(p);

    this->setFixedSize(550,550);

    setAcceptDrops(true);

    setMouseTracking(true);

    QGridLayout *layout=new QGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    initLegend();
    layout->setColumnMinimumWidth(0,20);
    layout->setColumnMinimumWidth(colCount+1,20);
    layout->setRowMinimumHeight(0,20);
    layout->setRowMinimumHeight(rowCount+1,20);

    initTiles();
    initChooseWidget();
}

void DarkChessBoardWidget::initLegend(){
    QGridLayout* gridLayout=qobject_cast<QGridLayout*>(layout());
    for(int i=0;i<_legendLabels.size();++i){
        gridLayout->removeWidget(_legendLabels[i]);
        delete _legendLabels[i];
    }
    _legendLabels.clear();

    for(size_t i=0;i<rowCount;++i){
        char letter[]="A";letter[0]+=i;
        char num[]="1";num[0]+=i;
        QLabel *lblLetter1=new QLabel(letter);
        QLabel *lblLetter2=new QLabel(letter);
        QLabel *lblNum1=new QLabel(num);
        QLabel *lblNum2=new QLabel(num);
        lblLetter1->setAlignment(Qt::AlignCenter);
        lblLetter2->setAlignment(Qt::AlignCenter);
        lblNum1->setAlignment(Qt::AlignCenter);
        lblNum2->setAlignment(Qt::AlignCenter);

        _legendLabels.push_back(lblLetter1);
        _legendLabels.push_back(lblLetter2);
        _legendLabels.push_back(lblNum1);
        _legendLabels.push_back(lblNum2);

        if(_direction==BoardDirection::BottomLeft || _direction==BoardDirection::BottomRight){
            gridLayout->addWidget(lblNum1,i+1,0);
            gridLayout->addWidget(lblNum2,i+1,rowCount+1);
        }else{
            gridLayout->addWidget(lblNum1,rowCount-i,0);
            gridLayout->addWidget(lblNum2,rowCount-i,rowCount+1);
        }
        if(_direction==BoardDirection::BottomLeft || _direction==BoardDirection::TopLeft){
            gridLayout->addWidget(lblLetter1,0,colCount-i);
            gridLayout->addWidget(lblLetter2,colCount+1,colCount-i);
        }else{
            gridLayout->addWidget(lblLetter1,0,i+1);
            gridLayout->addWidget(lblLetter2,colCount+1,i+1);
        }
    }
}

void DarkChessBoardWidget::initTiles(){
    _tiles.clear();
    _pieces.clear();
    _hightlightFlag.clear();
    _hideFlag.clear();

    QGridLayout* gridLayout=qobject_cast<QGridLayout*>(layout());

    Piece nonePiece;
    nonePiece.type=PieceType::None;
    nonePiece.color=PlayerColor::Black;
    _pieces.assign(rowCount*colCount,nonePiece);
    _hightlightFlag.assign(rowCount*colCount,0);
    _hideFlag.assign(rowCount*colCount,false);


    for(int i=0;i<rowCount;++i){
        for(int j=0;j<colCount;++j){
            AspectRatioPixmapLabel *tile=new AspectRatioPixmapLabel();
            tile->installEventFilter(this);
            //tile->setMouseTracking(true);
            QColor clr=((i+j)%2==0) ? _palette.blackTileColor : _palette.whiteTileColor;
            QString style=QString("QLabel { background-color : rgb(%1,%2,%3); }").arg(clr.red()).arg(clr.green()).arg(clr.blue());
            tile->setStyleSheet(style);
            tile->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            int jGrid,iGrid;
            translateCoord(j,i,BoardDirection::TopRight,_direction,jGrid,iGrid);
            translateCoord(jGrid,iGrid,BoardDirection::TopRight,BoardDirection::BottomRight,jGrid,iGrid);
            gridLayout->addWidget(tile,iGrid+1,jGrid+1);
            _tiles.push_back(tile);

        }
    }
}

size_t DarkChessBoardWidget::getTileIndex(Tile tile)
{
    return (tile.y-1)*colCount+tile.x-1;
}

void DarkChessBoardWidget::setPieceAtTile(Piece piece, Tile tile)
{
    if(!isCorrectTile(tile))return;
    size_t tileIndex=getTileIndex(tile);
    _pieces[tileIndex]=piece;
    if(!_hideFlag[tileIndex]){
        AspectRatioPixmapLabel* lbl= _tiles[tileIndex];
        if(piece.type!=PieceType::None){
            lbl->setPixmap(getPixmapForPiece(piece.type,piece.color));
        }else{
            QPixmap pixmap;
            lbl->setPixmap(pixmap);
        }
    }
}

void DarkChessBoardWidget::setPieceAtTile(TiledPiece piece){
    setPieceAtTile((Piece)piece,piece.place);
}

void DarkChessBoardWidget::removePieceAtTile(Tile tile){
    Piece piece;
    piece.type=PieceType::None;
    setPieceAtTile(piece,tile);
}

Piece DarkChessBoardWidget::getPieceAtTile(Tile tile){
    if(!isCorrectTile(tile))return Piece();
    size_t tileIndex=getTileIndex(tile);
    return _pieces[tileIndex];
}

void DarkChessBoardWidget::highlightAttackTile(Tile tile)
{
    if(!isCorrectTile(tile))return;
    size_t tileIndex=getTileIndex(tile);
    _hightlightFlag[tileIndex]=1;
    if(!_hideFlag[tileIndex]){
        AspectRatioPixmapLabel* lbl= _tiles[tileIndex];
        QColor clr=_palette.attackTileColor;
        QString style=QString("QLabel { background-color : rgb(%1,%2,%3); }").arg(clr.red()).arg(clr.green()).arg(clr.blue());
        lbl->setStyleSheet(style);
    }
}

void DarkChessBoardWidget::highlightMoveTile(Tile tile){
    if(!isCorrectTile(tile))return;
    size_t tileIndex=getTileIndex(tile);
    _hightlightFlag[tileIndex]=2;
    if(!_hideFlag[tileIndex]){
        AspectRatioPixmapLabel* lbl= _tiles[tileIndex];
        QColor clr=_palette.moveTileColor;
        QString style=QString("QLabel { background-color : rgb(%1,%2,%3); }").arg(clr.red()).arg(clr.green()).arg(clr.blue());
        lbl->setStyleSheet(style);
    }
}

void DarkChessBoardWidget::removeHighlightAtTile(Tile tile){
    if(!isCorrectTile(tile))return;
    size_t tileIndex=getTileIndex(tile);
    _hightlightFlag[tileIndex]=0;
    if(!_hideFlag[tileIndex]){
        AspectRatioPixmapLabel* lbl= _tiles[tileIndex];
        QColor clr=((tile.x+tile.y)%2==0) ? _palette.blackTileColor : _palette.whiteTileColor;
        QString style=QString("QLabel { background-color : rgb(%1,%2,%3); }").arg(clr.red()).arg(clr.green()).arg(clr.blue());
        lbl->setStyleSheet(style);
    }
}

void DarkChessBoardWidget::removeAllHighlights(){
    for(int i=0;i<rowCount;++i){
        for(int j=0;j<colCount;++j){
            Tile tile={j+1,i+1};
            removeHighlightAtTile(tile);
        }
    }
}

void DarkChessBoardWidget::hideTile(Tile tile)
{
    if(!isCorrectTile(tile))return;
    size_t tileIndex=getTileIndex(tile);
    _hideFlag[tileIndex]=true;
    AspectRatioPixmapLabel* lbl= _tiles[tileIndex];
    QColor clr=_palette.hideTileColor;
    QString style=QString("QLabel { background-color : rgb(%1,%2,%3); }").arg(clr.red()).arg(clr.green()).arg(clr.blue());
    lbl->setStyleSheet(style);
    lbl->hideImage();
}

void DarkChessBoardWidget::showTile(Tile tile)
{
    if(!isCorrectTile(tile))return;
    size_t tileIndex=getTileIndex(tile);
    _hideFlag[tileIndex]=false;
    AspectRatioPixmapLabel* lbl= _tiles[tileIndex];
    lbl->showImage();
    QColor clr;
    if(_hightlightFlag[tileIndex]!=0){
        clr=_hightlightFlag[tileIndex]==1 ? _palette.attackTileColor : _palette.moveTileColor;
    }else
        clr=((tile.x+tile.y)%2==0) ? _palette.blackTileColor : _palette.whiteTileColor;
    QString style=QString("QLabel { background-color : rgb(%1,%2,%3); }").arg(clr.red()).arg(clr.green()).arg(clr.blue());
    lbl->setStyleSheet(style);
}

void DarkChessBoardWidget::showAllTiles()
{
    for(int i=0;i<colCount;++i){
        for(int j=0;j<rowCount;++j){
            Tile tile={j+1,i+1};
            showTile(tile);
        }
    }
}

void DarkChessBoardWidget::hideAllTiles(){
    for(int i=0;i<colCount;++i){
        for(int j=0;j<rowCount;++j){
            Tile tile={j+1,i+1};
            hideTile(tile);
        }
    }
}

void DarkChessBoardWidget::convertPiece(TiledPiece cp)
{
    _convertPiece=cp;
    _chooseWidget->setGeometry(0,0,this->width(),this->height());
    int buttonSize=(this->width()-10)/2;
    for(int i=0;i<_chooseWidget->layout()->count();++i){
        QPushButton *pb=qobject_cast<QPushButton*>(_chooseWidget->layout()->itemAt(i)->widget());
        PieceType pt;
        QString pieceType=pb->property("PieceType").value<QString>();
        if(pieceType=="Q")pt=PieceType::Queen;
        else if(pieceType=="K")pt=PieceType::Knight;
        else if(pieceType=="R")pt=PieceType::Rook;
        else if(pieceType=="B")pt=PieceType::Bishop;
        pb->setIcon(QIcon(getPixmapForPiece(pt,cp.color)));
        pb->setIconSize(QSize(buttonSize,buttonSize));
    }
    _chooseWidget->show();
}

void DarkChessBoardWidget::initChooseWidget()
{
    _chooseWidget=new QWidget(this);
    _chooseWidget->hide();
    //_chooseWidget->setWindowOpacity(0.5);
    QString opaqueSetting="QPushButton{background-color: rgba(200, 200, 200, 50%);} QPushButton:hover{background-color: rgba(200, 200, 200, 90%);}";
    QGridLayout *layout=new QGridLayout(_chooseWidget);
    QPushButton *pb1=new QPushButton(0);
    pb1->setProperty("PieceType",QString("Q"));
    pb1->setStyleSheet(opaqueSetting);
    QPushButton *pb2=new QPushButton(0);
    pb2->setProperty("PieceType",QString("K"));
    pb2->setStyleSheet(opaqueSetting);
    QPushButton *pb3=new QPushButton(0);
    pb3->setProperty("PieceType",QString("R"));
    pb3->setStyleSheet(opaqueSetting);
    QPushButton *pb4=new QPushButton(0);
    pb4->setProperty("PieceType",QString("B"));
    pb4->setStyleSheet(opaqueSetting);
    layout->addWidget(pb1,0,0);
    layout->addWidget(pb2,0,1);
    layout->addWidget(pb3,1,0);
    layout->addWidget(pb4,1,1);

    QObject::connect(pb1,QPushButton::released,this,DarkChessBoardWidget::pieceChoosed);
    QObject::connect(pb2,QPushButton::released,this,DarkChessBoardWidget::pieceChoosed);
    QObject::connect(pb3,QPushButton::released,this,DarkChessBoardWidget::pieceChoosed);
    QObject::connect(pb4,QPushButton::released,this,DarkChessBoardWidget::pieceChoosed);
}

void DarkChessBoardWidget::setDirection(BoardDirection direct)
{
    _direction=direct;
    initLegend();
    QGridLayout* gridLayout=qobject_cast<QGridLayout*>(layout());
    for(int i=0;i<rowCount;++i){
        for(int j=0;j<colCount;++j){
            AspectRatioPixmapLabel *tile=_tiles[i*colCount+j];
            int jGrid,iGrid;
            translateCoord(j,i,BoardDirection::TopRight,_direction,jGrid,iGrid);
            translateCoord(jGrid,iGrid,BoardDirection::TopRight,BoardDirection::BottomRight,jGrid,iGrid);
            gridLayout->addWidget(tile,iGrid+1,jGrid+1);
            _tiles.push_back(tile);
        }
    }
}

BoardDirection DarkChessBoardWidget::getDirection()
{
    return _direction;
}

void DarkChessBoardWidget::setPalette(ChessBoardPallete cbp){_palette=cbp;}

ChessBoardPallete DarkChessBoardWidget::getPalette(){return _palette;}

void DarkChessBoardWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->source() == this) {
        event->acceptProposedAction();
    }
}

void DarkChessBoardWidget::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        AspectRatioPixmapLabel *child = qobject_cast<AspectRatioPixmapLabel*>(childAt(event->pos()));
        QGridLayout* gridLayout=qobject_cast<QGridLayout*>(layout());

        if(gridLayout==0 || child==0)return;

        int row,col,temp1,temp2;
        gridLayout->getItemPosition(gridLayout->indexOf(child),&row,&col,&temp1,&temp2);
        int xcoord,ycoord;
        translateCoord(col-1,row-1,BoardDirection::BottomRight,_direction,xcoord,ycoord);

        if(xcoord*colCount+ycoord<_pieces.size())return;
        Piece piece=_pieces[xcoord*colCount+ycoord];
        if(piece.type!=PieceType::None && !child->isHidden()){
            QPixmap pixmap = *child->pixmap();
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;
            QString str=(pieceTypeToString(piece.type)+","+playerColorToString(piece.color)+",").c_str()+QString::number(xcoord)+","+QString::number(ycoord);
            mimeData->setText(str);
            drag->setMimeData(mimeData);
            drag->setPixmap(pixmap);
            drag->setHotSpot(event->pos() - child->pos());
            drag->exec(Qt::MoveAction);
        }
    }
}

void DarkChessBoardWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->source() == this) {
        event->acceptProposedAction();
    }
}

void DarkChessBoardWidget::dropEvent(QDropEvent *event)
{
    if (event->source() == this) {
        QGridLayout* gridLayout=qobject_cast<QGridLayout*>(layout());
        int row=0,col=0,bla1=0,bla2=0;
        gridLayout->getItemPosition(gridLayout->indexOf(childAt(event->pos())),&row,&col,&bla1,&bla2);
        if(row>=1 && col>=1 && row<=1+rowCount && col<=1+colCount){
            int xcoord=0,ycoord=0;
            translateCoord(col-1,row-1,BoardDirection::BottomRight,_direction,xcoord,ycoord);
            QString text=event->mimeData()->text();
            QStringList strData=text.split(",");
            Piece piece;
            piece.type=stringToPieceType(strData[0].toStdString());
            piece.color=stringToPlayerColor(strData[1].toStdString());

            Tile from;
            from.x=strData[2].toInt();
            from.y=strData[3].toInt();

            Tile to={xcoord,ycoord};

            emit this->pieceMoved(piece,from,to);
        }
    }
}

void DarkChessBoardWidget::mouseMoveEvent(QMouseEvent *event){
    QLabel *child = qobject_cast<QLabel*>(childAt(event->pos()));
    QGridLayout* gridLayout=qobject_cast<QGridLayout*>(layout());


    if(child==0 || gridLayout==0 || event->buttons()!=Qt::NoButton)return;

    int row,col,temp1,temp2;
    gridLayout->getItemPosition(gridLayout->indexOf(child),&row,&col,&temp1,&temp2);
    if(row<1 || row>rowCount || col<1 || col>colCount)return;
    translateCoord(col-1,row-1,BoardDirection::BottomRight,_direction,col,row);

    Piece piece=_pieces[col*colCount+row];
    Tile tile={col,row};
    if(piece.type!=PieceType::None)
        emit this->pieceHover(piece,tile);
}

bool DarkChessBoardWidget::eventFilter(QObject *target, QEvent *event)
{
    if(event->type()==QEvent::MouseMove){
        mouseMoveEvent((QMouseEvent*)(event));
    }
    return false;
}

void DarkChessBoardWidget::pieceChoosed()
{
    QPushButton *pb=qobject_cast<QPushButton*>(QObject::sender());
    _chooseWidget->hide();
    if(pb){
        PieceType pt;
        QString pieceType=pb->property("PieceType").value<QString>();
        if(pieceType=="Q")pt=PieceType::Queen;
        else if(pieceType=="K")pt=PieceType::Knight;
        else if(pieceType=="R")pt=PieceType::Rook;
        else if(pieceType=="B")pt=PieceType::Bishop;
        TiledPiece tpt;
        tpt.color=_convertPiece.color;
        tpt.type=pt;
        tpt.place=_convertPiece.place;
        emit this->pieceConverted(_convertPiece,tpt);
    }
}
