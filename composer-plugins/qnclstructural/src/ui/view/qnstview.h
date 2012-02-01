#ifndef QNSTVIEW_H
#define QNSTVIEW_H

#include <QGraphicsView>
#include <QVector>
#include <QMap>
#include <QDomDocument>
#include <QDomElement>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QWheelEvent>
#include <QSet>
#include <QUndoStack>
#include <QDir>

#include <QDebug>

#include "qnstscene.h"
#include "qnstviewlink.h"
#include "qnstgraphicsentity.h"
#include "qnstgraphicsbody.h"
#include "qnstgraphicscontext.h"
#include "qnstgraphicsswitch.h"
#include "qnstgraphicsmedia.h"
#include "qnstgraphicsport.h"
#include "qnstgraphicsreference.h"
#include "qnstgraphicslink.h"
#include "qnstgraphicslinkdialog.h"
#include "qnstgraphicsconditiondialog.h"
#include "qnstgraphicsactiondialog.h"
#include "qnstgraphicscondition.h"
#include "qnstgraphicsaction.h"
#include "qnstconncetor.h"
#include "qnstlink.h"
#include "qnstbind.h"
#include "qnstgraphicsproperty.h"
#include "qnstgraphicsarea.h"
#include "qnstaddcommand.h"
#include "qnstchangecommand.h"
#include "qnstremovecommand.h"
#include "qnstgraphicsmapping.h"

class QnstAddCommand;

class QnstView : public QGraphicsView
{
    Q_OBJECT

public:
    QnstView(QWidget* parent = 0);

    ~QnstView();

    void load(QString data);

    QString serialize();

    void read(QDomElement element, QDomElement parent);

    void readLink(QDomElement element, QDomElement parent);

    void write(QDomElement element, QDomDocument* dom, QnstGraphicsEntity* entity);

    void writeLink(QDomElement element, QDomDocument* dom, QnstGraphicsEntity* entity);

public:
    void addEntity(const QString uid, const QString parent, const QMap<QString, QString> properties);

    void removeEntity(const QString uid, bool undo = false);

    void changeEntity(const QString uid, const QMap<QString, QString> properties);

    void selectEntity(const QString uid);

    QMap<QString, QnstGraphicsEntity*> entities;

public slots:
    void performHelp();

    void performUndo();

    void performRedo();

    void performCut();

    void performCopy();

    void performPaste();

    void performDelete();

    void performExport();

    void performZoomIn();

    void performZoomOut();

    void performZoomReset();

    void performFullscreen();

    void performBringfront();

    void performBringforward();

    void performSendback();

    void performSendbackward();

    void performHide();

    void performProperties();

signals:
    void entityAdded(const QString uid, const QString parent, const QMap<QString, QString> properties);

    void entityChanged(const QString uid, const QMap<QString, QString> properties);

    void entityRemoved(const QString uid);

    void entitySelected(const QString uid);

protected:
    virtual void mouseMoveEvent(QMouseEvent* event);

    virtual void mousePressEvent(QMouseEvent* event);

    virtual void mouseReleaseEvent(QMouseEvent*event);

    virtual void keyPressEvent(QKeyEvent *event);

    virtual void keyReleaseEvent(QKeyEvent *event);

    void wheelEvent(QWheelEvent * event);

public slots:
    void requestEntityAddition(QnstGraphicsEntity* entity, bool undo = false);

    void requestEntityRemotion(QnstGraphicsEntity* entity, bool undo = false);

    void requestEntityChange(QnstGraphicsEntity* entity);

    void requestEntityPreparation(QnstGraphicsEntity* entity, QMap<QString, QString> properties);

    void requestEntitySelection(QnstGraphicsEntity* entity);

private:
    void addBody(const QString uid, const QString parent, const QMap<QString, QString> properties, bool undo = false);

    void changeBody(QnstGraphicsBody* entity, const QMap<QString, QString> properties);

    void addImportBase(const QMap<QString, QString> properties);

    void changeImportBase(const QMap<QString, QString> properties);

    void addContext(const QString uid, const QString parent, const QMap<QString, QString> properties, bool undo = false);

    void changeContext(QnstGraphicsContext* entity, const QMap<QString, QString> properties);

    void adjustContext(QnstGraphicsContext* entity);

    void addSwitch(const QString uid, const QString parent, const QMap<QString, QString> properties, bool undo = false);

    void changeSwitch(QnstGraphicsSwitch* entity, const QMap<QString, QString> properties);

    void addMedia(const QString uid, const QString parent, const QMap<QString, QString> properties, bool undo = false);

    void changeMedia(QnstGraphicsMedia* entity, const QMap<QString, QString> properties);

    void adjustMedia(QnstGraphicsMedia* entity);

    void addPort(const QString uid, const QString parent, const QMap<QString, QString> properties, bool undo = false);

