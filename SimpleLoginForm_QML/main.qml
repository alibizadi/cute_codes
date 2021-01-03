import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import Database 2.12

ApplicationWindow {
    id: window;
    visible: true;
    width: Screen.width;
    height: Screen.height;
    title: qsTr("Hello World");

    EntryScene{
        id: entry;
        anchors.fill: parent;

        onLoginClicked: {apploader.sourceComponent=loginpage; visible=false;}
        onSignupClicked: {apploader.sourceComponent=signuppage; visible=false;}
    }

    Loader{
        id: apploader;
        anchors.fill: parent;
    }

    Component{
        id: loginpage;
        LogIn{

        }
    }

    Component{
        id: signuppage;
        SignUp{

        }
    }

    Component{
        id: homepage;
        HomePage{

        }
    }
}
