#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define pinpwr 14
#define pinrst 12

const char* ssid        = "XXXXX";
const char* password    = "XXXXX";

ESP8266WebServer server(80);

String html_same ="<!doctype html> <html lang=\"it-IT\"> <script src=\"https://code.jquery.com/jquery-3.5.1.min.js\" integrity=\"sha256-9/aliU8dGd2tb6OSsuzixeV4y/faTqgFtohetphbbj0=\" crossorigin=\"anonymous\"></script> <script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js\" integrity=\"sha384-B4gt1jrGC7Jh4AgTPSdUtOBvfO8shuf57BaghqFfPlYxofvL8/KUEfYiJOMMV+rV\" crossorigin=\"anonymous\"></script> <head> <meta charset=\"utf-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\"> <link rel=\"apple-touch-icon\" sizes=\"180x180\" href=\"https://raw.githubusercontent.com/WEEE-Open/tonno/main/favicon/apple-touch-icon.png\"> <link rel=\"icon\" type=\"image/png\" sizes=\"32x32\" href=\"https://raw.githubusercontent.com/WEEE-Open/tonno/main/favicon/favicon-32x32.png\"> <link rel=\"icon\" type=\"image/png\" sizes=\"16x16\" href=\"https://raw.githubusercontent.com/WEEE-Open/tonno/main/favicon/favicon-16x16.png\"> <link rel=\"manifest\" href=\"https://raw.githubusercontent.com/WEEE-Open/tonno/main/favicon/site.webmanifest\"> <link rel=\"mask-icon\" href=\"https://raw.githubusercontent.com/WEEE-Open/tonno/main/favicon/safari-pinned-tab.svg\" color=\"#5bbad5\"> <link rel=\"shortcut icon\" href=\"https://raw.githubusercontent.com/WEEE-Open/tonno/main/favicon/favicon.ico\"> <meta name=\"apple-mobile-web-app-title\" content=\"Tonno\"> <meta name=\"application-name\" content=\"Tonno\"> <meta name=\"msapplication-TileColor\" content=\"#da532c\"> <meta name=\"msapplication-config\" content=\"https://raw.githubusercontent.com/WEEE-Open/tonno/main/favicon/browserconfig.xml\"> <meta name=\"theme-color\" content=\"#ffffff\"> <title> Tonno </title> <link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css\" integrity=\"sha384-JcKb8q3iqJ61gNV9KGb8thSsNjpSL0n8PARn9HuZOnIxN0hoP+VmmDGMN5t9UJ0Z\" crossorigin=\"anonymous\"> </head> <body> <div class=\"container\"> <h1>Tonno</h1> <i>Transistor Occasionale Nella Necessità Operativa</i> <hr> <div class=\"row\"> <div class=\"col-md-6\"> <div class=\"jumbotron\"> <h2> UorchStescion </h2> <p> Usa questi bottoni per accendere, spegnere o riavviare la macchina. </p> </div> </div> <div class=\"col-md-6\"> <form method='POST'> <button type=\"submit\" name='US' value='on' class=\"btn btn-success btn-block\" id=\"on\"> Accendi <svg width=\"1em\" height=\"1em\" viewBox=\"0 0 16 16\" class=\"bi bi-power\" fill=\"currentColor\" xmlns=\"http://www.w3.org/2000/svg\"> <path fill-rule=\"evenodd\" d=\"M5.578 4.437a5 5 0 1 0 4.922.044l.5-.866a6 6 0 1 1-5.908-.053l.486.875z\"/> <path fill-rule=\"evenodd\" d=\"M7.5 8V1h1v7h-1z\"/> </svg> </button> <button type=\"submit\" name='US' value='reset' class=\"btn btn-warning btn-block\" id=\"reset\"> Riavvia <svg width=\"1em\" height=\"1em\" viewBox=\"0 0 16 16\" class=\"bi bi-bootstrap-reboot\" fill=\"currentColor\" xmlns=\"http://www.w3.org/2000/svg\"> <path fill-rule=\"evenodd\" d=\"M1.161 8a6.84 6.84 0 1 0 6.842-6.84.58.58 0 0 1 0-1.16 8 8 0 1 1-6.556 3.412l-.663-.577a.58.58 0 0 1 .227-.997l2.52-.69a.58.58 0 0 1 .728.633l-.332 2.592a.58.58 0 0 1-.956.364l-.643-.56A6.812 6.812 0 0 0 1.16 8zm5.48-.079V5.277h1.57c.881 0 1.416.499 1.416 1.32 0 .84-.504 1.324-1.386 1.324h-1.6zm0 3.75V8.843h1.57l1.498 2.828h1.314L9.377 8.665c.897-.3 1.427-1.106 1.427-2.1 0-1.37-.943-2.246-2.456-2.246H5.5v7.352h1.141z\"/> </svg> </button> <button type=\"submit\" name='US' value='off' class=\"btn btn-danger btn-block\" id=\"off\"> Spegni <svg width=\"1em\" height=\"1em\" viewBox=\"0 0 16 16\" class=\"bi bi-plug\" fill=\"currentColor\" xmlns=\"http://www.w3.org/2000/svg\"> <path fill-rule=\"evenodd\" d=\"M6 0a.5.5 0 0 1 .5.5V3h3V.5a.5.5 0 0 1 1 0V3h1a.5.5 0 0 1 .5.5v3A3.5 3.5 0 0 1 8.5 10c-.002.434-.01.845-.04 1.22-.041.514-.126 1.003-.317 1.424a2.083 2.083 0 0 1-.97 1.028C6.725 13.9 6.169 14 5.5 14c-.998 0-1.61.33-1.974.718A1.922 1.922 0 0 0 3 16H2c0-.616.232-1.367.797-1.968C3.374 13.42 4.261 13 5.5 13c.581 0 .962-.088 1.218-.219.241-.123.4-.3.514-.55.121-.266.193-.621.23-1.09.027-.34.035-.718.037-1.141A3.5 3.5 0 0 1 4 6.5v-3a.5.5 0 0 1 .5-.5h1V.5A.5.5 0 0 1 6 0zM5 4v2.5A2.5 2.5 0 0 0 7.5 9h1A2.5 2.5 0 0 0 11 6.5V4H5z\"/> </svg> </button> </form> ";
String html_progress ="<div id=\"progresso\"> <br> <form method='POST'> <button type=\"submit\" name='US' value='abort' class=\"btn btn-outline-danger btn-block\" id=\"annulla\"> Annulla </button> </form> <br> <div class=\"progress\"> <div class=\"progress-bar progress-bar-striped progress-bar-animated bg-info\" role=\"progressbar\" style=\"width: 0%\" aria-valuenow=\"0\" aria-valuemin=\"0\" aria-valuemax=\"100\"></div> </div> </div> <div id=\"avviso\"> <br> <div class=\"alert alert-dismissable alert-info fade show\" role=\"alert\"> <button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\"> <span aria-hidden=\"true\">&times;</span> </button> <strong>Fatto.</strong> aspetta qualche secondo e controlla. </div> </div> <script type=\"text/javascript\"> var i = 0; function makeProgress(){ if(i < 100){ i = i + 1; $(\".progress-bar\").css(\"width\", i + \"%\"); $(\"#avviso\").hide(); $(\"#on\").prop('disabled', true); $(\"#reset\").prop('disabled', true); $(\"#off\").prop('disabled', true); } else { $(\"#avviso\").show(); $(\"#progresso\").fadeOut(500,\"swing\"); $(\"#on\").prop('disabled', false); $(\"#reset\").prop('disabled', false); $(\"#off\").prop('disabled', false); } setTimeout(\"makeProgress()\", 50); } makeProgress(); </script> ";
String html_close ="</div> </div> </div> </body> </html>";

void paginetta() {
  Serial.println(server.arg("US"));
  if (server.hasArg("US") && server.arg("US") != "abort") {
  server.send(200, "text/html", html_same+html_progress+html_close);
  } else  server.send(200, "text/html", html_same+html_close);
}

void setup() {
  pinMode(pinpwr, OUTPUT);
  digitalWrite(pinpwr, LOW);
  pinMode(pinrst, OUTPUT);
  digitalWrite(pinrst, LOW);
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }
   Serial.print ( "IP address: " ); Serial.println ( WiFi.localIP() );
  server.on("/", paginetta);
  server.begin();
  Serial.println ( "HTTP server started" );
}

void loop() {
  server.handleClient();
  delay (250);
}