    void changePort(QnstGraphicsPort* entity, const QMap<QString, QString> properties);

    void adjustPort(QnstGraphicsPort* entity);

    void addArea(const QString uid, const QString parent, const QMap<QString, QString> properties, bool undo = false);

    void changeArea(QnstGraphicsArea* entity, const QMap<QString, QString> properties);

    void addProperty(const QString uid, const QString parent, const QMap<QString, QString> properties, bool undo = false);

    void changeProperty(QnstGraphicsProperty* entity, const QMap<QString, QString> properties);

    void addLink(const QString uid, const QString parent, const QMap<QString, QString> properties);

    void changeLink(QnstLink* entity, const QMap<QString, QString> properties);

    void adjustLink(QnstLink* entity);

    void addBind(const QString uid, const QString parent, const QMap<QString, QString> properties);

    void changeBind(QnstBind* entity, const QMap<QString, QString> properties);

    void adjustBind(QnstBind* entity);

    void addConnector(const QString uid, const QString parent, const QMap<QString, QString> properties);

    void changeConnector(QnstConncetor* entity, const QMap<QString, QString> properties);

    void addCondition(const QString uid, const QString parent, const QMap<QString, QString> properties);

    void changeCondition(QString condition, const QMap<QString, QString> properties);

    void addAction(const QString uid, const QString parent, const QMap<QString, QString> properties);

    void changeAction(QString condition, const QMap<QString, QString> properties);

    void adjustConnector(QnstConncetor* entity);

    void addAggregator(const QString uid, const QString parent, const QMap<QString, QString> properties, bool undo = false);

    void requestBodyAddition(QnstGraphicsBody* entity);

    void requestBodyChange(QnstGraphicsBody* entity);

    void requestContextAddition(QnstGraphicsContext* entity, bool undo = false);

    void requestContextChange(QnstGraphicsContext* entity);

    void requestSwitchAddition(QnstGraphicsSwitch* entity, bool undo = false);

    void requestSwitchChange(QnstGraphicsSwitch* entity);

    void requestMediaAddition(QnstGraphicsMedia* entity, bool undo = false);

    void requestMediaChange(QnstGraphicsMedia* entity);

    void requestAggregatorAddition(QnstGraphicsAggregator* entity);

    void requestPortAddition(QnstGraphicsPort* entity, bool undo = false);

    void requestPortChange(QnstGraphicsPort* entity);

    void requestMappingAddition(QnstGraphicsMapping* entity, bool undo = false);

    void requestMappingChange(QnstGraphicsMapping* entity);

    void requestSwitchPortAddition(QnstGraphicsSwitchPort* entity, bool undo = false);

    void requestSwitchPortChange(QnstGraphicsSwitchPort* entity);

    void requestAreaAddition(QnstGraphicsArea* entity, bool undo = false);

    void requestAreaChange(QnstGraphicsArea* entity);

    void requestPropertyAddition(QnstGraphicsProperty* entity);

    void requestPropertyChange(QnstGraphicsProperty* entity);

    void performCopy(QnstGraphicsEntity* entity, QnstGraphicsEntity* parent);

    void performPaste(QnstGraphicsEntity* copy, QnstGraphicsEntity* parent);

    void createObjects();

    void createConnection();

    void readImportBase(QDomElement e, const QString alias);

    void readConnector(QDomElement e, QnstConncetor* conn);

    void addNodetoNodeEdge(QnstGraphicsEntity* entitya, QnstGraphicsEntity* entityb);

    void addNodetoInterfaceEdge(QnstGraphicsEntity* entitya, QnstGraphicsEntity* entityb);

    void addInterfacetoNodeEdge(QnstGraphicsEntity* entitya, QnstGraphicsEntity* entityb);

    void addInterfacetoInterfaceEdge(QnstGraphicsEntity* entitya, QnstGraphicsEntity* entityb);

    int ncontext;

    int nswitch;

    int nport;

    int nmedia;

    int nlink;

    int nproperty;

    int narea;

    bool modified;

    bool linking;

    int zoomStep;

    QAction* undoAct;

    QAction* redoAct;

    QnstScene* scene;

    QnstViewLink* link;

    QnstGraphicsLinkDialog* linkDialog;

    QnstGraphicsConditionDialog* conditionDialog;

    QnstGraphicsActionDialog* actionDialog;

    QnstGraphicsEntity* selected;

    QnstGraphicsEntity* clipboard;

    QSet<QString> linkWriterAux;

    QMap<QString, QnstLink*> links;

    QMap<QString, QnstBind*> binds;

    QMap<QString, QString> brelations;

    QMap<QString, QString> link2conn;

    QMap<QString, QString> refers;

    QMap<QString, QnstConncetor*> connectors2;

    QMap<QString, QnstConncetor*> connectors;

    QUndoStack history;
};

#endif // QNSTVIEW_H
