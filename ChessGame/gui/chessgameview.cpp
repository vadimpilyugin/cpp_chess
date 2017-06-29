#include "chessgameview.h"
#include "ui_chessgamewidget.h"
#include<QMessageBox>
#include "darkchessboardview.h"
#include "chessboardcontroller.h"

const size_t rowCount=8;
const size_t colCount=8;

ChessGameView::ChessGameView(ADarkChessGame *game, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessGameWidget),_acg(0)
{
    ui->setupUi(this);

    DarkChessBoardView *dcbv=new DarkChessBoardView(game,this);

    ui->horizontalLayout->addWidget(dcbv);

    _cbw=dcbv;

    _cbc=new ChessBoardController(dynamic_cast<AChessGame*>(game),this);

    QObject *bla=dynamic_cast<QObject*>(_cbw);
    connect(dynamic_cast<QObject*>(_cbw), SIGNAL(pieceMovedByPlayer(ChessColor,Piece,Tile,Tile)),dynamic_cast<QObject*>(_cbc), SLOT(sendMoveCommand(ChessColor,Piece,Tile,Tile)));
    connect(dynamic_cast<QObject*>(_cbw), SIGNAL(piecePromotedByPlayer(ChessColor,TiledPiece,TiledPiece)),dynamic_cast<QObject*>(_cbc), SLOT(sendPromoteCommand(ChessColor,TiledPiece,TiledPiece)));

    if(game){
        _acg=game;
        _acg->attachObserver(this);
        NetworkDarkChessGame *ndcg=dynamic_cast<NetworkDarkChessGame*>(_acg);
        if(ndcg)initPlayersFromNDCG(ndcg);
    }

    QObject::connect(ui->giveupButton,&QPushButton::released,this,&ChessGameView::giveUpButtonReleased);
    QObject::connect(ui->offerDrawButton,&QPushButton::released,this,&ChessGameView::offerDrawButtonReleased);
}

ChessGameView::~ChessGameView()
{    
    if(_acg!=0) _acg->detachObserver(this);
    delete ui;
}


