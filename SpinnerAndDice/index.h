const char html[] = R"=====(
<!DOCTYPE html><html lang="en"><head> <meta charset="UTF-8"/> <meta name="viewport" content="width=device-width, initial-scale=1.0"/> <title>Matrix</title> <style>*{box-sizing: border-box;}#matrix{width: 200px; height: 200px; display: inline-flex; flex-direction: row; flex-wrap: wrap;}#dice{font-size: 30px; font-weight: 700;}.box{width: 40px; height: 40px; border: solid 10px #000; display: inline-block;}button{outline: 0; border: none; border-radius: 6px; padding: 10px 20px 10px 20px; background-color: #5f2c16; color: white; font-size: 22px; font-weight: 700; cursor: pointer;}button:hover{background-color: #833c1e;}</style></head><body> <center> <div id="matrix"></div><div id="dice"></div><br><br><button onclick="changeState('DICE')">DICE</button> <button onclick="changeState('SPINNER')">SPINNER</button> </center> <script>let matrix=document.getElementById("matrix");let dice=document.getElementById("dice");var mode="DICE";function update(color){if (color !=""){if (mode=="DICE"){if(color=="red"){dice.innerHTML="1";}else if (color=="orange"){dice.innerHTML="2";}else if (color=="yellow"){dice.innerHTML="3";}else if (color=="green"){dice.innerHTML="4";}else if (color=="blue"){dice.innerHTML="5";}else if (color=="purple"){dice.innerHTML="6";}}else{var element=""; for (var i=0; i < 5; i++){for (var j=0; j < 5; j++){element +="<div class='box' style='background-color: " + color + "'></div>";}}matrix.innerHTML=element;}}}function GetData(){var httpRequest; if (window.XMLHttpRequest){httpRequest=new XMLHttpRequest();}else if (window.ActiveXObject){httpRequest=new ActiveXObject();}httpRequest.open("GET", "/data", true); httpRequest.onreadystatechange=function(){update(httpRequest.responseText);}; httpRequest.send();}function changeState(state){var httpRequest; if (window.XMLHttpRequest){httpRequest=new XMLHttpRequest();}else if (window.ActiveXObject){httpRequest=new ActiveXObject();}httpRequest.open("GET", `/changeState?state=${state}`, true); httpRequest.onreadystatechange=function(){if (httpRequest.readyState==4 && httpRequest.status==200){state_res(httpRequest.responseText);}}; httpRequest.send();}function state_res(data){if (data=="SUCCESS"){if (mode=="SPINNER"){matrix.style.display="none"; dice.style.display="inline-block"; mode="DICE";}else{dice.style.display="none"; matrix.style.display="inline-flex"; mode="SPINNER";}}}setInterval(GetData, 400); </script></body></html>)=====";
