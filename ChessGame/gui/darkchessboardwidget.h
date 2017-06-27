#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QApplication>
#include "aspectratiopixmaplabel.h"
#include "idarkchessboardwidget.h"
#include <vector>
#include <QDrag>

using std::vector;

class ChessBoardPallete{
public:
    ChessBoardPallete():blackTileColor(QColor(153,76,0)),whiteTileColor(QColor(255,255,255)),
        moveTileColor(QColor(255,255,51)),attackTileColor(QColor(255,51,51)),hideTileColor(QColor(0,0,0)){}
    QColor blackTileColor,whiteTileColor,moveTileColor,attackTileColor,hideTileColor;
};

class DarkChessBoardWidget : public QWidget,public IDarkChessBoardWidget
{
    Q_OBJECT
public:
    explicit DarkChessBoardWidget(QWidget *parent = 0);

    virtual void setPieceAtTile(Piece piece,Tile tile);
    virtual void setPieceAtTile(TiledPiece piece);
    virtual Piece getPieceAtTile(Tile tile);
    virtual void removePieceAtTile(Tile tile);

    virtual void highlightAttackTile(Tile tile);
    virtual void highlightMoveTile(Tile tile);
    virtual void removeHighlightAtTile(Tile tile);
    virtual void removeAllHighlights();

    virtual void hideTile(Tile tile);
    virtual void showTile(Tile tile);
    virtual void showAllTiles();
    virtual void hideAllTiles();

    virtual void convertPiece(TiledPiece cp);
    virtual void hideConvert();

    void initChooseWidget();
    void setDirection(BoardDirection direct);
    BoardDirection getDirection();
    void setPalette(ChessBoardPallete cbp);
    ChessBoardPallete getPalette();

    virtual QSize sizeHint() const {
        return QSize(300, heightForWidth(300));
    }

    virtual int heightForWidth( int w )const {
        QApplication::postEvent(const_cast<DarkChessBoardWidget*>(this), new QEvent(QEvent::UpdateRequest));
        return w;
    }
private:
    void initLegend();
    void initTiles();
    size_t getTileIndex(Tile tile);

    QWidget *_chooseWidget;
    vector<AspectRatioPixmapLabel*> _tiles;
    vector<Piece> _pieces;
    vector<bool> _hideFlag;
    vector<char> _hightlightFlag;
    vector<QLabel*> _legendLabels;
    TiledPiece _convertPiece;
    BoardDirection _direction;
    ChessBoardPallete _palette;
    int _widthHeight=550,_legendHeight=10,_legendWidth=10;
    TiledPiece _lastHighlighted;

protected:
    void mousePressEvent(QMouseEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    bool eventFilter(QObject *target, QEvent *event);

signals:
    void pieceMoved(Piece piece,Tile from,Tile to);
    void pieceHover(Piece piece,Tile tile);
    void pieceConverted(TiledPiece piece,TiledPiece to);
private slots:
    void pieceChoosed();

};

#endif // CHESSBOARDWIDGET_H
