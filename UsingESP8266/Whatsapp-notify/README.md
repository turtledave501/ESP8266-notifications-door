# Notifikace přes WhatsApp

## Popis programu

Tento program umožňuje odesílat zprávy na WhatsApp pomocí CallMeBot API při změně stavu dveří. Pokud jsou dveře otevřené, program odešle zprávu "door: open", pokud jsou zavřené, odešle zprávu "door: closed".

## Knihovny
Program používá následující knihovny:
- `ESP8266WiFi.h`: Knihovna pro připojení k WiFi sítím s deseti funkcemi pro kontrolu stavu spojení.
- `ESP8266HTTPClient.h`: Knihovna pro ovládání HTTP klienta pro přenos dat.
- `WiFiClient.h`: Knihovna pro připojení k serveru přes TCP/IP protokol.
- `UrlEncode.h`: Knihovna pro kódování URL řetězců.

## Nastavení programu

Vyplňte proměnné `Wifi_Name` a Wifi_Password s názvem a heslem vaší WiFi sítě.
Vyplňte proměnné `phone_num` a `API` s telefonním číslem a API klíčem pro `CallMeBot API`.
Připojte spínač k pinu 4 a LED diodu k pinu 2 na vašem ESP8266.
*[jak spustit `CallMeBot`](https://www.callmebot.com/blog/free-api-whatsapp-messages/)*

### Funkce
- `sendMessage(String message)`: Funkce, která odesílá zprávy na WhatsApp pomocí webového API. 

### Setup
- Nastavení debug výstupu na sériovou linku.
- Nastavení reedového spínače jako INPUT_PULLUP.
- Nastavení LED podle stavu dveří.
- Nastavení přerušení pro reedový spínač, při změně stavu.
- Připojení k WiFi síti.

### Loop
- Kontrola změny stavu dveří.
- Kontrola časového intervalu mezi updaty.
- Aktualizace stavu dveří.
- Odeslání zprávy na WhatsApp.