void ChessGameView::update(AChessGame *game){
    if(game==0)game=_acg;
    if(game!=0){
        _log.addMove(game->getLastMove());
        ui->logLabel->setText(_log.logToString(_activePlayer).c_str());
        NetworkDarkChessGame *ndcg=dynamic_cast<NetworkDarkChessGame*>(_acg);
        if(ndcg)initPlayersFromNDCG(ndcg);

        if(_activePlayer!=ndcg->getOrderPlayer()){
            ui->giveupButton->setEnabled(false);
            ui->offerDrawButton->setEnabled(false);
            ui->playerNameLabel->setStyleSheet("font-weight:bold;color:rgb(0,0,0);");
            ui->opponentNameLabel->setStyleSheet("font-weight:bold;color:rgb(0,0,170);");
        }else{
            ui->giveupButton->setEnabled(true);
            ui->offerDrawButton->setEnabled(true);
            ui->playerNameLabel->setStyleSheet("font-weight:bold;color:rgb(0,0,170);");
            ui->opponentNameLabel->setStyleSheet("font-weight:bold;color:rgb(0,0,0);");
        }

        GameState state=game->getState();
        if((state==GameState::BlackVictory && _activePlayer==ChessColor::White) ||
               (state==GameState::WhiteVictory && _activePlayer==ChessColor::Black)){
            QMessageBox *mb=new QMessageBox(this);
            mb->setWindowTitle("Печалько");
            mb->setText("Вы проиграли((");
            mb->setInformativeText("Важно не то, проигрываем ли мы в игре, важно, как мы проигрываем и как мы благодаря этому изменимся, что нового вынесем для себя, как сможем применить это в других играх. Странным образом поражение оборачивается победой");
            mb->exec();
            emit gameEnded();
        }else if(state==GameState::Draw){
            QMessageBox *mb=new QMessageBox(this);
            mb->setWindowTitle("Ничья");
            mb->setText("Вы сыграли в ничью");
            mb->setInformativeText("Он так любил делать ничьи, что его прозвали шахпатистом");
            mb->exec();
            emit gameEnded();
        }else if( (_activePlayer==ChessColor::Black && state==GameState::WhiteGiveUp) ||
                  (_activePlayer==ChessColor::White && state==GameState::BlackGiveUp)){
            QMessageBox *mb=new QMessageBox(this);
            mb->setWindowTitle("Победа");
            mb->setText("Ваш соперник сдался");
            mb->setInformativeText("Поздравляю бравый рыцарь, соперник затрепетал перед вашим величие, обмочил штанишки и сдался!");
            mb->exec();
            emit gameEnded();
        }else if( (_activePlayer==ChessColor::Black && state==GameState::BlackGiveUp) ||
                  (_activePlayer==ChessColor::White && state==GameState::WhiteGiveUp)){
            QMessageBox *mb=new QMessageBox(this);
            mb->setWindowTitle("Поражение");
            mb->setText("Вы сдались");
            mb->setInformativeText("Важно не то, проигрываем ли мы в игре, важно, как мы проигрываем и как мы благодаря этому изменимся, что нового вынесем для себя, как сможем применить это в других играх. Странным образом поражение оборачивается победой");
            mb->exec();
            emit gameEnded();
        }else if((state==GameState::BlackVictory && _activePlayer==ChessColor::Black) ||
                 (state==GameState::WhiteVictory && _activePlayer==ChessColor::White)){
              QMessageBox *mb=new QMessageBox(this);
              mb->setWindowTitle("Победа");
              mb->setText("Вы победили соперника");
              mb->setInformativeText("Не проигрывает не тот, кто знает все варианты победы, а тот, кто знает все варианты поражения");
              mb->exec();
              emit gameEnded();
        }else if((state==GameState::BlackOfferDraw && _activePlayer==ChessColor::White) ||
            (state==GameState::WhiteOfferDraw && _activePlayer==ChessColor::Black)){
            Command *command;
            QMessageBox *mb=new QMessageBox(this);
            mb->setWindowTitle("Предложение ничьи");
            mb->setText("Ваш соперник предложил ничью. Желаете принять предложение?");
            mb->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            mb->setDefaultButton(QMessageBox::Ok);
            int ret = mb->exec();
            switch(ret){
            case QMessageBox::Ok:
                command=new AcceptDrawCommand();
                break;
            default:
                command=new RefuseDrawCommand();
                break;
            }
            command->playerColor=_activePlayer;
            if(_acg)_acg->doCommand(command);
            //delete command;
        }else if(state==GameState::Termination){
            QMessageBox *mb=new QMessageBox(this);
            mb->setWindowTitle("Аварийная ситуация");
            mb->setText("Игра аварийно завершилась");
            mb->exec();
            emit gameEnded();
        }
    }
}

void ChessGameView::setChessGameModel(AChessGame *game)
{
    if(_acg)_acg->detachObserver(this);
    _acg=game;
    if(_acg){
        _acg->attachObserver(this);
        update(_acg);
    }

}

AChessGame *ChessGameView::getChessGameModel()
{
    return _acg;
}

void ChessGameView::setActivePlayer(ChessColor player)
{
    _cbw->setActivePlayer(player);
    if(_player1.color!= ChessColor::None && _player2.color!=ChessColor::None){
        _activePlayer=player;
        Player activePlayer=(_player1.color == player) ?_player1 : _player2;
        Player inactivePlayer=(_player1.color == player) ?_player2 : _player1;
        ui->opponentNameLabel->setText(inactivePlayer.name.c_str());
        ui->playerNameLabel->setText(activePlayer.name.c_str());
    }
}

ChessColor ChessGameView::getActivePlayer()
{
    return _activePlayer;
}

void ChessGameView::setPlayers(Player player1, Player player2)
{
    return;
}

void ChessGameView::offerDrawButtonReleased()
{
    if(_acg && _activePlayer==_acg->getOrderPlayer()){
        OfferDrawCommand *odc=new OfferDrawCommand();
        odc->playerColor=_activePlayer;
        _acg->doCommand(odc);
    }
}

void ChessGameView::giveUpButtonReleased()
{
    if(_acg && _activePlayer==_acg->getOrderPlayer()){
        GiveUpCommand *guc=new GiveUpCommand();
        guc->playerColor=_activePlayer;
        _acg->doCommand(guc);
    }
}

void ChessGameView::initPlayersFromNDCG(NetworkDarkChessGame *ndcg)
{
    _player1=ndcg->getLocalPlayer();
    _player2=ndcg->getRemotePlayer();
    setActivePlayer(_player1.color);
}
