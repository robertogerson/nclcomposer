#ifndef QNST_H
#define QNST_H

class Qnst
{
public:
    enum EntityType {
        Node,

        Content,
        Media,
        Image,
        Audio,
        Video,
        Html,
        NCL,
        Text,
        Script,
        Settings,
        Aggregator,

        Compostion,
        Body,
        Context,
        Switch,

        Interface,
        Port,
        Area,
        SwitchPort,
        Property,

        Edge,
        Reference,
        Link,
        Mapping,
        Condition,
        Action,
        Bind,

        NoType
    };

    enum ConditionType {
        onBegin,
        onSelectiononBegin,
        onEnd,
        onSelection,
        onResume,
        onPause,

        NoConditionType
    };

    enum ActionType {
        Start,
        Stop,
        Resume,
        Pause,
        Set,

        NoActionType
    };
};

#endif // QNST_H
