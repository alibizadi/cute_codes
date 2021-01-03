import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    signal loginClicked();
    signal signupClicked();

    anchors.fill: parent;

    Image{
        anchors.centerIn: parent;
        source: "qrc:/images/background.jpg";
        //        scale: 0.8;
    }

    Image{
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 110;
        source: "qrc:/images/parli.png";
        scale: 0.55;
        opacity: 0.9;
    }

    Button{
        id: login;
        text: "Log In";
        font.bold: true;
        font.pointSize: 20;
        width: 200;
        height: 80;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 440;
        Material.background: Material.color(Material.Indigo,Material.ShadeA700);
        opacity: 0.7;

        onClicked: loginClicked();
    }
    Button{
        id: signup;
        text: "Sign Up";
        font.bold: true;
        font.pointSize: 20;
        width: 200;
        height: 80;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: login.bottom;
        anchors.topMargin: 20;
        Material.background: Material.color(Material.DeepOrange,Material.ShadeA700);
        opacity: 0.7;

        onClicked: signupClicked();
    }
}
