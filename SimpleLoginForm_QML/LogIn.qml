import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQuick.Controls.Material 2.12
import Database 2.12

Item {
    id: root;
    anchors.fill: parent;
    Image {
        id: backgroundimage;
        anchors.centerIn: parent;
        source: "qrc:/images/background.jpg";
        //        scale: 0.8;
    }
    FastBlur{
        id: fastblur;
        anchors.fill: backgroundimage;
        source: backgroundimage;
    }
    NumberAnimation {
        running: true;
        from: 0;
        to: 40;
        property: "radius";
        duration: 1500;
        easing.type: Easing.InOutQuad;
        targets: fastblur;
    }

    Image{
        id: parli;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 110;
        source: "qrc:/images/parli.png";
        scale: 0.55;
        opacity: 0.9;
    }

    Label{
        id: label
        text: "Please Enter Your Information For Loging In:";
        color: "#9E9E9E";
        font.bold: true;
        font.pointSize: 15;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 300;
    }

    TextField{
        id: username;
        placeholderText: "username";
        color: "#9E9E9E";
        font.bold: true;
        font.pointSize: 15;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;

        onTextChanged: {
            var pattern = /[^a-z0-9_@.]/;
            if(pattern.test(text)){
                valid1.text="Invalid username!";
                flag=false;
            }
            else valid1.text="";

            if(text.length===0){
                valid1.text="This field can't be empty!";
            }
        }
    }
    Label{
        id: valid1;
        color: "black";
        font.pointSize: 11;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: username.bottom;
    }

    TextField{
        id: password;
        placeholderText: "password";
        color: "#9E9E9E";
        font.bold: true;
        font.pointSize: 15;
        echoMode: "Password";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: username.bottom;
        anchors.topMargin: 50;
    }

    Button{
        id: submit;
        text: "Submit";
        width: 100;
        font.bold: true;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
        Material.background: Material.color(Material.Indigo,Material.ShadeA700);

        onClicked: {
            if(username.text!=="" && password.text!=="" && valid1.text===""){
                var ok;
                ok=mysql.checkuser(username.text);
                if(ok && password.text===mysql.passwordd())
                    apploader.sourceComponent=homepage;
                else{
                    errorlabel.text="User NOT Exists OR Password Wrong!!!";
                    error.open();
                }
            }
            else{
                errorlabel.text="Please Check Your Inputs!!!";
                error.open();
            }
        }
    }

    NumberAnimation {
        running: true;
        targets: [username,password];
        property: "width";
        from: 0;
        to: 250;
        duration: 3000;
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        running: true;
        targets: username;
        property: "anchors.topMargin";
        from: 0;
        to: 480;
        duration: 2000;
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        running: true;
        targets: label;
        property: "anchors.topMargin";
        from: 0;
        to: 300;
        duration: 1000;
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        running: true;
        targets: submit;
        property: "anchors.bottomMargin";
        from: 0;
        to: 90;
        duration: 2500;
        easing.type: Easing.InOutQuad
    }

    Database{
        id: mysql;
    }

    Dialog{
        id: error;
        anchors.centerIn: parent;
        width: parent.width/1.5;
        title: "Warning";
        Material.background: Material.Indigo;
        Label{
            id: errorlabel;
            font.bold: true;
            font.pointSize: 12;
        }
    }
}
