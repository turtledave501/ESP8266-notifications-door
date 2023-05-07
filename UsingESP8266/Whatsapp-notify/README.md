# Notifikace přes WhatsApp

## Popis programu

Tento program umožňuje odesílat zprávy na WhatsApp pomocí CallMeBot API při změně stavu dveří. Pokud jsou dveře otevřené, program odešle zprávu "door: open", pokud jsou zavřené, odešle zprávu "door: closed".

Program je napsán v jazyce C++ pro platformu ESP8266.

## Základní nastavení

Pro základní nastavení programu je nutné provést následující kroky:

- Stáhněte a nastavte[Arduino IDE](https://www.arduino.cc/en/software).
- Připojte ESP8266 k počítači pomocí USB kabelu.
- Otevřete program WhatsApp-notify.ino v Arduino IDE.
- Vyplňte proměnné `Wifi_Name` a `Wifi_Password` s názvem a heslem vaší WiFi sítě.
- Vyplňte proměnné `phone_num` a `API` s telefonním číslem a API klíčem pro `CallMeBot API`.
- Připojte spínač k pinu 4 a LED diodu k pinu 2 na vašem ESP8266.
- Program nahrajte na ESP8266.
*[jak spustit `CallMeBot`](https://www.callmebot.com/blog/free-api-whatsapp-messages/)*


## Knihovny
Program používá následující knihovny:
- `ESP8266WiFi.h`: Knihovna pro připojení k WiFi sítím s deseti funkcemi pro kontrolu stavu spojení.
- `ESP8266HTTPClient.h`: Knihovna pro ovládání HTTP klienta pro přenos dat.
- `WiFiClient.h`: Knihovna pro připojení k serveru přes TCP/IP protokol.
- `UrlEncode.h`: Knihovna pro kódování URL řetězců.

## Funkce

### sendMessage()
- Funkce, která odesílá zprávy na WhatsApp pomocí webového API. 

### Setup()
- Nastavení debug výstupu na sériovou linku.
- Nastavení reedového spínače jako INPUT_PULLUP.
- Nastavení LED podle stavu dveří.
- Nastavení přerušení pro reedový spínač, při změně stavu.
- Připojení k WiFi síti.

### Loop()
- Kontrola změny stavu dveří.
- Kontrola časového intervalu mezi updaty.
- Aktualizace stavu dveří.
- Odeslání zprávy na WhatsApp.

## Zapojení

Pro správné fungování programu je nutné správně zapojit ESP8266 a reedové spínače.

ESP8266 musí být napájeno z externího zdroje, například 5V napájení z USB portu. Reedové spínače jsou zapojeny na digitální vstup 4 desky ESP8266.

Pokud použijete jiný vstup, bude nutné aktualizovat programový kód tak, aby odpovídal použitým vstupům.

## Omezení programu

Program může být omezen tím, že reedové spínače nejsou dostatečně přesné a mohou detekovat nesprávný stav dveří. To může vést k odeslání chybných notifikací.

Je také nutné mít aktivní WiFi připojení, aby program mohl odesílat informace.

## Další možnosti vylepšení

Program lze dále vylepšit a upravit tak, aby lépe vyhovoval potřebám uživatele. Například:

- Přidání dalších vstupů pro monitorování dalších částí garáže, například teploty.
- Přidání možnosti nastavení intervalu mezi odesláním stavu dveří na WhatsApp.
- Přidání dalších akcí k vykonání při změně stavu dveří, například zapnutí světel.

## Závěr

Tento program umožňuje monitorování stavu dveří a odesílání notifikací za pomocí služby CallMeBot služby a WhatsApp. Program je poměrně jednoduchý, ale může být dále upraven a vylepšen podle potřeb uživatele.
