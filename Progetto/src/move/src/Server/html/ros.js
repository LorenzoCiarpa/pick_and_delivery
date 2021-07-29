  var provasl="";
  var stanzaLog = "stanza";
  var stanzaInviato = "altrastanza";
  var chiamato = false;
  var presente =false;
  var name;
  var surname;
function accedi(){
    name = document.getElementsByName('name')[0].value;
    surname = document.getElementsByName('surname')[0].value;
    var stanza;
    var cnt=0;
    var giusta;
    stanza = document.getElementsByName("stanza");
    for (var i=0; i<stanza.length;i++) {
        if (stanza[i].checked) {
            cnt+=1;
            if (cnt==1) {
                giusta = stanza[i];
            }
            console.log(stanza[i].value);
        }
    }
    if (cnt==0) {
        alert("Scegliere almeno una stanza in cui fare l'accesso");
        return false;
    }
    if (cnt>1) {
        alert("Scegliere solo una stanza in cui fare l'accesso");
        return false;
    }
    if(cnt==1){
        provasl=giusta.value;

        var command="1:"+provasl;
        twist.data=command;
        html_to_master.publish(twist);
      }
  }



function spedisci(){
  var stanza;
  var cnt=0;
  var giusta;
  stanza = document.getElementsByName("stanza2");
  for (var i=0; i<stanza.length;i++) {
      if (stanza[i].checked) {
          cnt+=1;
          if (cnt==1) {
              giusta = stanza[i];
          }
          console.log(stanza[i].value);
      }
  }
  if (cnt==0) {
      alert("Scegliere almeno una stanza in cui spedire il pacco");
      return false;
  }
  if (cnt>1) {
      alert("Scegliere solo una stanza in cui in cui spedire il pacco");
      return false;
  }
  else {
    stanzaInviato=giusta.value;
    var command="3:"+stanzaLog+":"+stanzaInviato;
    twist.data=command;
    html_to_master.publish(twist);

  }

}
function richiamaRobot() {
    attesaRobot();
    chiamato=true;
    var command="2:"+stanzaLog;
    twist.data=command;
    html_to_master.publish(twist);
}

function attesaRobot() {
    document.getElementById("attesa").innerHTML = '<h3> Attendi che il robot arrivi o che sia disponibile... <br>Immetti il pacco sul ROBOT e seleziona la destinazione del pacco da spedire </h3>';
    setTimeout(() => {
        document.getElementById("attesa").innerHTML = '<h3> Immetti il pacco sul ROBOT e seleziona la destinazione del pacco da spedire </h3>';
      },10000);

}




  var ros = new ROSLIB.Ros({
    url : 'ws://localhost:9090'
  });

  ros.on('connection', function() {
    console.log('Connected to websocket server.');
  });

  ros.on('error', function(error) {
    console.log('Error connecting to websocket server: ', error);
  });

  ros.on('close', function() {
    console.log('Connection to websocket server closed.');
  });

  // Publishing a Topic
  // ------------------

  var html_to_master = new ROSLIB.Topic({
    ros : ros,
    name : '/html_to_master',
    messageType : 'std_msgs/String'
  });

  var twist = new ROSLIB.Message({
    data : "1:Sala studio"
      });
  //html_to_master.publish(twist);

  // Subscribing to a Topic
  // ----------------------

  var listener = new ROSLIB.Topic({
    ros : ros,
    name : '/master_to_html',
    messageType : 'std_msgs/String'
  });

  listener.subscribe(function(message) {
    //console.log('Received message on ' + listener.name + ': ' + message.data);
    var tokens= message.data.split(":");
    if(tokens.length!=3) return console.log("lunghezza !=3!!!!!!!!!!!!");;
    var command = tokens[0];
    var stanza =tokens[1];
    var ris = tokens[2];
    console.log("comando= "+command+" "+stanza+" "+ris);
    console.log(ris=="consegnato");
    if(command=="1"){
      if(provasl==stanza){
        if (ris=="login") {
          stanzaLog=stanza;
          provasl="";
          document.getElementById("titolo0").innerHTML=name+" "+surname;
          document.getElementById("titolo1").innerHTML="Hai effettuato l'accesso nella stanza: ";
          document.getElementById("stanza-log").style.display="block";
          document.getElementById("stanza-log").innerHTML = stanzaLog;
          document.getElementById("titolo2").innerHTML="Attendi l'arrivo del robot ed inizia subito a spedire pacchi! ";
          document.getElementById("form-id").style.display="none";
          document.getElementById("main").padding="200px";
          document.getElementById("consegna").style.display="block";
          document.getElementById("sped").style.display="none";
        }
        else {
          document.getElementById("titolo1").innerHTML="La stanza a cui vuoi effettuare il login e' occupata! ";
        }
      }
    }
    if (command=="2") {
      if (stanzaLog==stanza) {
        if (ris=="coming") {
          document.getElementById("titolo2").innerHTML="Il robot sta arrivando!";
        }
        else if (ris=="consegnato") {
          document.getElementById("titolo2").innerHTML="Il robot e' arrivato!";
          document.getElementById("sped").style.display="inline-block";

        }
        else  {
          document.getElementById("titolo2").innerHTML="Il robot sta eseguendo altri compiti!";

        }


      }
      else{
        if(ris=="coming"){
          document.getElementById("sped").style.display="none";
          document.getElementById("titolo2").innerHTML="Il robot e' stato chiamato da un altro utente!";

        }
      }
    }
    if (command=="3") {

      if (stanzaInviato==stanza) {
        if (ris=="coming") {
          document.getElementById("titolo2").innerHTML="Il robot sta consegnado!";
        }
        else if (ris=="consegnato") {
         document.getElementById("titolo2").innerHTML="Il pacco e' stato consegnato al destinatario!";
         document.getElementById("sped").style.display="none";

       }
       else if (ris=="notlogged") {
        document.getElementById("titolo2").innerHTML="Non puoi inviare un pacco in una stanza vuota!";

      }

        else {

          document.getElementById("titolo2").innerHTML="Il robot sta eseguendo altri compiti!";

        }


      }
      if (stanzaLog==stanza) {
        if (ris=="coming") {
          document.getElementById("titolo2").innerHTML="Il robot sta arrivando nella tua stanza con un pacco!";
        }
        else if (ris=="consegnato") {
         document.getElementById("titolo2").innerHTML="Il pacco e' stato consegnato nella tua stanza!";
         document.getElementById("sped").style.display="inline-block";

       }


      }

    }

});
window.addEventListener('beforeunload', function (e) {
  var command="4:"+stanzaLog;
  twist.data=command;
  html_to_master.publish(twist);
});









/*

1)comando:stanza or commando:stanzap:stanzad (html -> master)
2)comando:stanza:risposta (master -> html)
3)comando:stanza:coordinate_stanza (master -> move)
4)comando:stanza:risposta (move -> master)
5)rifare punto (2) (master -> html)

login caso in cui si logga succesfully
coming nel caso in cui puo arrivare
busy caso in cui e impegnato



*/
