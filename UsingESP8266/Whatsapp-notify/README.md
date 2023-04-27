# Notifikace přes WhatsApp

Tento program využívá desku ESP8266 a magnetický spínač MC-38 k monitorování stavu dveří a posílání zpráv na WhatsApp pomocí webového API. 

## Knihovny
Program používá následující knihovny:
- `ESP8266WiFi.h`: Knihovna pro připojení k WiFi sítím s deseti funkcemi pro kontrolu stavu spojení.
- `ESP8266HTTPClient.h`: Knihovna pro ovládání HTTP klienta pro přenos dat.
- `WiFiClient.h`: Knihovna pro připojení k serveru přes TCP/IP protokol.
- `UrlEncode.h`: Knihovna pro kódování URL řetězců.

## Proměnné
- `Wifi_Name`: Název WiFi sítě, ke které se má ESP8266 připojit.
- `Wifi_Password`: Heslo pro připojení k WiFi síti.
- `phone_num`: Telefonní číslo, na které mají být odeslány zprávy.
- `API`: API klíč pro CallMeBot webové API.
- `doorStatus`: Bool proměnná, která indikuje, zda se změnil stav dveří.
- `state`: Bool proměnná, která drží stav reedového spínače (otevřeno=1, zavřeno=0).
- `doorState`: Řetězcová proměnná, která popisuje stav dveří (otevřeno/zavřeno).
- `reedSwitch`: Proměnná, která určuje pin reedového spínače.
- `LED`: Proměnná, která určuje pin LED.
- `previousMillis`: Proměnná pro ukládání předchozího času spuštění update funkce.
- `interval`: Konstanta, která určuje minimální časový interval mezi updaty.

## Funkce
- `sendMessage(String message)`: Funkce, která odesílá zprávy na WhatsApp pomocí webového API. 

## Setup
- Nastavení debug výstupu na sériovou linku.
- Nastavení reedového spínače jako INPUT_PULLUP.
- Nastavení LED podle stavu dveří.
- Nastavení přerušení pro reedový spínač, při změně stavu.
- Připojení k WiFi síti.

## Loop
- Kontrola změny stavu dveří.
- Kontrola časového intervalu mezi updaty.
- Aktualizace stavu dveří.
- Odeslání zprávy na WhatsApp.
