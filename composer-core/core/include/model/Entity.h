#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QMap>
#include <QUuid>
#include <QDebug>

namespace composer{
    namespace core {
        class MessageControl;
        class ProjectReader;

        namespace model {
            class Project;
} } } //end namespace

namespace composer {
    namespace core {
        namespace model {
/*!
 * \brief An Entity is the main class of the internal Composer core.
 *
 * The internal model Composer model is a tree of Entities.
 */
class Entity : public QObject
{
    Q_OBJECT

    // The following classes are "reliable" and can acess the
    // private and protected members of Entity.
    friend class composer::core::model::Project;
    friend class composer::core::MessageControl;
    friend class composer::core::ProjectReader;

private:
    QMutex lockAtts;
    QMutex lockID;
    QMutex lockType;
    QMutex lockChildren;
    QMutex lockParent;
    QString _id;
    QString type;
    Entity* parent;
    bool deleteChildren; /* initial value is true */
    QVector <Entity*> children;
    /*!
     * \brief This <map> represents the attributes of the element
     *   the Key is the name of the attribute and Value is the value of that
     *   attribute.
     */
    QMap<QString, QString> atts;

protected:
    /*!
     * \brief Constructor.
     *
     * \param parent The QObject parent.
     */
    explicit Entity(QObject *parent = 0);
    /*!
     * \brief Constructor.
     *
     * \param atts attributes to be set to this Entity.
     * \param parent the QObject parent.
     */
    explicit Entity(QMap<QString,QString> &atts, QObject *parent = 0);
    /*!
     * \brief Contructor.
     *
     * \param uniqueId the uniqueId of this Entiy.
     * \param atts attributes to be set to this Entity.
     * \param parent the QObject parent.
     */
    explicit Entity(QString uniqueId, QMap<QString,QString> &atts,
                    QObject *parent = 0);

    /*!
     * \brief Destructor.
     */
    ~Entity();
    /*!
     * \brief This method is used to set an specific attribute of the element
     *
     * \param name - The name of the attribute to be set
     * \param value - The value this attribute is going to be set
     */
    void setAttribute(QString name, QString value);

    /*!
     * \brief Set the attributes of the current entity to the value passed as
     *      parameter.
     *
     * \param newAtts the new value of entity's attributes.
     */
    void setAtrributes(QMap<QString,QString> &newatts);

    /*!
     * \brief Set the entity's type to the value passed as parameter.
     *
     * \param type The type of the entity.
     */
    void setType(QString type);

    /*!
     *  \brief Set the unique identifier of the entity to the value passed as
     *      parameter.
     *
     * \param _id The new uniqueId of the entity.
     */
    void setUniqueID(QString uniqueId);

    /*!
     * \brief Set the parent of the Entity.
     *
     * \param parent The new parent of this Entity.
     */
    void setParent(Entity *parent);

    //OBS: This addChild updates the parent referency
    bool addChild(Entity *entity);
    /*!
     * \brief This call deletes the child and his children in a recursive way.
     *
     * \param entity The Entity child to be removed.
     */
    bool deleteChild(Entity *entity);
    /*!
     * \brief This call removes the child and append his children to his parent.
     *
     * \param entity
     */
    bool removeChildAppendChildren(Entity *entity);
    /*!
     * \brief
     */
    void print();
    /*!
     * \brief Convert the current Entity to a XML String.
     *
     * \param ntabs the number of tabs to be inserted before the current entity.
     */
    QString toString(int ntabs);

public:
    /*!
     * \brief This method is used to get an specific attribute of the element.
     *
     * \param name - The name of the attribute been requested
     * \return A string with the requested attribute.
     */
    QString getAttribute(QString name);
    /*!
     * This method is used to get the iterator in the <map> of attributes.
     *
     * \param begin - a reference to be filled with the begin of the map.
     * \param end - a reference to be filled with the end of the map.
     */
    void getAttributeIterator (QMap<QString,QString>::iterator &begin,
                               QMap<QString,QString>::iterator &end);
    /*!
     * \brief This method is used to verify if this element has certain
     *      attribute.
     *
     * \param name - The name of the attribute to be verified.
     * \return an boolean depending of the existence of the attribute.
    */
    bool hasAttribute(const QString &name);

    QString getUniqueId();

    QString getType();

    Entity* getParent();

    QString getParentUniqueId();
    /*!
     * \brief Tell if the children should be deleted when this entity is deleted
     *          through destructor.
     *
     * \param mustDelete tell if the children also must be deleted.
     */
    void setDeleteChildren(bool mustDelete);

    QVector <Entity *> getChildren();

};
        }
    }
}

#endif // ENTITY_H
