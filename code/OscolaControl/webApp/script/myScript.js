
// Create a client instance
$(document).ready(function(){


  client = new Paho.MQTT.Client("test.mosquitto.org", 8080 ,"browser");

  // set callback handlers
  client.onConnectionLost = onConnectionLost;
  client.onMessageArrived = onMessageArrived;

  // connect the client
  client.connect({onSuccess:onConnect});


  // called when the client connects
  function onConnect() {
    // Once a connection has been made, make a subscription and send a message.
    console.log("onConnect");
    client.subscribe("test/esacono/1/");

  }

  // called when the client loses its connection
  function onConnectionLost(responseObject) {
    if (responseObject.errorCode !== 0) {
      console.log("onConnectionLost:"+responseObject.errorMessage);
    }
  }

  // called when a message arrives
  function onMessageArrived(message) {
    console.log("onMessageArrived:"+message.payloadString);
  }

  $('#colorpicker').farbtastic(function callback(color){
    //console.log(color);
    sendMessage('oscola/23981479834/changeColor',''+color);
  });


});

function sendMessage(address,val){
  console.log("sending " + val);
  message = new Paho.MQTT.Message(val);
  message.destinationName = address;
  message.payloadString=val;
  client.send(message); 
  //console.log(message);
}